-LINE 11 "NOTP.lss"
-INCLUDE 'STACK.INC'
-STITL NOTP
-EJECT
-LINE 46 "NOTP.lss"
*
************************************************************************
*                                                                      *
*                   #     #  #######  #######  ######                  *
*                   ##    #  #     #     #     #     #                 *
*                   # #   #  #     #     #     #     #                 *
*                   #  #  #  #     #     #     ######                  *
*                   #   # #  #     #     #     #                       *
*                   #    ##  #     #     #     #                       *
*                   #     #  #######     #     #                       *
*                                                                      *
* NOTP                       INVERT PATTERN                            *
*                                                                      *
************************************************************************
*
* NOTP.lss
*
-LINE 15 "NOTP.lss"
-MODULE NOTP
-PUBLIC NOTP()
         DEFINE('NOTP(P)')                                   :(NOTP_END)
*
-LINE 27 "NOTP.lss"
NOTP     NOTP = PUSH() P *?(POP() PUSH(1)) FAIL |
+               *IDENT(POP())                                  :(RETURN)
*
NOTP_END
*
* CE: .MSNOBOL4;
