-MODULE MBUG
-INCLUDE 'READLINE.INC'
-INCLUDE 'EDITLINE.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'TRIMB.INC'
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
* MBUG IS NOT A VERY SOPHISTICATED DEBUGGER. HOWEVER, MBUG IS
* INTEGRATED WITH ASM/JIT. SYMBOL TABLES ARE SUPPLIED, AND DISASSEMBLY
* OF CODE PROVIDED FROM ASM/JIT TO MBUG.
*
* HOW TO USE:
*
* MAKE SURE ROUTINES AND VARIABLES OF INTEREST ARE MARKED 'EXPORT' IN
* THE ASM SOURCE FILE. THESE NAMES WILL BE AVAILABLE IN MBUG. USE
* 'B NAME' TO SET BREAKPOINTS ON ROUTINES, 'S' TO EXAMINE/CHANGE DATA,
* 'X' OR 'X RAX' (REGISTER NAME) TO EXAMINE/CHANGE REGISTERS. 'G' TO
* EXECUTE TO BREAKPOINT. 'T' TO TRACE CODE. DISASSEMBLY FROM JIT IS
* AVAILABLE, ALONG WITH 'NOTE()' COMMENTS IN THE CODE. SEE RUN FOR
* HOW THIS IS INTERFACED INTO MBUG. NOTE THAT JIT_DISASSEMBLE()
* ALWAYS SENDS RESULTS TO STANDARD OUT -- RUN FORKS A SUBPROCESS, AND
* IN THAT SUBPROCESS REDIRECTS STANDARD OUT. THE DISASSEMBLY IS
* CAPTURED SO IT CAN BE SENT TO MBUG().
-TITLE MBUG
-INCLUDE 'UNIX.INC'
-INCLUDE 'LOGIC.INC'
-INCLUDE 'FFI.INC'
-INCLUDE 'NSPAN.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'KEYST.INC'
-INCLUDE 'ARRAY0.INC'
-INCLUDE 'DDT.INC'
-STITL
*
-PUBLIC MBUG()
*
         DEFINE('MBUG(SYMTAB,SRC)')
*
         INT3 = HI('CC')
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
* LONG PTRACE(ENUM __PTRACE_REQUEST REQUEST, PID_T PID,
*             VOID *ADDR, VOID *DATA)
*
         FFI_PTRACE = FFI_NEW('L', 'I,I,P,P')
         N = DLSYM(0, 'ptrace')
         FFI_SET_CALLP(FFI_PTRACE, N)
*
         DEFINE('PTRACE(REQUEST,PID,ADDR,DATA)')
         DEFINE('MBUG_ARG(S)')
         MBUG_REGS = MALLOC(256)
* ORIG_RAX=15 - ORIGINAL RAX ON SYSCALL
         MBUG_RNAMES = #('R15=0,R14=1,R13=2,R12=3,RBP=4,RBX=5,R11=6,'
+                        'R10=7,R9=8,R8=9,RAX=10,RCX=11,RDX=12,RSI=13,'
+                        'RDI=14,RIP=16,EFLAGS=18,RSP=19')
         MBUG_R2 = KEYST(MBUG_RNAMES)
                                                             :(MBUG_END)
*
MBUG_ARG S = TRIMB(S)
         U = REPLACE(S, &LCASE, &UCASE)
         MBUG_ARG = PEEK_P(MBUG_REGS + 8 * VDIFFER(MBUG_RNAMES<S>))
+                                                             :S(RETURN)
         MBUG_ARG = VDIFFER(SYMTAB<S>)                        :S(RETURN)
         MBUG_ARG = VDIFFER(SYMTAB<U>)                        :S(RETURN)
         MBUG_ARG = HI(S)                                      :(RETURN)
*
PTRACE   FFI_PAR_N_INTEGER(FFI_PTRACE, 1, REQUEST)
         FFI_PAR_N_INTEGER(FFI_PTRACE, 2, PID)
         FFI_PAR_N_PTR(FFI_PTRACE, 3, ADDR)
         FFI_PAR_N_PTR(FFI_PTRACE, 4, DATA)
         PTRACE = FFI_CALL_PTR(FFI_PTRACE)                     :(RETURN)
*
MBUG     TERMINAL = 'MBUG (TUE JUL  8 21:08:00 EDT 2014)'
*
* CONVERT SRC TO ARRAY OF LINES. INDEX BY ADDRESS. THE ADDRESSES ARE
* ABSOLUTE ADDRESSES. ON THE 'L' COMMAND AND ON BREAK, ISSUE SOURCE
* IF POSSIBLE. ON 'L', ALSO DISPLAY 4 BYTES OF CODE.
*
         SRC = CRACK(SRC, CHARS_NL)
         SRCIDX = TABLE()
         I = 1
MBUG5    S = SRC<I>                                            :F(MBUG6)
         S SPAN(' ') '0x' SPAN(&DIGITS 'abcdef') . IDX         :F(MBUG7)
         IDX = REPLACE(IDX, &LCASE, &UCASE)
         IDX = HI(IDX)
         SRCIDX<IDX> = I
MBUG7    I = I + 1                                              :(MBUG5)
MBUG6    B = 0
         BREAKPOINTS = TABLE()
         ORIGINAL = TABLE()
         PID = FORK()
         LT(PID)                                               :F(MBUG2)
         PERROR('FORK')                                           :(END)
MBUG2    EQ(PID)                                               :S(MBUG3)
*
         RLAPPNAME('MBUG')
         READ_HISTORY('.MBUG')
         STIFLE_HISTORY(50)
*
* WAIT FOR SIGSTOP FIRST (19), SINGLE STEP (5), NORMAL EXIT (0).
*
MBUG_TOP WAITPID(-1, 0)
         STATUS = GET_STATUS()
         TERMINAL = EQ(STATUS / 256) 'CODE UNDER MBUG EXITED'
         EC = STATUS / 256
*
* REMOVE BREAKPOINTS, NEED TO REWIND RIP BY ONE BYTE
*
         IDENT(BRKSET) :S(MBUG_PR)
         I = 1
MBUG_NB  BREAKA<I>                                           :F(MBUG_PR)
         V2 = PTRACE(PTRACE_PEEKDATA, PID, BREAKA<I>, 0)
         M = HI('FFFFFFFFFFFFFF00')
         V2 = AND(V2, M)
         V2 = OR(V2, ORIGINAL<BREAKA<I>>)
         N = PTRACE(PTRACE_POKEDATA, PID, BREAKA<I>, V2)
         I = I + 1                                            :(MBUG_NB)
*
MBUG_PR  N = PTRACE(PTRACE_GETREGS, PID, 0, MBUG_REGS)
         N = PEEK_P(MBUG_REGS + 8 * MBUG_RNAMES<'RIP'>)
*
* IF EC IS 5 AND BRKSET, WE HIT A BREAKPOINT (5 COULD ALSO BE SINGLE
* STEP, BUT WE DON'T SET BREAKPOINTS IN THAT CASE). BACK UP RIP BY
* ONE BYTE
         (EQ(EC, 5) DIFFER(BRKSET)) :F(MBUG_P2)
         N = N - 1
         POKE_P(MBUG_REGS + 8 * MBUG_RNAMES<'RIP'>, N)
         PTRACE(PTRACE_SETREGS, PID, 0, MBUG_REGS)
*
* PROMPT CONTAINS RIP (INSTRUCTION POINTER)
*
MBUG_P2  BRKSET =
         P = 'MBUG ' IH(N) ': '
         L = SRCIDX<N> :F(MBUG_CMD)
         TERMINAL = SRC<L>
MBUG_CMD MBUG_IN = TRIM(HISTORY_EXPAND(READLINE(P)))             :F(END)
         IDENT(MBUG_IN)                                     :S(MBUG_CMD)
         ADD_HISTORY(MBUG_IN)
         CMD = FENCE NSPAN(' ' CHARS_TAB)
+              ANY('TtDdBbXxLlSsGgEeQqYyRrKk=?') . C
+              NSPAN(' ' CHARS_TAB) REM . ARGS
         MBUG_IN CMD                                          :F(MBUG.H)
         ARGS = TRIM(ARGS)
         C = REPLACE(C, '?=', 'HE')                      :($('MBUG.' C))
*
* DUMP SYMBOL TABLE
*
MBUG.Y   A = KEYST(SYMTAB)                                  :F(MBUG_CMD)
         A = SORT(A)
         I = 1
MBUG.Y2  TERMINAL = LPAD(IH(SYMTAB<A<I>>), 16, '0') ' ' A<I>
+                                                           :F(MBUG_CMD)
         I = I + 1                                            :(MBUG.Y2)
*
* DISPLAY MEMORY
*
MBUG.D   IDENT(ARGS)                                         :S(MBUG.D5)
         ARGS BRKREM(',') . A1 =
         ARGS FENCE ',' =
         B = MBUG_ARG(A1)
         IDENT(ARGS)                                         :S(MBUG.D5)
         E = MBUG_ARG(ARGS)
         GT(E, B)                                            :S(MBUG.D4)
MBUG.D5  E = B + 256
*
MBUG.D4  A = LPAD(IH(B), 16, '0') ': '
         H =
         S =
MBUG.D2  V = AND(PTRACE(PTRACE_PEEKDATA, PID, B, 0), 255)
         S = S (LT(V, 32) '.', GT(V, 126) '.', CHAR(V))
         V = LPAD(IH(V), 2, '0')
         H = H V
         H = NE(AND(B, 1)) H ' '
         B = B + 1
         GE(B, E)                                            :S(MBUG.D3)
         EQ(AND(B, 15))                                      :F(MBUG.D2)
         TERMINAL = A LPAD(H, 40, ' ') S                      :(MBUG.D4)
MBUG.D3  TERMINAL = A RPAD(H, 40, ' ') S
         B = E                                               :(MBUG_CMD)
*
MBUG.B   CT = 'SET'
MBUG.B2  IDENT(ARGS)                                         :S(MBUG.B4)
         ARGS BRKREM(',') . A =
         ARGS FENCE ',' =
         A = TRIMB(A)
         IDENT(A)                                            :S(MBUG.B2)
         A2 = MBUG_ARG(A)
         IDENT(CT, 'SET')                                    :F(MBUG.B3)
         DIFFER(BREAKPOINTS<A2>)                             :S(MBUG.B2)
         BREAKPOINTS<A2> = A                                  :(MBUG.B2)
MBUG.B3  IDENT(BREAKPOINTS<A2>)                              :S(MBUG.B2)
         BREAKPOINTS<A2> =                                    :(MBUG.B2)
MBUG.B4  BREAKA = (KEYST(BREAKPOINTS), ARRAY0)               :(MBUG_CMD)
*
MBUG.R   I = 1
MBUG.R2  BREAKA<I> :F(MBUG_CMD)
         TERMINAL = LPAD(IH(BREAKA<I>), 16, '0')
+           ' (' BREAKPOINTS<BREAKA<I>> ')'
         I = I + 1 :(MBUG.R2)
*
MBUG.K   CT = 'CLEAR' :(MBUG.B2)
*
MBUG.L   A = MBUG_ARG(VDIFFER(ARGS))                         :F(MBUG.L3)
         L = SRCIDX<A>                                      :F(MBUG_CMD)
         TERMINAL = LPAD(IH(A), 16, '0') ' (' ARGS '):'
MBUG.L3  N = 12
MBUG.L2  TERMINAL = SRC<L>                                  :F(MBUG_CMD)
         L = L + 1
         N = N - 1
         GT(N)                                    :S(MBUG.L2)F(MBUG_CMD)
*
MBUG.S   TERMINAL = 'S COMMAND'
         SA = MBUG_ARG(VDIFFER(ARGS))
MBUG.S2  V = AND(PTRACE(PTRACE_PEEKDATA, PID, SA, 0), 255)
         V = LPAD(IH(V), 2, '0')
         V = EDITLINE(LPAD(IH(SA), 16, '0') ': ', V)
         V = TRIMB(V)
         IDENT(V)                                           :S(MBUG_CMD)
*        V ANY('./')                                        :S(MBUG_CMD)
         V = HI(V)                                          :F(MBUG_CMD)
         V2 = PTRACE(PTRACE_PEEKDATA, PID, SA, 0)
         M = HI('FFFFFFFFFFFFFF00')
         V2 = AND(V2, M)
         V2 = OR(V2, V)
         N = PTRACE(PTRACE_POKEDATA, PID, SA, V2)
         SA = SA + 1                                          :(MBUG.S2)
*
* G, EXECUTE
*
* ESTABLISH BREAKPOINTS - SAVE ORIGINAL VALUES, PUT IN INT3 CODES
*
MBUG.G   I = 1
         BRKSET = 1
MBUG.G3  BREAKA<I>                                           :F(MBUG.G2)
         V = AND(PTRACE(PTRACE_PEEKDATA, PID, BREAKA<I>, 0), 255)
         ORIGINAL<BREAKA<I>> = V
         V2 = PTRACE(PTRACE_PEEKDATA, PID, BREAKA<I>, 0)
         M = HI('FFFFFFFFFFFFFF00')
         V2 = AND(V2, M)
         V2 = OR(V2, INT3)
         N = PTRACE(PTRACE_POKEDATA, PID, BREAKA<I>, V2)
         I = I + 1                                            :(MBUG.G3)
MBUG.G2  PTRACE(PTRACE_CONT, PID, 0, 0)                      :(MBUG_TOP)
*
MBUG.E   TERMINAL = ARGS ' = ' EVAL(ARGS)                    :(MBUG_CMD)
*
MBUG.Q   WRITE_HISTORY('.MBUG')
         KILL(PID, SIGKILL)                                       :(END)
*
MBUG.X   DIFFER(ARGS)                                        :S(MBUG.X2)
*
* X ALONE DISPLAYS ALL REGISTERS. WE DON'T DO FLOATING POINT REGISTERS
* YET.
*
         I = 1
         S =
MBUG.X3  R = MBUG_R2<I>
         N = PEEK_P(MBUG_REGS + 8 * MBUG_RNAMES<R>)
         N = R '=' IH(N)
         X = SIZE(S) + SIZE(N) + 2
         TERMINAL = GE(X, 80) S
         S = GE(X, 80)
         S = VDIFFER(S) ', '
         S = S N
         I = I + 1
         MBUG_R2<I>                                          :S(MBUG.X3)
         TERMINAL = VDIFFER(S)                               :(MBUG_CMD)
*
* X REG DISPLAYS SPECIFIC REGISTER, ALLOWS EDIT OF REGISTER VALUE.
*
MBUG.X2  ARGS = REPLACE(ARGS, &LCASE, &UCASE)
         IDENT(MBUG_RNAMES<ARGS>)                           :S(MBUG_CMD)
         N = PEEK_P(MBUG_REGS + 8 * MBUG_RNAMES<ARGS>)
         N = IH(N)
         N = EDITLINE(ARGS ': ', N)
         N = HI(N)
         POKE_P(MBUG_REGS + 8 * MBUG_RNAMES<ARGS>, N)
         N = PTRACE(PTRACE_SETREGS, PID, 0, MBUG_REGS)       :(MBUG_CMD)
*
* HELP FOR MBUG
*
MBUG.H   TERMINAL = 'T       TRACE, SINGLE STEP'
         TERMINAL = 'X [REG] EXAMINE/CHANGE REGISTERS'
         TERMINAL = 'G       GO'
         TERMINAL = 'E EXPR  EVALUATE EXPRESSION'
         TERMINAL = 'Q       QUIT MBUG - EXIT TO SYSTEM'
         TERMINAL = 'H       HELP'
         TERMINAL = 'D B,E   DISPLAY MEMORY'
         TERMINAL = 'B ADDR  SET BREAKPOINT'
         TERMINAL = 'K ADDR  REMOVE BREAKPOINT'
         TERMINAL = 'R       REPORT BREAKPOINTS'
         TERMINAL = 'L ADDR  LIST CODE'
         TERMINAL = 'S ADDR  SET MEMORY'
                                                             :(MBUG_CMD)
*
MBUG.T   PTRACE(PTRACE_SINGLESTEP, PID, 0, 0)                :(MBUG_TOP)
*
* IN CHILD. WE CALL PTRACE() TO BECOME A CALLEE. PTRACE_TRACEME
* WON'T CAUSE THE CHILD TO STOP. THIS IS WHY WE IMMEDIATELY FOLLOW
* UP WITH RAISE(SIGSTOP). THE WAITPID() IN MBUG WILL NOW RETURN,
* WITH THE CHILD TRACED.
*
MBUG3    PTRACE(PTRACE_TRACEME, 0, 0, 0)
         RAISE(SIGSTOP)
*
* AFTER RETURN, ENTER FFI BASED OR LOAD() CODE IMMEDIATELY. ALL CODE
* AFTER THE RAISE(SIGSTOP) IS RUN UNDER THE CONTROL OF MBUG.
*
                                                               :(RETURN)
*
* CE: .MSNOBOL4;
*
MBUG_END
