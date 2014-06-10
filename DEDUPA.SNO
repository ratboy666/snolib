-MODULE DEDUPA
-IN72
-LINE 14 "DEDUPA.lss"
-INCLUDE 'SIZEA.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'SEQ.INC'
-LINE 45 "DEDUPA.lss"
-STITL DEDUPA
-EJECT
*
************************************************************************
*                                                                      *
*         ######   #######  ######   #     #  ######      #            *
*         #     #  #        #     #  #     #  #     #    # #           *
*         #     #  #        #     #  #     #  #     #   #   #          *
*         #     #  #####    #     #  #     #  ######   #     #         *
*         #     #  #        #     #  #     #  #        #######         *
*         #     #  #        #     #  #     #  #        #     #         *
*         ######   #######  ######    #####   #        #     #         *
*                                                                      *
*                                                                      *
* DEDUPA                      DEDUP ARRAY                              *
*                                                                      *
************************************************************************
*
* DEDUPA.lss
*
-LINE 20 "DEDUPA.lss"
-PUBLIC DEDUPA()
*
         DEFINE('DEDUPA(A)T,I')                            :(END_DEDUPA)
*
DEDUPA   DEDUPA = IDENT(A, ARRAY0) A                          :S(RETURN)
         T = TABLE()
         SEQ(' T<A<I>> = 1', .I)
         DEDUPA = KEYST(T)                                     :(RETURN)
*
END_DEDUPA
*
* CE: .MSNOBOL4;
