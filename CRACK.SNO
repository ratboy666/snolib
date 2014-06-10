-MODULE CRACK
-IN72
-LINE 16 "CRACK.lss"
-INCLUDE 'COUNT.INC'
-INCLUDE 'SEQ.INC'
-LINE 69 "CRACK.lss"
-STITL CRACK
-EJECT
*
************************************************************************
*                                                                      *
*               #####   ######      #      #####   #    #              *
*              #     #  #     #    # #    #     #  #   #               *
*              #        #     #   #   #   #        #  #                *
*              #        ######   #     #  #        ###                 *
*              #        #   #    #######  #        #  #                *
*              #     #  #    #   #     #  #     #  #   #               *
*               #####   #     #  #     #   #####   #    #              *
*                                                                      *
* CRACK                    STRING TO ARRAY                             *
*                                                                      *
************************************************************************
*
* CRACK.lss
*
-LINE 21 "CRACK.lss"
-PUBLIC CRACK(), %1
-PUBLIC COPYA()
*
         DEFINE('COPYA(A)I')
         DEFINE('CRACK_1(S)P')
         DEFINE('CRACK(S,B,F)I,PAT,N')
         DEFINE('CRACK_4(S)')
         OPSYN('%', 'CRACK_1', 1)                           :(CRACK_END)
*
COPYA    COPYA = ARRAY(PROTOTYPE(A))
         SEQ(' COPYA<I> = A<I>', .I)                           :(RETURN)
*
CRACK_1  P = IDENT(P) ','
         CRACK_1 = CRACK(S, P)                                 :(RETURN)
*
CRACK    F = IDENT(F) 'CRACK_4'
         IDENT(B, NULL)                                      :S(CRACK_3)
         S RTAB(1) B ABORT | REM . S = S B
         N = COUNT(S, B)
         EQ(N, 0)                                             :S(RETURN)
         CRACK = ARRAY(N)
         PAT = BREAK(B) . *CRACK<I> LEN(1)
CRACK_2  I = I + 1
         S PAT =                                              :F(RETURN)
         CRACK<I> = APPLY(F, CRACK<I>)             :S(CRACK_2)F(FRETURN)
CRACK_3  N = SIZE(S)
         EQ(N, 0)                                             :S(RETURN)
         CRACK = ARRAY(N)
         PAT = LEN(1) . *CRACK<I>                             :(CRACK_2)
*
CRACK_4  CRACK_4 = S                                           :(RETURN)
*
CRACK_END
*
* CE: .MSNOBOL4;
