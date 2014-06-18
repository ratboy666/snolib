-MODULE FASBOL
-INCLUDE 'SYSTEM.INC'
-INCLUDE 'LOGIC.INC'
-INCLUDE 'FASTBAL.INC'
-INCLUDE 'UNIQUE.INC'
-STITL FASBOL
*
************************************************************************
*                                                                      *
*         #######     #      #####   ######   #######  #               *
*         #          # #    #     #  #     #  #     #  #               *
*         #         #   #   #        #     #  #     #  #               *
*         #####    #     #   #####   ######   #     #  #               *
*         #        #######        #  #     #  #     #  #               *
*         #        #     #  #     #  #     #  #     #  #               *
*         #        #     #   #####   ######   #######  #######         *
*                                                                      *
* FASTBOL             FASBOL II COMPATIBILITY                          *
*                                                                      *
************************************************************************
*
* FASBOL.INC
*
* SUPPORTS FASBOL FEATURES. THIS IS PRIMARILY TO GET THE FASBOL II
* COMPILER TO RUN IN MAINBOL.
*
         &FULLSCAN = 1
*
         INPUT(.INPUTC, 18, 'T', '/dev/tty')
         OUTPUT(.OUTPUTC, 19, 'T', '/dev/tty')
*
         OPSYN('ILT', 'LT')
         OPSYN('ILE', 'LE')
         OPSYN('IEQ', 'EQ')
         OPSYN('INE', 'NE')
         OPSYN('IGE', 'GE')
         OPSYN('IGT', 'GT')
         DEFINE('FASBOL()')
         DEFINE('DECLARE()','RETURN.')
         DEFINE('INSERT(SUBSTRING,STRING,LEN,POS)PART1,PART2')
         OPSYN('REVERS', 'REVERSE')
         OPSYN('LSHIFT', 'SHL')
         OPSYN('RSHIFT', 'SHR')
         DEFINE('EJECT()', 'RETURN.')
         DEFINE('FREEZE()', 'RETURN.')
         DEFINE('EXTIME(PROGNAME)')
         OPSYN('DATE.', 'DATE')
         DEFINE('DATE()')
         DEFINE('DAYTIM()')
         DEFINE('REAL(X)')
         OPSYN('TABLE.', 'TABLE')
         OPSYN('ARRAY.', 'ARRAY')
         DEFINE('TABLE(P,P2)')
         DEFINE('ARRAY(P,P2)')
         DEFINE('NSPAN(P)')
         DEFINE('BREAKQ(S)NAME,R,P1,P2,P3')
         DEFINE('SUBSTR(STRING,LEN,POS)')                  :(FASBOL_END)
*
BREAKQ   NAME = UNIQUE()
         R = CONVERT(NAME, 'EXPRESSION')
         P1 = BREAK('"' "'" S)
         P2 = "'" BREAK("'") "'" R
         P3 = '"' BREAK('"') '"' R
         BREAKQ = P1 (P2 | P3 | BREAK(S))
         $NAME = BREAKQ                                        :(RETURN)
*
NSPAN    NSPAN = SPAN(P) | ''                                  :(RETURN)
*
TABLE    IDENT(DATATYPE(P), 'ARRAY')                         :S(TABLE..)
         TABLE = IDENT(DATATYPE(P), 'TABLE') TABLE()          :S(RETURN)
         TABLE = TABLE.(P,P2)                       :S(RETURN)F(FRETURN)
TABLE..  TABLE = CONVERT(P, 'TABLE')                :S(RETURN)F(FRETURN)
*
ARRAY    IDENT(DATATYPE(P), 'TABLE')                         :S(ARRAY..)
         ARRAY = ARRAY.(P,P2)                       :S(RETURN)F(FRETURN)
ARRAY..  ARRAY = CONVERT(P, 'ARRAY')                :S(RETURN)F(FRETURN)
*
REAL     IDENT(DATATYPE(X), 'REAL')                            :(RETURN)
         INTEGER(X)                                          :S(FRETURN)
         (IDENT(DATATYPE(X), 'STRING') CONVERT(X, 'REAL'))
+                                                   :S(RETURN)F(FRETURN)        
*
EXTIME   TERMINAL = 'EXECUTION TIME FOR ' PROGNAME
         TERMINAL = LPAD(CONVERT(&GCTIME, 'STRING'), 16) ' MS IN GC'
         TERMINAL = LPAD(CONVERT(&STEXEC, 'STRING'), 16) ' STATEMENTS'
         TERMINAL = LPAD(CONVERT(TIME(), 'STRING'), 16)  ' MS EXEC'
RETURN.                                                        :(RETURN)
*
DAYTIM   DATE.() BREAK(' ') ' ' REM . DAYTIM
         DAYTIM = DAYTIM '.00'                                 :(RETURN)
*
DATE     DATE.() BREAK(' ') . DATE                             :(RETURN)
*
SUBSTR   STRING TAB(POS) LEN(LEN) . SUBSTR          :S(RETURN)F(FRETURN)
*
INSERT   STRING TAB(POS) . PART1 LEN(LEN) REM . PART2        :F(FRETURN)
         INSERT = PART1 SUBSTRING PART2                        :(RETURN)
*
FASBOL   SYSTEM() 'FASBOL'                          :S(RETURN)F(FRETURN)
*
* SIMPLY PREDICATE ASSIGNMENTS TO THESE WITH FASBOL()
*     &STNTRACE
*     &DENSITY
*     &SLOWFRAG
*
* APPLY() IN FASBOL ACCEPTS MORE OR FEWER ARGUMENTS THAN REQUIRED BY
* THE FUNCTION. CSNOBOL4 PRODUCES ERROR 25.
*
* I/O FUNCTIONS ARE NOT HANDLED HERE. FASBOL II RAN ON A COMPLETELY
* DIFFERENT OS, AND THESE FUNCTIONS WOULD NEED TO BE RE-DONE.
* HOWEVER OUTPUTC AND INPUTC ARE DEFINED HERE TO COVER MOST SIMPLE
* NEEDS.
*
FASBOL_END
*
* CE: .MSNOBOL4;
*
