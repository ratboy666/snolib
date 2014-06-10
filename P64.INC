-STITL P64
-EJECT
*
-LINE 195 "P64.lss"
************************************************************************
*                                                                      *
*                       ######    ###   #   #                          *
*                       #     #  #   #  #   #                          *
*                       #     #  #      #   #                          *
*                       ######   ####   #####                          *
*                       #        #   #      #                          *
*                       #        #   #      #                          *
*                       #         ###       #                          *
*                                                                      *
* P64                    POINTER UTILITIES                             *
*                                                                      *
************************************************************************
*
* P64.lss
*
-LINE 22 "P64.lss"
-MODULE P64
-CASE 1
-LINE 27 "P64.lss"
-LINE 28 "P64.lss"
-LINE 29 "P64.lss"
-LINE 30 "P64.lss"
-LINE 31 "P64.lss"
-LINE 32 "P64.lss"
-LINE 37 "P64.lss"
         p64 = 'p64.c'
-LINE 124 "P64.lss"
-LINE 125 "P64.lss"
-LINE 126 "P64.lss"
-LINE 127 "P64.lss"
-LINE 128 "P64.lss"
-LINE 136 "P64.lss"
-PUBLIC PEEK_P(), PEEK_C(), PEEK_S(), PEEK_I(), PEEK_D(), PEEK_F()
-PUBLIC PEEK_LD()
-PUBLIC POKE_P(), POKE_C(), POKE_S(), POKE_I(), POKE_D(), POKE_F()
-PUBLIC POKE_LD()
*
         LOAD('PEEK_P(INTEGER)INTEGER', 'p64.so')
         LOAD('PEEK_C(INTEGER)INTEGER', 'p64.so')
         LOAD('PEEK_S(INTEGER)INTEGER', 'p64.so')
         LOAD('PEEK_I(INTEGER)INTEGER', 'p64.so')
         LOAD('PEEK_D(INTEGER)REAL', 'p64.so')
         LOAD('PEEK_F(INTEGER)REAL', 'p64.so')
         LOAD('PEEK_LD(INTEGER)REAL', 'p64.so')
         LOAD('POKE_P(INTEGER,INTEGER)', 'p64.so')
         LOAD('POKE_C(INTEGER,INTEGER)', 'p64.so')
         LOAD('POKE_S(INTEGER,INTEGER)', 'p64.so')
         LOAD('POKE_I(INTEGER,INTEGER)', 'p64.so')
         LOAD('POKE_D(INTEGER,REAL)', 'p64.so')
         LOAD('POKE_F(INTEGER,REAL)', 'p64.so')
         LOAD('POKE_LD(INTEGER,REAL)', 'p64.so')
         LOAD('MALLOC_(INTEGER)INTEGER', 'p64.so')
         LOAD('FREE_(INTEGER)', 'p64.so')
         LOAD('STRDUP_(STRING)INTEGER', 'p64.so')
         LOAD('STRLEN_(INTEGER)INTEGER', 'p64.so')
*
-LINE 165 "P64.lss"
-PUBLIC MALLOC(), FREE(), STRDUP(), STRLEN()
         DEFINE('MALLOC(N)')
         DEFINE('FREE(P)')
         DEFINE('STRDUP(S)')
         DEFINE('STRLEN(P)')                                  :(P64_END)
*
MALLOC   MALLOC = MALLOC_(N)                                   :(RETURN)
*
FREE     FREE_(P)                                              :(RETURN)
*
STRDUP   STRDUP = STRDUP_(S)                                   :(RETURN)
*
STRLEN   STRLEN = STRLEN_(P)                                   :(RETURN)
*
P64_END
*
* CE: .F.MSNOBOL4;
