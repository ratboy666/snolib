-MODULE P64
-LINE 19 "P64.lss"
-IN72
-LINE 190 "P64.lss"
-CASE 1
-STITL P64
-EJECT
*
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
-LINE 23 "P64.lss"
-LINE 24 "P64.lss"
-LINE 25 "P64.lss"
-LINE 26 "P64.lss"
-LINE 27 "P64.lss"
-LINE 32 "P64.lss"
         p64 = 'p64.c'
-LINE 119 "P64.lss"
-LINE 120 "P64.lss"
-LINE 121 "P64.lss"
-LINE 122 "P64.lss"
-LINE 123 "P64.lss"
-LINE 131 "P64.lss"
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
-LINE 160 "P64.lss"
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
