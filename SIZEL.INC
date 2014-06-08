-LINE 9 "SIZEL.lss"
-INCLUDE 'LINK.INC'
-STITL SIZEL
-EJECT
-LINE 38 "SIZEL.lss"
*
************************************************************************
*                                                                      *
*                #####   ###  #######  #######  #                      *
*               #     #   #        #   #        #                      *
*               #         #       #    #        #                      *
*                #####    #     #      #####    #                      *
*                     #   #    #       #        #                      *
*               #     #   #   #        #        #                      *
*                #####   ###  #######  #######  #######                *
*                                                                      *
* SIZEL                    SIZE OF LIST                                *
*                                                                      *
************************************************************************
*
* SIZEL.lss
*
-LINE 13 "SIZEL.lss"
-MODULE SIZEL
-PUBLIC SIZEL()
*
         DEFINE('SIZEL(L)')                                 :(END_SIZEL)
*
SIZEL    SIZEL = 0
SIZEL_2  SIZEL = DIFFER(L) SIZEL + 1                          :F(RETURN)
         L = NEXT(L)                                          :(SIZEL_2)
*
END_SIZEL
*
* CE: .MSNOBOL4;
