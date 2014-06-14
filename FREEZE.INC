-MODULE FREEZE
-LINE 7 "FREEZE.lss"
-INCLUDE 'SYSTEM.INC'
-IN72
-LINE 36 "FREEZE.lss"
-STITL FREEZE
-EJECT
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
-LINE 11 "FREEZE.lss"
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
