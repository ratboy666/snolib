-LINE 14 "HEX.lss"
-INCLUDE 'BLEND.INC'
-STITL HEX
-EJECT
-LINE 52 "HEX.lss"
*
************************************************************************
*                                                                      *
*                      #     #  #######  #     #                       *
*                      #     #  #         #   #                        *
*                      #     #  #          # #                         *
*                      #######  #####       #                          *
*                      #     #  #          # #                         *
*                      #     #  #         #   #                        *
*                      #     #  #######  #     #                       *
*                                                                      *
* HEX                    RETURN HEX FOR STRING                         *
*                                                                      *
************************************************************************
*
* HEX.lss
*
-LINE 18 "HEX.lss"
-MODULE HEX
-PUBLIC HEX()
         DEFINE('HEX(S)S2')
*
         H = '0123456789ABCDEF'
         HEX_2ND = DUPL(H, 16)
HEX_1    H LEN(1) . T =                                      :F(HEX_END)
         HEX_1ST = HEX_1ST DUPL(T, 16)                          :(HEX_1)
*
HEX      IDENT(S)                                             :S(RETURN)
         LE(SIZE(S), 128)                                      :S(HEX_2)
         S LEN(128) . S REM . S2
         HEX = HEX(S) HEX(S2)                                  :(RETURN)
HEX_2    HEX = BLEND(REPLACE(S, &ALPHABET, HEX_1ST),
+           REPLACE(S, &ALPHABET, HEX_2ND))                    :(RETURN)
*
HEX_END
*
* CE: .MSNOBOL4;
