-LINE 10 "VDIFFER.lss"
-INCLUDE 'SYSTEM.INC'
-STITL VDIFFER
-EJECT
-LINE 37 "VDIFFER.lss"
*
************************************************************************
*                                                                      *
*      #     #  ######   ###  #######  #######  #######  ######        *
*      #     #  #     #   #   #        #        #        #     #       *
*      #     #  #     #   #   #        #        #        #     #       *
*      #     #  #     #   #   #####    #####    #####    ######        *
*       #   #   #     #   #   #        #        #        #   #         *
*        # #    #     #   #   #        #        #        #    #        *
*         #     ######   ###  #        #        #######  #     #       *
*                                                                      *
* VDIFFER            RETURN FIRST ARG IF DIFFER                        *
*                                                                      *
************************************************************************
*
* VDIFFER.lss
*
-LINE 14 "VDIFFER.lss"
-MODULE VDIFFER
         SYSTEM() 'CSNOBOL4'                             :S(VDIFFER_END)
-PUBLIC VDIFFER()
         DEFINE('VDIFFER(P1,P2)')                         :(VDIFFER_END)
*
VDIFFER  VDIFFER = DIFFER(P1, P2) P1                :F(FRETURN)S(RETURN)
*
VDIFFER_END
*
* CE: .MSNOBOL4;
