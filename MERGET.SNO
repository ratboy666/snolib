-MODULE MERGET
-LINE 13 "MERGET.lss"
-INCLUDE 'COPYT.INC'
-INCLUDE 'SEQ.INC'
-IN72
-LINE 42 "MERGET.lss"
-STITL MERGET
-EJECT
*
************************************************************************
*                                                                      *
*         #     #  #######  ######    #####   #######  #######         *
*         ##   ##  #        #     #  #     #  #           #            *
*         # # # #  #        #     #  #        #           #            *
*         #  #  #  #####    ######   #  ####  #####       #            *
*         #     #  #        #   #    #     #  #           #            *
*         #     #  #        #    #   #     #  #           #            *
*         #     #  #######  #     #   #####   #######     #            *
*                                                                      *
* MERGET                     MERGE TABLES                              *
*                                                                      *
************************************************************************
*
* MERGET.lss
*
-LINE 18 "MERGET.lss"
-PUBLIC MERGET()
*
         DEFINE('MERGET(T1,T2)A,I')                        :(MERGET_END)
*
MERGET   MERGET = COPYT(T1)
         A = CONVERT(T2, 'ARRAY')
         SEQ(' MERGET<A<I, 1>> = A<I, 2> ', .I)                :(RETURN)
*
MERGET_END
*
* CE: .MSNOBOL4;
