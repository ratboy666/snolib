-LINE 15 "DISPLAY.lss"
-INCLUDE 'BQ.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'VDIFFER.INC'
-STITL DISPLAY
-EJECT
-LINE 148 "DISPLAY.lss"
*
************************************************************************
*                                                                      *
*     ######   ###   #####   ######   #           #     #     #        *
*     #     #   #   #     #  #     #  #          # #     #   #         *
*     #     #   #   #        #     #  #         #   #     # #          *
*     #     #   #    #####   ######   #        #     #     #           *
*     #     #   #         #  #        #        #######     #           *
*     #     #   #   #     #  #        #        #     #     #           *
*     ######   ###   #####   #        #######  #     #     #           *
*                                                                      *
* DISPLAY            DISPLAY CONTROL (FULL-SCREEN)                     *
*                                                                      *
************************************************************************
*
* DISPLAY.lss
*
-LINE 21 "DISPLAY.lss"
-MODULE DISPLAY
-PUBLIC DS_SMSO, DS_RMSO, DS_SMUL, DS_RMUL, DS_BLINK
-PUBLIC DS_BOLD, DS_DIM, DS_REV, DS_SGR0, DS_CIVIS, DS_CNORM, DS_CVVIS
-PUBLIC DS_GOTO(), DS_FOREGROUND_COLOR(), DS_BACKGROUND_COLOR()
-PUBLIC DS_BLACK, DS_RED, DS_GREEN, DS_YELLOW, DS_BLUE, DS_PURPLE
-PUBLIC DS_CYAN, DS_WHITE, DS_IND, DS_RI
-PUBLIC DS_EL, DS_HOME, DS_CLEAR, DS_COLS, DS_LINES
DISPLAY
*
* GATHER STATIC TERMINAL STRINGS.
*
* STANDOUT (BOLD)
         DS_SMSO  = BQ('tput smso')
* STANDOUT OFF
         DS_RMSO  = BQ('tput rmso')
* UNDERLINE
         DS_SMUL  = BQ('tput smul')
* UNDERLINE OFF
         DS_RMUL  = BQ('tput rmul')
* BLINK
         DS_BLINK = BQ('tput blink')
* BOLD
         DS_BOLD  = BQ('tput bold')
* DIM (HALF-BRIGHT)
         DS_DIM   = BQ('tput dim')
* REVERSE
         DS_REV   = BQ('tput rev')
* RESET ALL
         DS_SGR0  = BQ('tput sgr0')
*
* CURSOR OFF
         DS_CIVIS = BQ('tput civis')
* CURSOR ON
         DS_CNORM = BQ('tput cnorm')
* CURSOR VERY VISIBLE
         DS_CVVIS = BQ('tput cvvis')
*
* ERASE TO END-LINE
         DS_EL    = BQ('tput el')
* HOME CURSOR
         DS_HOME  = BQ('tput home')
* CLEAR DISPLAY
         DS_CLEAR = BQ('tput clear')
*
* NUMBER OF COLUMNS
         DS_COLS  = BQ('tput cols')
*
* NUMBER OF LINES
         DS_LINES = BQ('tput lines')
*
* DYNAMIC STRINGS. THESE ARE CACHED IN TABLE DS_
*
         DS_ = TABLE(DS_LINES * DS_COLS + 16)
*
         DEFINE('DS_GOTO(ROW,COL)')
         DEFINE('DS_FOREGROUND_COLOR(N)')
         DEFINE('DS_BACKGROUND_COLOR(N)')
*
* DEFINED COLORS
*
         DS_BLACK  = 0
         DS_RED    = 1
         DS_GREEN  = 2
         DS_YELLOW = 3
         DS_BLUE   = 4
         DS_PURPLE = 5
         DS_CYAN   = 6
         DS_WHITE  = 7                                    :(DS_GOTO_END)
*
-LINE 97 "DISPLAY.lss"
*
* SET FOREGROUND COLOR.
*
DS_FOREGROUND_COLOR
         DS_FOREGROUND_COLOR = VDIFFER(DS<'F' N>)             :S(RETURN)
         DS_<'F' N> = BQ('tput setaf ' N)         :(DS_FOREGROUND_COLOR)
*
* SET BACKGROUND COLOR.
*
DS_BACKGROUND_COLOR
         DS_BACKGROUND_COLOR = VDIFFER(DS<'B' N>)             :S(RETURN)
         DS_<'B' N> = BQ('tput setab ' N)         :(DS_BACKGROUND_COLOR)
*
* POSITION CURSOR TO (ROW, COLUMN)
*
DS_GOTO  DS_GOTO = VDIFFER(DS_<ROW ' ' COL>)                  :S(RETURN)
*
-LINE 120 "DISPLAY.lss"
         DS_<ROW ' ' COL> = BQ('tput cup ' ROW ' ' COL)       :(DS_GOTO)
*
DS_GOTO_END
*
* IND - SCROLL UP
* NOTE THAT IND IS NL, SO BQ RETURNS IS NOT SUITABLE WE THEREFORE
* DON'T USE BQ('tput ind') BUT CHARS_NL DIRECTLY
*
         DS_IND = DS_GOTO(DS_LINES - 1, 0) CHARS_NL
* RI - SCROLL DOWN
         DS_RI = DS_HOME BQ('tput ri')
*
         CODE('DISPLAY')
*
* CE: .MSNOBOL4;
