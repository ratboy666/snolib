-STITL AGT
-EJECT
*
-LINE 35 "AGT.lss"
************************************************************************
*                                                                      *
*                         #      #####   #######                       *
*                        # #    #     #     #                          *
*                       #   #   #           #                          *
*                      #     #  #  ####     #                          *
*                      #######  #     #     #                          *
*                      #     #  #     #     #                          *
*                      #     #   #####      #                          *
*                                                                      *
* AGT        ALPHABETIC COMPARISION WITH UPPER AND LOWER EQUAL         *
*                                                                      *
************************************************************************
*
* AGT.lss
*
-LINE 11 "AGT.lss"
         DEFINE('AGT(S1,S2)')
         AGT_TT = REPLACE(&ALPHABET, &UCASE, &LCASE)          :(AGT_END)
*
AGT      LGT(REPLACE(S1, &ALPHABET, AGT_TT),
+            REPLACE(S2, &ALPHABET, AGT_TT))        :S(RETURN)F(FRETURN)
*
AGT_END
*
* CE: .MSNOBOL4;
