-LINE 56 "HASH.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'SEQ.INC'
-STITL PSQL
-EJECT
-LINE 136 "HASH.lss"
*
************************************************************************
*                                                                      *
*                                                                      *
*                  #     #     #      #####   #     #                  *
*                  #     #    # #    #     #  #     #                  *
*                  #     #   #   #   #        #     #                  *
*                  #######  #     #   #####   #######                  *
*                  #     #  #######        #  #     #                  *
*                  #     #  #     #  #     #  #     #                  *
*                  #     #  #     #   #####   #     #                  *
*                                                                      *
* HASH                   INITIALIZE A TABLE                            *
*                                                                      *
************************************************************************
*
* HASH.lss
*
-LINE 61 "HASH.lss"
         DEFINE('HASH(S,E,P,TS,TI,FK,FV,SP)K,V,C')
         DEFINE('HASH_3(S)')
         DEFINE('COPY_TABLE(T)')
         DEFINE('MERGE_TABLE(T1,T2)A,I')
         DEFINE('KEYS_IN_TABLE(T)A,N,I')
         OPSYN('#', 'HASH', 1)                               :(HASH_END)
*
HASH     HASH = TABLE(TS, TI)
         E = IDENT(E) '='
         P = IDENT(P) ','
         FK = IDENT(FK) 'HASH_3'
         FV = IDENT(FV) 'HASH_3'
HASH_2   IDENT(S)                                             :S(RETURN)
         S POS(0) BREAK(E P) LEN(1) . C                       :F(HASH_5)
         C E                                                  :F(HASH_5)
         S POS(0) BREAK(E) . K E =                            :S(HASH_4)
HASH_5   K =
HASH_4   S POS(0) BRKREM(P) . V (P | RPOS(0)) =               :F(RETURN)
         K = APPLY(FK, K)
         V = APPLY(FV, V)
         HASH<K> = VDIFFER(HASH<K>) VDIFFER(SP) V             :S(HASH_2)
         HASH<K> = V                                           :(HASH_2)
*
HASH_3   HASH_3 = S                                            :(RETURN)
*
COPY_TABLE
         COPY_TABLE = CONVERT(CONVERT(T, 'ARRAY'), 'TABLE')    :(RETURN)
*
MERGE_TABLE
         MERGE_TABLE = COPY_TABLE(T1)
         A = CONVERT(T2, 'ARRAY')
         SEQ(' MERGE_TABLE<A<I, 1>> = A<I, 2> ', .I)           :(RETURN)
*
KEYS_IN_TABLE
         A = CONVERT(T, 'ARRAY')                             :F(FRETURN)
         PROTOTYPE(A) BREAK(',') . N                         :F(FRETURN)
         KEYS_IN_TABLE = ARRAY(N)
         SEQ(' KEYS_IN_TABLE<I> = A<I,1> ', .I)                :(RETURN)
*
HASH_END
*
* CE: .MSNOBOL4;