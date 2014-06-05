-LINE 12 "NOTP.lss"
-INCLUDE 'STACK.INC'
-STITL NOTP
-EJECT
-LINE 47 "NOTP.lss"
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
-LINE 16 "NOTP.lss"
-MODULE NOTP
-PUBLIC NOTP()
         DEFINE('NOTP(P)')                                   :(NOTP_END)
*
-LINE 28 "NOTP.lss"
NOTP     NOTP = PUSH() P *?(POP() PUSH(1)) FAIL |
+               *IDENT(POP())                                  :(RETURN)
*
NOTP_END
*
* CE: .MSNOBOL4;
