-MODULE ROTATER
-LINE 9 "ROTATER.lss"
-IN72
-LINE 38 "ROTATER.lss"
-STITL ROTATER
-EJECT
*
************************************************************************
*                                                                      *
*    ######   #######  #######     #     #######  #######  ######      *
*    #     #  #     #     #       # #       #     #        #     #     *
*    #     #  #     #     #      #   #      #     #        #     #     *
*    ######   #     #     #     #     #     #     #####    ######      *
*    #   #    #     #     #     #######     #     #        #   #       *
*    #    #   #     #     #     #     #     #     #        #    #      *
*    #     #  #######     #     #     #     #     #######  #     #     *
*                                                                      *
* ROTATER                    ROTATE STRING                             *
*                                                                      *
************************************************************************
*
* ROTATER.lss
*
-LINE 12 "ROTATER.lss"
-PUBLIC ROTATER()
*
         DEFINE('ROTATER(S,N)S1')                         :(ROTATER_END)
*
ROTATER  IDENT(S)                                             :S(RETURN)
         N = REMDR(N, SIZE(S))
         N = LT(N, 0) SIZE(S) + N
         S RTAB(N) . S  REM . S1 = S1 S
         ROTATER = S                                           :(RETURN)
*
ROTATER_END
*
* CE: .MSNOBOL4;
