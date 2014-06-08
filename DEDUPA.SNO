-LINE 14 "DEDUPA.lss"
-INCLUDE 'SIZEA.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'SEQ.INC'
-STITL DEDUPA
-EJECT
-LINE 46 "DEDUPA.lss"
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
-MODULE DEDUPA
-PUBLIC DEDUPA()
*
         DEFINE('DEDUPA(A)T,I')                            :(END_DEDUPA)
*
DEDUPA   DEDUPA = IDENT(A, ARRAY0) A                          :S(RETURN)
         T = TABLE()
         SEQ(' T<A<I>> = 1', .I)
         DEDUPA = KEYS_IN_TABLE(T)                             :(RETURN)
*
END_DEDUPA
*
* CE: .MSNOBOL4;
