-STITL BALREV
-EJECT
*
-LINE 29 "BALREV.lss"
************************************************************************
*                                                                      *
*           ######      #     #        ######   #######  #     #       *
*           #     #    # #    #        #     #  #        #     #       *
*           #     #   #   #   #        #     #  #        #     #       *
*           ######   #     #  #        ######   #####    #     #       *
*           #     #  #######  #        #   #    #         #   #        *
*           #     #  #     #  #        #    #   #          # #         *
*           ######   #     #  #######  #     #  #######     #          *
*                                                                      *
* BALREV                   BALANCED REVERSE                            *
*                                                                      *
************************************************************************
*
* BALREV.lss
*
-LINE 8 "BALREV.lss"
         DEFINE('BALREV(S)')                               :(BALREV_END)
*
BALREV   BALREV = REPLACE(REVERSE(S), ')(', '()')              :(RETURN)
*
BALREV_END
*
* CE: .MSNOBOL4;