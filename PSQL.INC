-LINE 69 "PSQL.lss"
-INCLUDE 'SCOOP.INC'
-INCLUDE 'REPL.INC'
-INCLUDE 'COUNT.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'SEQ.INC'
-INCLUDE 'CSNOBOL4.INC'
-INCLUDE 'BRKREM.INC'
-INCLUDE 'UNIQUE.INC'
-STITL PSQL
-EJECT
-LINE 374 "PSQL.lss"
*
************************************************************************
*                                                                      *
*                  ######    #####    #####   #                        *
*                  #     #  #     #  #     #  #                        *
*                  #     #  #        #     #  #                        *
*                  ######    #####   #     #  #                        *
*                  #              #  #   # #  #                        *
*                  #        #     #  #    #   #                        *
*                  #         #####    #### #  #######                  *
*                                                                      *
* PSQL                 INTERFACE TO POSTGRESQL                         *
*                                                                      *
************************************************************************
*
* PSQL.lss
*
-LINE 116 "PSQL.lss"
*
* THESE THREE ARE FUNCTIONS -- SIMPLY EASIER THAT WAY.
*
         DEFINE('PSQL_INSERT(T)N,V,I')
         DEFINE('PSQL_RESULT(S)I,N,R,T,KEY,DAT')
         DEFINE('PSQL_ESCAPE(S)')
*
* CREATE CLASS PSQL_CLASS AND POPULATE ITS METHODS
*
         PSQL_CLASS = SEND(CLASS, 'NEW_CLASS', 'PSQL_CLASS')
         DEFINE('PSQL_OPEN()L')
         SEND(PSQL_CLASS, 'ADD_METHOD', 'OPEN', 'PSQL_OPEN')
         DEFINE('PSQL_CLOSE()PID')
         SEND(PSQL_CLASS, 'ADD_METHOD', 'CLOSE', 'PSQL_CLOSE')
         SEND(PSQL_CLASS, 'ADD_METHOD', 'GET_PIPE', CODE(
+           ' SEND = |.PIPE :(RETURN)'))
         DEFINE('PSQL_DISCARD()L')
         SEND(PSQL_CLASS, 'ADD_METHOD', 'DISCARD', 'PSQL_DISCARD')
         DEFINE('PSQL_OUTPUT()L')
         SEND(PSQL_CLASS, 'ADD_METHOD', 'OUTPUT', 'PSQL_OUTPUT')
*
                                                             :(PSQL_END)
*
* CONVERT TABLE TO "(NAME, ...) VALUES (DATA, ...)" READY FOR SQL
* INSERT. USES PSQL_ESCAPE() TO ENSURE THAT VALUES ARE QUOTED CORRECTLY.
*
PSQL_INSERT
         T = CONVERT(T, 'ARRAY')
         SEQ(' N = N T<I, 1> ", "; '
+            ' V = V PSQL_ESCAPE(T<I, 2>) ", " ', .I)
         IDENT(N)                                            :S(FRETURN)
         N ', ' RPOS(0) =
         V ', ' RPOS(0) =
         PSQL_INSERT = '(' N ') VALUES (' V ')'                :(RETURN)
*
* CONVERT PSQL_OUTPUT() INTO ARRAY OF TABLES
*
PSQL_RESULT
         IDENT(S)                                            :S(FRETURN)
         S = S CHARS_NL
         N = COUNT(S, CHARS_NL CHARS_NL)
         EQ(N)                                               :S(FRETURN)
         PSQL_RESULT = ARRAY(N)
PSQL5    S POS(0) ARB . T CHARS_NL CHARS_NL REM . S           :F(RETURN)
         R = TABLE()
PSQL6    T POS(0) BREAK('|') . KEY '|'
+          BRKREM(CHARS_NL) . DAT (CHARS_NL | RPOS(0)) =       :F(PSQL7)
         R<KEY> = DAT                                           :(PSQL6)
PSQL7    I = I + 1
         PSQL_RESULT<I> = R                                     :(PSQL5)
*
* ESCAPE AND QUOTE AN SQL STRING
*
PSQL_ESCAPE
         PSQL_ESCAPE = "'" REPL(S, "'", "''") "'"              :(RETURN)
*
* DISCARD OUTPUT FROM LAST SQL COMMAND.
*
PSQL_DISCARD
         L = $|.PIPE                                         :F(FRETURN)
         L POS(0) '*' RPOS(0)                  :S(RETURN)F(PSQL_DISCARD)
*
* GATHER AND RETURN OUTPUT FROM SQL COMMAND. DISCARD COMMAND ECHO,
* RETURNING ONLY RESULTS.
*
PSQL_OUTPUT
PSQL2    L = $|.PIPE                                         :F(FRETURN)
         L POS(0) '*' RPOS(0)                                  :S(PSQL3)
         PSQL_OUTPUT = PSQL_OUTPUT L CHARS_NL                   :(PSQL2)
PSQL3    PSQL_OUTPUT CHARS_NL CHARS_NL RPOS(0) = CHARS_NL      :S(PSQL3)
PSQL4    PSQL_OUTPUT BREAK(CHARS_NL) CHARS_NL REM . PSQL_OUTPUT
+                                                            :F(FRETURN)
         PSQL_OUTPUT POS(0) '# '                      :S(PSQL4)F(RETURN)
*
* OPEN PSQL COMMAND. SEND COMMANDS TO MAKE PSQL_OUTPUT() EASIER,
* PSQL_RESULT() FOR PARSING SELECT RESULTS AND BUILDING RESULT ARRAYS.
*
PSQL_OPEN
         |.UNIT = IO_FINDUNIT()                              :F(FRETURN)
         |.PIPE = UNIQUE()
         INPUT(|.PIPE, |.UNIT, 'U', '||/usr/bin/psql -q')    :F(FRETURN)
         OUTPUT(|.PIPE, |.UNIT)                              :F(FRETURN)
         $|.PIPE = "\set PROMPT1 '\n*\n'"                    :F(FRETURN)
         SELF('DISCARD')                                     :F(FRETURN)
         $|.PIPE = "\set PROMPT2 '# '"                       :F(FRETURN)
         SELF('DISCARD')                                     :F(FRETURN)
         $|.PIPE = "\pset pager off"                         :F(FRETURN)
         SELF('DISCARD')                                     :F(FRETURN)
         $|.PIPE = "\a"                                      :F(FRETURN)
         SELF('DISCARD')                                     :F(FRETURN)
         $|.PIPE = "\x on"                                   :F(FRETURN)
         SELF('DISCARD')                            :F(FRETURN)S(RETURN)
*
* CLOSE PSQL
*
PSQL_CLOSE
         $|.PIPE = '\q'                                      :F(FRETURN)
         ENDFILE(|.UNIT)                                     :F(FRETURN)
         DETACH(|.PIPE)                                      :F(FRETURN)
*
* ENDFILE() CLOSES PSQL. INDEED, WE SEND A QUIT COMMAND (\q) FIRST!
* BUT... THE CLOSE CODE IN THE INTERPRETER DOES NOT REAP THE ZOMBIE.
* WAIT() IS DEFINED IN CSNOBOL4, USE WAIT() TO REAP. THIS IS WRONG,
* WE MAY REAP THE WRONG PROCESS! SHOULD FIX THIS IN IO.C - THE CODE
* IS IN IO.C, BUT ISN'T WORKING (?)
*
         PID = WAIT()                               :S(RETURN)F(FRETURN)
*
PSQL_END
*
* CE: .F.MSNOBOL4;
