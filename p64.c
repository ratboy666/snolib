#line 36 "P64.lss"
/* Generated by WRAPPER on 06/16/2014 00:31:41 */

#include "config.h"
#include "h.h"
#include "snotypes.h"
#include "macros.h"
#include "load.h"
#include "equ.h"
#include <string.h>

#line 37 "P64.lss"

#include <stdlib.h>
#include <string.h>

static long peek_p(long p) { return (long)*(void **)p; }


/* PEEK_P(LONG)LONG */
PEEK_P( LA_ALIST ) LA_DCL
{
    RETINT(peek_p((long)LA_INT(0)));
}
#line 44 "P64.lss"

static long peek_c(long p) { return *(char *)p; }


/* PEEK_C(LONG)INTEGER */
PEEK_C( LA_ALIST ) LA_DCL
{
    RETINT(peek_c((long)LA_INT(0)));
}
#line 48 "P64.lss"

static long peek_s(long p) { return *(short *)p; }


/* PEEK_S(LONG)INTEGER */
PEEK_S( LA_ALIST ) LA_DCL
{
    RETINT(peek_s((long)LA_INT(0)));
}
#line 52 "P64.lss"

static long peek_i(long p) { return *(int *)p; }


/* PEEK_I(LONG)INTEGER */
PEEK_I( LA_ALIST ) LA_DCL
{
    RETINT(peek_i((long)LA_INT(0)));
}
#line 56 "P64.lss"

static double peek_d(long p) { return *(double *)p; }


/* PEEK_D(LONG)REAL */
PEEK_D( LA_ALIST ) LA_DCL
{
    RETREAL(peek_d((long)LA_INT(0)));
}
#line 60 "P64.lss"

static double peek_f(long p) { return *(float *)p; }


/* PEEK_F(LONG)REAL */
PEEK_F( LA_ALIST ) LA_DCL
{
    RETREAL(peek_f((long)LA_INT(0)));
}
#line 64 "P64.lss"

static double peek_ld(long p) { return *(long double *)p; }


/* PEEK_LD(LONG)REAL */
PEEK_LD( LA_ALIST ) LA_DCL
{
    RETREAL(peek_ld((long)LA_INT(0)));
}
#line 68 "P64.lss"

static void poke_p(long p, long v) { *(void **)p = (void *)v; }


/* POKE_P(LONG,LONG) */
POKE_P( LA_ALIST ) LA_DCL
{
    poke_p((long)LA_INT(0),(long)LA_INT(1));
    RETNULL;
}
#line 72 "P64.lss"

static void poke_c(long p, int c) { *(char *)p = (char)c; }


/* POKE_C(LONG,INTEGER) */
POKE_C( LA_ALIST ) LA_DCL
{
    poke_c((long)LA_INT(0),(int)LA_INT(1));
    RETNULL;
}
#line 76 "P64.lss"

static void poke_s(long p, int s) { *(short *)p = (short)s; }


/* POKE_S(LONG,INTEGER) */
POKE_S( LA_ALIST ) LA_DCL
{
    poke_s((long)LA_INT(0),(int)LA_INT(1));
    RETNULL;
}
#line 80 "P64.lss"

static void poke_i(long p, int i) { *(int *)p = (int)i; }


/* POKE_I(LONG,INTEGER) */
POKE_I( LA_ALIST ) LA_DCL
{
    poke_i((long)LA_INT(0),(int)LA_INT(1));
    RETNULL;
}
#line 84 "P64.lss"

static void poke_d(long p, double v) { *(double *)p = v; }


/* POKE_D(LONG,REAL) */
POKE_D( LA_ALIST ) LA_DCL
{
    poke_d((long)LA_INT(0),(double)LA_REAL(1));
    RETNULL;
}
#line 88 "P64.lss"

static void poke_f(long p, double v) { *(float *)p = v; }


/* POKE_F(LONG,REAL) */
POKE_F( LA_ALIST ) LA_DCL
{
    poke_f((long)LA_INT(0),(double)LA_REAL(1));
    RETNULL;
}
#line 92 "P64.lss"

static void poke_ld(long p, double v) { *(long double *)p = v; }


/* POKE_LD(LONG,REAL) */
POKE_LD( LA_ALIST ) LA_DCL
{
    poke_ld((long)LA_INT(0),(double)LA_REAL(1));
    RETNULL;
}
#line 96 "P64.lss"

static long malloc_(int n) { return (long)malloc(n); }


/* MALLOC_(INTEGER)LONG */
MALLOC_( LA_ALIST ) LA_DCL
{
    RETINT(malloc_((int)LA_INT(0)));
}
#line 100 "P64.lss"

static void free_(long p) { free((void *)p); }


/* FREE_(LONG) */
FREE_( LA_ALIST ) LA_DCL
{
    free_((long)LA_INT(0));
    RETNULL;
}
#line 104 "P64.lss"

static long strdup_(char *s) { return (long)strdup(s); }


/* STRDUP_(STRING)LONG */
STRDUP_( LA_ALIST ) LA_DCL
{
    char arg0[1024];
    getstring(LA_PTR(0), arg0, sizeof(arg0));
    RETINT(strdup_(arg0));
}
#line 108 "P64.lss"

static long strlen_(long p) { return strlen((char *)p); }


/* STRLEN_(LONG)INTEGER */
STRLEN_( LA_ALIST ) LA_DCL
{
    RETINT(strlen_((long)LA_INT(0)));
}
#line 112 "P64.lss"

