-MODULE READLINE
-STITL READLINE
-EJECT
-LINE 167 "READLINE.lss"
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
-LINE 14 "READLINE.lss"
-LINE 15 "READLINE.lss"
-LINE 16 "READLINE.lss"
-LINE 17 "READLINE.lss"
-LINE 18 "READLINE.lss"
-LINE 19 "READLINE.lss"
-LINE 20 "READLINE.lss"
-LINE 23 "READLINE.lss"
         editline = 'editline.c'
-LINE 123 "READLINE.lss"
-LINE 124 "READLINE.lss"
-LINE 125 "READLINE.lss"
-LINE 126 "READLINE.lss"
-LINE 127 "READLINE.lss"
-LINE 128 "READLINE.lss"
-LINE 137 "READLINE.lss"
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
