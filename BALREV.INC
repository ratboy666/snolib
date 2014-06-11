-MODULE BALREV
-LINE 11 "BALREV.lss"
-IN72
-LINE 37 "BALREV.lss"
-STITL BALREV
-EJECT
*
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
-PUBLIC BALREV()
*
         DEFINE('BALREV(S)')                               :(BALREV_END)
*
BALREV   BALREV = REPLACE(REVERSE(S), ')(', '()')              :(RETURN)
*
BALREV_END
*
* CE: .MSNOBOL4;
