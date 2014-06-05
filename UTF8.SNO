-MODULE UTF8
-STITL UTF8
-EJECT
-LINE 250 "UTF8.lss"
*
************************************************************************
*                                                                      *
*                   #     #  #######  #######   ###                    *
*                   #     #     #     #        #   #                   *
*                   #     #     #     #        #   #                   *
*                   #     #     #     #####     ###                    *
*                   #     #     #     #        #   #                   *
*                   #     #     #     #        #   #                   *
*                    #####      #     #         ###                    *
*                                                                      *
* UTF8                                                                 *
*                                                                      *
************************************************************************
*
* SNOBOL4 FUNCTIONS TO IMPLEMENT UTF-ENCODED UNICODE HANDLING
* UTF8.lss
*
-LINE 13 "UTF8.lss"
* PHIL BUDNE <PHIL@ULTIMATE.COM>
* SEPTEMBER 1996
* UPDATED FOR 4/5/6 BYTE RUNES JUNE 1997
*
* MOST OF THIS IS JUST AWFUL, BUT THIS IS JUST A PROOF OF CONCEPT,
* AND LIKE ALL SNOBOL THERE IS ALWAYS A SMALLER, FASTER AND MORE
* PERVERSE WAY TO DO ANYTHING.
*
* TODO
*
* UTFNOTANY
* UTFSPAN
* UTFBREAK
* UTFBREAKX
*
* PATTERN TO MATCH ONE UTF ENCODED RUNE
*
* SNOBOL4 LACKS CHAR(), SPITBOL CHAR() LOSES ON CHAR(0)!
*
         DEFINE("XCHAR(N)")                                    :(EXCHAR)
*
XCHAR    &ALPHABET ARB POS(N) LEN(1) . XCHAR        :S(RETURN)F(FRETURN)
*
EXCHAR
*
* HELPER FUNCTION TO PATTERN THAT MATCHES A RANGE OF BYTE VALUES.
* THE TRUE SNO-HEAD MIGHT IMPLEMENT THIS AS A FUNCTION THAT TAKES
* STRINGS OF SPAN('01') ARBNO('X') DIRECTLY!!
*
         DEFINE("RANGE(START,END)")                            :(ERANGE)
*
RANGE
*
* SPITBOL COMPILES ANY() INTO A BITMAP;
         &ALPHABET ARB (XCHAR(START) ARB XCHAR(END)) . RANGE :F(FRETURN)
* SPITBOL COMPILES TABLES ONCE
         RANGE = ANY(RANGE)                                    :(RETURN)
* FOR SNOBOL4; CREATE BIG PATTERN
*        GE(START, END)                                      :S(FRETURN)
*        RANGE = XCHAR(START)
*RANGE1  GE(STAT, END)                                        :S(RETURN)
*        START = START + 1
*        RANGE = RANGE | XCHAR(START)                          :(RANGE1)
*
ERANGE
*
* SINGLE BYTE:       0XXXXXXX  VALUES 0..0X7F
*
         UTF.T1 = RANGE(0, 127)
*
* TWO-BYTE LEADER:   110XXXXX  VALUES 0X80..0X7FF
*
         UTF.T2 = RANGE(192, 223)
*
* THREE-BYTE LEADER: 1110XXXX  VALUES 0X800..0XFFFF
*
         UTF.T3 = RANGE(224, 239)
*
* FOUR-BYTE LEADER:  11110XXX  VALUES 0X10000..0X1FFFFF
*
         UTF.T4 = RANGE(240, 247)
*
* FIVE-BYTE LEADER:  111110XX  VALUES 0X200000..0X3FFFFFF
*
         UTF.T5 = RANGE(248, 251)
*
* FIVE-BYTE LEADER:  1111110X  VALUES 0X4000000..0X7FFFFFFF
*
         UTF.T6 = RANGE(252, 253)
*
* SUBSEQUENT BYTE:   10XXXXXX
*
         UTF.TX = RANGE(128, 191)
*
         UTF.RUNE = FENCE
+           (UTF.T1 |
+            UTF.T2 UTF.TX |
+            UTF.T3 UTF.TX UTF.TX |
+            UTF.T4 UTF.TX UTF.TX UTF.TX |
+            UTF.T5 UTF.TX UTF.TX UTF.TX UTF.TX |
+            UTF.T6 UTF.TX UTF.TX UTF.TX UTF.TX UTF.TX)
*
         UTF.RUNE0 = POS(0) UTF.RUNE
*
* PATTERN TO MOVE TO NEXY SYNC CHAR;
*
*        UTF.SYNC = BREAKX(UTF.T1 UTF.T2 UTF.T3 UTF.T4 UTF.T5 UTF.T6)
*
* UTF ANALOG OF ARB
*
         UTFARB = ARBNO(UTF.RUNE)
*
* UTF ANALOG OF LEN
*
         DEFINE("UTFLEN(N)")                                  :(EUTFLEN)
*
UTFLEN   LT(N, 0)                                             :(FRETURN)
         UTFLEN =
UTFLEN2  EQ(N, 0)                                             :S(RETURN)
         UTFLEN = UTFLEN UTF.RUNE
         N = N - 1                                            :(UTFLEN2)
*
EUTFLEN
*
* UTF ANALOG FOR ANY(STR)
*
         DEFINE("UTFANY(STR)R")                               :(EUTFANY)
*
UTFANY   STR UTF.RUNE0 . UTFANY =                            :F(FRETURN)
UTFANY2  IDENT(STR)                                           :S(RETURN)
         STR UTF.RUNE0 . R =                                 :F(FRETURN)
         UTFANY = UTFANY | R                                  :(UTFANY2)
EUTFANY
*
* UTF ANALOG FOR CHAR(N)
*
         DEFINE("RUNE(N)")                                      :(ERUNE)
*
RUNE     LT(N, 0)                                            :S(FRETURN)
         GT(N, 127)                                            :S(RUNE2)
* SINGLE BYTE RUNE
         RUNE = XCHAR(N)                                       :(RETURN)
RUNE2    GT(N, 2047)                                           :S(RUNE3)
* TWO-BYTE RUNE
         RUNE = XCHAR(192 + (N / 64))
+               XCHAR(128 + REMDR(N, 64))                      :(RETURN)
* THREE-BYTE RUNE
RUNE3    GT(N, 65535)                                          :S(RUNE4)
         RUNE = XCHAR(224 + N / 4096)
+               XCHAR(128 + REMDR(N / 64, 64))
+               XCHAR(128 + REMDR(N, 64))                      :(RETURN)
* FOUR-BYTE RUNE
RUNE4    GT(N, 2097151)                                        :S(RUNE5)
         RUNE = XCHAR(240 + N / 262144)
+               XCHAR(128 + REMDR(N / 65536, 64))
+               XCHAR(128 + REMDR(N / 64, 64))
+               XCHAR(128 + REMDR(N, 64))                      :(RETURN)
* FIVE-BYTE RUNE
RUNE5    GT(N, 67108863)                                       :S(RUNE6)
         RUNE = XCHAR(248 + N / 16777216)
+               XCHAR(128 + REMDR(N / 262144, 64))
+               XCHAR(128 + REMDR(N / 4096, 64))
+               XCHAR(128 + REMDR(N / 64, 64))
+               XCHAR(128 + REMDR(N, 64))                      :(RETURN)
* SIX-BYTE RUNE
RUNE6    GT(N, 2147483647)                                   :S(FRETURN)
         RUNE = XCHAR(252 + N / 1073741824)
+               XCHAR(128 + REMDR(N / 16777216, 64))
+               XCHAR(128 + REMDR(N / 262144, 64))
+               XCHAR(128 + REMDR(N / 4096, 64))
+               XCHAR(128 + REMDR(N / 64, 64))
+               XCHAR(128 + REMDR(N, 64))                      :(RETURN)
*
ERUNE
*
* UTF ANALOG FOR SIZE(STR)
*
         DEFINE("UTFSIZE(STR)")                              :(EUTFSIZE)
*
UTFSIZE  STR UTF.RUNE =                                      :F(UTFSIZ2)
         UTFSIZE = UTFSIZE + 1                                :(UTFSIZE)
UTFSIZ2  IDENT(STR)                                 :S(RETURN)F(FRETURN)
*
EUTFSIZE
*
* UTF ANALOG FOR REPLACE()
*
         DEFINE("UTFREPLACE(IN,FROM,TO)T,R1,R2")          :(EUTFREPLACE)
*
UTFREPLACE
         T = TABLE()
* PEEL RUNES OFF INPUT AND OUTPUT LANGUAGES ONE AT A TIME
UTFREP1  FROM UTF.RUNE0 . R1 =                               :F(UTFREP2)
         TO UTF.RUNE0 . R2 =                                 :F(UTFREP2)
         T<R1> = R2                                           :(UTFREP1)
* BOTH INPUT AND OUTPUT LANGUAGES SHOULD NOW BE EMPTY
UTFREP2  DIFFER(FROM)                                        :S(FRETURN)
         DIFFER(TO)                                          :S(FRETURN)
* FREEZE TABLE FOR SNOBOL4+?
* PEEL RUNES INPUT ONE AT A TIME, FEED THRU TABLE
         UTFREPLACE =
UTFREP3  IN UTF.RUNE0 . R1 =                                 :F(UTFREP4)
         UTFREPLACE = UTFREPLACE (IDENT(T<R1>) R1, T<R1>)     :(UTFREP3)
UTFREP4  IDENT(IN)                                  :S(RETURN)F(FRETURN)
*
EUTFREPLACE
*
************************************************************************
*
* TESTS
*
*        &ANCHOR = 1
*        S = "Hello World!!"
*
*        OUTPUT = UTFREPLACE(S,&UCASE "!",&LCASE "?")
*
*L       S UTF.RUNE $ OUTPUT =                                     :S(L)
*
*        "HELLO WORLD!" UTFARB . OUTPUT RPOS(0)
*        "Hello World!" UTFARB UTFANY(&LCASE) . OUTPUT
*        "Hello World!" UTFANY(&UCASE) . OUTPUT
*
*        OUTPUT = RUNE(0)
*        OUTPUT = RUNE(127)
*        OUTPUT = '-------'
*        OUTPUT = RUNE(128)
*        OUTPUT = RUNE(255)
*        OUTPUT = RUNE(2047)
*        OUTPUT = '-------'
*        OUTPUT = RUNE(2048)
*        OUTPUT = RUNE(65535)
*        OUTPUT = '-------'
*        OUTPUT = RUNE(65536)
*        OUTPUT = RUNE(2097151)
*        OUTPUT = '-------'
*        OUTPUT = RUNE(2097152)
*        OUTPUT = RUNE(67108863)
*        OUTPUT = '-------'
*        OUTPUT = RUNE(67108864)
*        OUTPUT = RUNE(2147483647)
*
*END
*
* CE: .MSNOBOL4;
