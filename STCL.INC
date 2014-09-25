-STITL STCL
-EJECT
*
-LINE 63 "STCL.lss"
************************************************************************
*                                                                      *
*                    #####   #######   #####   #                       *
*                   #     #     #     #     #  #                       *
*                   #           #     #        #                       *
*                    #####      #     #        #                       *
*                         #     #     #        #                       *
*                   #     #     #     #     #  #                       *
*                    #####      #      #####   #######                 *
*                                                                      *
* STCL                TCL INTERFACE FOR CSNOBOL4                       *
*                                                                      *
* PHIL BUDNE <PHIL@ULTIMATE.COM>                                       *
* DECEMBER 3, 2005                                                     *
*                                                                      *
* INSPIRED BY ARJEN MARKUS' 'FTCL' FORTRAN/TCL INTERFACE               *
*                                                                      *
************************************************************************
*
* STCL.lss
*
-LINE 11 "STCL.lss"
-MODULE TCL
STCL_LOAD
*
-PUBLIC STCL_CREATEINTERP(), STCL_EVALFILE(), STCL_GETVAR()
-PUBLIC STCL_SETVAR(), STCL_EVAL(), STCL_DELETEINTERP()
*
         LOAD('STCL_CREATEINTERP()INTEGER')
         LOAD('STCL_EVALFILE(INTEGER,STRING)STRING')
         LOAD('STCL_GETVAR(INTEGER,STRING)STRING')
         LOAD('STCL_SETVAR(INTEGER,STRING,STRING)STRING')
         LOAD('STCL_EVAL(INTEGER,STRING)STRING')
         LOAD('STCL_DELETEINTERP(INTEGER)STRING')
*
-PUBLIC STCL_NEWSTRINGOBJ(), STCL_GETSTRINGFROMOBJ(), STCL_APPENDTOOBJ()
-PUBLIC STCL_EVALOBJEX(), STCL_GETOBJRESULT(), STCL_OBJSETVAR2()
-PUBLIC STCL_OBJGETVAR2(), STCL_RELEASEOBJ()
*
         LOAD('STCL_NEWSTRINGOBJ(STRING)INTEGER')
         LOAD('STCL_GETSTRINGFROMOBJ(INTEGER)STRING')
         LOAD('STCL_APPENDTOOBJ(INTEGER,STRING)STRING')
         LOAD('STCL_EVALOBJEX(INTEGER,INTEGER,INTEGER)STRING')
         LOAD('STCL_GETOBJRESULT(INTEGER)')
         LOAD('STCL_OBJSETVAR2(INTEGER,STRING,STRING,INTEGER,INTEGER)'
+             'STRING')
         LOAD('STCL_OBJGETVAR2(INTEGER,STRING,STRING,INTEGER)STRING')
         LOAD('STCL_RELEASEOBJ(INTEGER)STRING')
*
-PUBLIC INIT_TCL()
*
         DEFINE('INIT_TCL()V,VPAT')                          :(END_STCL)
*
INIT_TCL INIT_TCL = STCL_CREATEINTERP()
         TCL_VERSION = STCL_GETVAR(INIT_TCL, 'tcl_version')
         TERMINAL = IDENT(TCL_VERSION) 'COULD NOT GET TCL_VERSION'
+                                                                :S(END)
         VPAT = SPAN(&DIGITS) '.' SPAN(&DIGITS)
         TCL_VERSION VPAT . V                               :S(INITTCL2)
         TERMINAL = 'COULD NOT PARSE TCL_VERSION'                 :(END)
INITTCL2 LT(V, 8.4)                                         :S(INITTCL3)
         STCL_EVAL(INIT_TCL, 'package require Tk')          :F(INITTCL5)
INITTCL3 TK_VERSION = STCL_GETVAR(INIT_TCL, 'tk_version')   :F(INITTCL4)
         DIFFER(TK_VERSION)                                   :S(RETURN)
INITTCL4 TERMINAL = 'COULD NOT FIND TK_VERSION'                   :(END)
INITTCL5 TERMINAL = 'REQUIRE TK FAILED'                           :(END)
*
END_STCL CODE('STCL_LOAD')
*
* CE: .MSNOBOL4;
