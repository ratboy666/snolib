-LINE 12 "SKIM.lss"
-INCLUDE 'SDIFF.INC'
-STITL SKIM
-EJECT
-LINE 41 "SKIM.lss"
*
************************************************************************
*                                                                      *
*                                                                      *
*                    #####   #    #  ###  #     #                      *
*                   #     #  #   #    #   ##   ##                      *
*                   #        #  #     #   # # # #                      *
*                    #####   ###      #   #  #  #                      *
*                         #  #  #     #   #     #                      *
*                   #     #  #   #    #   #     #                      *
*                    #####   #    #  ###  #     #                      *
*                                                                      *
* SKIM                 SKIM UNIQUE CHARACTERS                          *
*                                                                      *
************************************************************************
*
* SKIM.lss
*
-LINE 16 "SKIM.lss"
-MODULE SKIM
-PUBLIC SKIM()
         DEFINE('SKIM(S)C')                                  :(SKIM_END)
*
SKIM     S LEN(1) . C =                                       :F(RETURN)
         SKIM C                                               :S(SKIM_D)
         SKIM = SKIM C                                           :(SKIM)
SKIM_D   S = SDIFF(S, SKIM)                                      :(SKIM)
*
SKIM_END
*
* CE: .MSNOBOL4;
