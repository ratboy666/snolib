-STITL COUNT
-EJECT
*
-LINE 31 "COUNT.lss"
************************************************************************
*                                                                      *
*               #####   #######  #     #  #     #  #######             *
*              #     #  #     #  #     #  ##    #     #                *
*              #        #     #  #     #  # #   #     #                *
*              #        #     #  #     #  #  #  #     #                *
*              #        #     #  #     #  #   # #     #                *
*              #     #  #     #  #     #  #    ##     #                *
*               #####   #######   #####   #     #     #                *
*                                                                      *
* COUNT              COUNT STRING OCCURRENCES                          *
*                                                                      *
* COUNT(S1,S2) COUNTS THE NUMBER OF OCCURRENCES OF STRING S2 IN STRING *
* S1.                                                                  *
*                                                                      *
************************************************************************
*
* COUNT.lss
*
-LINE 6 "COUNT.lss"
         DEFINE('COUNT(S1,S2)FIRST,REST,P')                 :(COUNT_END)
*
COUNT    COUNT = 0
         S2 LEN(1) . FIRST REM . REST                         :F(RETURN)
         P = POS(0) BREAKX(FIRST) S2
COUNT_1  S1 P = REST                                          :F(RETURN)
         COUNT = COUNT + 1                                    :(COUNT_1)
*
COUNT_END
*
* CE: .MSNOBOL4;
