-STITL P64
-EJECT
*
-LINE 615 "P64.lss"
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
* P64                64 BIT PARAMETER HANDLING                         *
*                                                                      *
************************************************************************
*
* P64.lss
*
-LINE 54 "P64.lss"
-CASE 1
-LINE 63 "P64.lss"
-LINE 65 "P64.lss"
-LINE 66 "P64.lss"
-LINE 67 "P64.lss"
-LINE 68 "P64.lss"
-LINE 69 "P64.lss"
-LINE 76 "P64.lss"
         p64.h = 'p64.h'
-LINE 95 "P64.lss"
         p64 = 'p64.c'
-LINE 381 "P64.lss"
-LINE 382 "P64.lss"
-LINE 383 "P64.lss"
-LINE 384 "P64.lss"
-LINE 385 "P64.lss"
-LINE 396 "P64.lss"
         LOAD('GET_PHI()INTEGER', 'p64.so')
         LOAD('GET_PLO()INTEGER', 'p64.so')
         LOAD('SET_PHI(INTEGER)', 'p64.so')
         LOAD('SET_PLO(INTEGER)', 'p64.so')
-PUBLIC GET_P(), SET_P()
-PUBLIC P_TO_P2(), P_TO_P3(), P_TO_P4(), P2_TO_P(), P3_TO_P(), P4_TO_P()
         LOAD('P_TO_P2()', 'p64.so')
         LOAD('P_TO_P3()', 'p64.so')
         LOAD('P_TO_P4()', 'p64.so')
         LOAD('P2_TO_P()', 'p64.so')
         LOAD('P3_TO_P()', 'p64.so')
         LOAD('P4_TO_P()', 'p64.so')
-PUBLIC SET_F(), SET_D(), SET_LD(), GET_F(), GET_D(), GET_LD(), GET_S()
         LOAD('SET_F(REAL)', 'p64.so')
         LOAD('SET_D(REAL)', 'p64.so')
         LOAD('SET_LD(REAL)', 'p64.so')
         LOAD('GET_F()REAL', 'p64.so')
         LOAD('GET_D()REAL', 'p64.so')
         LOAD('GET_LD()REAL', 'p64.so')
         LOAD('GET_S()STRING', 'p64.so')
-PUBLIC SWAP_P()
         LOAD('SWAP_P()', 'p64.so')
         LOAD('PEEK_P_()', 'p64.so')
         LOAD('PEEK_C_()INTEGER', 'p64.so')
         LOAD('PEEK_S_()INTEGER', 'p64.so')
         LOAD('PEEK_I_()INTEGER', 'p64.so')
         LOAD('PEEK_D_()', 'p64.so')
         LOAD('PEEK_F_()', 'p64.so')
         LOAD('PEEK_LD_()', 'p64.so')
         LOAD('POKE_P_()', 'p64.so')
         LOAD('POKE_C_(INTEGER)', 'p64.so')
         LOAD('POKE_S_(INTEGER)', 'p64.so')
         LOAD('POKE_I_(INTEGER)', 'p64.so')
         LOAD('POKE_D_()', 'p64.so')
         LOAD('POKE_F_()', 'p64.so')
         LOAD('POKE_LD_()', 'p64.so')
         LOAD('MALLOC_(INTEGER)', 'p64.so')
         LOAD('FREE_()', 'p64.so')
         LOAD('STRDUP_(STRING)', 'p64.so')
         LOAD('STRLEN_()INTEGER', 'p64.so')
-PUBLIC PEEK_P(), PEEK_C(), PEEK_S(), PEEK_I(), PEEK_D(), PEEK_F()
-PUBLIC PEEK_LD()
-PUBLIC POKE_P(), POKE_C(), POKE_S(), POKE_I(), POKE_D(), POKE_F()
-PUBLIC POKE_LD()
*
-LINE 483 "P64.lss"
         DEFINE('GET_P()LO,HI')
         DEFINE('SET_P(P)LO,HI')
         DEFINE('PEEK_P(P)')
         DEFINE('PEEK_C(P)')
         DEFINE('PEEK_S(P)')
         DEFINE('PEEK_I(P)')
         DEFINE('PEEK_D(P)')
         DEFINE('PEEK_F(P)')
         DEFINE('PEEK_LD(P)')
         DEFINE('POKE_P(P,P2)')
         DEFINE('POKE_C(P,C)')
         DEFINE('POKE_S(P,S)')
         DEFINE('POKE_I(P,I)')
         DEFINE('POKE_D(P,D)')
         DEFINE('POKE_F(P,F)')
         DEFINE('POKE_LD(P,LD)')
         DEFINE('MALLOC(N)')
         DEFINE('FREE(P)')
         DEFINE('STRDUP(S)')
         DEFINE('STRLEN(P)')
-PUBLIC MALLOC(), FREE(), STRDUP(), STRLEN()
                                                              :(P64_END)
*
GET_P    HI = GET_PHI()
         HI = HI * (2 ** 32)
         LO = GET_PLO()
         LO = LT(LO, 0) LO + (2 ** 32)
         GET_P = HI + LO                                       :(RETURN)
*
SET_P    HI = P / (2 ** 32)
         LO = REMDR(P, 2 ** 32)
         SET_PHI(HI)
         SET_PLO(LO)                                           :(RETURN)
*
PEEK_P   SET_P(P)
         PEEK_P_()
         PEEK_P = GET_P()                                      :(RETURN)
*
PEEK_C   SET_P(P)
         PEEK_C = PEEK_C_()                                    :(RETURN)
*
PEEK_S   SET_P(P)
         PEEK_S = PEEK_S_()                                    :(RETURN)
*
PEEK_I   SET_P(P)
         PEEK_I = PEEK_I_()                                    :(RETURN)
*
PEEK_D   SET_P(P)
         PEEK_D_()
         PEEK_D = GET_D()                                      :(RETURN)
*
PEEK_F   SET_P(P)
         PEEK_F_()
         PEEK_F = GET_F()                                      :(RETURN)
*
PEEK_LD  SET_P(P)
         PEEK_LD_()
         PEEK_LD = GET_LD()                                    :(RETURN)
*
POKE_P   SET_P(P2)
         P_TO_P2()
         SET_P(P)
         POKE_P_()                                             :(RETURN)
*
POKE_C   SET_P(P)
         POKE_C_(C)                                            :(RETURN)
*
POKE_S   SET_P(P)
         POKE_S_(S)                                            :(RETURN)
*
POKE_I   SET_P(P)
         POKE_I_(I)                                            :(RETURN)
*
POKE_D   SET_P(P)
         SET_D(D)
         POKE_D_()                                             :(RETURN)
*
POKE_F   SET_P(P)
         SET_F(F)
         POKE_F_()                                             :(RETURN)
*
POKE_LD  SET_P(P)
         SET_LD(LD)
         POKE_LD_()                                            :(RETURN)
*
MALLOC   MALLOC_(N)
         MALLOC = GET_P()                                      :(RETURN)
*
FREE     SET_P(P)
         FREE_()                                               :(RETURN)
*
STRDUP   STRDUP_(S)
         STRDUP = GET_P()                                      :(RETURN)
*
STRLEN   SET_P(P)
         STRLEN = STRLEN_()                                    :(RETURN)
*
P64_END
*
* CE: .F.MSNOBOL4;
