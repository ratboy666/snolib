/* $Id: main.c,v 1.15 2011/02/16 19:56:08 phil Exp $ */

/* snobol4 main program (make this mlink.c??) */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H defined */

# ifdef HAVE_STDLIB_H
# include <stdlib.h>			/* for malloc */
# endif /* HAVE_STDLIB_H defined */

# include <stdio.h>			/* for lib.h */
# include "h.h"
# include "snotypes.h"
# include "lib.h"			/* version() */
# include "gen.h"
# include "macros.h"

# if defined(ENDEX_LONGJMP) || defined(NO_STATIC_VARS)
# include "equ.h"
# include "res.h"
# endif /* defined(ENDEX_LONGJMP) || defined(NO_STATIC_VARS) */

# ifdef ENDEX_LONGJMP
# include <setjmp.h>
# ifndef NO_STATIC_VARS
jmp_buf endex_jmpbuf;
# endif /* NO_STATIC_VARS not defined */
# endif /* ENDEX_LONGJMP defined */

# ifdef NO_STATIC_VARS
# include "vars.h"
struct vars *varp;
# undef argc
# undef argv
# endif /* NO_STATIC_VARS defined */

# include "proc.h"			/* BEGIN() */

# include "equ.h"			/* for res.h */
# include "data.h"
# include "res.h"			/* BANRCL */
# include "version.h"			/* VERSION, VERSION_DATE */

const char vers[] = VERSION;
const char vdate[] = VERSION_DATE;
const char snoname[] = "CSNOBOL4";

int
main(argc, argv)
    int argc;
    char *argv[];
{
# ifdef NO_STATIC_VARS
# ifdef ENDEX_LONGJMP
    jmp_buf _endex_jmpbuf;
# endif /* ENDEX_LONGJMP defined */

    varp = (struct vars *)malloc(sizeof(struct vars));
    if (!varp) {
	perror("could not allocate vars");
	exit(1);
    }
# ifdef ENDEX_LONGJMP
    varp->v_endex_jmpbuf = _endex_jmpbuf;
# endif /* ENDEX_LONGJMP defined */
# endif /* NO_STATIC_VARS defined */
    init_data();
    init_syntab();
    init_args( argc, argv );

    if( D_A(BANRCL) != 0 ) {
	io_printf(D_A(PUNCH),
"The Macro Implementation of SNOBOL4 in C (%s) Version %s\n", snoname, vers);
	io_printf(D_A(PUNCH), "    by Philip L. Budne, %s\n", vdate);
	io_printf(D_A(PUNCH), "    Patch Fridtjof Weigel\n");
    }

# ifdef ENDEX_LONGJMP
    if (setjmp(endex_jmpbuf))
	return(D_A(RETCOD));
# endif /* ENDEX_LONGJMP defined */
    BEGIN(NORET);
    return( 0 );
}
