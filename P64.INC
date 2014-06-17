-MODULE P64
-LINE 17 "P64.lss"
-IN72
-LINE 147 "P64.lss"
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
-LINE 20 "P64.lss"
-LINE 21 "P64.lss"
-LINE 22 "P64.lss"
-LINE 23 "P64.lss"
-LINE 24 "P64.lss"
-LINE 25 "P64.lss"
-LINE 30 "P64.lss"
         p64 = 'p64.c'
-LINE 101 "P64.lss"
-LINE 102 "P64.lss"
-LINE 103 "P64.lss"
-LINE 104 "P64.lss"
-LINE 105 "P64.lss"
-LINE 113 "P64.lss"
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
