-STITL SWAP
-EJECT
*
-LINE 30 "SWAP.lss"
************************************************************************
*                                                                      *
*                   #####   #     #     #     ######                   *
*                  #     #  #  #  #    # #    #     #                  *
*                  #        #  #  #   #   #   #     #                  *
*                   #####   #  #  #  #     #  ######                   *
*                        #  #  #  #  #######  #                        *
*                  #     #  #  #  #  #     #  #                        *
*                   #####    ## ##   #     #  #                        *
*                                                                      *
* SWAP                    SWAP TWO VARIABLES                           *
*                                                                      *
************************************************************************
*
* SWAP.lss
*
-LINE 7 "SWAP.lss"
         DEFINE('SWAP(SWAP_ARG1,SWAP_ARG2)')                 :(SWAP_END)
*
SWAP     SWAP = $SWAP_ARG1
         $SWAP_ARG1 = $SWAP_ARG2
         $SWAP_ARG2 = SWAP
         SWAP =                                                :(RETURN)
*
SWAP_END
*
* CE: .MSNOBOL4;