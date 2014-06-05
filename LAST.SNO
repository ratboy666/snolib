-LINE 12 "LAST.lss"
-INCLUDE 'LINK.INC'
-STITL LAST
-EJECT
-LINE 40 "LAST.lss"
*
************************************************************************
*                                                                      *
*                  #           #      #####   #######                  *
*                  #          # #    #     #     #                     *
*                  #         #   #   #           #                     *
*                  #        #     #   #####      #                     *
*                  #        #######        #     #                     *
*                  #        #     #  #     #     #                     *
*                  #######  #     #   #####      #                     *
*                                                                      *
* LAST                 RETURN LAST LIST ELEMENT                        *
*                                                                      *
************************************************************************
*
* LAST.lss
*
-LINE 16 "LAST.lss"
-MODULE LAST
-PUBLIC LAST()
         DEFINE('LAST(L)')                                   :(LAST_END)
*
LAST     IDENT(L)                                            :S(FRETURN)
LAST_1   L = DIFFER(NEXT(L)) NEXT(L)                          :S(LAST_1)
         LAST = .NEXT(L)                                      :(NRETURN)
*
LAST_END
*
* CE: .MSNOBOL4;
