-STITL RESOL
-EJECT
*
-LINE 51 "RESOL.lss"
************************************************************************
*                                                                      *
*                 ######   #######   #####   #######  #                *
*                 #     #  #        #     #  #     #  #                *
*                 #     #  #        #        #     #  #                *
*                 ######   #####     #####   #     #  #                *
*                 #   #    #              #  #     #  #                *
*                 #    #   #        #     #  #     #  #                *
*                 #     #  #######   #####   #######  #######          *
*                                                                      *
* RESOL             TIMER RESOLUTION IN MILLISECONDS                   *
*                                                                      *
************************************************************************
*
* RESOL.lss
*
-LINE 12 "RESOL.lss"
-MODULE RESOL
-PUBLIC RESOLUTION()
         DEFINE('RESOLUTION()T,N,R,T2')                :(RESOLUTION_END)
*
RESOLUTION
         DIFFER(RESOLUTION_)                                 :S(RESOL_4)
         R = 0.0
         T = TIME()
RESOL_1  EQ(T, TIME())                                       :S(RESOL_1)
         T = TIME()
RESOL_2  T2 = TIME()
RESOL_3  EQ(T2, TIME())                                      :S(RESOL_3)
         RESOLUTION_ = TIME() - T
         R = R + (TIME() - T2)
         N = N + 1
         LE(N, 100000)                                       :S(RESOL_2)
         RESOLUTION_ = R / 100000
RESOL_4  RESOLUTION = RESOLUTION_                              :(RETURN)
*
RESOLUTION_END
*
* CE: .MSNOBOL4;
