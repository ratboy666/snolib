-MODULE SYSTEM
-IN72
-LINE 49 "SYSTEM.lss"
-LINE 131 "SYSTEM.lss"
-STITL SYSTEM
-EJECT
*
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
-LINE 52 "SYSTEM.lss"
-PUBLIC SYSTEM(), ISSPITBOL(), ISSNOBOL4()
-PUBLIC ISASCII(), ISEBCDIC(), ISCDC_DISPLAY_CODE()
*
         DEFINE('SYSTEM()K,E,T')
         DEFINE('ISSPITBOL()')
         DEFINE('ISSNOBOL4()')
         DEFINE('ISASCII()A')
         DEFINE('ISEBCDIC()A')
         DEFINE('ISCDC_DISPLAY_CODE()A')                   :(SYSTEM_END)
*
ISASCII  A = &ANCHOR
         &ANCHOR = 0
         &ALPHABET '()'                          :S(ISASCII1)F(ISASCII2)
ISASCII1 &ANCHOR = A                                           :(RETURN)
ISASCII2 &ANCHOR = A                                          :(FRETURN)
*
* OR, TRY LLT('A',1)
ISEBCDIC A = &ANCHOR
         &ANCHOR = 0
         &ALPHABET '(+'                          :S(ISASCII1)F(ISASCII2)
*
ISCDC_DISPLAY_CODE
         A = &ANCHOR
         &ANCHOR = 0
         &ALPHABET ')*'                          :S(ISASCII1)F(ISASCII2)
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
* IBM MAINBOL RUNS ON SYSTEM/360, WHICH IS EBCDIC.
*
* AFTER 1.5 (VERSION 1.5+), CSNOBOL4 SUPPORTS BLOCKS WITH THE
* -B COMMAND LINE SWITCH AND -BLOCKS/-NOBLOCKS
*
SYSTEM_0 ISASCII()                                          :F(SYSTEM_1)
         SYSTEM = 'CSNOBOL4 MAINBOL'
         OPSYN('T', '#', 2)
         FUNCTION('T')                                        :F(RETURN)
*
SYSTEM_1 E = &ERRLIMIT
         &ERRLIMIT = 1
         T = DATATYPE(1 # 1)
         &ERRLIMIT = E
         DIFFER(T, 'BLOCK')                                   :S(RETURN)
         SYSTEM = SYSTEM ' WITH BLOCKS'                        :(RETURN)
*
SYSTEM_2 SYSTEM = DIFFER(SUBSTR('ABC', 2, 1), 'B') 'FASBOL'   :S(RETURN)
         SYSTEM = EQ(SIZE(&ALPHABET), 128)         'SITBOL'   :S(RETURN)
         SYSTEM =                                  'SPITBOL'   :(RETURN)
*
SYSTEM_END
*
* CE: .MSNOBOL4;
