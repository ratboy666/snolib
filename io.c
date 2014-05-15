/* $Id: io.c,v 1.146 2013/09/24 00:58:14 phil Exp $ */

/*
 * I/O support for CSNOBOL4
 *
 * This is the largest and nastiest file in the support library, and
 * the only one where I've tolerated extensive use of "ifdef".  The
 * complexity (and fragility) of the I/O support is due to a number of
 * factors;
 *
 * Assumptions built into the SIL source (both compiler and runtime).
 * Multiple layers of I/O (assocation, unit, stdio, fd)
 * Interactions of I/O options (buffered vs binary
 * Handling file lists.
 * O/S differnces (esp tty handling and winsock)
 *
 * A rewrite is badly needed, but would likely delay version 1.0, and
 * chances are good the result would not (initially) have fewer
 * problems.  An original goal was to depend entirely on stdio, but it
 * turns out almost every platform also provides open/close/read/write
 * support as well, so it's tempting to do away with stdio, and or at
 * add an abstraction layer over it.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H defined */

#ifdef __STDC__
#include <stdarg.h>
#else  /* __STDC__ not defined */
#include <varargs.h>
#endif /* __STDC__ not defined */

#ifdef HAVE_STDLIB_H			/* before stdio */
#include <stdlib.h>
#else  /* HAVE_STDLIB_H not defined */
extern void *malloc();
extern char *getenv();
#endif /* HAVE_STDLIB_H not defined */

#include <stdio.h>
#include <ctype.h>

#ifdef NEED_OFF_T
typedef long off_t;
#else  /* NEED_OFF_T not defined */
#include <sys/types.h>			/* off_t */
#endif /* NEED_OFF_T not defined */

#ifdef HAVE_UNISTD_H
#include <unistd.h>			/* SEEK_xxx, xxx_FILENO */
#endif /* HAVE_UNISTD_H defined */

#ifdef HAVE_UNIXIO_H			/* DECC v4 */
#include <unixio.h>			/* read(), lseek(), etc */
#endif /* HAVE_UNIXIO_H defined */

#include <sys/types.h>			/* pid_t */

#ifdef HAVE_FORKPTY
#include <sys/wait.h>			/* waitpid() */
#include <errno.h>

#ifdef HAVE_LIBUTIL_H
#include <libutil.h>			/* FreeBSD: forkpty */
#endif
#ifdef HAVE_UTIL_H
#include <util.h>			/* NetBSD: forkpty */
#endif
#ifdef HAVE_PTY_H
#include <pty.h>			/* linux: forkpty() */
#endif
#ifdef HAVE_PATHS_H
#include <paths.h>			/* _PATH_BSHELL */
#endif
#endif /* HAVE_FORKPTY */

#include "h.h"
#include "units.h"
#include "snotypes.h"
#include "macros.h"
#include "path.h"
#include "libret.h"			/* IO_xxx, INC_xxx */
#include "lib.h"
#include "str.h"

/* generated */
#include "equ.h"			/* for BCDFLD (for X_LOCSP), res.h */
#include "res.h"			/* needed on VAX/VMS for data.h */
#include "data.h"			/* for FILENM */
#include "proc.h"			/* UNDF() */

#ifdef COMPILER_READLINE			/* after proc.h */
#undef RETURN
#include <readline/readline.h>
#include <readline/history.h>
#endif /* COMPILER_READLINE */

#ifndef SEEK_SET
#define SEEK_SET 0
#endif /* SEEK_SET not defined */

#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif /* SEEK_CUR not defined */

#ifndef SEEK_END
#define SEEK_END 2
#endif /* SEEK_END not defined */

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif /* STDIN_FILENO not defined */

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif /* STDOUT_FILENO not defined */

#ifndef STDERR_FILENO
#define STDERR_FILENO 2
#endif /* STDERR_FILENO not defined */

#define NUNITS 256			/* XXX set at runtime? */

#ifndef PRELOAD_FILENAME
#define PRELOAD_FILENAME "preload.sno"
#endif

/* GOAL: "struct unit" does not leave io.c */
struct unit {
    struct file *curr;			/* ptr to current file */
    /* for rewind; */
    struct file *head;			/* first file in list */
    off_t offset;			/* offset in first file to rewind to */
};

/* GOAL: "struct file" does not leave io.c */
struct file {
    struct file *next;			/* next input file */
    FILE *f;				/* may be NULL if not (yet) open */
    int flags;				/* FL_xxx */
    enum {
	TYPE_NORM,
	TYPE_PIPE,
	TYPE_TTY,
	TYPE_PTY,
#ifdef MEM_IO
	TYPE_MEM,
#endif /* MEM_IO defined */
	TYPE_INET } type;
    union {
#ifdef MEM_IO
	struct {
	    char *ptr;		      /* pointer to buffer */
	    int len;		      /* length of buffer */
	    off_t pos;		      /* current position in buffer */
	} mem;
#endif /* MEM_IO defined */
#ifdef HAVE_FORKPTY
	struct {
	    pid_t pid;
	} pty;
#endif
	int nota;
    } u;
    /* XXX add methods for read/write/eof/mode/seek/close */
    /* XXX keep recl (shift flags up?)? */
    enum { LAST_NONE, LAST_OUTPUT, LAST_INPUT } last;
    /* MUST BE LAST!! */
    char fname[1];
};

/*
 * Per-file (unit) flags.
 *
 * ** NOTE **
 *
 * multiple units may refer to same stdio stream (via "-" and
 * /dev/std{in,out,err} magic files) or the same file descriptors (via
 * /dev/fd/N magic pathname) and have different behaviors.
 */

#define FL_EOL		01		/* strip EOL on input, add on output */
#define FL_BINARY	02		/* binary: no EOL; use recl */
#define FL_UPDATE	04		/* update: read+write */
#define FL_UNBUF	010		/* unbuffered write */
#define FL_APPEND	020		/* append */
#define FL_NOECHO	040		/* tty: no echo */
#define FL_NOCLOSE	0100		/* don't fclose() */

#if defined(INET_IO) || defined (MEM_IO)
/*
 * About the INET_IO crock:
 *
 * On Windows 3.1 and Win9x, file handles and winsock handles are
 * incompatible; winsock handles cannot be read or written with
 * ordinary file I/O calls (e.g. ReadFile, WriteFile), so attempting
 * to wrap a socket in a stdio stream won't work.
 *
 * [On NT based systems (XP and later), _open_osfhandle() + _fdopen
 *  may do the trick, as ReadFile() is supposed to work on winsockets]
 *
 * To work around this "feature", if INET_IO is defined, tcp_open()
 * and udp_open() return a "struct inet_file" pointer.  The code in
 * io.c has been crocked not to try normal I/O on things which have
 * the "NOTAFILE" flag set, instead calls inet_read_{raw,cooked},
 * inet_write and inet_close in inet.c, which merrily cast the "FILE *"
 * back to an "inet_file"
 *
 * The MEM_IO crock is to allow SNOBOL4 to be built as a shared
 * library (or DLL) which takes handles for buffers for input and
 * output.  BSD stdio funopen() would make this easy.
 *
 * All of this could go away if the I/O system were more object oriented.
 */
#define FL_NOTAFILE	0200		/* "f" is not a file (XXX TEMP) */
#define ISAFILE(FP) !((FP)->flags & FL_NOTAFILE)
#else  /* not defined(INET_IO) || defined(MEM_IO) */
#define ISAFILE(FP) 1
#endif /* not defined(INET_IO) || defined(MEM_IO) */

#ifdef MEM_IO
#define ISMEM(FP) ((FP)->type == TYPE_MEM)
#else  /* MEM_IO not defined */
#define ISMEM(FP) 0
#endif /* MEM_IO not defined */

#define ISPIPE(FP) ((FP)->type == TYPE_PIPE)
#define ISTTY(FP)  ((FP)->type == TYPE_TTY)
#define ISPTY(FP)  ((FP)->type == TYPE_PTY)
#define ISINET(FP) ((FP)->type == TYPE_INET)

#define ISOPEN(FP) ((FP)->f || IEMEM(FP))

#define MAXFNAME	1024		/* XXX use MAXPATHLEN? POSIX?? */
#define MAXOPTS		1024

struct iovars {
    /* XXX malloc at runtime? */
    struct unit units[NUNITS];
    struct file *includes;		/* list of included files */
    int finger;				/* for io_findunit */
    struct file *lib_dirs;		/* list of include directories */
    struct file *lib_dir_last;	/* tail of include directory list */

};

#ifdef NO_STATIC_VARS
#include "vars.h"
#else  /* NO_STATIC_VARS not defined */
extern int rflag;			/* from init.c */
extern int lflag;			/* from init.c */
static struct iovars iov;
#endif /* NO_STATIC_VARS not defined */

/* convert to internal (zero based) unit number; */
#define INTERN(U) ((U)-1)

/* check an internal (zero based) unit number; */
#define BADUNIT(U) ((U) < 0 || (U) >= NUNITS)

/*
 * take internal (zero-based) unit number; return "struct unit *"
 * all access to units array hidden, so it can be made sparse
 */
#define FINDUNIT(N) (iov.units + (N))

/*
 * Systems could implement 64-bit offsets using ANSI f[sg]etpos(),
 * and not have fseeko/ftello.
 *
 * create generic/fpos.c (use fseek/ftell to implement fseeko/ftello)
 * 	ansi/fpos.c	(use fsetpos/fgetpos)
 * ??
 *
 * nasty bit about fgetpos() is that the return value is opaque
 * (may return a cookie, without meaning, except to fsetpos)
 */
#ifndef HAVE_FSEEKO
#define ftello(FP) ftell(FP)
#define fseeko(FP,OFF,WHENCE) fseek(FP,(long)(OFF),WHENCE)
#endif /* HAVE_FSEEKO not defined */

static struct file *
io_newfile( path )
    char *path;
{
    struct file *fp;

    fp = (struct file *) malloc( sizeof( struct file ) + strlen(path) );
    if (fp == NULL)
	return NULL;

    bzero( (char *)fp, sizeof (struct file) );
    strcpy(fp->fname,path);
    fp->flags = FL_EOL;			/* normal */
    fp->type = TYPE_NORM;
    fp->last = LAST_NONE;		/* nothing yet */
    return fp;
}

#ifdef MEM_IO
static struct file *
io_memfile(name, data, len)
    char *name;
    char *data;
    int len;
{
    struct file *fp;

    fp = io_newfile(name);
    if (!fp)
	return NULL;

    fp->type = TYPE_MEM;
    fp->flags |= FL_NOTAFILE;
    fp->u.mem.ptr = data;
    fp->u.mem.len = len;
    fp->u.mem.pos = 0;
    return fp;
}
#endif /* MEM_IO defined */

void
io_initvars() {
#ifdef NO_STATIC_VARS
    if (!varp->v_iov) {
	varp->v_iov = (struct iovars *)malloc(sizeof(struct iovars));
	if (!varp->v_iov) {
	    perror("iovars malloc failed");
	    exit(1);
	}
	bzero(varp->v_iov, sizeof(struct iovars));
    }
#endif /* NO_STATIC_VARS defined */
}

/* add file to input list */
/* calls made here BEFORE io_init() called! */
static int
io_addfile( unit, fp, append )
    int unit;
    struct file *fp;
    int append;
{
    /* XXX check for commas in path? */
    struct unit *up;

    io_initvars();

    /* XXX allocate units array here? */

    up = FINDUNIT(unit);
    if (append) {			/* add to end of list */
	struct file *tp;

	tp = up->curr;
	if (tp == NULL) {
	    up->head = up->curr = fp;
	    up->offset = 0;
	}
	else {
	    while (tp->next)
		tp = tp->next;
	    tp->next = fp;
	}
    }
    else {				/* prepend (ie; for "include") */
	fp->next = up->curr;
	up->head = up->curr = fp;
	up->offset = 0;
    }
    return TRUE;
} /* io_addfile */

/* close currently open file on a unit */
/* XXX take flag: to free struct file, or not? */
static int
io_close(unit)				/* internal (zero-based unit) */
    int unit;
{
    struct file *fp;
    struct unit *up;
    int ret;

    up = FINDUNIT(unit);
    fp = up->curr;
    if (fp == NULL)
	return TRUE;

    if (fp->f) {
	/* XXX call close hook? */
#ifdef MEM_IO
	if (ISMEM(fp)) {
	    ret = TRUE;
	    fp->f = NULL;
	}
	else
#endif
	if (ISINET(fp)) {
	    ret = inet_close(fp->f);
	    fp->f = NULL;
	}
	else if (ISPIPE(fp)) {
	    ret = (pclose(fp->f) == 0);	/* XXX is process status!! */
	    fp->f = NULL;
	}
#ifdef HAVE_FORKPTY
	else if (ISPTY(fp)) {
	    pid_t pid;
	    int pstat;

	    fclose(fp->f);
	    fp->f = NULL;
	    // issue kill() if needed????
	    do {
                pid = waitpid(fp->u.pty.pid, &pstat, 0);
	    } while (pid == -1 && errno == EINTR);
	    if (pid == -1)
		ret = TRUE;
	    else
		ret = (pstat == 0);
	}
#endif
	else {				/* not a pipe */
	    if (ISTTY(fp)) {
		tty_close(fp->f);	/* advisory */
	    }
	    if (fp->flags & FL_NOCLOSE) {
		/* never close stdin, stdout, stderr */
		ret = (fflush(fp->f) != EOF);
	    }
	    else {
		ret = (fclose(fp->f) == 0);
		fp->f = NULL;
	    }
	} /* not a pipe */
    } /* have fp->f */
    else
	ret = TRUE;			/* keep gcc quiet! */

    up->curr = fp->next;
    return ret;
} /* io_close */

/* close a unit, flush current file list */
EXPORT(int)
io_closeall(unit)			/* internal (zero-based unit) */
    int unit;
{
    struct file *fp, *next;
    struct unit *up;
    int ret;

    /* close any/all open files on chain */
    ret = TRUE;
    up = FINDUNIT(unit);
    while (up->curr != NULL)
	if (!io_close(unit))
	    ret = FALSE;

    /* free up all file structs */
    fp = up->head;
    while (fp != NULL) {
	next = fp->next;
	free(fp);
	fp = next;
    }
    up->curr = up->head = NULL;

    return ret;
}

static void
io_fopen2( fp, base )
    struct file *fp;
    char *base;
{
    char *mp;
    char mode[4];			/* x+b<NUL> */

    fp->f = NULL;

#ifdef MEM_IO
    if (ISMEM(fp)) {
	fp->u.mem.pos = 0;
	fp->f = (FILE *)1;		/* non-NULL */
	return;
    }
#endif

    /* create full mode string for fopen() */
    mp = mode;
    if (base[0] == 'w' && (fp->flags & FL_APPEND))
	*mp++ = 'a';
    else
	*mp++ = base[0];		/* XXX append whole string? */
    if (fp->flags & FL_UPDATE)
	*mp++ = '+';
#ifndef NO_FOPEN_B
    if (fp->flags & FL_BINARY)
	*mp++ = 'b';
#endif /* NO_FOPEN_B not defined */
    *mp++ = '\0';

    /* handle magic filenames (have a table (prefix or full str)??) */

#ifdef OSDEP_OPEN
    /*
     * Allow interception of /dev/tty, /dev/null, etc on non-unix
     * systems.  Function should return TRUE if filename is being
     * intercepted, REGARDLESS of whether the actual open succeeds
     * (on successs, the function should set the FILE ** to point
     * to the open stream).
     */
    if (osdep_open(fp->fname, mode, &fp->f))
	return;				/* intercepted */
#endif /* OSDEP_OPEN defined */

    /* filename "-" goes to stdin/out */
    if (strcmp(fp->fname,"-") == 0) {
	if (mode[0] == 'r')
	    fp->f = stdin;
	else
	    fp->f = stdout;
	fp->flags |= FL_NOCLOSE;
	return;
    }
    if (strcmp(fp->fname,"/dev/stdin") == 0) {
	fp->f = stdin;
	fp->flags |= FL_NOCLOSE;
	return;
    }
    if (strcmp(fp->fname,"/dev/stdout") == 0) {
	fp->f = stdout;
	fp->flags |= FL_NOCLOSE;
	return;
    }
    if (strcmp(fp->fname,"/dev/stderr") == 0) {
	fp->f = stderr;
	fp->flags |= FL_NOCLOSE;
	return;
    }
#ifndef NO_FDOPEN
    if (strncmp(fp->fname, "/dev/fd/", 8) == 0) {
	int fd;

	if (sscanf(fp->fname+8, "%d", &fd) == 1) {
	    fp->f = fdopen(fd, mode);
	    switch (fd) {
	    case STDIN_FILENO:
	    case STDOUT_FILENO:
	    case STDERR_FILENO:
		fp->flags |= FL_NOCLOSE;
		break;
	    }
	}
	return;
    }
#endif /* NO_FDOPEN not defined */
    if (strncmp(fp->fname, "/tcp/", 5) == 0 ||
	strncmp(fp->fname, "/udp/", 5) == 0) {
	char fn2[MAXFNAME];		/* XXX */
	char *host, *service, *cp;
	int flags;

	flags = 0;
	strcpy( fn2, fp->fname + 5 );	/* XXX strdup()? */
	host = fn2;
	service = index(host, '/');
	if (service == NULL)
	    return;
	*service++ = '\0';

	/* look for option suffixes, ignore if unknown */
	cp = index(service, '/');
	if (cp) {
	    char *op;

	    *cp++ = '\0';
	    do {
		op = cp;
		cp = index(cp, '/');
		if (cp)
		    *cp++ = '\0';

		if (strcmp(op, "priv") == 0)
		    flags |= INET_PRIV;
		else if (strcmp(op, "broadcast") == 0)
		    flags |= INET_BROADCAST;
		else if (strcmp(op, "reuseaddr") == 0)
		    flags |= INET_REUSEADDR;
		else if (strcmp(op, "dontroute") == 0)
		    flags |= INET_DONTROUTE;
		else if (strcmp(op, "oobinline") == 0)
		    flags |= INET_OOBINLINE;
		else if (strcmp(op, "keepalive") == 0)
		    flags |= INET_KEEPALIVE;
		else if (strcmp(op, "nodelay") == 0)
		    flags |= INET_NODELAY;

		/* XXX more magic? non-booleans? linger?? */
	    } while (cp);
	} /* have suffixes */

	if (fp->fname[1] == 'u')
	    fp->f = udp_open( host, service, -1, flags );
	else
	    fp->f = tcp_open( host, service, -1, flags );
#ifdef INET_IO
	/* awful crock; fp->f is a SOCKET; do away with this!!!! */
	fp->flags |= FL_NOTAFILE;
#endif /* INET_IO defined */
	fp->type = TYPE_INET;
	return;
    }

    /* ANSI tmpfile() function returns anonymous file open for R/W */
    if (strcmp(fp->fname, "/dev/tmpfile") == 0) {
	fp->f = tmpfile();
	return;
    }

    /* **** add new special filename hacks here *** */

    if (fp->fname[0] == '|') { /* filename with leading '|' opens a pipe! */
	if (fp->fname[1] == '|') {	/* || opens a pty!! */
#ifdef HAVE_FORKPTY
	    int master;
	    pid_t pid = forkpty(&master, NULL, NULL, NULL);
	    if (pid == 0) {
		int i;
		for (i = getdtablesize(); i > 2; i--)
		    close(i);
		execl(_PATH_BSHELL, "sh", "-c", fp->fname+2, NULL);
		_exit(1);
	    }
	    else if (pid > 0) {
		fp->f = fdopen(master, mode);
		fp->type = TYPE_PTY;
		fp->u.pty.pid = pid;
	    }
#endif
	    return;
	} // ||

	/* SPITBOL: leading '!' means pipe, (with escaping?) */
	fp->type = TYPE_PIPE;
	fp->f = popen(fp->fname+1, mode);
	return;
    }

    fp->f = fopen(fp->fname, mode);
} /* io_fopen2 */

static FILE *
io_fopen( fp, mode )
    struct file *fp;
    char *mode;
{
    io_fopen2(fp,mode);
    if (fp->f == NULL)
	return NULL;

    if (ISAFILE(fp) && fisatty(fp->f, fp->fname))
	/* XXX set close hook? */
	fp->type = TYPE_TTY;


    /* XXX if FL_UNBUF call setbuf(fp->f, NULL)??
     * this may force a read or write per-character, which
     * isn't what we're after!
     */
    return fp->f;
} /* io_fopen */

/* skip to next input file */
static int
io_next( unit )				/* internal (zero-based unit) */
    int unit;
{
    struct file *fp;
    struct unit *up;

    up = FINDUNIT(unit);
    fp = up->curr;
    if (fp == NULL)
	return FALSE;

    /* in case called preemptively! */
    if (fp->f != NULL)
	io_close(unit);			/* close, and advance */

    /* get new current file (io_close advances to next file in list) */
    fp = up->curr;
    if (fp == NULL)
	return FALSE;

    if (fp->f != NULL)			/* already open? */
	return TRUE;

    /* XXX let io_read() do the work??? */
    /* XXX copy flags from previous file? */
    io_fopen( fp, "r");

    return fp->f != NULL;
} /* io_next */


/* skip to next file, for external use, takes external unit */
EXPORT(int)
io_skip( unit )
    int unit;
{
    return io_next(INTERN(unit));
}

/* here with filename from command line */
EXPORT(void)
io_input_file( path )
    char *path;
{
    struct file *fp;

    fp = io_newfile(path);
    if (fp == NULL)
	return;

    io_addfile( INTERN(UNITI), fp, TRUE );	/* append to list! */
}

#ifdef MEM_IO
void
io_input_string( name, str )
    char *name;
    char *str;
{
    struct file *fp;

    fp = io_memfile(name, str, strlen(str));
    if (fp == NULL)
	return;

    io_addfile( INTERN(UNITI), fp, TRUE );	/* append to list! */
}
#endif /* MEM_IO defined */

/* attach a "struct file" to a unit (external) */
static void
io_setfile(unit, fp)
    int unit;
    struct file *fp;
{
    struct unit *up;

    unit = INTERN(unit);
    io_closeall(unit);			/* close unit */

    up = FINDUNIT(unit);
    up->head = up->curr = fp;
    up->offset = 0;
}

/* setup a unit given an open stdio stream and a "filename" */
static int
io_mkfile2( unit, f, fname, flags )
    int unit;				/* external (1-based) unit */
    FILE *f;
    char *fname;			/* "filename" for error reports */
    int flags;
{
    struct file *fp;

    fp = io_newfile(fname);
    if (fp == NULL)
	return FALSE;
    fp->f = f;
    fp->flags |= flags;
    if (ISAFILE(fp) && fisatty(f, fname)) {
	/* XXX set close hook? */
	fp->type = TYPE_TTY;
    }

    io_setfile(unit, fp);
    return TRUE;
}

EXPORT(int)
io_mkfile( unit, f, fname )
    int unit;				/* external (1-based) unit */
    FILE *f;
    char *fname;			/* "filename" for error reports */
{
    return io_mkfile2( unit, f, fname, 0 );
}

EXPORT(int)
io_mkfile_noclose( unit, f, fname )
    int unit;				/* external (1-based) unit */
    FILE *f;
    char *fname;			/* "filename" for error reports */
{
    return io_mkfile2( unit, f, fname, FL_NOCLOSE );
}

/* return true if unit attached */
EXPORT(int)
io_attached( unit )
    int unit;
{
    struct unit *up = FINDUNIT(INTERN(unit));
    return up->curr != NULL;
}
#ifdef MEM_IO
/*
 * create a memory based output file and attach for output
 * pass in a char ** to be filled with a malloced buffer?
 */
EXPORT(int)
io_output_string( unit, fname, buf, len )
    int unit;				/* external (1-based) unit */
    char *fname;			/* "filename" for error reports */
    char *buf;
    int len;
{
    struct file *fp;

    fp = io_memfile(fname, buf, len);
    if (fp == NULL)
	return FALSE;
    io_setfile(unit, fp);
    return TRUE;
}
#endif

#ifdef MEM_IO
static int
mem_write(fp, cp, len)
    struct file *fp;
    char *cp;
    int len;
{
    if (len + fp->u.mem.pos + 1 <= fp->u.mem.len) {
	memcpy(fp->u.mem.ptr + fp->u.mem.pos, cp, len);
	fp->u.mem.pos += len;
	fp->u.mem.ptr[fp->u.mem.pos] = '\0';
	return TRUE;
    }
    return FALSE;
}

static int
mem_read_raw(fp, cp, recl)
    struct file *fp;
    char *cp;
    int recl;
{
    int rem = fp->u.mem.len - fp->u.mem.pos;
    if (rem == 0)
	return -1;			/* 0? */
    if (recl > rem)
	recl = rem;
    memcpy(cp, fp->u.mem.ptr + fp->u.mem.pos, recl);
    fp->u.mem.pos += recl;
    return recl;
}

static int
mem_read_cooked(fp, cp, recl, keepeol)
    struct file *fp;
    char *cp;
    int recl;
    int keepeol;
{
    int cc = 0;
    int nread = 0;
    int eol = FALSE;
    while (cc < recl && !eol && fp->u.mem.pos < fp->u.mem.len) {
	char c = fp->u.mem.ptr[fp->u.mem.pos++];
	nread++;
	if (c == '\r')
	    continue;
	if (c == '\n') {
	    eol = TRUE;
	    if (!keepeol)
		break;
	}
	*cp++ = c;
        cc++;
    }
    if (nread == 0)
	return -1;
    return cc;
}
#endif /* MEM_IO defined */

/*
 * implement SIL operations;
 */

/* limited printf */

#define COPY(SRC,LEN) \
{ \
    int len = LEN; \
    if (LEN > space) \
	len = space; \
    strncpy(lp, SRC, len); \
    lp += len; \
    space -= len; \
    *lp = '\0'; \
}

#define COPYTEMP COPY(temp, strlen(temp))

void
io_printf
#ifdef __STDC__
    (int_t unit, ...)
#else  /* __STDC__ not defined */
    (va_alist) va_dcl
#endif /* __STDC__ not defined */
{
    va_list vp;
    char *format;
    register char c;
    char line[1024];			/* XXX */
    int space;
    char *lp;
    struct unit *up;
#ifdef __STDC__
    va_start(vp,unit);
#else  /* __STDC__ not defined */
    int_t unit;
    va_start(vp);

    unit = va_arg(vp, int_t);
#endif /* __STDC__ not defined */

    unit = INTERN(unit);
    if (BADUNIT(unit))
	return;

    up = FINDUNIT(unit);
    if (up->curr == NULL)
	return;

    /* keep output in line buffer, in case output unbuffered (ie; stderr) */
    lp = line;
    space = sizeof(line) - 1;
    format = va_arg(vp, char *);
    while ((c = *format++) != '\0' && space > 0) {
	struct descr *dp;
	struct spec *sp;
	char temp[32];			/* large enough for 2^64 */
	char *cp;

	/* scan forward until first %, and print all at once? */
	if (c != '%') {
	    *lp++ = c;
	    space--;
	    continue;
	}
	c = *format++;
	if (c == '\0')
	    break;
	switch (c) {
	case 'd':			/* plain decimal */
	    dp = va_arg(vp, struct descr *);
	    sprintf(temp, "%ld", (long)D_A(dp)); /* XXX handle LP32LL64 int_t */
	    COPYTEMP;
	    break;
	case 'D':			/* padded decimal */
	    dp = va_arg(vp, struct descr *);
	    sprintf(temp, "%15ld", (long)D_A(dp)); /* XXX handle LP32LL64 int_t */
	    COPYTEMP;
	    break;
	case 'F':			/* padded float */
	    dp = va_arg(vp, struct descr *);
	    sprintf(temp, "%15.3f", D_RV(dp));
	    COPYTEMP;
	    break;
	case 'G':			/* padded g/float */
	    dp = va_arg(vp, struct descr *);
	    sprintf(temp, "%15.3g", D_RV(dp));
	    COPYTEMP;
	    break;
	case 'g':			/* unpadded g/float */
	    dp = va_arg(vp, struct descr *);
	    sprintf(temp, "%g", D_RV(dp));
	    COPYTEMP;
	    break;
	case 's':			/* c-string (from version.c) */
	    cp = va_arg(vp, char *);
	    COPY(cp, strlen(cp));
	    break;
	case 'S':			/* spec */
	    sp = va_arg(vp, struct spec *);
	    /* might contain NUL's... will stop short! */
	    COPY(S_SP(sp), S_L(sp));
	    break;
	case 'v':			/* variable */
	    dp = va_arg(vp, struct descr *);
	    dp = (struct descr *) D_A(dp); /* get var pointer */
	    if (dp) {
		struct spec s[1];

		S_A(s) = 0;		/* try to keep gcc quiet */
		S_O(s) = 0;		/* try to keep gcc quiet */
		X_LOCSP(s, dp);		/* get specifier */

		/* might contain NUL's... will stop short! */
		COPY(S_SP(s), S_L(s));
	    }
	    break;
	default:
	    *lp++ = c;
	    space--;
	    break;
	}
    } /* while */
    va_end(vp);
    *lp = '\0';

#ifdef MEM_IO
    if (ISMEM(up->curr))
	mem_write(up->curr, line, strlen(line));
    else
#endif
    if (up->curr->f)
	fputs(line, up->curr->f);
} /* io_printf */

void
io_print( iokey, iob, sp )		/* STPRNT */
    struct descr *iokey;
    struct descr *iob;
    struct spec *sp;
{
    int unit;
    struct file *fp;
    struct unit *up;
    FILE *f;
    int ret;

    /* IOB->
     * title descr
     * integer unit number
     * pointer to natural var for format
     */

    D_A(iokey) = FALSE;			/* default to error */

    unit = INTERN(D_A(D_A(iob) + DESCR));
    if (BADUNIT(unit))
	return;

    up = FINDUNIT(unit);
    fp = up->curr;
    if (fp == NULL)
	return;

    f = fp->f;
    if (f == NULL)
	return;

    /*
     * ANSI C requires that a file positioning function intervene
     * between output and input. Would not be needed if UPDATE I/O
     * performed using read()/write() (ie; FL_UNBUF)
     */

    if ((fp->flags & FL_UPDATE) && fp->last == LAST_INPUT && ISAFILE(fp)) {
	fseeko(f, (off_t)0, SEEK_CUR);	/* seek relative by zero */
	/*
	 * XXX set fp->last to LAST_NONE; don't set to LAST_OUTPUT
	 * until an actual stdio operation is done?
	 */
    }
    fp->last = LAST_OUTPUT;

    ret = TRUE;
    if (S_A(sp) && S_L(sp)) {
	int len;
	char *cp;

	len = S_L(sp);
	cp = S_SP(sp);
	if (D_A(COMPCL)) {
	    char *ep;
	    int l2;

	    /* trim spaces & NUL's (without altering specifier) */
	    ep = cp + len - 1;
	    while (len > 0 && (*ep == ' ' || *ep == '\0')) {
		len--;
		ep--;
	    }

	    /* plug remaining NULs with spaces */
	    for (l2 = len; l2 > 0; l2--) {
		if (*cp == '\0')
		    *cp = ' ';
		cp++;
	    }
	    cp = S_SP(sp);
	} /* compiling */

#ifdef INET_IO
	if (ISINET(fp)) {
	    if (inet_write(f, cp, len) != len)
		ret = FALSE;
	}
	else
#endif /* INET_IO defined */
#ifdef MEM_IO
	if (ISMEM(fp)) {
	    ret = mem_write(fp, cp, len);
	}
	else
#endif /* MEM_IO defined */
#ifndef NO_UNBUF_RW
	if (fp->flags & FL_UNBUF) {
	    if (write(fileno(f), cp, len) != len)
		ret = FALSE;
	}
	else
#endif /* NO_UNBUF_RW not defined */
	if (fwrite( cp, 1, len, f ) != len)
	    ret = FALSE;
    } /* have string */

    /* XXX check ret first? */

    if (fp->flags & FL_EOL) {
#ifdef INET_IO
	if (ISINET(fp)) {
	    if (inet_write(f, "\n", 1) != 1)
		ret = FALSE;
	}
	else
#endif /* INET_IO defined */
#ifdef MEM_IO
	if (ISMEM(fp)) {
	    ret = mem_write(fp, "\n", 1);
	}
	else
#endif /* MEM_IO defined */
#ifndef NO_UNBUF_RW
	if (fp->flags & FL_UNBUF) {
	    if (write(fileno(f), "\n", 1) != 1)
		ret = FALSE;
	}
	else
#endif /* NO_UNBUF_RW not defined */
	if (putc( '\n', f ) == EOF)
	    ret = FALSE;
    }

#ifdef NO_UNBUF_RW
    if ((fp->flags & FL_UNBUF) && ISAFILE(fp)) {
	/* simulate unbuffered I/O */
	if (fflush(f) == EOF)
	    ret = FALSE;
    }
#endif /* NO_UNBUF_RW defined */

    D_A(iokey) = ret;
} /* io_print */

int
io_endfile(unit)			/* ENFILE */
    int_t unit;
{
    struct unit *up;

    unit = INTERN(unit);

    /* bad unit a fatal error in SPITBOL, but not in SNOBOL4+; */
    if (BADUNIT(unit))
	return TRUE;
    up = FINDUNIT(unit);
    if (up->curr == NULL && up->head == NULL)
	return TRUE;

    return io_closeall(unit);
}

#define COMPILING(UNIT) ((UNIT) == INTERN(UNITI) && D_A(COMPCL))

#ifdef COMPILER_READLINE
static int readline_inited;
#ifdef HAVE_RL_SET_KEYMAP
static Keymap initial_keymap, compile_keymap;
#endif

static void
init_readline() {
    rl_initialize();
#ifdef HAVE_RL_SET_KEYMAP
    initial_keymap = rl_get_keymap();
    compile_keymap = rl_copy_keymap(initial_keymap);
    rl_set_keymap(compile_keymap);
#endif
    /* disable TAB completion */
    rl_bind_key('\t', rl_insert);

    readline_inited = 1;
}

static void
restore_readline() {
    if (!readline_inited)
	return;
#ifdef HAVE_RL_SET_KEYMAP
    /* restore initial keymap */
    if (initial_keymap)
	rl_set_keymap(initial_keymap);
#if 0
    /* dies with free() of invalid pointer on Ubuntu. */
    if (compile_keymap)
	rl_discard_keymap(compile_keymap);
    compile_keymap = NULL;
#endif
#else
    /*
     * probably here with "editline" library (OS X, NetBSD?)
     */
    rl_initialize();			/* seems to work */
#endif
    clear_history();
}
#endif /* ifdef COMPILER_READLINE */

enum io_read_ret
io_read( dp, sp )			/* STREAD */
    struct descr *dp;
    struct spec *sp;
{
    int unit;
    int recl;
    int len;
    char *cp;
    FILE *f;
    struct file *fp;
    struct unit *up;
#ifdef _MSC_VER
    int_t err_count = D_A(UINTCL);
#endif

    unit = INTERN(D_A(dp));
    if (BADUNIT(unit) || (up = FINDUNIT(unit)) == NULL || up->curr == NULL) {
	if (COMPILING(unit)) {
	    return IO_ERR;		/* compiler never quits!! */
	}
	return IO_EOF;
    }

    recl = S_L(sp);			/* YUK! */
    cp = S_SP(sp);
    for (;;) {
	fp = up->curr;
	f = fp->f;
	if (f == NULL) {
	    f = io_fopen( fp, "r" );
	    if (f == NULL)
		return IO_ERR;
	}

	/*
	 * ANSI C requires that a file positioning function intervene
	 * between output and input. Would not be needed if UPDATE I/O
	 * performed using read()/write() (ie; FL_UNBUF).
	 *
	 * before FL_TTY check, in case tty_read() uses stdio functions.
	 */

	if ((fp->flags & FL_UPDATE) && fp->last == LAST_OUTPUT && ISAFILE(fp)) {
	    fseeko(f, (off_t)0, SEEK_CUR); /* seek relative by zero */
	    /*
	     * XXX set fp->last to LAST_NONE; don't set to LAST_OUTPUT
	     * until an actual stdio operation is done?
	     */
	}
	fp->last = LAST_INPUT;

	if (ISTTY(fp)) {
	    tty_mode( fp->f,
		     (fp->flags & FL_BINARY) != 0,
		     (fp->flags & FL_NOECHO) != 0,
		     recl );
	} /* FL_TTY set */

	if (fp->flags & FL_BINARY) {
#ifdef INET_IO
	    if (ISINET(fp))
		len = inet_read_raw(f, cp, recl);
	    else
#endif /* INET_IO defined */
#ifdef MEM_IO
	    if (ISMEM(fp)) {
		len = mem_read_raw(fp, cp, recl);
	    }
	    else
#endif /* MEM_IO defined */
#ifdef TTY_READ_RAW
	    if (ISTTY(fp))
		len = tty_read(f, cp, recl,
			       TRUE,	/* "raw" */
			       (fp->flags & FL_NOECHO) != 0, /* "noecho" */
			       FALSE,	/* "keepeol" */
			       fp->fname);
	    else
#endif /* TTY_READ_RAW defined */
#ifndef NO_UNBUF_RW
	    if (fp->flags & FL_UNBUF)
		len = read(fileno(f), cp, recl);
	    else
#endif /* NO_UNBUF_RW not defined */
		len = fread(cp, 1, recl, f);

	    if (len > 0)
		break;
	} /* binary */
#ifdef COMPILER_READLINE
	else if (ISTTY(fp) && COMPILING(unit)) {
	    char *tp;

	    if (!readline_inited)
		init_readline();
	    tp = readline("snobol4> ");
	    if (!tp)
	       return IO_EOF;
	    if (*tp)
		add_history(tp);
	    len = strlen(tp);
	    if (len > recl-1)	/* leave room for space */
	        len = recl-1;
	    strncpy(cp, tp, len);
	    free(tp);
	    break;
	}
#endif /* COMPILER_READLINE defined */
#ifdef INET_IO
	else if (ISINET(fp)) {
	    len = inet_read_cooked(f, cp, recl, (fp->flags & FL_EOL) == 0);
	    if (len > 0)
		break;
	}
#endif /* INET_IO defined */
#ifdef MEM_IO
	else if (ISMEM(fp)) {
	    len = mem_read_cooked(fp, cp, recl, (fp->flags & FL_EOL) == 0);
	    if (len > 0)
		break;
	}
#endif /* MEM_IO defined */
#ifdef TTY_READ_COOKED
	else if (ISTTY(fp)) {
	    len = tty_read(f, cp, recl,
			   FALSE,	/* "raw" */
			   (fp->flags & FL_NOECHO) != 0, /* "noecho" */
			   (fp->flags & FL_EOL) == 0, /* "keepeol" */
			   fp->fname);
	    if (len >= 0)		/* allow empty lines! */
		break;
	}
#endif /* TTY_READ_COOKED defined */
	else {				/* not binary */
	    /*
	     * fgets() returns at most recl-1 characters + NUL; we
	     * want excactly recl characters, and don't want the NUL
	     * but the buffer (passed in from SIL) doesn't have room
	     * for recl+1 characters.  Use fgets(), then fudge the
	     * last character, since fgets() can be much more
	     * efficient than a getc() loop (good implementations can
	     * block transfer characters from stdio buffers to ours).
	     *
	     * Handle CRLF for files ftp'ed from DOS in BINARY mode
	     * or on Cygwin with files transferred in ASCII mode!
	     * Don't treat a bare CR as an EOL; just discard it.
	     */
	    if (fgets(cp, recl, f) != NULL) {
		len = strlen(cp);

		/* ASSERT(len > 0) ??? */
		if (cp[len-1] == '\n') {	/* saw EOL */
		    if (fp->flags & FL_EOL) {	/* hide eol? */
			len--;			/* yes. */

			if (len > 0 && cp[len-1] == '\r')
			    len--;
		    }
		    else if (len > 1 && cp[len-2] == '\r') {
			/*
			 * If not hiding EOL, and saw CRLF
			 * replace CRLF with just NL
			 */
			len--;
			cp[len-1] = '\n';
		    }
		}
		else {				/* no EOL seen */
		    register int c;

		    /* ASSERT(len == recl-1) ??? */

		    /* read one more character, to fill in for NUL byte */
		    c = getc(f);

		    /*
		     * Handle CRLF for files transferred from DOS,
		     * or on cygwin with files transferred in ASCII mode!
		     */
		    if (c == '\r')		/* CR? */
			c = getc(f);		/* toss it */

		    if (c != EOF) {
			/* save additional character if not EOL
			 * or if EOL should be returned
			 */
			if (c != '\n' || !(fp->flags & FL_EOL)) {
			    cp[len] = c;
			    len++;
			} /* not EOL or not hiding EOL */
		    } /* extra char not EOF */

		    /* if not at EOL or EOF, discard rest of "record" */
		    while (c != EOF && c != '\n')
			c = getc(f);

		    /* don't care if line terminated by EOL or EOF? */
		} /* no EOL */
		break;
	    } /* fgets OK */
	} /* not binary */

	/* here when read failed */
	if (!ISAFILE(fp) || feof(f)) {
#ifdef _MSC_VER
	    /* Control C causes EOF to be set in VS10;
	     * SIGINT catcher increments UINTCL, so hopefully
	     * combinations of ^C and ^Z won't cause infinite loop!
	     */
	    if (++err_count == D_A(UINTCL) && ISAFILE(fp) && ISTTY(fp)) {
		clearerr(f);
		continue;
	    }
#endif
	    if (!io_next(unit)) {	/* skip to next file, if any */
		/* XXX perror? */
		return IO_EOF;		/* no more files */
	    }
	    if (COMPILING(unit)) {
		/* force call to INCCK to pop old FILENM and LNNOCL */
		return IO_EOF;
	    }
	    continue;			/* try again! */
	} /* feof */
//FMGW - got fail on UPDATE PIPE - errno == ESPIPE (29).
//This likely causes other issue -- partially, my old problem with BQ().
//Now, dump errno. Create alternate routines using read()/write()
//in CSNOBOL4.
  fprintf(stderr, "\n**** ERRNO: %d\n", errno);
	/* error, wasn't eof?! */
	return IO_ERR;
    } /* forever */

    /* here on successful read */
    if (COMPILING(unit)) {
	/* compiler doesn't handle exaustion well; tack on a space.
	 * INBUF has extra room (for LIST RIGHT output)
	 */
	cp[len++] = ' ';
    }
    S_L(sp) = len;

    return IO_OK;
} /* io_read */

/* will never be implemented; I/O is not record oriented; use "SET" to seek */
void
io_backspace(unit)			/* BKSPCE */
    int_t unit;
{
    UNDF(NORET);
}

void
io_rewind(unit)				/* REWIND */
    int_t unit;
{
    FILE *f;
    struct file *fp;
    struct unit *up;

    unit = INTERN(unit);
    if (BADUNIT(unit))
	return;

    up = FINDUNIT(unit);
    if (up->curr != up->head) {
	if (up->curr != NULL)		/* open file not first in list */
	    io_close(unit);		/* close it */
	up->curr = up->head;		/* reset to head of list */
	if (up->curr->f == NULL)
	    io_fopen(up->curr, "r");	/* XXX use original mode? */
    }
    fp = up->curr;
    if (fp == NULL)
	return;

#ifdef MEM_IO
    if (ISMEM(fp)) {
	if (up->offset <= fp->u.mem.len)
	    fp->u.mem.pos = up->offset;
	else
	    fp->u.mem.pos = 0;		/* XXX fp->u.mem.len? */
	return;
    }
#endif /* MEM_IO defined */

    f = fp->f;
    if (f != NULL && !ISPIPE(fp) && ISAFILE(fp) && !ISPTY(fp)) {
	fseeko(f, up->offset, SEEK_SET);
	fp->last = LAST_NONE;		/* reset last I/O type */
   }
} /* io_rewind */

/* extensions; */

/* here at end of compilation */
void
io_ecomp()				/* XECOMP */
{
    struct unit *up;
    struct file *fp;

#ifdef COMPILER_READLINE
    restore_readline();
#endif

    if (lflag) {
	/* if -l was given, switch OUTPUT to stdout! */

	/* XXX check return?! */
	io_mkfile2( UNITO, stdout, STDOUT_NAME, FL_NOCLOSE );
    }

    if (rflag == 0) {
	/* if -r was not given, switch INPUT to stdin!! */

	/* XXX check return?! */
	io_mkfile2( UNITI, stdin, STDIN_NAME, FL_NOCLOSE );
	return;
    }

    /*
     * else (start INPUT after END stmt)
     * save the file position the data begins at for rewind.
     *
     * SITBOL would skip to next input file (ie; io_next())
     * but SPARC SPITBOL doesn't!
     */

    up = FINDUNIT(UNITI - 1);

    /* free source files... */
    fp = up->head;
    while (fp != up->curr) {
	struct file *tp;

	tp = fp->next;
	free(fp);
	fp = tp;
    }

    up->head = up->curr;		/* save file for rewind */
#ifdef MEM_IO
    if (ISMEM(up->curr))
	up->offset = up->curr->u.mem.pos;
    else
#endif
	up->offset = ftello(up->curr->f); /* save offset for rewind */

    /* free list of included filenames */
    while (iov.includes) {
	struct file *tp;

	tp = iov.includes->next;
	free(iov.includes);
	iov.includes = tp;
    }

    /* free list of include file directories */
    while (iov.lib_dirs) {
	struct file *tp;

	tp = iov.lib_dirs->next;
	free(iov.lib_dirs);
	iov.lib_dirs = tp;
    }
    iov.lib_dir_last = NULL;
}

/* process I/O option strings for io_openi and io_openo */
static int
io_options( fp, op, rp )
    struct file *fp;			/* IN: file pointer */
    char *op;				/* IN: options */
    int *rp;				/* OUT: recl */
{
    int flags;
    int recl;

    flags = fp->flags;
    recl = 0;

    /* XXX check here for leading hyphen; process SPITBOL style options? */

    while (*op) {
	switch (*op) {
	case '-':			/* reserved for SPITBOL ops */
	    /* XXX skip ahead 'till space or EOS? */
	    return FALSE;

	case ',':			/* optional SNOBOL4+ seperator */
	    op++;			/* skip it */
	    break;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
#if 0
	    if (recl)			/* already got one? */
		return FALSE;		/* boing! */
#endif /* 0 */
	    recl = 0;
	    while (isdigit(*op)) {
		recl = recl * 10 + *op - '0'; /* XXX works for ASCII */
		op++;
	    }
	    break;

	case 'A':			/* SITBOL/SPITBOL: append */
	case 'a':
	    flags |= FL_APPEND;
	    op++;
	    break;

	case 'B':			/* SITBOL/SNOBOL4+: binary */
	case 'b':
	    flags |= FL_BINARY;
	    flags &= ~FL_EOL;
	    op++;
	    break;

	case 'C':			/* SITBOL/SPITBOL: character */
	case 'c':
	    flags |= FL_BINARY;
	    flags &= ~FL_EOL;
#if 0
	    if (recl)			/* already have recl? */
		return FALSE;		/* fail */
#endif /* 0 */
	    recl = 1;
	    op++;
	    break;

	case 'T':			/* SITBOL: "terminal" (no EOL) */
	case 't':
	    flags &= ~FL_EOL;
	    flags |= FL_UNBUF;		/* force prompt output */
	    op++;
	    break;

	case 'Q':			/* SNOBOL4+/SPITBOL: quiet */
	case 'q':
	    flags |= FL_NOECHO;
	    op++;
	    break;

	case 'U':			/* SITBOL/SPITBOL: update */
	case 'u':
	    flags |= FL_UPDATE;
	    op++;
	    break;

	case 'W':			/* SPITBOL: write unbuffered */
	case 'w':
	    flags |= FL_UNBUF;
	    op++;
	    break;

	default:
	    op++;
	    break;
	}
    } /* while *op */

    fp->flags = flags;
    if (rp)
	*rp = recl;
    return TRUE;
}

int
io_openi(dunit, sfile, sopts, drecl)	/* called from SNOBOL INPUT() */
    struct descr *dunit;		/* IN: unit */
    struct spec *sfile;			/* IN: filename */
    struct spec *sopts;			/* IN: options */
    struct descr *drecl;		/* OUT: rec len */
{
    char fname[MAXFNAME];		/* XXX malloc(S_L(sfile)+1)? */
    char opts[MAXOPTS];			/* XXX malloc(S_L(sopts)+1)? */
    struct file *fp;
    struct unit *up;
    FILE *f;
    int unit;
    int recl;

    unit = INTERN(D_A(dunit));
    if (BADUNIT(unit))
	return FALSE;			/* fail */
    up = FINDUNIT(unit);

    spec2str( sfile, fname, sizeof(fname) );
    spec2str( sopts, opts, sizeof(opts) );

    /* XXX if no sopts;
     * extract options suffix (if any) from filename here?
     */

    if (fname[0]) {
	/* SITBOL takes comma seperated file list */
	fp = io_newfile(fname);
    }
    else {
	fp = up->curr;
    }
    if (fp == NULL)
	return FALSE;

    /* process options */
    if (!io_options(fp, opts, &recl)) {
	free(fp);
	return FALSE;
    }

    /* open it now, so we can return status! */
    if (fname[0]) {
	f = io_fopen( fp, "r");
	if (f == NULL) {
	    free(fp);
	    return FALSE;		/* fail; no harm done! */
	}
	io_closeall(unit);
	up->curr = up->head = fp;
    }

    /* pass recl back up */
    D_A(drecl) = recl;
    D_F(drecl) = 0;
    D_V(drecl) = I;

    return TRUE;
} /* io_openi */

int
io_openo(dunit, sfile, sopts)		/* called from SNOBOL OUTPUT() */
    struct descr *dunit;		/* IN: unit */
    struct spec *sfile;			/* IN: filename */
    struct spec *sopts;			/* IN: options */
{
    char fname[MAXFNAME];		/* XXX malloc(S_L(sfile)+1)? */
    char opts[MAXOPTS];			/* XXX malloc(S_L(sopts)+1)? */
    struct file *fp;
    struct unit *up;
    int unit;
    FILE *f;

    unit = INTERN(D_A(dunit));
    if (BADUNIT(unit))
	return FALSE;			/* fail */
    up = FINDUNIT(unit);

    spec2str( sfile, fname, sizeof(fname) );
    spec2str( sopts, opts, sizeof(opts) );

    /* XXX if no sopts;
     * extract options suffix (if any) from filename here?
     */

    if (fname[0]) {
	/* SITBOL takes comma seperated file list */
	fp = io_newfile(fname);
    }
    else {
	fp = up->curr;
    }

    if (fp == NULL)
	return FALSE;			/* fail; no harm done! */

    /* process options */
    if (!io_options(fp, opts, NULL)) {	/* XXX error if recl set?? */
	free(fp);
	return FALSE;
    }

    /* open it now, so we can return status! */
    if (fname[0]) {
	f = io_fopen( fp, "w");
	if (f == NULL) {
	    free(fp);
	    return FALSE;		/* fail; no harm done! */
	}
	io_closeall(unit);
	up->curr = up->head = fp;
    }
    return TRUE;
} /* io_openo */

enum io_include_ret
io_include( dp, sp )
    struct descr *dp;			/* input unit */
    struct spec *sp;			/* file name (with quotes) */
{
    int l;
    char fname[MAXFNAME];		/* XXX */
    struct file *fp;
    struct unit *up;

    spec2str( sp, fname, sizeof(fname) );

    /* search includes list to see if file already included!! */
    for (fp = iov.includes; fp; fp = fp->next)
	if (strcmp(fname, fp->fname) == 0) /* found it!!! */
	    return INC_SKIP;		/* as you were! */

    /* strip off trailing spaces after uniqueness test */
    l = S_L(sp);
    while (l > 0 && fname[l-1] == ' ') {
	l--;
    }
    fname[l] = '\0';

    fp = io_newfile(fname);
    if (fp == NULL)
	return INC_FAIL;

    if (io_fopen( fp, "r") == NULL) {
	char *fn2;

	free(fp);

	fn2 = io_lib_find(NULL, fname, NULL);
	if (!fn2)
	    return INC_FAIL;		/* not found */

	fp = io_newfile(fn2);
	free(fn2);
	if (fp == NULL)
	    return INC_FAIL;		/* alloc failure */

	if (io_fopen( fp, "r") == NULL) {
	    free(fp);
	    return INC_FAIL;
	}
    }

    up = FINDUNIT(INTERN(D_A(dp)));

    /* push new file onto top of input list */
    fp->next = up->curr;
    up->curr = fp;

    /* add base filename to list of files already included */
    fp = io_newfile(fname);		/* reuse struct file!! */
    if (fp) {
	fp->next = iov.includes;
	iov.includes = fp;		/* XXX keep per unit? nah. */
    }
    return INC_OK;
} /* io_include */

/*
 * retrieve file name currently associated with a unit, or NULL.
 * data only valid while current file open
 */
char *
io_fname( unit )
    int unit;
{
    struct unit *up;
    struct file *fp;

    unit = INTERN(unit);
    if (BADUNIT(unit))
	return NULL;

    up = FINDUNIT(unit);
    if (up == NULL)
	return NULL;

    fp = up->curr;
    if (fp == NULL)
	return NULL;

    return fp->fname;
}

/*
 * retrieve file currently associated with a unit
 * used by compiler to pick up filenames from command line
 */
int
io_file( dp, sp )
    struct descr *dp;			/* IN: unit number */
    struct spec *sp;			/* OUT: filename */
{
    char *fname;

    fname = io_fname(D_A(dp));
    if (fname == NULL)
	return FALSE;

    S_A(sp) = (int_t) fname;		/* OY! */
    S_F(sp) = 0;			/* NOTE: *not* a PTR! */
    S_V(sp) = 0;
    S_O(sp) = 0;
    S_L(sp) = strlen(fname);
    CLR_S_UNUSED(sp);
    
    return TRUE;
}

/*
 * support for SPITBOL SET() function
 *
 * problems on systems (like bsd44) where sizeof(off_t) > sizeof(int_t)
 * on most hardware...
 */
int
io_seek(dunit, doff, dwhence)
    struct descr *dunit, *doff, *dwhence;
{
    int unit, whence;
    off_t off;
    struct file *fp;
    struct unit *up;
    FILE *f;

    unit = INTERN(D_A(dunit));
    if (BADUNIT(unit))
	return FALSE;
    up = FINDUNIT(unit);
    fp = up->curr;
    if (fp == NULL)
	return FALSE;

    off = (off_t) D_A(doff);
    whence = D_A(dwhence);
    if (whence < 0 || whence > 2)
	return FALSE;

    /* translate n -> SEEK_xxx using switch stmt (if SEEK_xxx available)? */

#ifdef MEM_IO
    if (ISMEM(fp)) {
	/* XXX special fun here */
	return FALSE;
    }
#endif /* MEM_IO defined */

    if (!ISAFILE(fp))
	return FALSE;

    f = fp->f;
    if (f == NULL)
	return FALSE;

#ifndef NO_UNBUF_RW
    if (fp->flags & FL_UNBUF) {
	off_t pos;

	/* optimized stdio libraries might try to optimize away
	 * the lseek if they've seen no read/write ops!
	 */
	pos = lseek(fileno(f), off, whence);
	if (pos != (off_t)-1)
	    return FALSE;
	D_A(doff) = (int_t)pos;		/* XXX truncation possible! */
    }
    else
#endif /* NO_UNBUF_RW not defined */
    if (fseeko(f, off, whence) == 0)
	D_A(doff) = (int_t)ftello(f);	/* XXX truncation possible! */
    else
	return FALSE;

    fp->last = LAST_NONE;		/* reset last I/O type */

    return TRUE;
}

/*
 * new 3/12/99
 * Experimental "scaled SET" function
 * called as external function from snolib/sset.c
 */
int
io_sseek(unit, soff, whence, scale, oof )
    int_t unit, soff, whence, scale, *oof;
{
    off_t off;
    struct file *fp;
    struct unit *up;
    FILE *f;

    unit = INTERN(unit);
    if (BADUNIT(unit))
	return FALSE;
    up = FINDUNIT(unit);
    fp = up->curr;
    if (fp == NULL)
	return FALSE;

    off = soff * (off_t)scale;
    if (whence < 0 || whence > 2)
	return FALSE;

    /* translate n -> SEEK_xxx using switch stmt (if SEEK_xxx available)? */

#ifdef MEM_IO
    if (ISMEM(fp)) {
	/* XXX special fun here */
	return FALSE;
    }
#endif /* MEM_IO defined */

    if (!ISAFILE(fp))
	return FALSE;

    f = fp->f;
    if (f == NULL)
	return FALSE;

#ifndef NO_UNBUF_RW
    if (fp->flags & FL_UNBUF) {
	off_t pos;			/* XXX pos_t? */

	/* optimized stdio libraries might try to optimize away
	 * the lseek if they've seen no read/write ops!
	 */
	pos = lseek(fileno(f), off, whence);
	if (pos != (off_t)-1)
	    return FALSE;
	*oof = pos / scale;
    }
    else
#endif /* NO_UNBUF_RW not defined */
    if (fseeko(f, off, whence) == 0)
	*oof = ftello(f)/scale;
    else
	return FALSE;

    fp->last = LAST_NONE;		/* reset last I/O type */

    return TRUE;
}

/* flush all pending output before system(), exec(), or death */
int
io_flushall(dummy)
    int dummy;
{
    int i;

    for (i = 1; i <= NUNITS; i++) {
	struct file *fp;
	struct unit *up;

	up = FINDUNIT(INTERN(i));
	fp = up->curr;
	if (fp) {
	    FILE *f;

	    f = fp->f;
	    if (f) {
		if (fp->last == LAST_OUTPUT && ISAFILE(fp))
		    fflush(f);		/* keep err count?? */
	    } /* have f */
	} /* have fp */
    } /* foreach unit */
    return TRUE;
}

/*
 * for PML functions; return a free unit number, returns -1 on failure
 * (use io_mkfile() to attach open file to unit)
 */

#define MINFIND 20			/* minimum unit to return */
#define MAXFIND NUNITS			/* maximum unit to return */

EXPORT(int)
io_findunit()
{
    int start;

    for (;;) {
	if (iov.finger < MINFIND)
	    iov.finger = MAXFIND;

	start = iov.finger;
	while (iov.finger >= MINFIND) {
	    int u;
	    struct unit *up;
	    int ret;

	    u = INTERN(iov.finger);
	    up = FINDUNIT(u);
	    ret = iov.finger--;
	    if (up->curr == NULL && up->head == NULL)
		return ret;		/* found a free unit */
	}

	/*
	 * if we didn't find anything, and we started from scratch,
	 * then we're out of luck.  Only REALLY need to search from
	 * start0 downto MINFIND, then from MAXFIND to start0+1,
	 * but this code is ugly enough
	 */
	if (start == MAXFIND)
	    return -1;

	/* if we didn't start from scratch, then do that */
    }
} /* io_findunit */

/* for PML functions; get current fp on a unit */
EXPORT(FILE *)
io_getfp(unit)
    int unit;				/* "external" unit */
{
    struct unit *up;

    unit = INTERN(unit);
    if (BADUNIT(unit))
	return NULL;

    up = FINDUNIT(unit);
    if (up->curr == NULL)
	return NULL;

    return up->curr->f;
} /* io_getfp */

/*
 * new 9/9/97
 * Pad listing line out to input record length for "-LIST RIGHT"
 * Not strictly an "I/O" function, but here because the work used
 * to be done in io_read() for all compiler input, regardless of
 * listing on/off and left/right.
 */

int
io_pad(sp, len)
    struct spec *sp;
    int len;
{
    register char *cp;
    register int i;

    cp = S_SP(sp) + S_L(sp);
    for (i = len - S_L(sp); i > 0; i--)
	*cp++ = ' ';
    S_L(sp) = len;

    return 1;				/* for XCALLC */
}

/* new 9/21/97 called from endex() */
int
io_finish() {
    int i;
    
    /* should visit from most recently opened to least recent? */
    for (i = 0; i < NUNITS; i++)
	io_closeall(i);

#ifdef NO_STATIC_VARS
    free(varp->v_iov);
    varp->v_iov = NULL;
#endif /* NO_STATIC_VARS defined */

    return TRUE;
}

/* new 1/12/2012 call to add a dir to include dir list */
int
io_add_lib_dir(dirname)
     char *dirname;
{
    struct file *fp = io_newfile(dirname);
    if (!fp)
	return FALSE;
    if (iov.lib_dir_last)
	iov.lib_dir_last->next = fp;
    else
	iov.lib_dirs = fp;		/* new list */
    iov.lib_dir_last = fp;
    return TRUE;
}

/* new 1/12/2012 add a (PATH_SEP separated) path to include dir list */
int
io_add_lib_path(path)
    char *path;
{
    char *p2 = malloc(strlen(path)+1);
    char *pp = p2;
    if (!p2)
	return FALSE;
    strcpy(p2, path);			/* XXX strdup */

    while (pp) {
	/* XXX need strstr if sizeof(PATH_SEP) != 2 */
	char *tpp = index(pp, PATH_SEP[0]);
	if (tpp)
	    *tpp++ = '\0';		/* tie off and advance */
	io_add_lib_dir(pp);
	pp = tpp;
    }
    free(p2);
    return TRUE;
}

void
io_show_paths()
{
    struct file *fp;
    for (fp = iov.lib_dirs; fp; fp = fp->next)
	puts(fp->fname);
}

/*
 * search for a file, given a path, and optional subdir and extension
 * returns malloc'ed string or NULL
 */

/* helper */
static char *
trypath(dir, subdir, file, ext)
    char *dir;
    char *subdir;			/* optional: may be NULL */
    char *file;
    char *ext;				/* optional: may be NULL */
{
    int l = strlen(dir) + strlen(file) + sizeof(DIR_SEP);
    char *path;
    if (subdir)
	l += strlen(subdir) + sizeof(DIR_SEP) - 1;
    if (ext)
	l += strlen(ext);
    path = malloc(l);
    if (!path)
	return NULL;
    strcpy(path, dir);
    strcat(path, DIR_SEP);
    if (subdir) {
	strcat(path, subdir);
	strcat(path, DIR_SEP);
    }
    strcat(path, file);
    if (ext)
	strcat(path, ext);
    if (exists(path))
	return path;
    free(path);
    return NULL;
}

char *
io_lib_find(subdir, file, ext)
    char *subdir;
    char *file;
    char *ext;
{
    struct file *ip;

    if (abspath(file))
	return NULL;			/* absolute path */

    for (ip = iov.lib_dirs; ip; ip = ip->next) {
	char *path;

	path = trypath(ip->fname, subdir, file, ext);
	if (path)
	    return path;

	if (ext) {
	    path = trypath(ip->fname, subdir, file, NULL);
	    if (path)
		return path;
	}

	/* if given subdir, try without it (for dynamic libraries) */
	if (subdir) {
	    path = trypath(ip->fname, NULL, file, ext);
	    if (path)
		return path;

	    if (ext) {
		path = trypath(ip->fname, NULL, file, NULL);
		if (path)
		    return path;
	    }
	}
    }
    return NULL;
}

static void
try_preload(path)
    char *path;
{
    if (!exists(path))
	return;

    if (isdir(path)) {
	int len = strlen(path) + sizeof(PRELOAD_FILENAME) + sizeof(DIR_SEP) - 1;
	char *fname = malloc(len);
	if (fname) {
	    strcpy(fname, path);
	    strcat(fname, DIR_SEP);
	    strcat(fname, PRELOAD_FILENAME);
	    if (exists(fname)) 
		io_input_file(fname);
	    free(fname);
	}
    }
    else
	io_input_file(path);
} /* try_preload */

/* called from init.c to preload source files */
void
io_preload() {
    char *env = getenv("SNOBOL_PRELOAD_PATH");
    if (env) {
	char *tmp, *tp;
	tmp = tp = malloc(strlen(env)+1); /* want strdup */
	strcpy(tmp, env);
	while (tp) {
	    char *np = index(tp, PATH_SEP[0]); /* strstr? */
	    if (np)
		*np++ = '\0';
	    try_preload(tp);
	    tp = np;
	}
	free(tmp);
    }
    else {				/* no SNOBOL_PRELOAD_PATH */
	struct file *ip;

	/* use include search path */
	for (ip = iov.lib_dirs; ip; ip = ip->next)
	    try_preload(ip->fname);
    }
} /* io_preload */
