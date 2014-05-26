-LINE 13 "TIMEGC.lss"
-INCLUDE 'LINK.INC'
-INCLUDE 'SYSTEM.INC'
-INCLUDE 'RESOL.INC'
-STITL TIMEGC
-EJECT
-LINE 70 "TIMEGC.lss"
*
************************************************************************
*                                                                      *
*           #######  ###  #     #  #######   #####    #####            *
*              #      #   ##   ##  #        #     #  #     #           *
*              #      #   # # # #  #        #        #                 *
*              #      #   #  #  #  #####    #  ####  #                 *
*              #      #   #     #  #        #     #  #                 *
*              #      #   #     #  #        #     #  #     #           *
*              #     ###  #     #  #######   #####    #####            *
*                                                                      *
* TIMEGC                TIME GARBAGE COLLECT                           *
*                                                                      *
************************************************************************
*
* TIMEGC.lss
*
-LINE 19 "TIMEGC.lss"
         DEFINE('TIMEGC(N)I,S,A,L,T,K,FREED')              :(TIMEGC_END)
*
TIMEGC   I = ; S = ; A = ; L =
         COLLECT()
         N = IDENT(N) 25
         A = ARRAY(N)
TIMEGC_1 I = I + 1
         $I = DUPL(' ', 78) I
         A<I> = DUPL('*', I)
         L = LINK(NULL, L)
         GE(I, N)                                           :F(TIMEGC_1)
         STREM = COLLECT()
TIMEGC_2 $I = ; A<I> = ; L = NEXT(L)
         I = I - 2 GT(I, 2)                                 :S(TIMEGC_2)
         T = TIME()
         FREED = FREED + (COLLECT() - STREM)
         TIMEGC = TIMEGC + (TIME() - T)
         K = K + 1
*        LT(TIMEGC, 50 * RESOLUTION())                        :S(TIMEGC)
         LT(TIMEGC, 5000 * RESOLUTION())                      :S(TIMEGC)
         OUTPUT =
         OUTPUT = 'IN ' SYSTEM() ' ' K ' GARBAGE COLLECTS'
+           ' REQUIRED A TOTAL OF ' TIMEGC ' MILLISECONDS TO FREE '
+           FREED ' STORAGE UNITS.'
         TIMEGC = CONVERT(TIMEGC, 'REAL')
*        OUTPUT = 'THIS AVERAGES TO ' (TIMEGC / K) 'MSEC. PER'
*+          ' GARBAGE COLLECT AND ' (TIMEGC / FREED) ' MSEC.'
*+          ' PER STORAGE UNIT.'                               :(RETURN)
         OUTPUT = 'THIS AVERAGES TO ' (TIMEGC / K) 'MSEC. PER'
+           ' GARBAGE COLLECT AND ' (TIMEGC * 1000 / FREED) ' USEC.'
+           ' PER STORAGE UNIT.'                               :(RETURN)
*
TIMEGC_END
*
* CE: .MSNOBOL4;