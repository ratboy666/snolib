-MODULE COMPLEX
-LINE 8 "COMPLEX.lss"
-IN72
-LINE 59 "COMPLEX.lss"
-STITL COMPLEX
-EJECT
*
************************************************************************
*                                                                      *
*                                                                      *
*     #####   #######  #     #  ######   #        #######  #     #     *
*    #     #  #     #  ##   ##  #     #  #        #         #   #      *
*    #        #     #  # # # #  #     #  #        #          # #       *
*    #        #     #  #  #  #  ######   #        #####       #        *
*    #        #     #  #     #  #        #        #          # #       *
*    #     #  #     #  #     #  #        #        #         #   #      *
*     #####   #######  #     #  #        #######  #######  #     #     *
*                                                                      *
*                                                                      *
* COMPLEX                   COMPLEX NUMBERS                            *
*                                                                      *
************************************************************************
*
* COMPLEX.lss
*
-LINE 11 "COMPLEX.lss"
-PUBLIC COMPLEX(), R(), I()
*
         DATA('COMPLEX(R,I)')
*
-PUBLIC ADD_COMPLEX(), MUL_COMPLEX(), NEG_COMPLEX(), INV_COMPLEX()
-PUBLIC PRINT_COMPLEX()
*
         DEFINE('ADD_COMPLEX(X,Y)')
         DEFINE('MUL_COMPLEX(X,Y)A,B,C,D')
         DEFINE('NEG_COMPLEX(X)')
         DEFINE('INV_COMPLEX(X)D')
         DEFINE('PRINT_COMPLEX(X)SIGN')                   :(COMPLEX_END)
*
ADD_COMPLEX
         ADD_COMPLEX = COMPLEX(R(X) + R(Y), I(X) + I(Y))       :(RETURN)
*
MUL_COMPLEX
         A = R(X); B = I(X); C = R(Y); D = I(Y)
         MUL_COMPLEX = COMPLEX(A * C - B * D, B * C + A * D)   :(RETURN)
*
NEG_COMPLEX
         NEG_COMPLEX = COMPLEX(-R(X), -I(X))                   :(RETURN)
*
INV_COMPLEX
         D = (R(X) * R(X)) + (I(X) * I(X))
         INV_COMPLEX = COMPLEX(1.0 * R(X) / D, 1.0 * -I(X) / D)
+                                                              :(RETURN)
*
PRINT_COMPLEX
         SIGN = GE(I(X)) '+'
         PRINT_COMPLEX = R(X) SIGN I(X) 'i'                    :(RETURN)
*
COMPLEX_END
*
* CE: .MSNOBOL4;
