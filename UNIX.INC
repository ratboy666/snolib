-MODULE UNIX
-INCLUDE 'FFI.INC'
-INCLUDE 'P64.INC'
-IN72
-STITL UNIX
*
************************************************************************
*                                                                      *
*                    #     #  #     #  ###  #     #                    *
*                    #     #  ##    #   #    #   #                     *
*                    #     #  # #   #   #     # #                      *
*                    #     #  #  #  #   #      #                       *
*                    #     #  #   # #   #     # #                      *
*                    #     #  #    ##   #    #   #                     *
*                     #####   #     #  ###  #     #                    *
*                                                                      *
* UNIX                       UNIX SUPPORT                              *
*                                                                      *
************************************************************************
*
* UNIX.INC
*
* AFTER CSNOBOL4 FUNCTIONS REFACTORED TO UNIX, ADD PEEK_STRING()
* AND REFACTOR TEMPORARY FILE TO HERE AS WELL.
* ADD SPRINTF() TO unix.so
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
-PUBLIC FORK(), WAIT(), WAITPID(), GET_STATUS(), PERROR()
*
         LOAD('WAITPID(INTEGER,INTEGER)', 'unix.so')
         LOAD('GET_STATUS()INTEGER', 'unix.so')
*
         FFI_PERROR = FFI_NEW('V', 'P')
         FFI_SET_CALLP(FFI_PERROR, DLSYM(0, 'perror'))
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
         FFI_READ = FFI_NEW('I', 'I,P,I')
         FFI_SET_CALLP(FFI_READ, DLSYM(0, 'read'))
         FFI_WRITE = FFI_NEW('I', 'I,P,I')
         FFI_SET_CALLP(FFI_WRITE, DLSYM(0, 'write'))
         FFI_GETPID = FFI_NEW('I', '')
         FFI_SET_CALLP(FFI_GETPID, DLSYM(0, 'getpid'))
         FFI_GETPPID = FFI_NEW('I', '')
         FFI_SET_CALLP(FFI_GETPPID, DLSYM(0, 'getppid'))
         FFI_KILL = FFI_NEW('I', 'I,I')
         FFI_SET_CALLP(FFI_KILL, DLSYM(0, 'kill'))
         FFI_RAISE = FFI_NEW('I', 'I')
         FFI_SET_CALLP(FFI_RAISE, DLSYM(0, 'raise'))
         FFI_OPEN = FFI_NEW('I', 'P,I')
         FFI_SET_CALLP(FFI_OPEN, DLSYM(0, 'open'))
         FFI_CREAT = FFI_NEW('I', 'P,I')
         FFI_SET_CALLP(FFI_CREAT, DLSYM(0, 'creat'))
         FFI_DUP = FFI_NEW('I', 'I')
         FFI_SET_CALLP(FFI_DUP, DLSYM(0, 'dup'))
*
-PUBLIC O_RDONLY, O_WRONLY, O_RDWR
*
         O_RDONLY = 0
         O_WRONLY = 1
         O_RDWR   = 2
*
* SIGNAL DEFINITIONS
*
-PUBLIC SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGBUS
*
         SIGHUP    = 1
         SIGINT    = 2
         SIGQUIT   = 3
         SIGILL    = 4
         SIGTRAP   = 5
         SIGABRT   = 6
         SIGBUS    = 7
*
-PUBLIC SIGFPE, SIGKILL, SIGUSR1, SIGSEGV, SIGUSR2, SIGALRM, SIGTERM
*
         SIGFPE    = 8
         SIGKILL   = 9
         SIGUSR1   = 10
         SIGSEGV   = 11
         SIGUSR2   = 12
         SIGPIPE   = 13
         SIGALRM   = 14
         SIGTERM   = 15
*
-PUBLIC SIGSTKFLT, SIGCHLD, SIGCONT, SIGSTOP, SIGTSTP, SIGTTIN, SIGTTOU
*
         SIGSTKFLT = 16
         SIGCHLD   = 17
         SIGCONT   = 18
         SIGSTOP   = 19
         SIGTSTP   = 20
         SIGTTIN   = 21
         SIGTTOU   = 22
*
-PUBLIC SIGURG, SIGXCPU, SIGXFSZ, SIGVTALRM, SIGPROF, SIGWINCH
*
         SIGURG    = 23
         SIGXCPU   = 24
         SIGXFSZ   = 25
         SIGVTALRM = 26
         SIGPROF   = 27
         SIGWINCH  = 28
*
-PUBLIC SIGIO, SIGPWR, SIGSYS
*
         SIGIO     = 29
         SIGPWR    = 30
         SIGSYS    = 31
*
-PUBLIC FILENO(), READ(), WRITE(), GETPID(), GETPPID(), KILL(), RAISE()
-PUBLIC OPEN(), CREAT(), DUP()
*
         DEFINE('KILL(PID,SIG)')
         DEFINE('RAISE(SIG)')
         DEFINE('GETPID()')
         DEFINE('GETPPID()')
         DEFINE('READ(FD,BUF,NBYTES)')
         DEFINE('CLOSE(FD)')
         DEFINE('OPEN(FN,F)')
         DEFINE('CREAT(FN,M)')
         DEFINE('DUP(FD)')
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
         DEFINE('PERROR(S)')
         DEFINE('MALLOC(N)')
         DEFINE('FREE(P)')
         DEFINE('STRDUP(S)')
         DEFINE('STRLEN(S)')                                 :(UNIX_END)
*
PERROR   FFI_PAR_N_STRING(FFI_PERROR, 1, S)
         FFI_CALL_VOID(FFI_PERROR)                             :(RETURN)
*
KILL     FFI_PAR_N_INTEGER(FFI_KILL, 1, PID)
         FFI_PAR_N_INTEGER(FFI_KILL, 2, SIG)
         KILL = FFI_CALL_INTEGER(FFI_KILL)                     :(RETURN)
*
RAISE    FFI_PAR_N_INTEGER(FFI_RAISE, 1, SIG)
         RAISE = FFI_CALL_INTEGER(FFI_RAISE)                   :(RETURN)
*
GETPID   GETPID = FFI_CALL_INTEGER(FFI_GETPID)                 :(RETURN)
*
GETPPID  GETPPID = FFI_CALL_INTEGER(FFI_GETPPID)               :(RETURN)
*
WRITE    FFI_PAR_N_INTEGER(FFI_WRITE, 1, FD)
         FFI_PAR_N_PTR(FFI_WRITE, 2, BUF)
         FFI_PAR_N_PTR(FFI_WRITE, 3, NBYTES)
         WRITE = FFI_CALL_INTEGER(FFI_WRITE)                   :(RETURN)
*
READ     FFI_PAR_N_INTEGER(FFI_READ, 1, FD)
         FFI_PAR_N_PTR(FFI_READ, 2, BUF)
         FFI_PAR_N_PTR(FFI_READ, 3, NBYTES)
         READ = FFI_CALL_INTEGER(FFI_READ)                     :(RETURN)
*
OPEN     FFI_PAR_N_STRING(FFI_OPEN, 1, FN)
         FFI_PAR_N_INTEGER(FFI_OPEN, 2, F)
         OPEN = FFI_CALL_INTEGER(FFI_OPEN)                     :(RETURN)
*
CREAT    FFI_PAR_N_STRING(FFI_CREAT, 1, FN)
         FFI_PAR_N_INTEGER(FFI_CREAT, 2, M)
         CREAT = FFI_CALL_INTEGER(FFI_CREAT)                   :(RETURN)
*
DUP      FFI_PAR_N_INTEGER(FFI_DUP, 1, FD)
         DUP = FFI_CALL_INTEGER(FFI_DUP)                       :(RETURN)
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
