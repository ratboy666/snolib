-MODULE REDEFINE
-LINE 16 "REDEFINE.lss"
-IN72
-LINE 58 "REDEFINE.lss"
-STITL REDEFINE
-EJECT
*
************************************************************************
*                                                                      *
*  ######   #######  ######   #######  #######  ###  #     #  #######  *
*  #     #  #        #     #  #        #         #   ##    #  #        *
*  #     #  #        #     #  #        #         #   # #   #  #        *
*  ######   #####    #     #  #####    #####     #   #  #  #  #####    *
*  #   #    #        #     #  #        #         #   #   # #  #        *
*  #    #   #        #     #  #        #         #   #    ##  #        *
*  #     #  #######  ######   #######  #        ###  #     #  #######  *
*                                                                      *
* REDEFINE             REDEFINE OPERATORS                              *
*                                                                      *
************************************************************************
*
* REDEFINE.lss
*
* FMGW:
*
* - ADD REDEFINERESTORE() TO ALLOW INFINIP.SNO TO ENABLE/DISABLE
*   LONG INTEGERS
* - FACTOR REDEFINECOMMON() TO ALLOW REDEFINE() AND REDEFINERESTORE()
*   TO SHARE CODE
*
-LINE 19 "REDEFINE.lss"
-PUBLIC REDEFINE(), REDEFINERESTORE()
*
         DEFINE('REDEFINE(OP,DEF,LBL)NAME,N,FLAG')
         DEFINE('REDEFINERESTORE(OP,DEF)NAME,N,FLAG')
         DEFINE('REDEFINECOMMON()')                      :(REDEFINE_END)
*
REDEFINECOMMON
         DEF BREAK('(') . NAME '(' BREAK('),') LEN(1) . FLAG
         N = 1
         N = IDENT(FLAG, ',') 2
         N = IDENT(OP)
         OP = IDENT(OP) NAME
                                                               :(RETURN)
*
REDEFINE REDEFINECOMMON()
         OPSYN(NAME '.', OP, N)
         DEFINE(DEF, LBL)
         OPSYN(OP, NAME, N)                                    :(RETURN)
*
REDEFINERESTORE
         REDEFINECOMMON()
         OPSYN(OP, NAME '.', N)                                :(RETURN)
*
REDEFINE_END
*
* CE: .MSNOBOL4;
