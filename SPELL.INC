-STITL SPELL
-EJECT
*
-LINE 58 "SPELL.lss"
************************************************************************
*                                                                      *
*                 #####   ######   #######  #        #                 *
*                #     #  #     #  #        #        #                 *
*                #        #     #  #        #        #                 *
*                 #####   ######   #####    #        #                 *
*                      #  #        #        #        #                 *
*                #     #  #        #        #        #                 *
*                 #####   #        #######  #######  #######           *
*                                                                      *
* SPELL                    SPELL OUT A NUMBER                          *
*                                                                      *
************************************************************************
*
* SPELL.lss
*
-LINE 12 "SPELL.lss"
-MODULE SPELL
-PUBLIC SPELL()
         DEFINE('SPELL(N)M')                                :(SPELL_END)
*
SPELL    GE(N, 1000)                                      :S(SPELL_1000)
         GE(N, 100)                                        :S(SPELL_100)
         GE(N, 20)                                          :S(SPELL_20)
         GE(N, 13)                                          :S(SPELL_13)
         ('1ONE,2TWO,3THREE,4FOUR,5FIVE,6SIX,7SEVEN,8EIGHT,9NINE,'
+           '10TEN,11ELEVEN,12TWELVE,') N ARB . SPELL ','      :(RETURN)
SPELL_13 N 1 LEN(1) . M
         SPELL = SPELL(M 0)
         SPELL 'TY' = 'TEEN'
         SPELL 'FOR' = 'FOUR'                                  :(RETURN)
SPELL_20 N LEN(1) . M =
         '2TWEN,3THIR,4FOR,5FIF,6SIX,7SEVEN,8EIGH,9NINE,'
+           M BREAK(',') . SPELL
         SPELL = SPELL 'TY'
         SPELL = NE(N,0) SPELL '-' SPELL(N)                    :(RETURN)
SPELL_100
         N LEN(1) . M  =
         SPELL = SPELL(M) ' HUNDRED'
         SPELL = NE(N, 0) SPELL ' AND ' SPELL(+N)              :(RETURN)
SPELL_1000
         N RTAB(3) . M  =
         SPELL = SPELL(M)
         SPELL 'THOUSAND' = 'MILLION'
         SPELL = SPELL ' THOUSAND'
         SPELL = NE(N, 0) SPELL ' AND ' SPELL(+N)              :(RETURN)
*
SPELL_END
*
* CE: .MSNOBOL4;
