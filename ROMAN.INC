-STITL ROMAN
-EJECT
*
-LINE 51 "ROMAN.lss"
************************************************************************
*                                                                      *
*             ######   #######  #     #     #     #     #              *
*             #     #  #     #  ##   ##    # #    ##    #              *
*             #     #  #     #  # # # #   #   #   # #   #              *
*             ######   #     #  #  #  #  #     #  #  #  #              *
*             #   #    #     #  #     #  #######  #   # #              *
*             #    #   #     #  #     #  #     #  #    ##              *
*             #     #  #######  #     #  #     #  #     #              *
*                                                                      *
* ROMAN                      ROMAN NUMERAL                             *
*                                                                      *
************************************************************************
*
* ROMAN.lss
*
-LINE 10 "ROMAN.lss"
-PUBLIC ROMAN()
         DEFINE('ROMAN(N)T')                                :(ROMAN_END)
*
ROMAN    N RPOS(1) LEN(1) . T =                               :F(RETURN)
         '0,1I,2II,3III,4IV,5V,6VI,7VII,8VIII,9IX,'
+           T BREAK(',') . T                                 :F(FRETURN)
         ROMAN = REPLACE(ROMAN(N), 'IVXLCDM', 'XLCDM**') T
+                                                   :S(RETURN)F(FRETURN)
*
ROMAN_END
*
-PUBLIC ARABIC()
         DEFINE('ARABIC(R)T,X')                            :(ARABIC_END)
*
ARABIC   R RPOS(1) LEN(1) . T =                               :F(RETURN)
         'M1000,D500,C100,L50,X10,V5,I1,' T BREAK(',') . T   :F(FRETURN)
         T = LT(T, X) -T
         ARABIC = ARABIC + (X = T)                             :(ARABIC)
*
ARABIC_END
*
* CE: .MSNOBOL4;
