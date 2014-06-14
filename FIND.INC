-MODULE FIND
-LINE 14 "FIND.lss"
-IN72
-LINE 47 "FIND.lss"
-STITL FIND
-EJECT
*
************************************************************************
*                                                                      *
*                    #######  ###  #     #  ######                     *
*                    #         #   ##    #  #     #                    *
*                    #         #   # #   #  #     #                    *
*                    #####     #   #  #  #  #     #                    *
*                    #         #   #   # #  #     #                    *
*                    #         #   #    ##  #     #                    *
*                    #        ###  #     #  ######                     *
*                                                                      *
* FIND                       FIND EXTREME                              *
*                                                                      *
************************************************************************
*
* FIND.lss
*
-LINE 17 "FIND.lss"
-PUBLIC FIND()
*
         DEFINE('FIND(A,PRED)EX,I,MAX,TEST')                 :(FIND_END)
*
FIND     EX = CONVERT(PRED '(MAX,TEST)', 'EXPRESSION')
         FIND = 1
         MAX = A<FIND>
         I = 1
FIND_1   I = I + 1
         TEST = A<I>                                          :F(RETURN)
         EVAL(EX)                                             :S(FIND_1)
         MAX = TEST
         FIND = I                                              :(FIND_1)
*
FIND_END
*
* CE: .MSNOBOL4;
