-LINE 12 "BRKREM.lss"
-INCLUDE 'SDIFF.INC'
-STITL BRKREM
-EJECT
-LINE 42 "BRKREM.lss"
*
************************************************************************
*                                                                      *
*                                                                      *
*         ######   ######   #    #  ######   #######  #     #          *
*         #     #  #     #  #   #   #     #  #        ##   ##          *
*         #     #  #     #  #  #    #     #  #        # # # #          *
*         ######   ######   ###     ######   #####    #  #  #          *
*         #     #  #   #    #  #    #   #    #        #     #          *
*         #     #  #    #   #   #   #    #   #        #     #          *
*         ######   #     #  #    #  #     #  #######  #     #          *
*                                                                      *
* BRKREM                   BREAK(S) OR REM                             *
*                                                                      *
************************************************************************
*
* BRKREM.lss
*
-LINE 16 "BRKREM.lss"
-MODULE BRKREM
-PUBLIC BRKREM()
         DEFINE('BRKREM(S)CS')                             :(BRKREM_END)
*
BRKREM   BRKREM = IDENT(S) REM                                :S(RETURN)
         CS = SDIFF(&ALPHABET, S)
         IDENT(CS)                                            :S(RETURN)
         BRKREM = RPOS(0) | SPAN(CS) RPOS(0) | BREAK(S)
                                                               :(RETURN)
*
BRKREM_END
*
* CE: .MSNOBOL4;
