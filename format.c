#line 41 "CSNOBOL4.lss"
/* Generated by WRAPPER on 06/05/2014 19:59:30 */

#include "config.h"
#include "h.h"
#include "snotypes.h"
#include "macros.h"
#include "load.h"
#include "equ.h"
#include <string.h>

#line 42 "CSNOBOL4.lss"

/* Adds FORTRAN IV FORMAT to CSNOBOL4 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "p64.h"

static int status;

static int pipefds[2];

static int createpipe(void)
{
    return pipe(pipefds);
}


/* CREATEPIPE()INTEGER */
CREATEPIPE( LA_ALIST ) LA_DCL
{
    RETINT(createpipe());
}
#line 66 "CSNOBOL4.lss"

static int getpipefd(int n)
{
    if ((n < 0) || (n > 1))
        return -1;
    return pipefds[n];
}


/* GETPIPEFD(INTEGER)INTEGER */
GETPIPEFD( LA_ALIST ) LA_DCL
{
    RETINT(getpipefd((int)LA_INT(0)));
}
#line 75 "CSNOBOL4.lss"

static int get_errno(void)
{
    return errno;
}


/* GET_ERRNO()INTEGER */
GET_ERRNO( LA_ALIST ) LA_DCL
{
    RETINT(get_errno());
}
#line 82 "CSNOBOL4.lss"

/* fd_set holds a set of file descriptors. On 64 bit Linux, this is
 * a 128 byte object. This may be as little as 4 bytes on some systems
 * (which would limit the number of fd's to 32).
 */

static int sizeof_timeval(void)
{
    return sizeof (struct timeval);
}


/* SIZEOF_TIMEVAL()INTEGER */
SIZEOF_TIMEVAL( LA_ALIST ) LA_DCL
{
    RETINT(sizeof_timeval());
}
#line 94 "CSNOBOL4.lss"

static int set_timeval_(int sec, int usec)
{
    struct timeval *tv = get_p_();
    tv->tv_sec = sec;
    tv->tv_usec = usec;
}


/* SET_TIMEVAL_(INTEGER,INTEGER) */
SET_TIMEVAL_( LA_ALIST ) LA_DCL
{
    set_timeval_((int)LA_INT(0),(int)LA_INT(1));
    RETNULL;
}
#line 103 "CSNOBOL4.lss"

static int sizeof_fd_set(void)
{
    return sizeof (fd_set);
}


/* SIZEOF_FD_SET()INTEGER */
SIZEOF_FD_SET( LA_ALIST ) LA_DCL
{
    RETINT(sizeof_fd_set());
}
#line 110 "CSNOBOL4.lss"

static int fd_isset_(int fd)
{
    return FD_ISSET(fd, (fd_set *)get_p_());
}


/* FD_ISSET_(INTEGER)INTEGER */
FD_ISSET_( LA_ALIST ) LA_DCL
{
    RETINT(fd_isset_((int)LA_INT(0)));
}
#line 117 "CSNOBOL4.lss"

static void fd_zero_(void)
{
    FD_ZERO((fd_set *)get_p_());
}


/* FD_ZERO_() */
FD_ZERO_( LA_ALIST ) LA_DCL
{
    fd_zero_();
    RETNULL;
}
#line 124 "CSNOBOL4.lss"

static void fd_clr(int fd)
{
    FD_ClR(fd, (fd_set *)get_p_());
}


/* FD_CLR_(INTEGER) */
FD_CLR_( LA_ALIST ) LA_DCL
{
    fd_clr_((int)LA_INT(0));
    RETNULL;
}
#line 131 "CSNOBOL4.lss"

static void fd_set_(int fd)
{
    FD_SET(fd, (fd_set *)get_p_());
}


/* FD_SET_(INTEGER) */
FD_SET_( LA_ALIST ) LA_DCL
{
    fd_set_((int)LA_INT(0));
    RETNULL;
}
#line 138 "CSNOBOL4.lss"

static int clear_errno(void)
{
    errno = 0;
}


/* CLEAR_ERRNO() */
CLEAR_ERRNO( LA_ALIST ) LA_DCL
{
    clear_errno();
    RETNULL;
}
#line 145 "CSNOBOL4.lss"

static int waitpid_(int pid, int options)
{
    return waitpid(pid, &status, options);
}


/* WAITPID_(INTEGER,INTEGER)INTEGER */
WAITPID_( LA_ALIST ) LA_DCL
{
    RETINT(waitpid_((int)LA_INT(0),(int)LA_INT(1)));
}
#line 152 "CSNOBOL4.lss"

static int get_status(void)
{
    return status;
}


/* GET_STATUS()INTEGER */
GET_STATUS( LA_ALIST ) LA_DCL
{
    RETINT(get_status());
}
#line 159 "CSNOBOL4.lss"

static int format(char **in_s, char **fmt, char **buf, char **limit,
           char **base, int reps, int level)
{
    int w, r;
    char *bfmt = *fmt;
    char c;
    int aseen = 0;

    for (; reps; --reps) {
	for (*fmt = bfmt; **fmt;) {
	    while ((**fmt == ',') || (**fmt == ' ')) {
		++*fmt;
	    }
	    if (isdigit(**fmt)) {
		r = 0;
		while (isdigit(**fmt)) {
		    r = r * 10 + **fmt - '0';
		    ++*fmt;
		}
		r &= 0xff;
	    } else {
		r = -1;
	    }
	    c = **fmt;
	    ++*fmt;
	    switch (c) {
		case ',': break;
		case 'X':
		    if (r < 0) {
			r = 1;
		    }
		    for (; r; --r) {
			**buf = ' ';
			++*buf;
		    }
		    break;
		case 'A':
		    ++aseen;
		    if (isdigit(**fmt)) {
			w = 0;
			while (isdigit(**fmt)) {
			    w = w * 10 + **fmt - '0';
			    ++*fmt;
			}
		    } else {
			w = 1;
		    }
		    if (r < 0) {
			r = 1;
		    }
		    r *= w;
		    for (; r; --r) {
			if (**in_s == 0) {
			    break;
			}
			**buf = **in_s;
			++*buf;
			++*in_s;
		    }
		    for (; r; --r) {
			**buf = ' ';
			++*buf;
		    }
		    break;
		case '/':
		    if (r < 0) {
			r = 1;
		    }
		    for (; r; --r) {
			**buf = '\n';
			++*buf;
			*base = *buf;
		    }
		    break;
		case '\'':
		    for (;;) {
			if (**fmt == 0) {
			    fprintf(stderr,
                   "ftn_format: missing close \' in string constant\n");
			    return 1;
			}
			if (**fmt == '\'') {
			    ++*fmt;
			    if (**fmt == '\'') {
				**buf = '\'';
				++*buf;
				++*fmt;
			    } else {
				break;
			    }
			} else {
			    **buf = **fmt;
			    ++*buf;
			    ++*fmt;
			}
		    }
		    break;
		case 'H':
		    if (r == 0) {
			break;
		    }
		    for (; r; --r) {
			if (**fmt == 0) {
			    fprintf(stderr,
                          "ftn_format: Hollerith constant too short\n");
			    return 1;
			}
			**buf = **fmt;
			++*buf;
			++*fmt;
		    }
		    break;
		case 'T': /* T TL TR */
		    if (**fmt == 'R') {
			c = 'R';
			++*fmt;
		    } else if (**fmt == 'L') {
			c = 'L';
			++*fmt;
		    }
		    if (isdigit(**fmt)) {
			w = 0;
			while (isdigit(**fmt)) {
			    w = w * 10 + **fmt - '0';
			    ++*fmt;
			}
		    } else {
			w = 1;
		    }
		    if (c == 'L') {
			*buf -= w;
		    } else if (c == 'R') {
			*buf += w;
		    } else {
			*buf = *base + w - 1;
		    }
		    break;
		case ')':
		    if (**in_s == 0) {
			return 0;
		    }
		    if ((level == 1) && **in_s) {
			reps = 2;
			goto btm;
		    }
		    if ((level > 1) && (reps > 1)) {
			goto btm;
		    }
		    if ((level > 1) && (reps < 0) && (aseen == 0)) {
			return 0;
		    }
		    goto btm;
		    return 0;
		case '(':
		    r = format(in_s, fmt, buf, limit, base,
			       r, level + 1);
		    if (r) {
			return r;
		    }
		    break;
		default:
		    if (c == 0) {
			fprintf(stderr,
                               "ftn_format: premature end of format\n");
		    } else {
			fprintf(stderr,
                           "ftn_format: bad format character: %c\n", c);
		    }
		    return 1;
	    }
	    if (*limit < *buf) {
		*limit = *buf;
	    }
	}
btm: ;
    }
    return 0;
}

static char *ftn_format(char *s, char *f)
{
    char *in_s, *fmt, *buf, *limit, *base, *b;
    int r;

    /* format state */
    base = malloc(4096);
    fmt = f;
    in_s = s;
    buf = base;
    limit = base;
    b = base;

    for (r = 0; r < 4096; ++r) {
	base[r] = ' ';
    }
    if (*fmt != '(') {
	fprintf(stderr, "ftn_format: missing begin (\n");
	goto err;
    }
    if (*(fmt + strlen(fmt) - 1)  != ')') {
	fprintf(stderr, "ftn_format: missing end )\n");
	goto err;
    }

    ++fmt;
    r = format(&in_s, &fmt, &buf, &limit, &b, 1, 1);
    if (r == 0) {
	*limit = 0;
	return base;
    }
err:
    free(base);
    return NULL;
}

/* FTN_FORMAT(STRING,STRING)STRING_FREE
 *
 * First STRING is the FORMAT, second is the FORMAT
 */
FTN_FORMAT( LA_ALIST ) LA_DCL
{
    char *result;
    char data[4096];
    char format[1024];
    getstring(LA_PTR(0), format, sizeof(format));
    getstring(LA_PTR(1), data, sizeof(data));
    result = ftn_format(data, format);
    if (result == NULL)
	RETFAIL;
    RETSTR_FREE(result);
}
