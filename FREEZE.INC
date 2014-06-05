-LINE 8 "FREEZE.lss"
-INCLUDE 'SYSTEM.INC'
-STITL FREEZE
-EJECT
-LINE 37 "FREEZE.lss"
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
-LINE 12 "FREEZE.lss"
-MODULE FREEZE
         SYSTEM() 'CSNOBOL4'                              :S(FREEZE_END)
-PUBLIC FREEZE(), THAW()
         DEFINE('FREEZE(X)')
         DEFINE('THAW(X)')                                 :(FREEZE_END)
*
FREEZE
THAW                                                           :(RETURN)
*
FREEZE_END
*
* CE: .MSNOBOL4;
