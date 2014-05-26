-LINE 6 "VDIFFER.lss"
-INCLUDE 'SYSTEM.INC'
-STITL VDIFFER
-EJECT
-LINE 31 "VDIFFER.lss"
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
-LINE 10 "VDIFFER.lss"
         SYSTEM() 'CSNOBOL4'                             :S(VDIFFER_END)
         DEFINE('VDIFFER(P1,P2)')                         :(VDIFFER_END)
*
VDIFFER  VDIFFER = DIFFER(P1, P2) P1                :F(FRETURN)S(RETURN)
*
VDIFFER_END
*
* CE: .MSNOBOL4;
