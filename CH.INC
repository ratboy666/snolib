-LINE 10 "CH.lss"
-INCLUDE 'HEX.INC'
-STITL CH
-EJECT
-LINE 46 "CH.lss"
*
************************************************************************
*                                                                      *
*                            #####   #     #                           *
*                           #     #  #     #                           *
*                           #        #     #                           *
*                           #        #######                           *
*                           #        #     #                           *
*                           #     #  #     #                           *
*                            #####   #     #                           *
*                                                                      *
* CH                         HEX TO STRING                             *
*                                                                      *
************************************************************************
*
* CH.lss
*
-LINE 14 "CH.lss"
-PUBLIC CH()
         DEFINE('CH(H)C,P')
*
         CH_H_ = ' ' HEX(&ALPHABET)
CH_2     CH_H_ ' ' LEN(2) . C1
+          (ANY('0123456789ABCDEF') LEN(1)) . C2 = ' ' C1 ' ' C2
+                                                      :S(CH_2)F(CH_END)
*
CH       H = REPLACE(H, &LCASE, &UCASE)
CH_3     H LEN(2) . C =                                       :F(RETURN)
         CH_H_ ' ' C @P                                      :F(FRETURN)
         P = (P - 1) / 3
         &ALPHABET LEN(P) LEN(1) . C
         CH = CH C                                               :(CH_3)
*
CH_END
*
* CE: .MSNOBOL4;
