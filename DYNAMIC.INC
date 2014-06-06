-LINE 11 "DYNAMIC.lss"
-INCLUDE 'BQ.INC'
-INCLUDE 'HOST.INC'
-INCLUDE 'REPL.INC'
-STITL DYNAMIC
-EJECT
-LINE 197 "DYNAMIC.lss"
*
************************************************************************
*                                                                      *
*    ######   #     #  #     #     #     #     #  ###   #####          *
*    #     #   #   #   ##    #    # #    ##   ##   #   #     #         *
*    #     #    # #    # #   #   #   #   # # # #   #   #               *
*    #     #     #     #  #  #  #     #  #  #  #   #   #               *
*    #     #     #     #   # #  #######  #     #   #   #               *
*    #     #     #     #    ##  #     #  #     #   #   #     #         *
*    ######      #     #     #  #     #  #     #  ###   #####          *
*                                                                      *
* DYNAMIC       CREATE DYNAMICALLY LOADABLE MODULE FOR LOAD()          *
*                                                                      *
* PHIL BUDNE, NOVEMBER 2005                                            *
*                                                                      *
************************************************************************
*
* DYNAMIC.lss
*
-LINE 17 "DYNAMIC.lss"
-MODULE DYNAMIC
-PUBLIC COMPILE_COBOL(), COMPILE_FORTRAN(), COMPILE_SCHEME()
-PUBLIC COMPILE_DYNAMIC(), LIBS_FORTRAN(), LIBS_COBOL(), LIBS_SCHEME()
DYNAMIC  DEFINE('COMPILE_COBOL(SRC)CMD,COBC')
         DEFINE('COMPILE_FORTRAN(SRC)CMD')
         DEFINE('COMPILE_SCHEME(SRC)CMD,CC,DL_CFLAGS,COPT')
         DEFINE('COMPILE_DYNAMIC(SRC)CMD,CC,DL_CFLAGS,COPT,CINC')
         DEFINE('LIBS_FORTRAN()')
         DEFINE('LIBS_COBOL()')
         DEFINE('LIBS_SCHEME()')                  :(COMPILE_DYNAMIC_END)
*
-LINE 33 "DYNAMIC.lss"
LIBS_FORTRAN
         LIBS_FORTRAN = '-lgfortran'                           :(RETURN)
*
-LINE 42 "DYNAMIC.lss"
LIBS_COBOL
         LIBS_COBOL = BQ('cob-config --libs')                  :(RETURN)
*
-LINE 50 "DYNAMIC.lss"
LIBS_SCHEME
         LIBS_SCHEME = 'prog_.o -lgambc -ldl -lm -lutil'       :(RETURN)
-LINE 59 "DYNAMIC.lss"
*
* DYNAMIC COMPILE COBOL SOURCE
*
COMPILE_COBOL
         CMD = 'cobc -C ' SRC
         TERMINAL = DIFFER(DYNAMIC_DEBUG) CMD
         HOST(HOST_SYSCMD, CMD)                              :F(FRETURN)
*
         COBC = BQ('cob-config --cflags')
         SRC '.cbl' =
         SRC '.CBL' =
         CC = HOST(HOST_CC)                                  :F(FRETURN)
         IDENT(CC)                                           :S(FRETURN)
         DL_CFLAGS = HOST(HOST_DL_CFLAGS) ' '
         COPT = HOST(HOST_COPT) ' '
         CMD = CC ' -c ' COPT DL_CFLAGS ' -DPIC -O3 ' COBC ' ' SRC '.c'
         TERMINAL = DIFFER(DYNAMIC_DEBUG) CMD
         HOST(HOST_SYSCMD, CMD)                              :F(FRETURN)
*
         DELETE(SRC '.c')
         DELETE(SRC '.c.h')
         DELETE(SRC '.c.l.h')                                  :(RETURN)
-LINE 90 "DYNAMIC.lss"
*
* DYNAMIC COMPILE FORTRAN SOURCE
*
COMPILE_FORTRAN
         CMD = 'gfortran -c -fpic -O3 -ff2c -std=legacy ' SRC
         TERMINAL = DIFFER(DYNAMIC_DEBUG) CMD
         HOST(HOST_SYSCMD, CMD)                     :F(FRETURN)S(RETURN)
*
-LINE 105 "DYNAMIC.lss"
COMPILE_SCHEME
         CMD = 'gsc -c ' SRC
         TERMINAL = DIFFER(DYNAMIC_DEBUG) CMD
         HOST(HOST_SYSCMD, CMD)                              :F(FRETURN)
         SRC '.scm' = '.c'
         SRC '.six' = '.c'
         CMD = 'gsc -link -o prog_.c ' SRC
         TERMINAL = DIFFER(DYNAMIC_DEBUG) CMD
         HOST(HOST_SYSCMD, CMD)                              :F(FRETURN)
*
         CC = HOST(HOST_CC)                                  :F(FRETURN)
         IDENT(CC)                                           :S(FRETURN)
         DL_CFLAGS = HOST(HOST_DL_CFLAGS) ' '
         COPT = HOST(HOST_COPT) ' '
         CMD = CC ' -c -D___LIBRARY ' COPT DL_CFLAGS ' ' SRC ' prog_.c'
         TERMINAL = DIFFER(DYNAMIC_DEBUG) CMD
         HOST(HOST_SYSCMD, CMD)                              :F(FRETURN)
*
         DELETE(SRC)
         DELETE('prog_.c')                                     :(RETURN)
-LINE 131 "DYNAMIC.lss"
*
* DYNAMIC COMPILE C SOURCE
*
COMPILE_DYNAMIC
         CC = HOST(HOST_CC)                                  :F(FRETURN)
         IDENT(CC)                                           :S(FRETURN)
         DL_CFLAGS = HOST(HOST_DL_CFLAGS) ' '
         COPT = HOST(HOST_COPT) ' '
         CINC = HOST(HOST_SNOLIB_DIR)
         CINC = HOST(HOST_INCLUDE_DIR)
         CMD = CC ' -c ' COPT DL_CFLAGS ' -I' CINC ' ' SRC
         TERMINAL = DIFFER(DYNAMIC_DEBUG) CMD
         HOST(HOST_SYSCMD, CMD)                     :F(FRETURN)S(RETURN)
*
COMPILE_DYNAMIC_END
*
-PUBLIC LINK_DYNAMIC()
         DEFINE('LINK_DYNAMIC(OUT,OBJ,LIBS)'
+               'CMD,DL_LD,DL_EXT,DL_LDFLAGS,DSEP')  :(LINK_DYNAMIC_END)
*
LINK_DYNAMIC
         DL_LD = HOST(HOST_DL_LD)                            :F(FRETURN)
         IDENT(DL_LD)                                        :S(FRETURN)
         DL_EXT = HOST(HOST_DL_EXT)
         OUT = DIFFER(DL_EXT) OUT DL_EXT
         DL_LDFLAGS = HOST(HOST_DL_LDFLAGS) ' '
         CMD = DL_LD ' ' DL_LDFLAGS '-o ' OUT ' ' OBJ ' ' LIBS
         TERMINAL = DIFFER(DYNAMIC_DEBUG) CMD
         HOST(HOST_SYSCMD, CMD)                              :F(FRETURN)
         LINK_DYNAMIC = OUT
         DSEP = HOST(HOST_DIR_SEP)
         LINK_DYNAMIC BREAK(DSEP) DSEP                        :S(RETURN)
         LINK_DYNAMIC = '.' DSEP LINK_DYNAMIC                  :(RETURN)
LINK_DYNAMIC_END
*
* MAKE A DYNAMIC MODULE, GIVEN C SOURCES
* LIBS MAY CONTAIN BOTH OBJECTS AND LIBRARIES
*
-PUBLIC MAKE_DYNAMIC_MODULE()
         DEFINE('MAKE_DYNAMIC_MODULE(OUT,SRC,LIBS)OBJ')
                                              :(MAKE_DYNAMIC_MODULE_END)
MAKE_DYNAMIC_MODULE
         IDENT(SRC)                                         :S(MDM_LINK)
         COMPILE_DYNAMIC(SRC)                                :F(FRETURN)
         OBJ = REPL(SRC, '.o', '.c')
MDM_LINK IDENT(OBJ LIBS)                                     :S(FRETURN)
         MAKE_DYNAMIC_MODULE = LINK_DYNAMIC(OUT, OBJ, LIBS)  :F(FRETURN)
                                                               :(RETURN)
MAKE_DYNAMIC_MODULE_END
*
DYNAMIC_END
*
* CE: .MSNOBOL4;
