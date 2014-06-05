-LINE 13 "SLOAD.lss"
-INCLUDE 'CRACK.INC'
-INCLUDE 'HOST.INC'
-INCLUDE 'TRIMB.INC'
-STITL SLOAD
-EJECT
-LINE 113 "SLOAD.lss"
*
************************************************************************
*                                                                      *
*              #####   #        #######     #     ######               *
*             #     #  #        #     #    # #    #     #              *
*             #        #        #     #   #   #   #     #              *
*              #####   #        #     #  #     #  #     #              *
*                   #  #        #     #  #######  #     #              *
*             #     #  #        #     #  #     #  #     #              *
*              #####   #######  #######  #     #  ######               *
*                                                                      *
* SLOAD                LOAD SNOBOL4 SOURCE                             *
*                                                                      *
* (C) COPYRIGHT 1985, 1987 - CATSPAW, INCORPORATED                     *
*                                                                      *
* MODIFIED TO SUPPORT /DEV FILES, SEARCH CSNOBOL4 PATHS                *
*                                                                      *
************************************************************************
*
* SLOAD.lss
*
-LINE 19 "SLOAD.lss"
-MODULE SLOAD
-PUBLIC SLOAD()
         DEFINE('SLOAD(FILENAME)'
+               'LIB,CODE,PATH,X,A,I,P,PS,DS,TRIM_SAV,POSITION,UNIT')
         Q_ = "'"
         QQ_ = '"'
         SLOAD_STMT = ARBNO(Q_ BREAK(Q_) Q_ | QQ_ BREAK(QQ_) QQ_ |
+                     NOTANY(Q_ QQ_) BREAK(Q_ QQ_ ';')) ';'
         SLOAD_STMTS = FENCE (';' ARBNO(SLOAD_STMT)) . X '*' REM
* NOTE THAT ; FOLLOWED BY ANYTHING OTHER THAN . OR + IS ALSO A COMMENT
         SLOAD_CCPAT = FENCE ('*' | '-' | '#' | '!' | '|' | RPOS(0))
         SLOAD_CNPAT = FENCE (';.' | ';+')
         SLOAD_INPAT = FENCE '-' ((ANY('Ii') ('NCLUDE' | 'nclude')) |
+                                (ANY('Cc') ('OPY' | 'opy')))
+                      BREAK(QQ_ Q_) LEN(1) BREAK(QQ_ Q_) . X
         SLOAD_TAB = TABLE()                                :(SLOAD_END)
*
* FUNCTION TO READ AND COMPILE SNOBOL4 FUNCTIONS FROM A DISK FILE.
* THE FILENAME IS SPECIFIED AS THE ARGUMENT TO FUNCTION SLOAD.
*
SLOAD    UNIT = IO_FINDUNIT()
         PATH = FILENAME
         INPUT(.LIB, UNIT,, PATH)                            :S(SLOAD_0)
         DS = HOST(HOST_DIR_SEP)
         PS = HOST(HOST_PATH_SEP)
         X = HOST(HOST_GETENV, 'SNOPATH')                    :S(SLOAD_8)
         X = HOST(HOST_GETENV, 'SNOLIB')                     :S(SLOAD_8)
         X = HOST(HOST_SNOLIB_DIR)                           :F(FRETURN)
SLOAD_8  A = CRACK(X, PS)
         I = 1
SLOAD_10 P = TRIMB(A<I>)                                     :F(FRETURN)
         PATH = P DS FILENAME
         INPUT(.LIB, UNIT,, PATH)                            :S(SLOAD_0)
         I = I + 1                                           :(SLOAD_10)
*
SLOAD_0  TRIM_SAV = &TRIM
         &TRIM = 1
*
SLOAD_1  X = LIB                                             :F(SLOAD_2)
         X SLOAD_CCPAT                                       :S(SLOAD_4)
         X = ';' X
         X SLOAD_CNPAT = ' '
         X SLOAD_STMTS
         CODE = CODE X                                        :(SLOAD_1)
*
SLOAD_4  X SLOAD_INPAT                                       :F(SLOAD_1)
         DIFFER(SLOAD_TAB<X>)                                :S(SLOAD_1)
*
         POSITION = SET(UNIT, 0, 1)
         ENDFILE(UNIT)
         DETACH(.LIB)
*
         SLOAD(X)                                            :F(FRETURN)
*
         INPUT(.LIB, UNIT,, PATH)                            :F(FRETURN)
*
         SLOAD_TAB<X> = 1
         FILENAME FENCE '/dev/'                              :S(SLOAD_1)
         EQ(SET(UNIT, POSITION, 0), POSITION)      :S(SLOAD_1)F(FRETURN)
*
SLOAD_2  ENDFILE(UNIT)
         DETACH(.LIB)
         CODE = CODE(CODE '; :(SLOAD_3)')                       :S<CODE>
         TERMINAL = 'COMPILATION ERROR, FILE: ' FILENAME
*
* ERROR. TAKE CODE APART STATEMENT BY STATEMENT TO FIND THE PROBLEM.
* FIRST REMOVE FROM INCLUDE FILE TABLE, THEN REMOVE INITIAL ';'
*
         SLOAD_TAB<X> =
         CODE = SUBSTR(CODE, 2)
SLOAD_6  CODE FENCE SLOAD_STMT . X =                         :F(SLOAD_7)
         CODE(X)                                             :S(SLOAD_6)
         X RTAB(1) . TERMINAL
SLOAD_7  &TRIM = TRIM_SAV
         TERMINAL = &ERRTEXT                                  :(FRETURN)
*
SLOAD_3  &TRIM = TRIM_SAV                                      :(RETURN)
*
SLOAD_END
*
* CE: .MSNOBOL4;
