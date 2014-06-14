-MODULE NOTP
-LINE 11 "NOTP.lss"
-INCLUDE 'STACK.INC'
-IN72
-LINE 46 "NOTP.lss"
-STITL NOTP
-EJECT
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
-PUBLIC NOTP()
*
         DEFINE('NOTP(P)')                                   :(NOTP_END)
*
-LINE 27 "NOTP.lss"
NOTP     NOTP = PUSH() P *?(POP() PUSH(1)) FAIL |
+               *IDENT(POP())                                  :(RETURN)
*
NOTP_END
*
* CE: .MSNOBOL4;
