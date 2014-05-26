-STITL SYSTEM
-EJECT
*
-LINE 92 "SYSTEM.lss"
************************************************************************
*                                                                      *
*          #####   #     #   #####   #######  #######  #     #         *
*         #     #   #   #   #     #     #     #        ##   ##         *
*         #          # #    #           #     #        # # # #         *
*          #####      #      #####      #     #####    #  #  #         *
*               #     #           #     #     #        #     #         *
*         #     #     #     #     #     #     #        #     #         *
*          #####      #      #####      #     #######  #     #         *
*                                                                      *
* SYSTEM            DETERMINE KIND OF SNOBOL4                          *
*                                                                      *
************************************************************************
*
* SYSTEM.lss
*
-LINE 29 "SYSTEM.lss"
         DEFINE('SYSTEM()K')
         DEFINE('ISSPITBOL()')
         DEFINE('ISSNOBOL4()')
         DEFINE('ISASCII()')
         DEFINE('ISEBCDIC()')
         DEFINE('ISCDC_DISPLAY_CODE()')                    :(SYSTEM_END)
*
ISASCII  &ALPHABET '()'                             :S(RETURN)F(FRETURN)
*
* LLT('A',1)
ISEBCDIC &ALPHABET '(+'                             :S(RETURN)F(FRETURN)
*
ISCDC_DISPLAY_CODE
         &ALPHABET ')*'                             :S(RETURN)F(FRETURN)
*
ISSPITBOL
         DIFFER(.NAME, 'NAME')                      :S(RETURN)F(FRETURN)
*
ISSNOBOL4
         IDENT(.NAME, 'NAME')                       :S(RETURN)F(FRETURN)
*
SYSTEM   IDENT(DATATYPE(.X), 'STRING')                      :F(SYSTEM_2)
         K = SIZE(&ALPHABET)
         SYSTEM = EQ(K,512) 'HONEYWELL MAINBOL'               :S(RETURN)
         SYSTEM = EQ(K,256) 'IBM MAINBOL'                   :S(SYSTEM_0)
         SYSTEM = EQ(K,128) 'PDP-10 MAINBOL'                  :S(RETURN)
         SYSTEM =           'CDC MAINBOL'
         ISASCII()                                          :S(SYSTEM_1)
         SYSTEM =           'UNIVAC MAINBOL'                   :(RETURN)
*
* DISTINGUISH IBM MAINBOL AND CSNOBOL, ASSUME ASCII FOR CSNOBOL4.
* NOTE THAT AFTER 1.5, CSNOBOL4 WILL LIKELY SUPPORT BLOCKS AS WELL.
*
SYSTEM_0 ISASCII()                                          :F(SYSTEM_1)
         SYSTEM = 'CSNOBOL4'
*
SYSTEM_1 OPSYN('OLD_SHARP', '#', 2)
         OPSYN('#', '+', 2)
         T = 1 5 # 5
         OPSYN('#', 'OLD_SHARP', 2)
         EQ(T, 110)                                           :S(RETURN)
         SYSTEM = SYSTEM ' WITH BLOCKS'                        :(RETURN)
*
SYSTEM_2 SYSTEM = DIFFER(SUBSTR('ABC', 2, 1), 'B') 'FASBOL'   :S(RETURN)
         SYSTEM = EQ(SIZE(&ALPHABET), 128)         'SITBOL'   :S(RETURN)
         SYSTEM =                                  'SPITBOL'   :(RETURN)
*
SYSTEM_END
*
* CE: .MSNOBOL4;