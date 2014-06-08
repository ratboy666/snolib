-LINE 10 "SIZET.lss"
-INCLUDE 'HASH.INC'
-INCLUDE 'SIZEA.INC'
-STITL SIZET
-EJECT
-LINE 38 "SIZET.lss"
*
************************************************************************
*                                                                      *
*                #####   ###  #######  #######  #######                *
*               #     #   #        #   #           #                   *
*               #         #       #    #           #                   *
*                #####    #     #      #####       #                   *
*                     #   #    #       #           #                   *
*               #     #   #   #        #           #                   *
*                #####   ###  #######  #######     #                   *
*                                                                      *
* SIZET                    SIZE OF TABLE                               *
*                                                                      *
************************************************************************
*
* SIZET.lss
*
-LINE 15 "SIZET.lss"
-MODULE SIZEL
-PUBLIC SIZET()
*
         DEFINE('SIZET(T)')                                 :(END_SIZET)
*
SIZET    SIZET =  SIZEA(KEYS_IN_TABLE(T))                      :(RETURN)
*
END_SIZET
*
* CE: .MSNOBOL4;
