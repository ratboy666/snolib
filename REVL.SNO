-LINE 11 "REVL.lss"
-INCLUDE 'LINK.INC'
-STITL REVL
-EJECT
-LINE 43 "REVL.lss"
*
************************************************************************
*                                                                      *
*                    ######   #######  #     #  #                      *
*                    #     #  #        #     #  #                      *
*                    #     #  #        #     #  #                      *
*                    ######   #####    #     #  #                      *
*                    #   #    #         #   #   #                      *
*                    #    #   #          # #    #                      *
*                    #     #  #######     #     #######                *
*                                                                      *
* REVL                      REVERSE LIST                               *
*                                                                      *
************************************************************************
*
* REVL.lss
*
-LINE 15 "REVL.lss"
         DEFINE('REVL(L)T')                                  :(REVL_END)
*
REVL     REVL = L
         IDENT(DATATYPE(L), 'LINK')                           :F(RETURN)
         L = NEXT(REVL)
         NEXT(REVL) =
REVL_1   IDENT(L)                                             :S(RETURN)
         T = NEXT(L)
         NEXT(L) = REVL
         REVL = L
         L = T                                                 :(REVL_1)
*
REVL_END
*
* CE: .MSNOBOL4;
