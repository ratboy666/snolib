-LINE 12 "REVL.lss"
-INCLUDE 'LINK.INC'
-STITL REVL
-EJECT
-LINE 46 "REVL.lss"
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
-LINE 16 "REVL.lss"
-MODULE REVL
-PUBLIC REVL()
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
