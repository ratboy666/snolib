-LINE 15 "READL.lss"
-INCLUDE 'LINK.INC'
-STITL READL
-EJECT
-LINE 47 "READL.lss"
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
-LINE 19 "READL.lss"
-MODULE READL
-PUBLIC READL()
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
