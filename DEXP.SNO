-MODULE DEXP
-LINE 13 "DEXP.lss"
-IN72
-LINE 41 "DEXP.lss"
-STITL DEXP
-EJECT
*
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
-LINE 16 "DEXP.lss"
-PUBLIC DEXP()
*
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
