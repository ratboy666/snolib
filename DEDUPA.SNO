-MODULE DEDUPA
-LINE 14 "DEDUPA.lss"
-INCLUDE 'SIZEA.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'SEQ.INC'
-INCLUDE 'ARRAY0.INC'
-IN72
-LINE 46 "DEDUPA.lss"
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
-LINE 21 "DEDUPA.lss"
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
