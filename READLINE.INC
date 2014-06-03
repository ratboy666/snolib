-STITL READLINE
-EJECT
*
-LINE 161 "READLINE.lss"
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
-LINE 8 "READLINE.lss"
-LINE 9 "READLINE.lss"
-LINE 10 "READLINE.lss"
-LINE 11 "READLINE.lss"
-LINE 12 "READLINE.lss"
-LINE 13 "READLINE.lss"
-LINE 14 "READLINE.lss"
-LINE 17 "READLINE.lss"
         editline = 'editline.c'
-LINE 117 "READLINE.lss"
-LINE 118 "READLINE.lss"
-LINE 119 "READLINE.lss"
-LINE 120 "READLINE.lss"
-LINE 121 "READLINE.lss"
-LINE 122 "READLINE.lss"
-LINE 131 "READLINE.lss"
-PUBLIC READLINE(), ADD_HISTORY(), HISTORY_EXPAND()
READLINE LOAD('READLINE(STRING)STRING')
         LOAD('ADD_HISTORY(STRING)STRING')
         LOAD('HISTORY_EXPAND(STRING)STRING')
*
-PUBLIC EDITLINE(), RLAPPNAME(), CLEAR_HISTORY(), STIFLE_HISTORY()
-PUBLIC READ_HISTORY(), WRITE_HISTORY()
         LOAD('EDITLINE(STRING,STRING)STRING', 'editline.so')
         LOAD('RLAPPNAME(STRING)', 'editline.so')
         LOAD('CLEAR_HISTORY()', 'editline.so')
         LOAD('STIFLE_HISTORY(INTEGER)', 'editline.so')
         LOAD('READ_HISTORY(STRING)INTEGER', 'editline.so')
         LOAD('WRITE_HISTORY(STRING)INTEGER', 'editline.so')
*
         CODE('READLINE')
*
* CE: .MSNOBOL4;
