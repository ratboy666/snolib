-STITL GOTOS
-EJECT
*
-LINE 58 "GOTOS.lss"
************************************************************************
*                                                                      *
*              #####   #######  #######  #######   #####               *
*             #     #  #     #     #     #     #  #     #              *
*             #        #     #     #     #     #  #                    *
*             #  ####  #     #     #     #     #   #####               *
*             #     #  #     #     #     #     #        #              *
*             #     #  #     #     #     #     #  #     #              *
*              #####   #######     #     #######   #####               *
*                                                                      *
* GOTOS        KEEP THE LAST 10 OR SO GOTOS OF A PROGRAM               *
*                                                                      *
************************************************************************
*
* GOTOS.lss
*
-LINE 28 "GOTOS.lss"
         DEFINE('GOTOS_()')
         GOTOS_LENGTH = 119
         GOTOS_QUEUE = DUPL('.', GOTOS_LENGTH)
         GOTOS_PAT = POS(0) LEN(GOTOS_LENGTH) . GOTOS_QUEUE
         TRACE('STCOUNT', 'KEYWORD',, 'GOTOS_')
         &TRACE = 999999999
         &DUMP = 1                                          :(GOTOS_END)
*
GOTOS_   GOTOS_NO = &LASTNO
         EQ(GOTOS_LAST, GOTOS_NO)                             :S(RETURN)
         GOTOS_LAST = EQ(GOTOS_NO, GOTOS_LAST + 1) GOTOS_NO   :S(RETURN)
         (GOTOS_LAST '>' GOTOS_NO ';' GOTOS_QUEUE) ? GOTOS_PAT
         GOTOS_LAST = GOTOS_NO                                 :(RETURN)
*
GOTOS_END
*
* CE: .MSNOBOL4;
