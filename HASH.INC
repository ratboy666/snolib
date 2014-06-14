-MODULE HASH
-LINE 54 "HASH.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'COPYT.INC'
-INCLUDE 'KEYST.INC'
-INCLUDE 'MERGET.INC'
-INCLUDE 'TRIMB.INC'
-INCLUDE 'VDIFFER.INC'
-IN72
-LINE 126 "HASH.lss"
-STITL HASH
-EJECT
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
-LINE 63 "HASH.lss"
-PUBLIC HASH(), #1
*
         DEFINE('HASH(S,E,P,TS,TI,FK,FV,SP)K,V,C')
         DEFINE('HASH_3(S)')
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
HASH_END
*
* CE: .MSNOBOL4;
