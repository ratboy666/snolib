-LINE 4 "FREEZE.lss"
-INCLUDE 'SYSTEM.INC'
-STITL FREEZE
-EJECT
-LINE 31 "FREEZE.lss"
*
************************************************************************
*                                                                      *
*         #######  ######   #######  #######  #######  #######         *
*         #        #     #  #        #             #   #               *
*         #        #     #  #        #            #    #               *
*         #####    ######   #####    #####      #      #####           *
*         #        #   #    #        #         #       #               *
*         #        #    #   #        #        #        #               *
*         #        #     #  #######  #######  #######  #######         *
*                                                                      *
* FREEZE            FREEZE AND THAW FOR SPITBOL                        *
*                                                                      *
************************************************************************
*
* FREEZE.lss
*
-LINE 8 "FREEZE.lss"
         SYSTEM() 'CSNOBOL4'                              :S(FREEZE_END)
         DEFINE('FREEZE(X)')
         DEFINE('THAW(X)')                                 :(FREEZE_END)
*
FREEZE
THAW                                                           :(RETURN)
*
FREEZE_END
*
* CE: .MSNOBOL4;
