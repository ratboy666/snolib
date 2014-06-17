-INCLUDE 'FFI.INC'
-INCLUDE 'P64.INC'
*
* AFTER CSNOBOL4 FUNCTIONS REFACTORED TO UNIX, ADD PEEK_STRING()
* AND REFACTOR TEMPORARY FILE TO HERE AS WELL.
*
-PUBLIC SIZEOF_INT(), SIZEOF_LONG(), SIZEOF_TIMEVAL(), SIZEOF_FD_SET()
*
         LOAD('SIZEOF_INT()INTEGER', 'unix.so')
         LOAD('SIZEOF_LONG()INTEGER', 'unix.so')
         LOAD('SIZEOF_TIMEVAL()INTEGER', 'unix.so')
         LOAD('SIZEOF_FD_SET()INTEGER', 'unix.so')
*
-PUBLIC GET_ERRNO(), CLEAR_ERRNO()
*
         LOAD('GET_ERRNO()INTEGER', 'unix.so')
         LOAD('CLEAR_ERRNO()INTEGER', 'unix.so')
*
-PUBLIC SET_TIMEVAL()
*
         LOAD('SET_TIMEVAL(INTEGER,INTEGER)', 'unix.so')
*
-PUBLIC FD_ISSET(), FD_ZERO(), FD_SET(), FD_CLR()
*
         LOAD('FD_ISSET_(INTEGER,INTEGER)INTEGER', 'unix.so')
         LOAD('FD_ZERO_(INTEGER)', 'unix.so')
         LOAD('FD_CLR_(INTEGER,INTEGER)', 'unix.so')
         LOAD('FD_SET_(INTEGER,INTEGER)', 'unix.so')
*
-PUBLIC FORK(), WAIT(), WAITPID(), GET_STATUS()
*
         LOAD('WAITPID(INTEGER,INTEGER)', 'unix.so')
         LOAD('GET_STATUS()INTEGER', 'unix.so')
*
         FFI_MALLOC = FFI_NEW('P', 'I')
         FFI_SET_CALLP(FFI_MALLOC, DLSYM(0, 'malloc'))
         FFI_FREE = FFI_NEW('V', 'I')
         FFI_SET_CALLP(FFI_FREE, DLSYM(0, 'free'))
         FFI_STRDUP = FFI_NEW('P', 'P')
         FFI_SET_CALLP(FFI_STRDUP, DLSYM(0, 'strdup'))
         FFI_STRLEN = FFI_NEW('I', 'P')
         FFI_SET_CALLP(FFI_STRLEN, DLSYM(0, 'strlen'))
*
         FFI_PIPE = FFI_NEW('I', 'P')
         FFI_SET_CALLP(FFI_PIPE, DLSYM(0, 'pipe'))
         FFI_FORK = FFI_NEW('I', '')
         FFI_SET_CALLP(FFI_FORK, DLSYM(0, 'fork'))
         FFI_WAIT = FFI_NEW('I', '')
         FFI_SET_CALLP(FFI_WAIT, DLSYM(0, 'wait'))
         FFI_FILENO = FFI_NEW('I', 'P')
         FFI_SET_CALLP(FFI_FILENO, DLSYM(0, 'fileno'))
         FFI_CLOSE = FFI_NEW('I', 'I')
         FFI_SET_CALLP(FFI_CLOSE, DLSYM(0, 'close'))
         FFI_SELECT = FFI_NEW('I', 'I,P,P,P,P')
         FFI_SET_CALLP(FFI_SELECT, DLSYM(0, 'select'))
*
-PUBLIC FILENO()
*
         DEFINE('CLOSE(FD)')
         DEFINE('SELECT(NFDS,READFDS,WRITEFDS,EXCEPTFDS,TIMEOUT)')
         DEFINE('FILENO(FP)')
         DEFINE('FORK()')
         DEFINE('WAIT()')
         DEFINE('FD_ZERO(FDS)')
         DEFINE('FD_ISSET(FD,FDS)')
         DEFINE('FD_CLR(FD,FDS)')
         DEFINE('FD_SET(FD,FDS)')
         DEFINE('NEW_FD_SET()')
         DEFINE('NEW_TIMEVAL()')
*
-PUBLIC PIPE(), MALLOC(), FREE(), STRDUP(), STRLEN(), CLOSE()
-PUBLIC SELECT()
*
         DEFINE('PIPE()R,P')
         DEFINE('MALLOC(N)')
         DEFINE('FREE(P)')
         DEFINE('STRDUP(S)')
         DEFINE('STRLEN(S)')                                 :(UNIX_END)
*
CLOSE    FFI_PAR_N_INTEGER(FFI_CLOSE, 1, FD)
         CLOSE = FFI_CALL_INTEGER(FFI_CLOSE)                   :(RETURN)
*
SELECT   FFI_PAR_N_INTEGER(FFI_SELECT, 1, NFDS)
         FFI_PAR_N_PTR(FFI_SELECT, 2, READFDS)
         FFI_PAR_N_PTR(FFI_SELECT, 3, WRITEFDS)
         FFI_PAR_N_PTR(FFI_SELECT, 4, EXCEPTFDS)
         FFI_PAR_N_PTR(FFI_SELECT, 5, TIMEOUT)
         SELECT = FFI_CALL_INTEGER(FFI_SELECT)                 :(RETURN)
*
FILENO   FFI_PAR_N_PTR(FFI_FILENO, 1, FP)
         FILENO = FFI_CALL_INTEGER(FFI_FILENO)                 :(RETURN)
*
FORK     FORK = FFI_CALL_INTEGER(FFI_FORK)                     :(RETURN)
*
WAIT     WAIT = FFI_CALL_INTEGER(FFI_WAIT)                     :(RETURN)
*
FD_ZERO  FD_ZERO_(FDS)                                         :(RETURN)
*
FD_ISSET FD_ISSET = FD_ISSET_(FD, FDS)                         :(RETURN)
*
FD_CLR   FD_CLR_(FD, FDS)                                      :(RETURN)
*
FD_SET   FD_SET_(FD, FDS)                                      :(RETURN)
*
NEW_FD_SET
         NEW_FD_SET = MALLOC(SIZEOF_FD_SET())                  :(RETURN)
*
NEW_TIMEVAL
         NEW_TIMEVAL = MALLOC(SIZEOF_TIMEVAL())                :(RETURN)
*
MALLOC   FFI_PAR_N_INTEGER(FFI_MALLOC, 1, N)
         MALLOC = FFI_CALL_PTR(FFI_MALLOC)                     :(RETURN)
*
FREE     FFI_PAR_N_PTR(FFI_FREE, 1, P)
         FFI_CALL_VOID(FFI_FREE)                               :(RETURN)
*
STRDUP   FFI_PAR_N_STRING(FFI_STRDUP, 1, S)
         STRDUP = FFI_CALL_PTR(FFI_STRDUP)                     :(RETURN)
*
STRLEN   FFI_PAR_N_PTR(FFI_STRLEN, 1, S)
         STRLEN = FFI_CALL_INTEGER(FFI_STRLEN)                 :(RETURN)
*
PIPE     P = MALLOC(2 * SIZEOF_INT())
         FFI_PAR_N_PTR(FFI_PIPE, 1, P)
         R = FFI_CALL_INTEGER(FFI_PIPE)
         NE(R) FREE(P)                                       :S(FRETURN)
         PIPE = ARRAY(2)
         PIPE<1> = PEEK_I(P)
         PIPE<2> = PEEK_I(P + SIZEOF_INT())
         FREE(P)                                               :(RETURN)
*
UNIX_END
*
* CE: .MSNOBOL4;
