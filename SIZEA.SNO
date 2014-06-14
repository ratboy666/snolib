-MODULE SIZEA
-IN72
-LINE 13 "SIZEA.lss"
-INCLUDE 'ARRAY0.INC'
-INCLUDE 'BRKREM.INC'
-INCLUDE 'LOWA.INC'
-INCLUDE 'SWAP.INC'
-LINE 65 "SIZEA.lss"
-STITL SIZEA
-EJECT
*
************************************************************************
*                                                                      *
*                 #####   ###  #######  #######     #                  *
*                #     #   #        #   #          # #                 *
*                #         #       #    #         #   #                *
*                 #####    #     #      #####    #     #               *
*                      #   #    #       #        #######               *
*                #     #   #   #        #        #     #               *
*                 #####   ###  #######  #######  #     #               *
*                                                                      *
* SIZEA                       SIZE OF ARRAY                            *
*                                                                      *
************************************************************************
*
* SIZEA.lss
*
-LINE 20 "SIZEA.lss"
-PUBLIC SIZEA()
*
         DEFINE('SIZEA(A)L,U')                              :(SIZEA_END)
*
SIZEA    SIZEA = IDENT(A) 0                                   :S(RETURN)
         SIZEA = IDENT(A, ARRAY0) 0                           :S(RETURN)
         IDENT(DATATYPE(A), 'ARRAY')                         :F(FRETURN)
         L =
         U =
         PROTOTYPE(A) (BRKREM(':,') . L) ((':' BRKREM(',') . U) | NULL)
         IDENT(L)                                            :S(FRETURN)
         U = IDENT(U) 1                                      :F(SIZEA_2)
         SWAP(.L, .U)
SIZEA_2  SIZEA = LT(U, L) 0                                   :S(RETURN)
         SIZEA = U - L + 1                                     :(RETURN)
*
SIZEA_END
*
* CE: .F.MSNOBOL4;
