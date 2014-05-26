-LINE 11 "SKIM.lss"
-INCLUDE 'SDIFF.INC'
-STITL SKIM
-EJECT
-LINE 38 "SKIM.lss"
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
-LINE 15 "SKIM.lss"
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