-STITL RESOL
-EJECT
*
-LINE 38 "RESOL.lss"
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
-LINE 7 "RESOL.lss"
         DEFINE('RESOLUTION()T,N,R')                   :(RESOLUTION_END)
*
RESOLUTION
         DIFFER(RESOLUTION_)                                 :S(RESOL_4)
         T = TIME()
RESOL_1  EQ(T, TIME())                                       :S(RESOL_1)
RESOL_2  T = TIME()
RESOL_3  EQ(T, TIME())                                       :S(RESOL_3)
         R = R + (TIME() - T)
         N = N + 1
         LE(N, 100000)                                       :S(RESOL_2)
         RESOLUTION_ = R / 100000
RESOL_4  RESOLUTION = RESOLUTION_                              :(RETURN)
*
RESOLUTION_END
*
* CE: .MSNOBOL4;
