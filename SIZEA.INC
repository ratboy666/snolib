-LINE 20 "SIZEA.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'SWAP.INC'
-STITL SIZEA
-EJECT
-LINE 76 "SIZEA.lss"
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
-LINE 25 "SIZEA.lss"
         DEFINE('SIZEA(A)L,U')
         DEFINE('LOWA(A)L,U')
         ARRAY0 = ARRAY('0:-1')                             :(SIZEA_END)
*
LOWA     LOWA = IDENT(A) 0                                    :S(RETURN)
         IDENT(DATATYPE(A), 'ARRAY')                         :F(FRETURN)
         PROTOTYPE(A) (BRKREM(':,') . L) ((':' BRKREM(',') . U) | NULL)
         IDENT(L)                                            :S(FRETURN)
         LOWA = L
         LOWA = IDENT(U) 1                                     :(RETURN)
*
SIZEA    SIZEA = IDENT(A) 0                                   :S(RETURN)
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
