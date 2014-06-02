-STITL DEXP
-EJECT
*
-LINE 34 "DEXP.lss"
************************************************************************
*                                                                      *
*                   ######   #######  #     #  ######                  *
*                   #     #  #         #   #   #     #                 *
*                   #     #  #          # #    #     #                 *
*                   #     #  #####       #     ######                  *
*                   #     #  #          # #    #                       *
*                   #     #  #         #   #   #                       *
*                   ######   #######  #     #  #                       *
*                                                                      *
* DEXP                 SIMPLE FUNCTION DEFINTION                       *
*                                                                      *
************************************************************************
*
* DEXP.lss
*
-LINE 11 "DEXP.lss"
         DEFINE('DEXP(PROTO)NAME,ARGS')                      :(DEXP_END)
*
DEXP     PROTO POS(0) SPAN(' ') =
         PROTO BREAK('(') . NAME BAL . ARGS = NAME
         CODE(NAME ' ' PROTO ' :S(RETURN)F(FRETURN)')
         DEFINE(NAME ARGS)                                     :(RETURN)
*
DEXP_END
*
* CE: .MSNOBOL4;
