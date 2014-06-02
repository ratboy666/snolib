-STITL STCL
-EJECT
*
-LINE 32 "STCL.lss"
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
-LINE 6 "STCL.lss"
STCL_LOAD
*
         LOAD('STCL_CREATEINTERP()INTEGER')
         LOAD('STCL_EVALFILE(INTEGER,STRING)STRING')
         LOAD('STCL_GETVAR(INTEGER,STRING)STRING')
         LOAD('STCL_SETVAR(INTEGER,STRING,STRING)STRING')
         LOAD('STCL_EVAL(INTEGER,STRING)STRING')
         LOAD('STCL_DELETEINTERP(INTEGER)STRING')
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
         CODE('STCL_LOAD')
*
* CE: .MSNOBOL4;
