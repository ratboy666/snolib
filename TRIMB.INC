-STITL TRIMB
-EJECT
*
-LINE 29 "TRIMB.lss"
************************************************************************
*                                                                      *
*               #######  ######   ###  #     #  ######                 *
*                  #     #     #   #   ##   ##  #     #                *
*                  #     #     #   #   # # # #  #     #                *
*                  #     ######    #   #  #  #  ######                 *
*                  #     #   #     #   #     #  #     #                *
*                  #     #    #    #   #     #  #     #                *
*                  #     #     #  ###  #     #  ######                 *
*                                                                      *
* TRIMB            TRIM BOTH LEFT AND RIGHT OF STRING                  *
*                                                                      *
************************************************************************
*
* TRIMB.lss
*
-LINE 6 "TRIMB.lss"
-PUBLIC TRIMB()
         DEFINE('TRIMB(S)')                                 :(TRIMB_END)
*
TRIMB    TRIMB = REVERSE(TRIM(REVERSE(TRIM(S))))               :(RETURN)
*
TRIMB_END
*
* CE: .MSNOBOL4;
