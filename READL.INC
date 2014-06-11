-MODULE READL
-LINE 14 "READL.lss"
-INCLUDE 'LINK.INC'
-STITL READL
-LINE 46 "READL.lss"
-EJECT
*
************************************************************************
*                                                                      *
*             ######   #######     #     ######   #                    *
*             #     #  #          # #    #     #  #                    *
*             #     #  #         #   #   #     #  #                    *
*             ######   #####    #     #  #     #  #                    *
*             #   #    #        #######  #     #  #                    *
*             #    #   #        #     #  #     #  #                    *
*             #     #  #######  #     #  ######   #######              *
*                                                                      *
* READL                      READ LIST                                 *
*                                                                      *
************************************************************************
*
* READL.lss
*
-LINE 18 "READL.lss"
-PUBLIC READL()
*
         DEFINE('READL(P,IN)N,S')                           :(READL_END)
*
READL    P = IDENT(P) ABORT
         IN = IDENT(IN) .INPUT
         N = .READL
READL_1  S = $IN                                              :F(RETURN)
         S P                                                  :S(RETURN)
         $N = LINK(S)
         N = .NEXT($N)                                        :(READL_1)
*
READL_END
*
* CE: .MSNOBOL4;
