-MODULE MBUG
-INCLUDE 'READLINE.INC'
-INCLUDE 'EDITLINE.INC'
-IN72
-STITL MBUG
-EJECT
*
************************************************************************
*                                                                      *
*                                                                      *
*                  #     #  ######   #     #   #####                   *
*                  ##   ##  #     #  #     #  #     #                  *
*                  # # # #  #     #  #     #  #                        *
*                  #  #  #  ######   #     #  #  ####                  *
*                  #     #  #     #  #     #  #     #                  *
*                  #     #  #     #  #     #  #     #                  *
*                  #     #  ######    #####    #####                   *
*                                                                      *
*                                                                      *
************************************************************************
*
* MBUG. A SIMPLE MACHINE LEVEL DEBUG FACILITY FOR USE WITH FFI BASED
* CODE. USES PTRACE(). FORK PROCESS. PARENT RUNS MBUG. CHILD ENTERS
* PTRACE. PARENT ACCEPTS COMMANDS AND CONTROLS CHILD. NEVER TERMINATES.
* ONCE MBUG IS IN CONTROL, THE ONLY EXIT IS EXIT! WE DO THIS BECAUSE
* NORMALLY DATA IS FED INTO THE MACHINE CODE, AND RESULTS RETURNED.
* UNDER PTRACE, THE PROCESS IS FORKED AND THE CHILD IS RUNNING IN
* A COMPLETELY SEPARATE ADDRESS SPACE. NO DATA EXCHANGE IS POSSIBLE.
* THE SIMPLEST SOLUTION IS TO DEMAND AN APPLICATION SHUTDOWN AFTER THE
* DEBUG IS COMPLETE. IN FUTURE, MBUG MAY BE STARTED EARLIER, ALLOWING
* THE PROCESS TO CONTINUE. BUT IT IS DIFFICULT TO DETERMINE WHERE TO
* SET BREAKPOINTS IN THE DYNAMIC CODE (FROM JIT.INC OR ASM.INC LAYERS).
* FOR THIS REASON, WE TAKE THE SIMPLE APPROACH (USEFUL, EVEN IF NOT
* COMPLETE).
*
-TITLE MBUG
-INCLUDE 'UNIX.INC'
-INCLUDE 'LOGIC.INC'
-INCLUDE 'FFI.INC'
-INCLUDE 'DDT.INC'
-STITL
*
-PUBLIC MBUG()
*
         DEFINE('MBUG()')
*
* 0xCC is int3 breakpoint -- for later
*
         PTRACE_TRACEME            = 0
         PTRACE_PEEKTEXT           = 1
         PTRACE_PEEKDATA           = 2
         PTRACE_PEEKUSER           = 3
         PTRACE_POKETEXT           = 4
         PTRACE_POKEDATA           = 5
         PTRACE_POKEUSER           = 6
         PTRACE_CONT               = 7
         PTRACE_KILL               = 8
         PTRACE_SINGLESTEP         = 9
         PTRACE_GETREGS            = 12
         PTRACE_SETREGS            = 13
         PTRACE_GETFPREGS          = 14
         PTRACE_SETFPREGS          = 15
         PTRACE_ATTACH             = 16
         PTRACE_DETACH             = 17
         PTRACE_GETFPXREGS         = 18
         PTRACE_SETFPXREGS         = 19
         PTRACE_SYSCALL            = 24
         PTRACE_SETOPTIONS         = HI('4200')
         PTRACE_GETEVENTMSG        = HI('4201')
         PTRACE_GETSIGINFO         = HI('4202')
         PTRACE_SETSIGINFO         = HI('4203')
         PTRACE_GETREGSET          = HI('4204')
         PTRACE_SETREGSET          = HI('4205')
         PTRACE_SEIZE              = HI('4206')
         PTRACE_INTERRUPT          = HI('4207')
         PTRACE_LISTEN             = HI('4208')
         PTRACE_PEEKSIGINFO        = HI('4209')
         PTRACE_SEIZE_DEVEL        = HI('80000000')
         PTRACE_O_TRACESYSGOOD     = HI('00000001')
         PTRACE_O_TRACEFORK        = HI('00000002')
         PTRACE_O_TRACEVFORK       = HI('00000004')
         PTRACE_O_TRACECLONE       = HI('00000008')
         PTRACE_O_TRACEEXEC        = HI('00000010')
         PTRACE_O_TRACEVFORKDONE   = HI('00000020')
         PTRACE_O_TRACEEXIT        = HI('00000040')
         PTRACE_O_TRACESECCOMP     = HI('00000080')
         PTRACE_O_EXITKILL         = HI('00100000')
         PTRACE_O_MASK             = HI('001000FF')
         PTRACE_EVENT_FORK         = 1
         PTRACE_EVENT_VFORK        = 2
         PTRACE_EVENT_CLONE        = 3
         PTRACE_EVENT_EXEC         = 4
         PTRACE_EVENT_VFORK_DONE   = 5
         PTRACE_EVENT_EXIT         = 6
         PTRACE_EVENT_SECCOMP      = 5
         PTRACE_PEEKSIGINFO_SHARED = 1
*
* PTRACE_PEEKSIGINFO ARG
*     UINT64 OFF
*     UINT32 FLAGS
*     INT32 NR
*
* INDEX INTO ARRAY OF 8 BYTE LONGS RETURNED FROM PTRACE FOR LOCATION
* OF THE USERS' GENERAL PURPOSE REGISTERS (216 BYTES)
*
         REGS_R15      = 0
         REGS_R14      = 1
         REGS_R13      = 2
         REGS_R12      = 3
         REGS_RBP      = 4
         REGS_RBX      = 5
         REGS_R11      = 6
         REGS_R10      = 7
         REGS_R9       = 8
         REGS_R8       = 9
         REGS_RAX      = 10
         REGS_RCX      = 11
         REGS_RDX      = 12
         REGS_RSI      = 13
         REGS_RDI      = 14
         REGS_ORIG_RAX = 15
         REGS_RIP      = 16
         REGS_CS       = 17
         REGS_EFLAGS   = 18
         REGS_RSP      = 19
         REGS_SS       = 20
         REGS_FS_BASE  = 21
         REGS_GS_BASE  = 22
         REGS_DS       = 23
         REGS_ES       = 24
         REGS_FS       = 25
         REGS_GS       = 26
*
* FP REGS. THESE ARE BYTE OFFSETS (user.h)
*
         FPREGS_CWD       = 0
         FPREGS_SWD       = 2
         FPREGS_FTW       = 4
         FPREGS_FOP       = 6
         FPREGS_RIP       = 8
         FPREGS_RDP       = 16
         FPREGS_MXCSR     = 24
         FPREGS_MXCR_MASK = 28
* 8 * 16 BYTES FOR EACH FP-REG = 128 BYTES
         FPREGS_ST_SPACE  = 32
* 16 * 16 BYTES FOR EACH XMM REG = 256 BYTES
         FPREGS_XMM_SPACE = FP_FPREGS_ST_SPACE + 128
* PADDING = 96 BYTES
         FPREGS_PADDING   = FPREGS_XMM_SPACE + 256
*
* NEED REGISTER DEFINITIONS FOR 386, OTHER MACHINES AS APPROPRIATE.
* RIGHT NOW, ALL OF MY WORK IS ON X86_64 PLATFORM, NOT ABLE TO TEST
* OTHERS.
*
* long ptrace(enum __ptrace_request request, pid_t pid,
*             void *addr, void *data)
*
         FFI_PTRACE = FFI_NEW('L', 'I,I,P,P')
         N = DLSYM(0, 'ptrace')
         FFI_SET_CALLP(FFI_PTRACE, N)
*
* SIGNAL DEFINITIONS
*
         SIGHUP    = 1
         SIGINT    = 2
         SIGQUIT   = 3
         SIGILL    = 4
         SIGTRAP   = 5
         SIGABRT   = 6
         SIGIOT    = 6
         SIGBUS    = 7
         SIGFPE    = 8
         SIGKILL   = 9
         SIGUSR1   = 10
         SIGSEGV   = 11
         SIGUSR2   = 12
         SIGPIPE   = 13
         SIGALRM   = 14
         SIGTERM   = 15
         SIGSTKFLT = 16
         SIGCHLD   = 17
         SIGCONT   = 18
         SIGSTOP   = 19
         SIGTSTP   = 20
         SIGTTIN   = 21
         SIGTTOU   = 22
         SIGURG    = 23
         SIGXCPU   = 24
         SIGXFSZ   = 25
         SIGVTALRM = 26
         SIGPROF   = 27
         SIWINCH   = 28
         SIGIO     = 29
         SIGPWR    = 30
         SIGSYS    = 31

         FFI_RAISE = FFI_NEW('I', 'I')
         N = DLSYM(0, 'raise')
         FFI_SET_CALLP(FFI_RAISE, N)
*
         DEFINE('PTRACE(REQUEST,PID,ADDR,DATA)')
         DEFINE('RAISE(SIGNAL)')                           :(PTRACE_END)
*
PTRACE   FFI_PAR_N_INTEGER(FFI_PTRACE, 1, REQUEST)
         FFI_PAR_N_INTEGER(FFI_PTRACE, 2, PID)
         FFI_PAR_N_PTR(FFI_PTRACE, 3, ADDR)
         FFI_PAR_N_PTR(FFI_PTRACE, 4, DATA)
* CONSIDER CALL_INTEGER
         PTRACE = FFI_CALL_PTR(FFI_PTRACE)                     :(RETURN)
*
RAISE    FFI_PAR_N_INTEGER(FFI_RAISE, 1, SIGNAL)
         RAISE = FFI_CALL_INTEGER(FFI_RAISE)                   :(RETURN)
*
PTRACE_END
*
MBUG     TERMINAL = 'MBUG (TUE JUL  8 21:08:00 EDT 2014)'
*
         PID = FORK()
         LT(PID)                                               :F(MBUG2)
         PERROR('FORK')                                           :(END)
MBUG2    EQ(PID)                                               :S(MBUG3)
*
* IN PARENT. THIS IS MBUG MAIN. STATUS 4991 IS RETURNED (HIGH = 19
* WHICH IS SIGSTOP, LOW = 127, OR 0177). FOR SINGLE STEP, WE EXPECT
* STATUS 1407 (HIGH 5 - SIGTRAP, LOW 0177)
*
         DDT()
         RLAPPNAME('MBUG')
         READ_HISTORY('.MBUG')
         STIFLE_HISTORY(50)
*
* WAIT FOR SIGSTOP FIRST
*
         WAITPID(-1, 0)
         STATUS = GET_STATUS()
*
         MBUG_IN = TRIM(HISTORY_EXPAND(READLINE('MBUG: ')))      :F(END)
* NOTE THAT WE WANT TO EXPAND EXPRESSIONS - STEAL CODE FROM DDT/CODE.
* THIS WILL LET US ACCESS GLOBALS AND ASM STRUCTURES. ALSO, NEED
* DISASSEMBLY FROM ASM/JIT TO TELL US WHERE TO PLANT BREAKPOINTS.
* ALSO, SYMBOL TABLE FROM ASM COMPONENT FOR VARIABLES.
*
* SINGLE STEP, COUNTING INSTRUCTIONS
*
STEP     PTRACE(PTRACE_SINGLESTEP, PID, 0, 0)
         WAITPID(-1, 0)
         STATUS = GET_STATUS()
         INSTRUCTIONS = INSTRUCTIONS + 1
         EQ(STATUS, 1407)                                       :S(STEP)
         TERMINAL = 'TOTAL INSTRUCTIONS = ' INSTRUCTIONS         
                                                                  :(END)
*
MBUG3
*
* IN CHILD. WE CALL PTRACE() TO BECOME A CALLEE. PTRACE_TRACEME
* WON'T CAUSE THE CHILD TO STOP. THIS IS WHY WE IMMEDIATELY FOLLOW
* UP WITH RAISE(SIGSTOP). THE WAITPID() IN MBUG WILL NOW RETURN,
* WITH THE CHILD TRACED.
*
         PTRACE(PTRACE_TRACEME, 0, 0, 0)
         RAISE(SIGSTOP)
*
* TEST CODE FOLLOWS - USUALLY, THIS RETURNS, AND THEN ENTERS FFI BASED
* OR LOAD() CODE IMMEDIATELY.
*
         I = 0
LUP      I = I + 1
         LT(I, 100)                                              :S(LUP)
         TERMINAL = 'CHILD COMPLETE'                              :(END)
*
* CE: .MSNOBOL4;
*
END
