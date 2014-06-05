-STITL BQ
-EJECT
*
-LINE 69 "BQ.lss"
************************************************************************
*                                                                      *
*                          ######    #####                             *
*                          #     #  #     #                            *
*                          #     #  #     #                            *
*                          ######   #     #                            *
*                          #     #  #   # #                            *
*                          #     #  #    #                             *
*                          ######    #### #                            *
*                                                                      *
* BQ          EXECUTE A SHELL COMMAND LINE AND CAPTURE STDOUT          *
*                                                                      *
* P BUDNE, JUNE 20, 1994                                               *
*                                                                      *
************************************************************************
*
* BQ.lss
*
-LINE 15 "BQ.lss"
-WEAK DDT_ACTIVE, DDT_SUSPEND(), DDT_RESUME()
-PUBLIC BQ()
         DEFINE('BQ(COMMAND,OFS)DDTF')
         DEFINE('BQ2(COMMAND,OFS)X,UNIT')                      :(BQ_END)
*
-LINE 31 "BQ.lss"
BQ       DDTF = DDT_ACTIVE
         NE(DDTF) DDT_SUSPEND()
         BQ = BQ2(COMMAND, OFS)                                  :F(BQ3)
         NE(DDTF) DDT_RESUME()                                 :(RETURN)
BQ3      NE(DDTF) DDT_RESUME()                                :(FRETURN)
-LINE 43 "BQ.lss"
BQ2      UNIT = IO_FINDUNIT()                                :F(FRETURN)
         INPUT(.X, UNIT,, '|' COMMAND)                       :F(FRETURN)
         OFS = IDENT(OFS) ' '
         BQ2 = X                                                 :S(BQ4)
         ENDFILE(UNIT)
         DETACH(.X)                                           :(FRETURN)
BQ4      BQ2 = BQ2 OFS X                                         :S(BQ4)
         ENDFILE(UNIT)
         DETACH(.X)                                            :(RETURN)
*
BQ_END
*
* CE: .MSNOBOL4;
