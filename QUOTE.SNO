-MODULE QUOTE
-LINE 11 "QUOTE.lss"
-INCLUDE 'REPL.INC'
-IN72
-LINE 38 "QUOTE.lss"
-STITL QUOTE
-EJECT
*
************************************************************************
*                                                                      *
*               #####   #     #  #######  #######  #######             *
*              #     #  #     #  #     #     #     #                   *
*              #     #  #     #  #     #     #     #                   *
*              #     #  #     #  #     #     #     #####               *
*              #   # #  #     #  #     #     #     #                   *
*              #    #   #     #  #     #     #     #                   *
*               #### #   #####   #######     #     #######             *
*                                                                      *
* QUOTE                      QUOTE A STRING                            *
*                                                                      *
************************************************************************
*
* QUOTE.lss
*
-LINE 15 "QUOTE.lss"
-PUBLIC QUOTE()
*
         DEFINE('QUOTE(S)Q,QQ')                             :(QUOTE_END)
*
QUOTE    Q = "'"; QQ = '"'
         QUOTE = Q REPL(S, Q, Q ' ' QQ Q QQ ' ' Q) Q           :(RETURN)
*
QUOTE_END
*
* CE: .MSNOBOL4;
