-MODULE READLINE
-LINE 9 "READLINE.lss"
-IN72
-LINE 34 "READLINE.lss"
-STITL READLINE
-EJECT
*
************************************************************************
*                                                                      *
*  ######   #######     #     ######   #        ###  #     #  #######  *
*  #     #  #          # #    #     #  #         #   ##    #  #        *
*  #     #  #         #   #   #     #  #         #   # #   #  #        *
*  ######   #####    #     #  #     #  #         #   #  #  #  #####    *
*  #   #    #        #######  #     #  #         #   #   # #  #        *
*  #    #   #        #     #  #     #  #         #   #    ##  #        *
*  #     #  #######  #     #  ######   #######  ###  #     #  #######  *
*                                                                      *
* READLINE                 READLINE FUNCTIONS                          *
*                                                                      *
* PHIL BUDNE <PHIL@ULTIMATE.COM>                                       *
* JANUARY 3, 2011                                                      *
*                                                                      *
************************************************************************
*
* READLINE.lss
*
-LINE 12 "READLINE.lss"
-PUBLIC READLINE(), ADD_HISTORY(), HISTORY_EXPAND()
*
READLINE LOAD('READLINE(STRING)STRING')
         LOAD('ADD_HISTORY(STRING)STRING')
         LOAD('HISTORY_EXPAND(STRING)STRING')
*
         CODE('READLINE')
*
* CE: .MSNOBOL4;
