-LINE 14 "TIMEGC.lss"
-INCLUDE 'LINK.INC'
-INCLUDE 'RESOL.INC'
-INCLUDE 'SYSTEM.INC'
-STITL TIMEGC
-EJECT
-LINE 71 "TIMEGC.lss"
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
-LINE 20 "TIMEGC.lss"
-MODULE TIMEGC
-PUBLIC TIMEGC()
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
         M = 50
         M = LT(RESOLUTION(), 0.9) 5000
         LT(TIMEGC, M * RESOLUTION())                         :S(TIMEGC)
         OUTPUT =
         OUTPUT = 'IN ' SYSTEM() ' ' K ' GARBAGE COLLECTS'
+           ' REQUIRED A TOTAL OF ' TIMEGC ' MILLISECONDS TO FREE '
+           FREED ' STORAGE UNITS.'
         TIMEGC = CONVERT(TIMEGC, 'REAL')
         OUTPUT = 'THIS AVERAGES TO ' (TIMEGC / K) ' MILLISECONDS PER'
+           ' GARBAGE COLLECT AND ' (TIMEGC * 1000000 / FREED)
+           ' NANOSECONDS PER STORAGE UNIT.'                   :(RETURN)
*
TIMEGC_END
*
* CE: .MSNOBOL4;
