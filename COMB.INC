-STITL COMB
-EJECT
*
-LINE 28 "COMB.lss"
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
-LINE 7 "COMB.lss"
         DEFINE('COMB(N,M)')                                 :(COMB_END)
*
COMB     COMB = EQ(M, 0) 1                                    :S(RETURN)
         COMB = COMB(N - 1, M - 1) * N / M                     :(RETURN)
*
COMB_END
*
* CE: .MSNOBOL4;