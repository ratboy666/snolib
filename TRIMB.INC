-STITL TRIMB
-EJECT
*
-LINE 36 "TRIMB.lss"
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
-LINE 12 "TRIMB.lss"
-MODULE TRIMB
-PUBLIC TRIMB()
         DEFINE('TRIMB(S)')                                 :(TRIMB_END)
*
TRIMB    TRIMB = REVERSE(TRIM(REVERSE(TRIM(S))))               :(RETURN)
*
TRIMB_END
*
* CE: .MSNOBOL4;
