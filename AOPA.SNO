-LINE 17 "AOPA.lss"
-INCLUDE 'SEQ.INC'
-STITL AOPA
-EJECT
-LINE 73 "AOPA.lss"
*
************************************************************************
*                                                                      *
*                    #     #######  ######      #                      *
*                   # #    #     #  #     #    # #                     *
*                  #   #   #     #  #     #   #   #                    *
*                 #     #  #     #  ######   #     #                   *
*                 #######  #     #  #        #######                   *
*                 #     #  #     #  #        #     #                   *
*                 #     #  #######  #        #     #                   *
*                                                                      *
* AOPA                 APPLY OPERATOR TO ARRAY                         *
*                                                                      *
************************************************************************
*
* AOPA.lss
*
-LINE 21 "AOPA.lss"
-MODULE AOPA
-PUBLIC AOPA()
         DEFINE('AOPA(A1,OP,A2)S1,I,S2,S')                   :(AOPA_END)
*
AOPA     IDENT(DATATYPE(A1), 'ARRAY')                         :S(AOPA_1)
         IDENT(DATATYPE(A2), 'ARRAY')                         :S(AOPA_2)
         AOPA = EVAL('A1 ' OP ' A2')                           :(RETURN)
AOPA_1   S1 = '<I>'
         S2 = IDENT(DATATYPE(A2), 'ARRAY')  '<I>'
         AOPA = ARRAY(PROTOTYPE(A1))                      :(AOPA_COMMON)
AOPA_2   S2 = '<I>'
         AOPA = ARRAY(PROTOTYPE(A2))
AOPA_COMMON
         S = ' AOPA<I> = A1' S1 ' ' OP ' A2' S2
         SEQ(S, .I)                                            :(RETURN)
*
AOPA_END
*
* CE: .MSNOBOL4;
