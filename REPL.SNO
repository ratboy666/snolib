-STITL REPL
-EJECT
*
-LINE 38 "REPL.lss"
************************************************************************
*                                                                      *
*                   ######   #######  ######   #                       *
*                   #     #  #        #     #  #                       *
*                   #     #  #        #     #  #                       *
*                   ######   #####    ######   #                       *
*                   #   #    #        #        #                       *
*                   #    #   #        #        #                       *
*                   #     #  #######  #        #######                 *
*                                                                      *
* REPL                   REPLACE STRINGS                               *
*                                                                      *
************************************************************************
*
* REPL.lss
*
-LINE 11 "REPL.lss"
         DEFINE('REPL(S1,S2,S3)C,T,FINDC')                   :(REPL_END)
*
REPL     S2 LEN(1) . C =                                     :F(FRETURN)
         FINDC = BREAK(C) . T LEN(1)
         S2 = POS(0) S2
REPL_1   S1 FINDC =                                           :F(REPL_2)
         S1 S2 =                                              :F(REPL_3)
         REPL = REPL T S3                                      :(REPL_1)
REPL_3   REPL = REPL T C                                       :(REPL_1)
REPL_2   REPL = REPL S1                                        :(RETURN)
*
REPL_END
*
* CE: .MSNOBOL4;
