/* $Id: init.c,v 1.98 2013/09/24 23:07:51 phil Exp $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H defined */

#ifdef HAVE_STDLIB_H			/* before stdio */
#include <stdlib.h>			/* for malloc */
#else  /* HAVE_STDLIB_H not defined */
extern void *malloc();
#endif /* HAVE_STDLIB_H not defined */

#include <stdio.h>
#include <signal.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>			/* xxx_FILENO */
#endif /* HAVE_UNISTD_H defined */

#include "h.h"
#include "snotypes.h"
#include "macros.h"
#include "lib.h"			/* io_init(), io_input() protos */
#include "str.h"			/* strlen() */
#include "units.h"			/* UNIT[IOPT] */

#include "equ.h"			/* SIL equ's */
#include "res.h"			/* for data.h */
#include "data.h"			/* SIL data */
#include "proc.h"			/* for SYSCUT() */

#ifndef DEF_SNOPATH
#include "version.h"
#endif

/* return type of signal handler functions */
#ifndef SIGFUNC_T
#define SIGFUNC_T void
#endif /* SIGFUNC_T not defined */

#ifndef NDYNAMIC
#define NDYNAMIC (512*1024)		/* default dynamic region size */
#endif /* NDYNAMIC not defined */

#ifndef PSSIZE
#define PSSIZE SPDLSZ			/* default pattern stack size */
#endif /* PSSIZE not defined */

#ifndef ISSIZE
#define ISSIZE STSIZE
#endif /* ISSIZE not defined */

#ifdef NO_STATIC_VARS
#include "vars.h"
#else  /* NO_STATIC_VARS not defined */

#ifdef HAVE_BUILD_VARS
extern const char build_date[];		/* from build.c */
#endif /* HAVE_BUILD_VARS defined */

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif /* STDOUT_FILENO not defined */

/* global for access by io.c; */
int rflag;
int lflag;

/* global for access by host.c; */
size_t ndynamic;
size_t pmstack;
size_t istack;
char *params;
char **argv;
int firstarg;
int argc;
int nfiles;
#endif /* NO_STATIC_VARS not defined */

extern int optind;
extern char *optarg;
extern int getopt();

static void
p( flag, str )
    char flag;
    char *str;
{
    fprintf(stderr, "-%c\t%s\n", flag, str);
}

static char *
showk( n )
    int n;
{
    static char buf[32];
    int k, m;

    k = n / 1024;
    m = k / 1024;

    if (m*1024*1024 == n)
	sprintf(buf, "%dm", m);
    else if (k*1024 == n)
	sprintf(buf, "%dk", k);
    else
	sprintf(buf, "%d", n);

    return buf;
}

static void
usage( jname, justversion )
    char *jname;
    int justversion;
{
    extern const char snoname[], vers[], vdate[];
    fprintf( stderr, "%s version %s (%s)\n", snoname, vers, vdate );
#ifdef HAVE_BUILD_VARS
    fprintf( stderr, "built %s\n", build_date);
#endif /* HAVE_BUILD_VARS defined */
    if (justversion)
	exit(1);

    fprintf( stderr,
	    "Usage: %s [options...] [files...] [parameters...]\n", jname );
/* XXX stuff about parameters */
    p('b',"toggle display of startup banner");
    fprintf(stderr,
	    "-d DESCRS[km]\n\tsize of dynamic region in descriptors (default: %s)\n", showk(NDYNAMIC));
    p('f',"toggle folding of identifiers to upper case (-CASE)");
    p('g',"enable GC trace (&GTRACE)");
    p('h',"help (this message)");
    p('k',"toggle running programs with compilation errors (-[NO]ERRORS)");
    fprintf(stderr, 
	    "-l LISTINGFILE\n\tenable listing (-LIST) and specify file\n");
    p('n',"toggle running program after compilation (-[NO]EXECUTE)");
    p('p',"toggle SPITBOL operators (-PLUSOPS)");
    p('r',"toggle reading INPUT from after END statement");
    p('s',"toggle display of statistics");
    fprintf(stderr, "-u PARMS\n\tparameter data available via HOST(0)\n");
    p('v',"display version and exit");
    fprintf(stderr, "-L SOURCE\n");
    fprintf(stderr, "\tload source file before user program\n");
    p('M',"process multiple files for program code");
    fprintf(stderr, "-P DESCRS[km]\n");
    fprintf(stderr, "\tsize of pattern match stack in descriptors (default: %s)\n", showk(PSSIZE));
    fprintf(stderr, "-S DESCRS[km]\n");
    fprintf(stderr, "\tsize of interpreter stack in descriptors (default: %s)\n", showk(ISSIZE));

    fprintf(stderr, "\n");
    fprintf(stderr, "For memory region sizes a suffix of 'k' (1024) and 'm' (1024*1024)\n");
    fprintf(stderr, "can be used. A descriptor takes up %d bytes.\n", (int)DESCR );
    exit(1);
}

static int
getk( str, out )
    char *str;
    size_t *out;
{
    char suff;
    unsigned long val;
    switch (sscanf(str, "%lu%c", &val, &suff)) {
    case 2:				/* number & suffix */
	if (suff == 'k' || suff == 'K')
	    val *= 1024;
	else if (suff == 'm' || suff == 'M')
	    val *= 1024*1024;
	else
	    return 0;			/* bad suffix; fail */
	/* FALL */
    case 1:				/* just number */
	*out = val;
	return 1;			/* return OK */

    default:				/* no number */
	return 0;			/* fail */
    }
}

/*
 * create c-string of args from start .. argc in a malloc'ed buffer.
 * fills in an optional SPEC
 */

static char *
getargs(start, sp)
    int start;				/* which argument to start on */
    struct spec *sp;			/* dest spec, or NULL */
{
    int i;
    char *parms;
    register char *pp;
    int len;

    len = 0;
    for (i = start; i < argc; i++)
	len += strlen(argv[i]) + 1;	/* add one for space or NUL */

    parms = malloc(len);
    if (!parms)
	return NULL;			/* XXX perror & exit? */

    pp = parms;
    for (i = start; i < argc; i++) {
	register char *ap;

	if (pp != parms)
	    *pp++ = ' ';

	ap = argv[i];
	while ((*pp = *ap++))
	    pp++;
    }

    if (sp) {
	S_A(sp) = (int_t) parms;	/* OY! */
	S_F(sp) = 0;			/* NOTE: *not* a PTR! */
	S_V(sp) = 0;
	S_O(sp) = 0;
	S_L(sp) = len - 1;		/* omit trailing NUL */
	CLR_S_UNUSED(sp);
    }

    return parms;
}

void
io_init()				/* here from INIT */
{
    FILE *termin;

    io_initvars();

    /* but not if set-uid!!! */
    io_add_lib_dir(".");

// nfiles = 0
// rflag = 0	-r
// pmstack
// istack
// D_A(STATCL)
// D_A(LISTCL) lflag
// ndynamic
// D_A(BANRCL)		-b
    if (nfiles == 0) {			/* no input file(s)? */
#ifdef MEM_IO_TEST

        char *str =
#include "prog.inc"
;

//	char *str = "\tOUTPUT = 'Hello World'\n\tOUTPUT = INPUT\nEND\nFOO\n";
	io_input_string( "input", str );
#else  /* MEM_IO_TEST not defined */
	/* read code from stdin.... Macro SPITBOL requires '-' for this */
#if 1
	io_input_file("-");		/* implicit "-"! */
#else
	/* blows away preload list */
	if (!io_mkfile_noclose(UNITI, stdin, STDIN_NAME)) {
	    perror("could not attach stdin to INPUT");
	    exit(1);
	}
#endif
#endif /* MEM_IO_TEST not defined */
    }
    else {
	if (!io_skip(UNITI)) {		/* force file open */
	    char *fname;
	    fname = io_fname(UNITI);
	    if (!fname)
		fname = "unknown input file";
	    perror(fname);
	    exit(1);
	}
    }

    /* XXX support -o outputfile? */

    if (!D_A(LISTCL) && !io_mkfile_noclose(UNITO, stdout, STDOUT_NAME)) {
	perror("could not attach stdout to OUTPUT");
	exit(1);
    }

    if (!io_mkfile_noclose(UNITP, stderr, STDERR_NAME)) {
	perror("could not attach stderr to TERMINAL");
	exit(1);
    }

    termin = term_input();		/* call system dependant function */
    if (termin && !io_mkfile_noclose(UNITT, termin, TERMIN_NAME)) {
	perror("could not open TERMINAL for input");
	exit(1);
    }
} /* io_init */

/* called after -I paths have already been added, before preload, sources */
static void
pathinit() {
    char *env = getenv("SNOPATH");
    if (env) {
	io_add_lib_path(env);
    }
    else {
#ifdef DEF_SNOPATH
	io_add_lib_path(DEF_SNOPATH);
#else
	char *tmp;

	/* get old variable */
	env = getenv("SNOLIB");
	if (!env)
	    env = SNOLIB_BASE;

	/* local, version-specific */
	tmp = strjoin(env, DIR_SEP, VERSION, DIR_SEP, "local", NULL);
	io_add_lib_dir(tmp);
	free(tmp);

	/* distribution files (version-specific) */
	tmp = strjoin(env, DIR_SEP, VERSION, DIR_SEP, "lib", NULL);
	io_add_lib_dir(tmp);
	free(tmp);

	/* local -- all versions */
	tmp = strjoin(env, DIR_SEP, "local", NULL);
	io_add_lib_dir(tmp);
	free(tmp);

	/* old directory */
	io_add_lib_dir(env);
#endif
    }

#ifdef EXTRA_SNOPATH
    io_add_lib_path(EXTRA_SNOPATH);
#endif
}

/* called from main.c after init_data, before xfer to SIL BEGIN label */
void
init_args( ac, av )
    int ac;
    char *av[];
{
    int errs;
    int c;
    int multifile;
    int justversion;
    int showpaths = 0;

    ndynamic = NDYNAMIC;
    pmstack = PSSIZE;
    istack = ISSIZE;

    /* save in globals for HOST(), getparm(), init() */
    argc = ac;
    argv = av;

#ifdef vms
    argc = getredirection(argc, argv);
#endif /* vms defined */

    errs = 0;
    multifile = 0;			/* SITBOL behavior */
    justversion = 0;

#ifdef MEM_IO_TEST
    D_A(BANRCL) = 0;
// these sent in via configure
#ifdef APP_PMSTACK
    pmstack = APP_PMSTACK;
#endif
#ifdef APP_ISTACK
    istack = APP_ISTACK;
#endif
#ifdef APP_DYNAMIC
    ndynamic = APP_DYNAMIC;
#endif
    pathinit();
    optind = 1;
#else
    /*
     * ***** NOTE ******
     *
     * * Options are compatible (where possible) with Catspaw Macro SPITBOL
     *
     * * When adding options, update usage() function (above) and man page!!!
     *
     * * '+' at start is required w/ GNU libc (Linux) to avoid broken
     *		default (non POSIX) behavior (continues picking up
     *		switches after first file) and is HOPEFULLY harmless
     *		(-+ if given should fall into default case.  If we
     *		ever want a real -+ option, ANOTHER + will need to be
     *		added, but it better not want an argument!)
     */

    while ((c = getopt(argc, argv, "+bd:fghkl:nprsu:vzI:L:MP:S:")) != -1) {
	switch (c) {
	case 'b':
	    D_A(BANRCL) = !D_A(BANRCL);	/* toggle banner output */
	    break;

	case 'd':			/* number of dynamic descrs */
	    if (!getk(optarg, &ndynamic))
		errs++;
	    /* XXX enforce a minimum?? */
	    break;

	case 'f':			/* toggle case folding */
	    D_A(CASECL) = !D_A(CASECL);
	    break;

	case 'g':
	    D_A(GCTRCL) = -1;		/* enable &GCTRACE */
	    break;

	case 'v':			/* version */
	    justversion = 1;
	    errs++;
	    break;

	case 'h':			/* help */
	    justversion = 0;
	    errs++;
	    break;

	case 'k':
	    /* toggle running programs with compile errors */
	    D_A(NERRCL) = !D_A(NERRCL);
	    break;

	case 'l':			/* -LIST */
	    {
		/* now takes an argument!!! */
		FILE *listfile;
		if (strcmp(optarg, "-") == 0)
		    listfile = fdopen(dup(STDOUT_FILENO), "w");
		else
		    listfile = fopen(optarg, "w");
		D_A(LISTCL) = lflag = 1;
		if (!listfile || !io_mkfile(UNITO, listfile, optarg)) {
		    perror(optarg);
		    exit(1);
		}
	    }
	    break;

	case 'n':			/* toggle -[NO]EXECUTE */
	    D_A(EXECCL) = !D_A(EXECCL);
	    break;

	case 'p':			/* toggle -PLUSOPS */
	    D_A(SPITCL) = !D_A(SPITCL);
	    break;

	case 'r':			/* read INPUT from source after END */
	    rflag = !rflag;
	    break;

	case 's':			/* toggle statistics */
	    D_A(STATCL) = !D_A(STATCL);
	    break;

	case 'u':			/* parameter data */
	    params = optarg;
	    break;

	case 'z':
	    showpaths = 1;
	    break;

	case 'I':			/* include path dir */
	    io_add_lib_dir(optarg);
	    break;

	case 'L':			/* pre-load files */
	    if (exists(optarg)) 
		io_input_file(optarg);
	    else {
		/* look for file on SNOPATH (BUG: not yet populated?) */
		/* XXX check for no DIR_SEP? */
		char *path = io_lib_find(NULL, optarg, ".inc");
		if (path)
		    io_input_file(path);
		else {
		    fprintf(stderr, "%s: file not found\n", optarg);
		    exit(1);
		}
	    }
	    break;

	case 'M':			/* multi-file input */
	    multifile = !multifile;
	    break;

	case 'P':			/* pattern match stack size */
	    if (!getk(optarg, &pmstack))
		errs++;
	    break;

	case 'S':			/* interpreter stack size */
	    if (!getk(optarg, &istack))
		errs++;
	    break;

	default:
	    errs++;
	}
    } /* while getopt */

    pathinit();

    if (showpaths) {
	io_show_paths();
	exit(0);
    }

    /* XXX option to disable? */
    io_preload();

    /*
     * append first file (or all additional args until "--" seen
     * in "multi-file" mode) to INPUT stream
     */
    while (optind < argc) {
	if (strcmp(argv[optind], "--") == 0) { /* terminator? */
	    optind++;			/* skip it */
	    break;			/* leave loop */
	}
	io_input_file( argv[optind] );
	optind++;
	nfiles++;
	if (!multifile)			/* not in multi-file mode? */
	    break;			/* break out */
    }
#endif
    /* if no -u option, process any remaining items as arguments for HOST(0) */
    if (params == NULL && optind < argc) {
	params = getargs(optind, NULL);
    }

    firstarg = optind;			/* save for HOST(3) */

    if (errs) {
	usage(argv[0], justversion);
    }

    io_init();				/* AFTER io_input calls! */
#ifdef HAVE_OS_INIT
    os_init();
#endif /* HAVE_OS_INIT defined */
}

#ifndef NO_STATIC_VARS
volatile int math_error;		/* see macros.h */
#endif /* NO_STATIC_VARS not defined */

static SIGFUNC_T
math_catch(sig)
    int sig;
{
#ifdef SIGFPE
    signal(SIGFPE, math_catch);
#endif /* SIGFPE defined */
#ifdef SIGOVER
    signal(SIGOVER, math_catch);
#endif /* SIGOVER defined */

    math_error = TRUE;
    /* XXX need to longjump out on some systems to avoid restarting insn? */
}

/* handle fatal errors */
static SIGFUNC_T
err_catch(sig)
    int sig;
{
    D_A(SIGNCL) = sig;			/* save signal number for output */
    SYSCUT(NORET);
}

/* handle ^C (SIGINT) here */
static SIGFUNC_T
sig_catch(sig)
    int sig;
{
    if (D_A(COMPCL) || D_A(ERRLCL) == 0) /* in compiler or &ERRLIMIT == 0*/
	err_catch(sig);			/* treat as before */

    /*
     * top of INIT checks UINTCL and causes "User Interrupt" error
     * which can be caught with SETEXIT() and continued with :(SCONTINUE)
     * Keep count, so windoze code in io.c can detect ^C vs EOF
     */
    D_A(UINTCL)++;
    signal( SIGINT, sig_catch );	/* re-arm for Win32/VC10 */
}

#ifdef SIGTSTP
static SIGFUNC_T
suspend(sig)
    int sig;
{
    tty_suspend();			/* restore tty mode(s) */

    /* reestablish handler (does any system with job control,
     * in case signal() has System V semantics
     */
    signal(SIGTSTP, suspend);

    /* no need to restore tty modes; next I/O will reset as needed */
}
#endif /* SIGTSTP defined */

/* called by SIL INIT macro (first SIL op executed) */
void
init()
{
    char *ptr;

    /****************
     * allocate dynamic data region
     */

    ndynamic *= DESCR;			/* get bytes */

    ptr = dynamic(ndynamic);

    if (ptr == NULL) {
	fprintf(stderr, "%s: could not allocate dynamic region of %lu bytes\n",
		argv[0], (unsigned long)ndynamic);
	exit(1);
    }

    bzero( ptr, ndynamic );		/* XXX needed? */

    D_A(FRSGPT) = D_A(HDSGPT) = (int_t) ptr; /* first dynamic descr */

    /* first descr past end of dynamic storage */
    D_A(TLSGP1) = (int_t) ptr + ndynamic;


    /****************
     * allocate pattern match stack
     */

    pmstack *= DESCR;			/* get bytes */

    ptr = malloc(pmstack);		/* NOTE: malloc(), not dynamic() */
    if (ptr == NULL) {
	fprintf(stderr, "%s: could not allocate pattern stack of %lu bytes\n",
		argv[0], (unsigned long)pmstack);
	exit(1);
    }

    /* set up stack title */
    D_A(ptr) = (int_t) ptr;
    D_F(ptr) = TTL + MARK;
    D_V(ptr) = pmstack;			/* length in bytes */

    /* pointers to top of stack */
    D_A(PDLPTR) = D_A(PDLHED) = (int_t) ptr;

    /* pointer to end of stack for overflow checks */
    D_A(PDLEND) = (int_t) ptr + pmstack - NODESZ;

    /****************
     * allocate interpreter stack
     */

    istack *= DESCR;			/* get bytes */

    ptr = malloc(istack);		/* NOTE: malloc(), not dynamic() */
    if (ptr == NULL) {
	fprintf(stderr, "%s: could not allocate interpreter stack of %lu bytes\n",
		argv[0], (unsigned long) istack);
	exit(1);
    }

    /* set up stack title */
    D_A(ptr) = (int_t) ptr;
    D_F(ptr) = TTL + MARK;
    D_V(ptr) = istack;			/* length in bytes */

    /* pointers to top of stack */
    D_A(STKPTR) = D_A(STKHED) = (int_t) ptr;

    /* pointer to end of stack, for overflow checks */
    D_A(STKEND) = (int_t) ptr + istack;

    /****************
     * setup signal handlers
     */

    signal( SIGINT, sig_catch );

    /* catch bad memory references */
    signal( SIGSEGV, err_catch );
#ifdef SIGBUS
    signal( SIGBUS, err_catch );
#endif /* SIGBUS defined */

    /* catch math errors */
#ifdef SIGFPE
    signal(SIGFPE, math_catch);
#endif /* SIGFPE defined */
#ifdef SIGOVER
    signal(SIGOVER, math_catch);
#endif /* SIGOVER defined */

    /* catch resource limit errors */
#ifdef SIGXCPU
    signal(SIGXCPU, err_catch);
#endif /* SIGXCPU defined */
#ifdef SIGXFSZ
    signal(SIGXFSZ, err_catch);
#endif /* SIGXFSZ defined */

    /* catch network errors! */
#ifdef SIGPIPE
    signal(SIGPIPE, err_catch);
#endif /* SIGPIPE defined */

    /* catch suspend */
#ifdef SIGTSTP
    signal(SIGTSTP, suspend);
#endif /* SIGTSTP defined */
}

/* 9/21/96 - set specifier to point to entire command line for &PARM */
int
getparm( sp )
    struct spec *sp;
{
    return getargs(0, sp) != NULL;
}
