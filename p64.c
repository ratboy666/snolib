#line 109 "P64.lss"
/* Generated by WRAPPER on 06/05/2014 15:07:58 */

#include "config.h"
#include "h.h"
#include "snotypes.h"
#include "macros.h"
#include "load.h"
#include "equ.h"
#include <string.h>

#line 110 "P64.lss"

#include <stdlib.h>
#include <string.h>

static void *p;
static void *p2;
static void *p3;
static void *p4;
static float f;
static double d;
static long double ld;

void *get_p_(void) { return p; }
void *get_p2_(void) { return p2; }
float get_f_(void) { return f; }
double get_d_(void) { return d; }
long double get_ld_(void) { return ld; }
void set_p_(void *v) { p = v; }
void set_p2_(void *v) { p2 = v; }
void set_f_(float v) { f = v; }
void set_d_(double v) { d = v; }
void set_ld_(long double v) { ld = v; }


static int get_phi(void)
{
    long n = (long)p;
    return (int)(n >> 32);
}


/* GET_PHI()INTEGER */
GET_PHI( LA_ALIST ) LA_DCL
{
    RETINT(get_phi());
}
#line 142 "P64.lss"

static int get_plo(void)
{
    long n = (long)p;
    return (int)(n & 0xffffffff);
}


/* GET_PLO()INTEGER */
GET_PLO( LA_ALIST ) LA_DCL
{
    RETINT(get_plo());
}
#line 150 "P64.lss"

static void set_phi(int h)
{
    long n = (long)p;
    n &= 0xffffffff;
    p = (void *)(((long)h << 32) | n);
}


/* SET_PHI(INTEGER) */
SET_PHI( LA_ALIST ) LA_DCL
{
    set_phi((int)LA_INT(0));
    RETNULL;
}
#line 159 "P64.lss"

static void set_plo(int l)
{
    long n = (long)p;
    n &= 0xffffffff00000000L;
    p = (void *)(n | (unsigned)l);
}


/* SET_PLO(INTEGER) */
SET_PLO( LA_ALIST ) LA_DCL
{
    set_plo((int)LA_INT(0));
    RETNULL;
}
#line 168 "P64.lss"



static void p_to_p2(void) { p2 = p; }


/* P_TO_P2() */
P_TO_P2( LA_ALIST ) LA_DCL
{
    p_to_p2();
    RETNULL;
}
#line 186 "P64.lss"

static void p_to_p3(void) { p3 = p; }


/* P_TO_P3() */
P_TO_P3( LA_ALIST ) LA_DCL
{
    p_to_p3();
    RETNULL;
}
#line 190 "P64.lss"

static void p_to_p4(void) { p4 = p; }


/* P_TO_P4() */
P_TO_P4( LA_ALIST ) LA_DCL
{
    p_to_p4();
    RETNULL;
}
#line 194 "P64.lss"

static void p2_to_p(void) { p = p2; }


/* P2_TO_P() */
P2_TO_P( LA_ALIST ) LA_DCL
{
    p2_to_p();
    RETNULL;
}
#line 198 "P64.lss"

static void p3_to_p(void) { p = p3; }


/* P3_TO_P() */
P3_TO_P( LA_ALIST ) LA_DCL
{
    p3_to_p();
    RETNULL;
}
#line 202 "P64.lss"

static void p4_to_p(void) { p = p4; }


/* P4_TO_P() */
P4_TO_P( LA_ALIST ) LA_DCL
{
    p4_to_p();
    RETNULL;
}
#line 206 "P64.lss"

static void set_f(double v) { f = v; }


/* SET_F(REAL) */
SET_F( LA_ALIST ) LA_DCL
{
    set_f((double)LA_REAL(0));
    RETNULL;
}
#line 210 "P64.lss"

static void set_d(double v) { d = v; }


/* SET_D(REAL) */
SET_D( LA_ALIST ) LA_DCL
{
    set_d((double)LA_REAL(0));
    RETNULL;
}
#line 214 "P64.lss"

static void set_ld(double v) { ld = v; }


/* SET_LD(REAL) */
SET_LD( LA_ALIST ) LA_DCL
{
    set_ld((double)LA_REAL(0));
    RETNULL;
}
#line 218 "P64.lss"

static float get_f(void) { return f; }


/* GET_F()REAL */
GET_F( LA_ALIST ) LA_DCL
{
    RETREAL(get_f());
}
#line 222 "P64.lss"

static double get_d(void) { return d; }


/* GET_D()REAL */
GET_D( LA_ALIST ) LA_DCL
{
    RETREAL(get_d());
}
#line 226 "P64.lss"

static double get_ld(void) { return ld; }


/* GET_LD()REAL */
GET_LD( LA_ALIST ) LA_DCL
{
    RETREAL(get_ld());
}
#line 230 "P64.lss"

static char *get_s(void) { return (char *)p; }


/* GET_S()STRING */
GET_S( LA_ALIST ) LA_DCL
{
    RETSTR((char *)get_s());
}
#line 234 "P64.lss"

static void swap_p(void)
{
    void *t = p2;
    p2 = p;
    p = t;
}


/* SWAP_P() */
SWAP_P( LA_ALIST ) LA_DCL
{
    swap_p();
    RETNULL;
}
#line 243 "P64.lss"


static void peek_p_(void) { p = *(void **)p; }


/* PEEK_P_() */
PEEK_P_( LA_ALIST ) LA_DCL
{
    peek_p_();
    RETNULL;
}
#line 249 "P64.lss"

static int peek_c_(void) { return *(char *)p; }


/* PEEK_C_()INTEGER */
PEEK_C_( LA_ALIST ) LA_DCL
{
    RETINT(peek_c_());
}
#line 253 "P64.lss"

static int peek_s_(void) { return *(short *)p; }


/* PEEK_S_()INTEGER */
PEEK_S_( LA_ALIST ) LA_DCL
{
    RETINT(peek_s_());
}
#line 257 "P64.lss"

static int peek_i_(void) { return *(int *)p; }


/* PEEK_I_()INTEGER */
PEEK_I_( LA_ALIST ) LA_DCL
{
    RETINT(peek_i_());
}
#line 261 "P64.lss"

static void peek_d_(void) { d =  *(double *)p; }


/* PEEK_D_() */
PEEK_D_( LA_ALIST ) LA_DCL
{
    peek_d_();
    RETNULL;
}
#line 265 "P64.lss"

static void peek_f_(void) { f = *(float *)p; }


/* PEEK_F_() */
PEEK_F_( LA_ALIST ) LA_DCL
{
    peek_f_();
    RETNULL;
}
#line 269 "P64.lss"

static void peek_ld_(void) { ld = *(long double *)p; }


/* PEEK_LD_() */
PEEK_LD_( LA_ALIST ) LA_DCL
{
    peek_ld_();
    RETNULL;
}
#line 273 "P64.lss"

static void poke_p_(void) { *(void **)p = p2; }


/* POKE_P_() */
POKE_P_( LA_ALIST ) LA_DCL
{
    poke_p_();
    RETNULL;
}
#line 277 "P64.lss"

static void poke_c_(int c) { *(char *)p = (char)c; }


/* POKE_C_(INTEGER) */
POKE_C_( LA_ALIST ) LA_DCL
{
    poke_c_((int)LA_INT(0));
    RETNULL;
}
#line 281 "P64.lss"

static void poke_s_(int s) { *(short *)p = (short)s; }


/* POKE_S_(INTEGER) */
POKE_S_( LA_ALIST ) LA_DCL
{
    poke_s_((int)LA_INT(0));
    RETNULL;
}
#line 285 "P64.lss"

static void poke_i_(int i) { *(int *)p = (int)i; }


/* POKE_I_(INTEGER) */
POKE_I_( LA_ALIST ) LA_DCL
{
    poke_i_((int)LA_INT(0));
    RETNULL;
}
#line 289 "P64.lss"

static void poke_d_(void) { *(double *)p = d; }


/* POKE_D_() */
POKE_D_( LA_ALIST ) LA_DCL
{
    poke_d_();
    RETNULL;
}
#line 293 "P64.lss"

static void poke_f_(void) { *(float *)p = f; }


/* POKE_F_() */
POKE_F_( LA_ALIST ) LA_DCL
{
    poke_f_();
    RETNULL;
}
#line 297 "P64.lss"

static void poke_ld_(void) { *(long double *)p = ld; }


/* POKE_LD_() */
POKE_LD_( LA_ALIST ) LA_DCL
{
    poke_ld_();
    RETNULL;
}
#line 301 "P64.lss"

static void malloc_(int n) { p = malloc(n); }


/* MALLOC_(INTEGER) */
MALLOC_( LA_ALIST ) LA_DCL
{
    malloc_((int)LA_INT(0));
    RETNULL;
}
#line 305 "P64.lss"

static void free_(void) { free(p); }


/* FREE_() */
FREE_( LA_ALIST ) LA_DCL
{
    free_();
    RETNULL;
}
#line 309 "P64.lss"

static int strdup_(char *s) { p = strdup(s); }


/* STRDUP_(STRING) */
STRDUP_( LA_ALIST ) LA_DCL
{
    char arg0[1024];
    getstring(LA_PTR(0), arg0, sizeof(arg0));
    strdup_(arg0);
    RETNULL;
}
#line 313 "P64.lss"

static int strlen_(void) { return strlen((char *)p); }


/* STRLEN_()INTEGER */
STRLEN_( LA_ALIST ) LA_DCL
{
    RETINT(strlen_());
}
#line 317 "P64.lss"



