-MODULE EDITLINE
-LINE 10 "EDITLINE.lss"
-IN72
-LINE 163 "EDITLINE.lss"
-STITL EDITLINE
-EJECT
*
************************************************************************
*                                                                      *
*    #######  ######   ###  #######  #        ###  #     #  #######    *
*    #        #     #   #      #     #         #   ##    #  #          *
*    #        #     #   #      #     #         #   # #   #  #          *
*    #####    #     #   #      #     #         #   #  #  #  #####      *
*    #        #     #   #      #     #         #   #   # #  #          *
*    #        #     #   #      #     #         #   #    ##  #          *
*    #######  ######   ###     #     #######  ###  #     #  #######    *
*                                                                      *
* EDITLINE                 EDIT LINE FUNCTIONS                         *
*                                                                      *
************************************************************************
*
* EDITLINE.lss
*
-LINE 13 "EDITLINE.lss"
-LINE 14 "EDITLINE.lss"
-LINE 15 "EDITLINE.lss"
-LINE 16 "EDITLINE.lss"
-LINE 17 "EDITLINE.lss"
-LINE 18 "EDITLINE.lss"
-LINE 19 "EDITLINE.lss"
-LINE 22 "EDITLINE.lss"
         editline = 'editline.c'
-LINE 122 "EDITLINE.lss"
-LINE 123 "EDITLINE.lss"
-LINE 124 "EDITLINE.lss"
-LINE 125 "EDITLINE.lss"
-LINE 126 "EDITLINE.lss"
-LINE 127 "EDITLINE.lss"
-LINE 136 "EDITLINE.lss"
*
-PUBLIC EDITLINE(), RLAPPNAME(), CLEAR_HISTORY(), STIFLE_HISTORY()
-PUBLIC READ_HISTORY(), WRITE_HISTORY()
*
EDITLINE LOAD('EDITLINE(STRING,STRING)STRING', 'editline.so')
         LOAD('RLAPPNAME(STRING)', 'editline.so')
         LOAD('CLEAR_HISTORY()', 'editline.so')
         LOAD('STIFLE_HISTORY(INTEGER)', 'editline.so')
         LOAD('READ_HISTORY(STRING)INTEGER', 'editline.so')
         LOAD('WRITE_HISTORY(STRING)INTEGER', 'editline.so')
*
         CODE('EDITLINE')
*
* CE: .MSNOBOL4;
