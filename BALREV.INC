-STITL BALREV
-EJECT
*
-LINE 37 "BALREV.lss"
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
-LINE 14 "BALREV.lss"
-MODULE BALREV
-PUBLIC BALREV()
         DEFINE('BALREV(S)')                               :(BALREV_END)
*
BALREV   BALREV = REPLACE(REVERSE(S), ')(', '()')              :(RETURN)
*
BALREV_END
*
* CE: .MSNOBOL4;
