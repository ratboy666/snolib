/* unix.c
 *
 * LOAD() functions for unix support. Most functions are defined
 * with FFI, but some things cannot be expressed with FFI.
 *
 * Access to errno, waitpid, fd_set (file descriptor sets), along
 * with the size of int, long, timeval, fd_set. fd sets are here
 * because they they are likely macros.
 *
 * gcc -shared -I /usr/local/lib/snobol4/1.5+/include -fPIC -O3 -o unix.so unix.c
 */

#include "config.h"
#include "h.h"
#include "snotypes.h"
#include "macros.h"
#include "load.h"
#include "equ.h"

#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

static int status;

/* SIZEOF_INT()INTEGER */
SIZEOF_INT( LA_ALIST ) LA_DCL
{
    RETINT((int)sizeof (int));
}

/* SIZEOF_LONG()INTEGER */
SIZEOF_LONG( LA_ALIST ) LA_DCL
{
    RETINT((int)sizeof (long));
}

/* GET_ERRNO()INTEGER */
GET_ERRNO( LA_ALIST ) LA_DCL
{
    RETINT((int)errno);
}

/* CLEAR_ERRNO() */
CLEAR_ERRNO( LA_ALIST ) LA_DCL
{
    errno = 0;
    RETNULL;
}

/* SIZEOF_TIMEVAL()INTEGER */
SIZEOF_TIMEVAL( LA_ALIST ) LA_DCL
{
    RETINT((int)sizeof (struct timeval));
}

/* SET_TIMEVAL(LONG,INTEGER,INTEGER) */
SET_TIMEVAL( LA_ALIST ) LA_DCL
{
    struct timeval *tv = (void *)(long)LA_INT(0);
    tv->tv_sec = (long)LA_INT(1);
    tv->tv_usec = (long)LA_INT(2);
    RETNULL;
}

/* SIZEOF_FD_SET()INTEGER */
SIZEOF_FD_SET( LA_ALIST ) LA_DCL
{
    RETINT((int)sizeof (fd_set));
}

/* FD_ISSET_(INTEGER,LONG)INTEGER */
FD_ISSET_( LA_ALIST ) LA_DCL
{
    RETINT((int)FD_ISSET(
			    (int)LA_INT(0),
			    (fd_set *)(long)LA_INT(1)
			));
}

/* FD_ZERO_(LONG) */
FD_ZERO_( LA_ALIST ) LA_DCL
{
    FD_ZERO((fd_set *)(long)LA_INT(0));
    RETNULL;
}

/* FD_CLR_(INTEGER,LONG) */
FD_CLR_( LA_ALIST ) LA_DCL
{
    FD_CLR(
	    (int)LA_INT(0),
	    (fd_set *)(long)LA_INT(1)
	  );
    RETNULL;
}

/* FD_SET_(INTEGER,LONG) */
FD_SET_( LA_ALIST ) LA_DCL
{
    FD_SET(
	    (int)LA_INT(0),
	    (fd_set *)(long)LA_INT(1)
	  );
    RETNULL;
}

/* WAITPID(INTEGER,INTEGER)INTEGER */
WAITPID( LA_ALIST ) LA_DCL
{
    RETINT((int)waitpid((int)LA_INT(0), &status, (int)LA_INT(1)));
}

/* GET_STATUS()INTEGER */
GET_STATUS( LA_ALIST ) LA_DCL
{
    RETINT(status);
}
