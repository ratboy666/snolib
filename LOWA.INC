-MODULE LOWA
-IN72
-LINE 8 "LOWA.lss"
-INCLUDE 'ARRAY0.INC'
-LINE 41 "LOWA.lss"
-STITL LOWA
-EJECT
*
************************************************************************
*                                                                      *
*                  #        #######  #     #     #                     *
*                  #        #     #  #  #  #    # #                    *
*                  #        #     #  #  #  #   #   #                   *
*                  #        #     #  #  #  #  #     #                  *
*                  #        #     #  #  #  #  #######                  *
*                  #        #     #  #  #  #  #     #                  *
*                  #######  #######   ## ##   #     #                  *
*                                                                      *
* LOWA                       LOW INDEX OF ARRAY                        *
*                                                                      *
************************************************************************
*
* LOWA.lss
*
-LINE 12 "LOWA.lss"
-PUBLIC LOWA()
*
         DEFINE('LOWA(A)L,U')                                :(LOWA_END)
*
LOWA     LOWA = IDENT(A) 0                                    :S(RETURN)
         LOWA = IDENT(A, ARRAY0) 0                            :S(RETURN)
         IDENT(DATATYPE(A), 'ARRAY')                         :F(FRETURN)
         PROTOTYPE(A) (BRKREM(':,') . L) ((':' BRKREM(',') . U) | NULL)
         IDENT(L)                                            :S(FRETURN)
         LOWA = L
         LOWA = IDENT(U) 1                                     :(RETURN)
*
LOWA_END
*
* CE: .F.MSNOBOL4;
