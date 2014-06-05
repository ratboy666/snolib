-LINE 11 "QUOTE.lss"
-INCLUDE 'REPL.INC'
-STITL QUOTE
-EJECT
-LINE 38 "QUOTE.lss"
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
-MODULE QUOTE
-PUBLIC QUOTE()
         DEFINE('QUOTE(S)Q,QQ')                             :(QUOTE_END)
*
QUOTE    Q = "'"; QQ = '"'
         QUOTE = Q REPL(S, Q, Q ' ' QQ Q QQ ' ' Q) Q           :(RETURN)
*
QUOTE_END
*
* CE: .MSNOBOL4;
