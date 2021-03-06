-MODULE COMB
-LINE 9 "COMB.lss"
-IN72
-LINE 35 "COMB.lss"
-STITL COMB
-EJECT
*
************************************************************************
*                                                                      *
*                     #####   #######  #     #  ######                 *
*                    #     #  #     #  ##   ##  #     #                *
*                    #        #     #  # # # #  #     #                *
*                    #        #     #  #  #  #  ######                 *
*                    #        #     #  #     #  #     #                *
*                    #     #  #     #  #     #  #     #                *
*                     #####   #######  #     #  ######                 *
*                                                                      *
* COMB                        COMBINATIONS                             *
*                                                                      *
************************************************************************
*
* COMB.lss
*
-LINE 12 "COMB.lss"
-PUBLIC COMB()
*
         DEFINE('COMB(N,M)')                                 :(COMB_END)
*
COMB     COMB = EQ(M, 0) 1                                    :S(RETURN)
         COMB = COMB(N - 1, M - 1) * N / M                     :(RETURN)
*
COMB_END
*
* CE: .MSNOBOL4;
