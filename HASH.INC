-LINE 58 "HASH.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'SEQ.INC'
-INCLUDE 'VDIFFER.INC'
-STITL HASH
-EJECT
-LINE 148 "HASH.lss"
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
-LINE 64 "HASH.lss"
-MODULE HASH
-PUBLIC HASH(), COPYT(), MERGET(), KEYST(), #1
-PUBLIC PRUNET()
*
         DEFINE('HASH(S,E,P,TS,TI,FK,FV,SP)K,V,C')
         DEFINE('HASH_3(S)')
         DEFINE('COPYT(T)')
         DEFINE('MERGET(T1,T2)A,I')
         DEFINE('KEYST(T)A,N,I')
         DEFINE('PRUNET(T)A,I')
         OPSYN('#', 'HASH', 1)                               :(HASH_END)
*
PRUNET
         PRUNET = TABLE()
         A = KEYST(T)                                         :F(RETURN)
         SEQ( ' PRUNET<A<I>> = VDIFFER(T<A<I>>)', .I)          :(RETURN)
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
COPYT
         COPYT = CONVERT(CONVERT(T, 'ARRAY'), 'TABLE')         :(RETURN)
*
MERGET
         MERGET = COPYT(T1)
         A = CONVERT(T2, 'ARRAY')
         SEQ(' MERGET<A<I, 1>> = A<I, 2> ', .I)                :(RETURN)
*
KEYST    A = CONVERT(T, 'ARRAY')                             :F(FRETURN)
         PROTOTYPE(A) BREAK(',') . N                         :F(FRETURN)
         KEYST = ARRAY(N)
         SEQ(' KEYST<I> = A<I,1> ', .I)                        :(RETURN)
*
HASH_END
*
* CE: .MSNOBOL4;
