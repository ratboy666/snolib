-STITL ROTATER
-EJECT
*
-LINE 38 "ROTATER.lss"
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
-MODULE ROTATER
-PUBLIC ROTATER()
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
