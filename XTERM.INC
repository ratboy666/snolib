-MODULE XTERM
-INCLUDE 'SCOOP.INC'
-INCLUDE 'HOST.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'BQ.INC'
-INCLUDE 'CRACK.INC'
-INCLUDE 'SEQ.INC'
-INCLUDE 'UNIX.INC'
-INCLUDE 'CSNOBOL4.INC'
-INCLUDE 'DISPLAY.INC'
-INCLUDE 'READLINE.INC'
-INCLUDE 'FFI.INC'
-INCLUDE 'LOGIC.INC'
-INCLUDE 'P64.INC'
-INCLUDE 'UNIQUE.INC'
-INCLUDE 'DDT.INC'
-IN72
-STITL XTERM
-EJECT
*
************************************************************************
*                                                                      *
*                                                                      *
*             #     #  #######  #######  ######   #     #              *
*              #   #      #     #        #     #  ##   ##              *
*               # #       #     #        #     #  # # # #              *
*                #        #     #####    ######   #  #  #              *
*               # #       #     #        #   #    #     #              *
*              #   #      #     #        #    #   #     #              *
*             #     #     #     #######  #     #  #     #              *
*                                                                      *
* XTERM                     XTERM TERMINAL                             *
*                                                                      *
************************************************************************
*
* LAUNCH XTERM AS AN EXTERNAL TERMINAL FOR APPLICATIONS. THIS CAN
* PROVIDE TEXT AND TEK 4014 GRAPHICS. AS WELL, THE READLINE LIBRARY
* CAN USE THE XTERM TERMINAL.
*
* -xrm 'XTerm.vt100.initialFont: 6'
*
-PUBLIC CLASS:XTERM_CLASS
*
         XTERM_CLASS = SEND(CLASS, 'NEW_CLASS', 'XTERM_CLASS')
         DEFINE('XTERM_INIT(OPTIONS)')
*
-PUBLIC XTERM_CLASS:'INIT'
*
         SEND(XTERM_CLASS, 'ADD_METHOD', 'INIT', 'XTERM_INIT')
*
-PUBLIC FDOPEN()
*
         FFI_FDOPEN = FFI_NEW('P', 'I,P')
         FFI_SET_CALLP(FFI_FDOPEN, DLSYM(0, 'fdopen'))
         DEFINE('FDOPEN(FD,MODE)')
*
-PUBLIC XTERM_CLASS:'CLOSE'
*
         DEFINE('XTERM_CLOSE()E')
         SEND(XTERM_CLASS, 'ADD_METHOD', 'CLOSE', 'XTERM_CLOSE')
*
-PUBLIC XTERM_CLASS:'GET_XTERM'
*
         SEND(XTERM_CLASS, 'ADD_METHOD', 'GET_XTERM', CODE(
+           ' SEND = |.XTERM :(RETURN)'))
*
-PUBLIC XTERM_CLASS:'PREP_READLINE'
*
         DEFINE('XTERM_READLINE()')
         SEND(XTERM_CLASS, 'ADD_METHOD',
+           'PREP_READLINE', 'XTERM_READLINE')
*
-PUBLIC XTERM_CLASS:'NO_READLINE'
*
         DEFINE('XTERM_NOREADLINE()')
         SEND(XTERM_CLASS, 'ADD_METHOD',
+           'NO_READLINE', 'XTERM_NOREADLINE')              :(XTERM_END)
*
XTERM_INIT
         XTERM_INIT = SUPER('INIT')
         |.RL_INSTREAM = DLSYM(0, 'rl_instream')
         |.RL_OUTSTREAM = DLSYM(0, 'rl_outstream')
         |.OLD_RL_INSTREAM = PEEK_P(|.RL_INSTREAM)
         |.OLD_RL_OUTSTREAM = PEEK_P(|.RL_OUTSTREAM)
         |.UNIT = IO_FINDUNIT()
         |.XTERM = UNIQUE()
         INPUT(|.XTERM, |.UNIT, 'U',
+           '|/usr/bin/xterm -Sxx0 ' OPTIONS ' 2>/dev/null')
         OUTPUT(|.XTERM, |.UNIT, 'W,T')
         |.ID = $|.XTERM
         TERMINAL = |.ID                                       :(RETURN)
*
FDOPEN   FFI_PAR_N_INTEGER(FFI_FDOPEN, 1, FD)
         FFI_PAR_N_STRING(FFI_FDOPEN, 2, MODE)
         FDOPEN = FFI_CALL_PTR(FFI_FDOPEN)                     :(RETURN)
*
* PREPARE XTERM FOR READLINE/EDITLINE
*
XTERM_READLINE
         |.FILEH = IDENT(|.FILEH)
+           FDOPEN(FILENO(IO_GETFP(|.UNIT)), 'r+')
         POKE_P(|.RL_INSTREAM, |.FILEH)
         POKE_P(|.RL_OUTSTREAM, |.FILEH)                       :(RETURN)
*
XTERM_NOREADLINE
         POKE_P(|.RL_INSTREAM, |.OLD_RL_INSTREAM)
         POKE_P(|.RL_OUTSTREAM, |.OLD_RL_OUTSTREAM)            :(RETURN)
*
XTERM_CLOSE
         HOST(HOST_SYSCMD, '/usr/bin/xkill -id 0x' |.ID ' >/dev/null')
         E = &ERRLIMIT
         &ERRLIMIT = 1
         ENDFILE(|.UNIT)
         DETACH(|.XTERM)
         &ERRLIMIT = E                                         :(RETURN)
*
XTERM_END
*
* CE: .MSNOBOL4;
