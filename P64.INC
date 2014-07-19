-MODULE P64
-LINE 37 "P64.lss"
-IN72
-LINE 217 "P64.lss"
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
-LINE 40 "P64.lss"
-LINE 41 "P64.lss"
-LINE 42 "P64.lss"
-LINE 43 "P64.lss"
-LINE 44 "P64.lss"
-LINE 45 "P64.lss"
-LINE 50 "P64.lss"
         p64 = 'p64.c'
-LINE 164 "P64.lss"
-LINE 165 "P64.lss"
-LINE 166 "P64.lss"
-LINE 167 "P64.lss"
-LINE 168 "P64.lss"
-LINE 176 "P64.lss"
-PUBLIC PEEK_STRING(), POKE_STRING(), PEEK_BUFFER(), POKE_BUFFER()
*
         LOAD('PEEK_STRING(INTEGER)STRING', 'p64.so')
         LOAD('POKE_STRING(INTEGER,STRING)', 'p64.so')
         LOAD('PEEK_BUFFER(INTEGER,INTEGER)STRING', 'p64.so')
         LOAD('POKE_BUFFER(INTEGER,STRING)', 'p64.so')
*
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
*
* CE: .F.MSNOBOL4;
