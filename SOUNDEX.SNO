-STITL SOUNDEX
-EJECT
*
-LINE 47 "SOUNDEX.lss"
************************************************************************
*                                                                      *
*     #####   #######  #     #  #     #  ######   #######  #     #     *
*    #     #  #     #  #     #  ##    #  #     #  #         #   #      *
*    #        #     #  #     #  # #   #  #     #  #          # #       *
*     #####   #     #  #     #  #  #  #  #     #  #####       #        *
*          #  #     #  #     #  #   # #  #     #  #          # #       *
*    #     #  #     #  #     #  #    ##  #     #  #         #   #      *
*     #####   #######   #####   #     #  ######   #######  #     #     *
*                                                                      *
* SOUNDEX                   NARA SOUNDEX                               *
*                                                                      *
************************************************************************
*
* SOUNDEX.lss
*
-LINE 12 "SOUNDEX.lss"
-MODULE SOUNDEX
-PUBLIC SOUNDEX()
         DEFINE('SOUNDEX(STR)SDXMAP,INIT,CH')             :(SOUNDEX_END)
*
SOUNDEX  SDXMAP = '01230127022455012623017202'
         STR = REPLACE(STR, &LCASE, &UCASE)
SDX1     STR NOTANY(&UCASE) =                                   :S(SDX1)
         INIT = SUBSTR(STR, 1, 1)
         STR = REPLACE(STR, &UCASE, SDXMAP)
SDX2     STR LEN(1) $ CH SPAN(*CH) = CH                         :S(SDX2)
* OMIT NEXT LINE FOR KNUTH'S SIMPLE SOUNDEX
SDX3     STR LEN(1) $ CH ('7' *CH) = CH                         :S(SDX3)
         STR LEN(1) = INIT
SDX4     STR ANY('07') =                                        :S(SDX4)
         STR = SUBSTR(STR, 1, 4)
         STR = LT(SIZE(STR), 4) STR DUPL('0', 4 - SIZE(STR))
         SOUNDEX = STR                                         :(RETURN)
*
SOUNDEX_END
*
* CE: .MSNOBOL4;
