#line 41 "FFI.lss"
/* Generated by WRAPPER on 06/09/2014 13:53:10 */

#include "config.h"
#include "h.h"
#include "snotypes.h"
#include "macros.h"
#include "load.h"
#include "equ.h"
#include <string.h>

#line 42 "FFI.lss"

#include <ffi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

static int errors;
static ffi_status ffi_error;

#line 69 "FFI.lss"

static void *interpret_ptype(char **s)
{
    int w = 32;
    int t = 2;
    if (**s == ',')
	++(*s);
    if (**s == 0)
	return NULL;
    for (; **s && (**s != ','); ++(*s)) {
	switch (**s) {
	case ' ':
	case '3':
	case '6':         break;
	case 'v':
	case 'V': t =  0; break;
	case 'u':
	case 'U': t =  1; break;
	case 's':
	case 'S': t =  2; break;
	case 'f':
	case 'F': t =  3; break;
	case 'd':
	case 'D': t =  4; break;
	case 'p':
	case 'P': t =  5; break;
	case 'e':
	case 'E': t =  6; break;
	case 'c':
	case 'C':
	case '8': w =  8; break;
	case '1': w = 16; break;
	case 'i':
	case 'I':
	case '2': w = 32; break;
	case 'l':
	case 'L':
	case '4': w = 64; break;
	default: ++errors; return NULL;
	}
    }
    switch (t) {
    case 0: return &ffi_type_void;
    case 1: switch (w) {
	    case  8: return &ffi_type_uint8;
	    case 16: return &ffi_type_uint16;
	    case 32: return &ffi_type_uint32;
	    case 64: return &ffi_type_uint64;
	    default: ++errors; return NULL;
	    }
    case 2: switch (w) {
	    case  8: return &ffi_type_sint8;
	    case 16: return &ffi_type_sint16;
	    case 32: return &ffi_type_sint32;
	    case 64: return &ffi_type_sint64;
	    default: +errors; return NULL;
	    }
    case 3: return &ffi_type_float;
    case 4: return &ffi_type_double;
    case 5: return &ffi_type_pointer;
    case 6: return &ffi_type_longdouble;
    default: ++errors; return NULL;
    }
    ++errors;
    return NULL;
}

#line 145 "FFI.lss"

typedef struct {
    ffi_cif *cif;
    ffi_type **arg_types;
    ffi_arg *arg_values;
    void **arg_ptrs;
    int *arg_needfree;
    ffi_type *result_type;
    ffi_arg result;
    int nargs;
    void *callp;
} ffi_t;

#line 164 "FFI.lss"

static long ffi_new(char *r, char *s)
{
    ffi_t *ffip;
    int n = 0;
    char *s2 = s;
    ffi_error = FFI_OK;
    ffip = malloc(sizeof(ffi_t));
    if (ffip == NULL) {
	return 0;
    }
    ffip->result_type = interpret_ptype(&r);
    if (ffip->result_type == NULL) {
	return 0;
    }
    errors = 0;
    while (interpret_ptype(&s)) {
	++n;
	if (errors)
	    return 0;
    }
    ffip->nargs = n;
    if (n == 0)
	n = 1;
    ffip->cif = malloc(sizeof(ffi_cif));
    ffip->arg_types = malloc((n + 1) * (sizeof(ffi_type *)));
    ffip->arg_values = malloc((n + 1) * (sizeof(ffi_arg)));
    ffip->arg_needfree = malloc((n + 1) * (sizeof(int)));
    ffip->arg_ptrs = malloc((n + 1) * (sizeof(void *)));
    if ((ffip->arg_types == NULL) ||
	(ffip->arg_values == NULL) ||
	(ffip->arg_ptrs == NULL) ||
	(ffip->arg_needfree == NULL) ||
	(ffip->cif == NULL))
	return 0;
    s = s2;
    n = 0;
    while ((ffip->arg_types[n] = interpret_ptype(&s)) != NULL) {
	ffip->arg_ptrs[n] = &ffip->arg_values[n];
	ffip->arg_needfree[n] = 0;
	++n;
    }
    ffi_error = ffi_prep_cif(ffip->cif,
			     FFI_DEFAULT_ABI,
			     ffip->nargs,
			     ffip->result_type,
			     ffip->arg_types);
    if (ffi_error != FFI_OK)
	return 0;
    return (long)ffip;
}


/* FFI_NEW(STRING,STRING)LONG */
FFI_NEW( LA_ALIST ) LA_DCL
{
    char arg0[1024];
    char arg1[1024];
    getstring(LA_PTR(0), arg0, sizeof(arg0));
    getstring(LA_PTR(1), arg1, sizeof(arg1));
    RETINT(ffi_new(arg0,arg1));
}
#line 217 "FFI.lss"

#line 224 "FFI.lss"

static void ffi_clear(long p)
{
    ffi_t *ffip = (void *)p;
    int i;
    for (i = 0; i < ffip->nargs; ++i) {
	if (ffip->arg_needfree[i]) {
	    free((void *)ffip->arg_values[i]);
	    ffip->arg_needfree[i] = 0;
	}
    }
}


/* FFI_CLEAR(LONG) */
FFI_CLEAR( LA_ALIST ) LA_DCL
{
    ffi_clear((long)LA_INT(0));
    RETNULL;
}
#line 238 "FFI.lss"

#line 244 "FFI.lss"

static void ffi_free(long p)
{
    ffi_t *ffip = (void *)p;
    free(ffip->arg_values);
    free(ffip->arg_types);
    free(ffip->arg_needfree);
    free(ffip->cif);
    free(ffip);
}


/* FFI_FREE(LONG) */
FFI_FREE( LA_ALIST ) LA_DCL
{
    ffi_free((long)LA_INT(0));
    RETNULL;
}
#line 256 "FFI.lss"

#line 263 "FFI.lss"

static int ffi_par_n_needfree(long p,int n)
{
    ffi_t *ffip = (void *)p;
    if ((n < 1) || (n > ffip->nargs))
	return 0;
    ffip->arg_needfree[n - 1] = 1;
    return 1;
}


/* FFI_PAR_N_NEEDFREE(LONG,INTEGER)PREDICATE */
FFI_PAR_N_NEEDFREE( LA_ALIST ) LA_DCL
{
    if (ffi_par_n_needfree((long)LA_INT(0),(int)LA_INT(1)))
	RETNULL;
    RETFAIL;
}
#line 275 "FFI.lss"

#line 281 "FFI.lss"

static int ffi_par_n_integer(long p, int n, int v)
{
    ffi_t *ffip = (void *)p;
    if ((n < 1) || (n > ffip->nargs))
	return 0;
    ffip->arg_values[n - 1] = v;
    return 1;
}


/* FFI_PAR_N_INTEGER(LONG,INTEGER,INTEGER)PREDICATE */
FFI_PAR_N_INTEGER( LA_ALIST ) LA_DCL
{
    if (ffi_par_n_integer((long)LA_INT(0),(int)LA_INT(1),(int)LA_INT(2)))
	RETNULL;
    RETFAIL;
}
#line 293 "FFI.lss"

#line 300 "FFI.lss"

static int ffi_par_n_real(long p, int n, double v)
{
    ffi_t *ffip = (void *)p;
    if ((n < 1) || (n > ffip->nargs))
	return 0;
    ffip->arg_values[n - 1] = v;
    return 1;
}


/* FFI_PAR_N_REAL(LONG,INTEGER,REAL)PREDICATE */
FFI_PAR_N_REAL( LA_ALIST ) LA_DCL
{
    if (ffi_par_n_real((long)LA_INT(0),(int)LA_INT(1),(double)LA_REAL(2)))
	RETNULL;
    RETFAIL;
}
#line 312 "FFI.lss"

#line 319 "FFI.lss"

static int ffi_par_n_ptr(long p, int n, long p2)
{
    ffi_t *ffip = (void *)p;
    if ((n < 1) || (n > ffip->nargs))
	return 0;
    ffip->arg_values[n - 1] = (long)p2;
    return 1;
}


/* FFI_PAR_N_PTR(LONG,INTEGER,LONG)PREDICATE */
FFI_PAR_N_PTR( LA_ALIST ) LA_DCL
{
    if (ffi_par_n_ptr((long)LA_INT(0),(int)LA_INT(1),(long)LA_INT(2)))
	RETNULL;
    RETFAIL;
}
#line 331 "FFI.lss"

#line 337 "FFI.lss"

static int ffi_par_n_f(long p, int n, double f)
{
    ffi_t *ffip = (void *)p;
    if ((n < 1) || (n > ffip->nargs))
	return 0;
    ffip->arg_values[n - 1] = (float)f;
    return 1;
}


/* FFI_PAR_N_F(LONG,INTEGER,REAL)PREDICATE */
FFI_PAR_N_F( LA_ALIST ) LA_DCL
{
    if (ffi_par_n_f((long)LA_INT(0),(int)LA_INT(1),(double)LA_REAL(2)))
	RETNULL;
    RETFAIL;
}
#line 349 "FFI.lss"

#line 355 "FFI.lss"

static int ffi_par_n_d(long p, int n, double d)
{
    ffi_t *ffip = (void *)p;
    if ((n < 1) || (n > ffip->nargs))
	return 0;
    ffip->arg_values[n - 1] = (double)d;
    return 1;
}


/* FFI_PAR_N_D(LONG,INTEGER,REAL)PREDICATE */
FFI_PAR_N_D( LA_ALIST ) LA_DCL
{
    if (ffi_par_n_d((long)LA_INT(0),(int)LA_INT(1),(double)LA_REAL(2)))
	RETNULL;
    RETFAIL;
}
#line 367 "FFI.lss"

#line 373 "FFI.lss"

static int ffi_par_n_ld(long p, int n, double d)
{
    ffi_t *ffip = (void *)p;
    if ((n < 1) || (n > ffip->nargs))
	return 0;
    ffip->arg_values[n - 1] = (long double)d;
    return 1;
}


/* FFI_PAR_N_LD(LONG,INTEGER,REAL)PREDICATE */
FFI_PAR_N_LD( LA_ALIST ) LA_DCL
{
    if (ffi_par_n_ld((long)LA_INT(0),(int)LA_INT(1),(double)LA_REAL(2)))
	RETNULL;
    RETFAIL;
}
#line 385 "FFI.lss"

#line 392 "FFI.lss"

static int ffi_par_n_string(long p, int n, char *s)
{
    ffi_t *ffip = (void *)p;
    if ((n < 1) || (n > ffip->nargs))
        return 0;
    ffip->arg_values[n - 1] = (long)strdup(s);
    if (ffip->arg_values[n - 1] == (long)NULL)
        return 0;
    ffip->arg_needfree[n - 1] = 1;
    return 1;
}


/* FFI_PAR_N_STRING(LONG,INTEGER,STRING)PREDICATE */
FFI_PAR_N_STRING( LA_ALIST ) LA_DCL
{
    char arg2[1024];
    getstring(LA_PTR(2), arg2, sizeof(arg2));
    if (ffi_par_n_string((long)LA_INT(0),(int)LA_INT(1),arg2))
	RETNULL;
    RETFAIL;
}
#line 407 "FFI.lss"

#line 413 "FFI.lss"

/* CIF in P2, FN in P */
static void ffi_set_callp(long p2, long p)
{
    ffi_t *ffip = (void *)p2;
    ffip->callp = (void *)p;
}


/* FFI_SET_CALLP(LONG,LONG) */
FFI_SET_CALLP( LA_ALIST ) LA_DCL
{
    ffi_set_callp((long)LA_INT(0),(long)LA_INT(1));
    RETNULL;
}
#line 422 "FFI.lss"

#line 428 "FFI.lss"

static void call_ffi(long p)
{
    ffi_t *ffip = (void *)p;
    ffi_call(ffip->cif, FFI_FN(ffip->callp),
	     &ffip->result, ffip->arg_ptrs);
}


/* CALL_FFI(LONG) */
CALL_FFI( LA_ALIST ) LA_DCL
{
    call_ffi((long)LA_INT(0));
    RETNULL;
}
#line 437 "FFI.lss"

/* Return address of call result, use peek_() function to retrieve */
static long ffi_resultp(long p)
{
    ffi_t *ffip = (void *)p;
    return (long)(&(ffip->result));
}


/* FFI_RESULTP(LONG)LONG */
FFI_RESULTP( LA_ALIST ) LA_DCL
{
    RETINT(ffi_resultp((long)LA_INT(0)));
}
#line 446 "FFI.lss"

#line 453 "FFI.lss"

static int call_integer_ffi(long p)
{
    ffi_t *ffip = (void *)p;
    ffi_call(ffip->cif, FFI_FN(ffip->callp),
	     &ffip->result, ffip->arg_ptrs);
    return ffip->result;
}


/* CALL_INTEGER_FFI(LONG)INTEGER */
CALL_INTEGER_FFI( LA_ALIST ) LA_DCL
{
    RETINT(call_integer_ffi((long)LA_INT(0)));
}
#line 463 "FFI.lss"

static long call_ptr_ffi(long p)
{
    ffi_t *ffip = (void *)p;
    ffi_call(ffip->cif, FFI_FN(ffip->callp),
	     &ffip->result, ffip->arg_ptrs);
    return ffip->result;
}


/* CALL_PTR_FFI(LONG)LONG */
CALL_PTR_FFI( LA_ALIST ) LA_DCL
{
    RETINT(call_ptr_ffi((long)LA_INT(0)));
}
#line 473 "FFI.lss"

static double call_real_ffi(long p)
{
    ffi_t *ffip = (void *)p;
    ffi_call(ffip->cif, FFI_FN(ffip->callp),
	     &ffip->result, ffip->arg_ptrs);
    return ffip->result;
}


/* CALL_REAL_FFI(LONG)REAL */
CALL_REAL_FFI( LA_ALIST ) LA_DCL
{
    RETREAL(call_real_ffi((long)LA_INT(0)));
}
#line 483 "FFI.lss"

static char *call_string_ffi(long p)
{
    ffi_t *ffip = (void *)p;
    ffi_call(ffip->cif, FFI_FN(ffip->callp),
	     &ffip->result, ffip->arg_ptrs);
    return (char *)ffip->result;
}


/* CALL_STRING_FFI(LONG)STRING */
CALL_STRING_FFI( LA_ALIST ) LA_DCL
{
    RETSTR((char *)call_string_ffi((long)LA_INT(0)));
}
#line 493 "FFI.lss"

#line 501 "FFI.lss"

/* DL functions
 */
static long dlopen_(char *s, int n) { return (long)dlopen(s, n); }


/* DLOPEN_(STRING,INTEGER)LONG */
DLOPEN_( LA_ALIST ) LA_DCL
{
    char arg0[1024];
    getstring(LA_PTR(0), arg0, sizeof(arg0));
    RETINT(dlopen_(arg0,(int)LA_INT(1)));
}
#line 507 "FFI.lss"

static char *dlerror_(void)
{
    char *s = dlerror();
    if (s == NULL) return "";
    return s;
}


/* DLERROR_()STRING */
DLERROR_( LA_ALIST ) LA_DCL
{
    RETSTR((char *)dlerror_());
}
#line 516 "FFI.lss"

static long dlsym_(long p, char *s)
{
    return (long)dlsym((void *)p, s);
}


/* DLSYM_(LONG,STRING)LONG */
DLSYM_( LA_ALIST ) LA_DCL
{
    char arg1[1024];
    getstring(LA_PTR(1), arg1, sizeof(arg1));
    RETINT(dlsym_((long)LA_INT(0),arg1));
}
#line 523 "FFI.lss"

static int dlclose_(long p) { return dlclose((void *)p); }


/* DLCLOSE_(LONG)INTEGER */
DLCLOSE_( LA_ALIST ) LA_DCL
{
    RETINT(dlclose_((long)LA_INT(0)));
}
#line 527 "FFI.lss"

