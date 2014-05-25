-LINE 13 "CH.lss"
-INCLUDE 'LOGIC.INC'
-STITL CH
-EJECT
-LINE 41 "CH.lss"
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
-LINE 17 "CH.lss"
         DEFINE('CH(HEX)T,C,N')                                :(CH_END)
*
CH       HEX LEN(2) . T =                                     :F(RETURN)
         C = HI(T)
         &ALPHABET LEN(C) LEN(1) . C
         CH = CH C                                                 :(CH)
*
CH_END
*
* CE: .MSNOBOL4;
