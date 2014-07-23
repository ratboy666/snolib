-STITL TRIMB
-EJECT
*
-LINE 38 "TRIMB.lss"
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
         DEFINE('LTRIM(S)')
         DEFINE('TRIMB(S)')                                 :(TRIMB_END)
*
LTRIM    LTRIM = REVERSE(TRIM(REVERSE(S)))                     :(RETURN)
TRIMB    TRIMB = LTRIM(TRIM(S))                                :(RETURN)
*
TRIMB_END
*
* CE: .MSNOBOL4;
