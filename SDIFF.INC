-MODULE SDIFF
-LINE 10 "SDIFF.lss"
-IN72
-LINE 38 "SDIFF.lss"
-STITL SDIFF
-EJECT
*
************************************************************************
*                                                                      *
*                #####   ######   ###  #######  #######                *
*               #     #  #     #   #   #        #                      *
*               #        #     #   #   #        #                      *
*                #####   #     #   #   #####    #####                  *
*                     #  #     #   #   #        #                      *
*               #     #  #     #   #   #        #                      *
*                #####   ######   ###  #        #                      *
*                                                                      *
* SDIFF                     SET DIFFERENCE                             *
*                                                                      *
************************************************************************
*
* SDIFF.lss
*
-LINE 13 "SDIFF.lss"
-PUBLIC SDIFF()
*
         DEFINE('SDIFF(S1,S2)')                             :(SDIFF_END)
*
SDIFF    SDIFF = S1
         IDENT(S2, NULL)                                      :S(RETURN)
         S2 = SPAN(S2)
SDIFF_1  SDIFF S2 =                                 :S(SDIFF_1)F(RETURN)
*
SDIFF_END
*
* CE: .MSNOBOL4;
