-STITL FIND
-EJECT
*
-LINE 40 "FIND.lss"
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
-LINE 12 "FIND.lss"
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
