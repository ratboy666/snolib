-STITL BLEND
-EJECT
*
-LINE 50 "BLEND.lss"
************************************************************************
*                                                                      *
*              ######   #        #######  #     #  ######              *
*              #     #  #        #        ##    #  #     #             *
*              #     #  #        #        # #   #  #     #             *
*              ######   #        #####    #  #  #  #     #             *
*              #     #  #        #        #   # #  #     #             *
*              #     #  #        #        #    ##  #     #             *
*              ######   #######  #######  #     #  ######              *
*                                                                      *
* BLEND                      BLEND STRINGS                             *
*                                                                      *
************************************************************************
*
* BLEND.lss
*
-LINE 13 "BLEND.lss"
-MODULE BLEND
-PUBLIC BLEND()
         DEFINE('BLEND(S1,S2)T1,T2,ABC,XYZ,L1,L2')
         &ALPHABET LEN(128) . ABC LEN(128) . XYZ
BLE_1    ABC LEN(1) . T1 =                                 :F(BLEND_END)
         XYZ LEN(1) . T2 =
         BLENDED_ALPHABET = BLENDED_ALPHABET T1 T2              :(BLE_1)
*
BLEND    L1 = SIZE(S1)
         GT(L1, 128)                                         :F(BLEND_1)
         EQ(L1, 0)                                            :S(RETURN)
         S1 LEN(128) . S1 REM . T1
         S2 LEN(128) . S2 REM . T2
         BLEND = REPLACE(BLENDED_ALPHABET, &ALPHABET, S1 S2)
         BLEND(T1, T2)                                         :(RETURN)
BLEND_1  L2 = SIZE(S2)
         &ALPHABET LEN(*L1) . ABC TAB(128) LEN(*L2) . XYZ
         BLENDED_ALPHABET LEN(*(L1 + L2)) . AXBYCZ
         BLEND = REPLACE(AXBYCZ, ABC XYZ, S1 S2)               :(RETURN)
*
BLEND_END
*
* CE: .MSNOBOL4;
