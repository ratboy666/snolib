-LINE 44 "GETKEY.lss"
-INCLUDE 'BQ.INC'
-INCLUDE 'CHARS.INC'
-STITL GETKEY
-EJECT
-LINE 148 "GETKEY.lss"
*
************************************************************************
*                                                                      *
*           #####   #######  #######  #    #  #######  #     #         *
*          #     #  #           #     #   #   #         #   #          *
*          #        #           #     #  #    #          # #           *
*          #  ####  #####       #     ###     #####       #            *
*          #     #  #           #     #  #    #           #            *
*          #     #  #           #     #   #   #           #            *
*           #####   #######     #     #    #  #######     #            *
*                                                                      *
* GETKEY      GET KEY, INCLUDING ARROWS AND FUNCTION KEYS              *
*                                                                      *
************************************************************************
*
* GETKEY.lss
*
-LINE 49 "GETKEY.lss"
-MODULE GETKEY
-PUBLIC GETKEY()
         DEFINE('GETKEY(IN)KEY,M')
*
GETKEY_INIT
*
-PUBLIC KEY_ESC, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_PAGEDN
-PUBLIC KEY_PAGEUP, KEY_HOME, KEY_END, KEY_INS
         KEY_ESC    = CHARS_ESC CHARS_ESC
         KEY_LEFT   = BQ('tput kcub1')
         KEY_RIGHT  = BQ('tput kcuf1')
         KEY_UP     = BQ('tput kcuu1')
         KEY_DOWN   = BQ('tput kcud1')
         KEY_PAGEDN = BQ('tput knp')
         KEY_PAGEUP = BQ('tput kpp')
         KEY_HOME   = BQ('tput khome')
         KEY_END    = BQ('tput kend')
         KEY_INS    = BQ('tput kich1')
-LINE 77 "GETKEY.lss"
         BQ('echo $TERM') 'xterm'                         :F(GETKEY_END)
         KEY_LEFT   = REPLACE(KEY_LEFT,  'O', '[')
         KEY_RIGHT  = REPLACE(KEY_RIGHT, 'O', '[')
         KEY_UP     = REPLACE(KEY_UP,    'O', '[')
         KEY_DOWN   = REPLACE(KEY_DOWN,  'O', '[')
         KEY_HOME   = REPLACE(KEY_HOME,  'O', '[')
         KEY_END    = REPLACE(KEY_END,   'O', '[')
         KEY_INS    = REPLACE(KEY_INS,   'O', '[')
                                                           :(GETKEY_END)
*
GETKEY   &INPUT = 1; KEY =
GK1      M = ; KEY = KEY $IN
*
GK2      M = ?(KEY_UP ? FENCE KEY) 1                             :F(GK3)
         EQ(SIZE(KEY), SIZE(KEY_UP))                             :S(GKR)
*
GK3      M = ?(KEY_DOWN ? FENCE KEY) 1                           :F(GK4)
         EQ(SIZE(KEY), SIZE(KEY_DOWN))                           :S(GKR)
*
GK4      M = ?(KEY_RIGHT ? FENCE KEY) 1                          :F(GK5)
         EQ(SIZE(KEY), SIZE(KEY_RIGHT))                          :S(GKR)
*
GK5      M = ?(KEY_LEFT ? FENCE KEY) 1                           :F(GK6)
         EQ(SIZE(KEY), SIZE(KEY_LEFT))                           :S(GKR)
*
GK6      M = ?(KEY_PAGEDN ? FENCE KEY) 1                         :F(GK7)
         EQ(SIZE(KEY), SIZE(KEY_PAGEDN))                         :S(GKR)
*
GK7      M = ?(KEY_PAGEUP ? FENCE KEY) 1                         :F(GK8)
         EQ(SIZE(KEY), SIZE(KEY_PAGEUP))                         :S(GKR)
*
GK8      M = ?(KEY_HOME ? FENCE KEY) 1                           :F(GK9)
         EQ(SIZE(KEY), SIZE(KEY_HOME))                           :S(GKR)
*
GK9      M = ?(KEY_END ? FENCE KEY) 1                           :F(GK10)
         EQ(SIZE(KEY), SIZE(KEY_END))                            :S(GKR)
*
GK10     M = ?(KEY_INS ? FENCE KEY) 1                           :F(GK11)
         EQ(SIZE(KEY), SIZE(KEY_INS))                            :S(GKR)
*
GK11     M = ?(KEY_ESC ? FENCE KEY) 1                           :F(GK12)
         EQ(SIZE(KEY), SIZE(KEY_ESC))                            :S(GKR)
+                                                                 F(GK1)
-LINE 127 "GETKEY.lss"
GK12     DIFFER(M)                                               :S(GK1)
GKR      GETKEY = KEY                                          :(RETURN)
*
         CODE('GETKEY_INIT')
*
GETKEY_END
*
* CE: .MSNOBOL4;
