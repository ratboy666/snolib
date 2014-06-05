-LINE 11 "TPROFILE.lss"
-INCLUDE 'LPROG.INC'
-INCLUDE 'SEQ.INC'
-STITL TPROFILE
-EJECT
-LINE 55 "TPROFILE.lss"
*
************************************************************************
*                                                                      *
*  #######  ######   ######   #######  #######  ###  #        #######  *
*     #     #     #  #     #  #     #  #         #   #        #        *
*     #     #     #  #     #  #     #  #         #   #        #        *
*     #     ######   ######   #     #  #####     #   #        #####    *
*     #     #        #   #    #     #  #         #   #        #        *
*     #     #        #    #   #     #  #         #   #        #        *
*     #     #        #     #  #######  #        ###  #######  #######  *
*                                                                      *
* TPROFILE                 TIME PROFILE                                *
*                                                                      *
************************************************************************
*
* TPROFILE.lss
*
-LINE 16 "TPROFILE.lss"
-MODULE TPROFILE
-PUBLIC TPROFILE(), TPROFILE_DUMP()
         DEFINE('TPROFILE()S,T')
         DEFINE('TPROFILE_DUMP()I')
         TP_ARY = ARRAY(LPROG())
         &STLIMIT = 999999999
         &TRACE = 999999999
         TRACE('STCOUNT', 'KEYWORD',, 'TPROFILE')        :(TPROFILE_END)
*
TPROFILE S = &LASTNO
         T = TIME()
         TP_ARY<LAST_STNO> = TP_ARY<LAST_STNO> + T - LAST_TIME
         LAST_STNO = S
         LAST_TIME = TIME()                                    :(RETURN)
*
TPROFILE_DUMP
         &STLIMIT = -1
         STOPTR('STCOUNT', 'KEYWORD')
         TERMINAL = 'TIME PROFILE'
         TERMINAL =
         SEQ(' TERMINAL = LPAD(I, 5) ": " TP_ARY<I> ', .I)
                                                               :(RETURN)
*
TPROFILE_END
*
* CE: .MSNOBOL4;
