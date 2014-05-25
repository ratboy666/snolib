-LINE 13 "HEX.lss"
-INCLUDE 'BLEND.INC'
-STITL HEX
-EJECT
-LINE 42 "HEX.lss"
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
-LINE 17 "HEX.lss"
         DEFINE('HEX(S)')
*
         H = '0123456789ABCDEF'
         HEX_2ND = DUPL(H, 16)
HEX_1    H LEN(1) . T =                                      :F(HEX_END)
         HEX_1ST = HEX_1ST DUPL(T, 16)                          :(HEX_1)
HEX      HEX = BLEND(REPLACE(S, &ALPHABET, HEX_1ST),
+           REPLACE(S, &ALPHABET, HEX_2ND))                    :(RETURN)
*
HEX_END
*
* CE: .MSNOBOL4;
