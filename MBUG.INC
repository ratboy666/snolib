-MODULE MBUG
-INCLUDE 'READLINE.INC'
-INCLUDE 'EDITLINE.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'TRIMB.INC'
-INCLUDE 'UNIX.INC'
-INCLUDE 'LOGIC.INC'
-INCLUDE 'FFI.INC'
-INCLUDE 'NSPAN.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'KEYST.INC'
-INCLUDE 'ARRAY0.INC'
-INCLUDE 'BRKREM.INC'
-INCLUDE 'DDT.INC'
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
* MBUG                 MACHINE LEVEL DEBUGGER                          *
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
* OF CODE PROVIDED FROM ASM/JIT TO MBUG. IF LIBOPCODE IS FOUND,
* DISASSEMBLY OF CODE IS AVAILABLE (NOT JUST LISTINGS FROM ASM/JIT).
* LIBOPCODE IS SUPPORTED WITH FEDORA 19/20, BECAUSE IT REQUIRES
* DYNAMIC LINKING TO THE LIBOPCODE SHARED LIBRARY.
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
*
-PUBLIC MBUG(), INT3
*
         DEFINE('MBUG(SYMTAB,SRC)')
*
         INT3 = HI('CC') ;* OR CD 03
*
-PUBLIC PTRACE_TRACEME, PTRACE_PEEKTEXT, PTRACE_PEEKDATA
*
         PTRACE_TRACEME            = 0
         PTRACE_PEEKTEXT           = 1
         PTRACE_PEEKDATA           = 2
*
-PUBLIC PTRACE_PEEKUSER, PTRACE_POKETEXT, PTRACE_POKEDATA
*
         PTRACE_PEEKUSER           = 3
         PTRACE_POKETEXT           = 4
         PTRACE_POKEDATA           = 5
*
-PUBLIC PTRACE_POKEUSER, PTRACE_CONT, PTRACE_KILL, PTRACE_SINGLESTEP
*
         PTRACE_POKEUSER           = 6
         PTRACE_CONT               = 7
         PTRACE_KILL               = 8
         PTRACE_SINGLESTEP         = 9
*
-PUBLIC PTRACE_GETREGS, PTRACE_SETREGS, PTRACE_GETFPREGS
*
         PTRACE_GETREGS            = 12
         PTRACE_SETREGS            = 13
         PTRACE_GETFPREGS          = 14
*
-PUBLIC PTRACE_SETFPREGS, PTRACE_ATTACH, PTRACE_DETACH
*
         PTRACE_SETFPREGS          = 15
         PTRACE_ATTACH             = 16
         PTRACE_DETACH             = 17
*
-PUBLIC PTRACE_GETFPXREGS, PTRACE_SETFPXREGS, PTRACE_SYSCALL
*
         PTRACE_GETFPXREGS         = 18
         PTRACE_SETFPXREGS         = 19
         PTRACE_SYSCALL            = 24
*
-PUBLIC PTRACE_SETOPTIONS, PTRACE_GETEVENTMSG, PTRACE_GETSIGINFO
*
         PTRACE_SETOPTIONS         = HI('4200')
         PTRACE_GETEVENTMSG        = HI('4201')
         PTRACE_GETSIGINFO         = HI('4202')
*
-PUBLIC PTRACE_SETSIGINFO, PTRACE_GETREGSET, PTRACE_SETREGSET
*
         PTRACE_SETSIGINFO         = HI('4203')
         PTRACE_GETREGSET          = HI('4204')
         PTRACE_SETREGSET          = HI('4205')
*
-PUBLIC PTRACE_SEIZE, PTRACE_INTERRUPT, PTRACE_LISTEN
*
         PTRACE_SEIZE              = HI('4206')
         PTRACE_INTERRUPT          = HI('4207')
         PTRACE_LISTEN             = HI('4208')
*
-PUBLIC PTRACE_PEEKSIGINFO, PTRACE_SEIZE_DEVEL, PTRACE_O_TRACESYSGOOD
*
         PTRACE_PEEKSIGINFO        = HI('4209')
         PTRACE_SEIZE_DEVEL        = HI('80000000')
         PTRACE_O_TRACESYSGOOD     = HI('00000001')
*
-PUBLIC PTRACE_O_TRACEFORK, PTRACE_O_TRACEVFORK, PTRACE_O_TRACECLONE
*
         PTRACE_O_TRACEFORK        = HI('00000002')
         PTRACE_O_TRACEVFORK       = HI('00000004')
         PTRACE_O_TRACECLONE       = HI('00000008')
*
-PUBLIC PTRACE_O_TRACEEXEC, PTRACE_O_TRACEVFORKDONE, PTRACE_TRACEEXIT
*
         PTRACE_O_TRACEEXEC        = HI('00000010')
         PTRACE_O_TRACEVFORKDONE   = HI('00000020')
         PTRACE_O_TRACEEXIT        = HI('00000040')
*
-PUBLIC PTRACE_O_TRACESECCOMP, PTRACE_O_EXITKILL, PTRACE_O_MASK
*
         PTRACE_O_TRACESECCOMP     = HI('00000080')
         PTRACE_O_EXITKILL         = HI('00100000')
         PTRACE_O_MASK             = HI('001000FF')
*
-PUBLIC PTRACE_EVENT_FORK, PTRACE_EVENT_VFORK, PTRACE_EVENT_CLONE
*
         PTRACE_EVENT_FORK         = 1
         PTRACE_EVENT_VFORK        = 2
         PTRACE_EVENT_CLONE        = 3
*
-PUBLIC PTRACE_EVENT_EXEC, PTRACE_EVENT_VFORK_DONE, PTRACE_EVENT_EXIT
*
         PTRACE_EVENT_EXEC         = 4
         PTRACE_EVENT_VFORK_DONE   = 5
         PTRACE_EVENT_EXIT         = 6
*
-PUBLIC PTRACE_EVENT_SECCOMP, PTRACE_PEEKSIGINFO_SHARED
*
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
-PUBLIC REGS_R15, REGS_R14, REGS_R13, REGS_R12, REGS_RBP, REGS_RBX
*
         REGS_R15      = 0
         REGS_R14      = 1
         REGS_R13      = 2
         REGS_R12      = 3
         REGS_RBP      = 4
         REGS_RBX      = 5
*
-PUBLIC REGS_R11, REGS_R10, REGS_R9, REGS_R8, REGS_RAX, REGS_RCX
*
         REGS_R11      = 6
         REGS_R10      = 7
         REGS_R9       = 8
         REGS_R8       = 9
         REGS_RAX      = 10
         REGS_RCX      = 11
*
-PUBLIC REGS_RDX, REGS_RSI, REGS_RDI, REGS_ORIG_RAX, REGS_RIP
*
         REGS_RDX      = 12
         REGS_RSI      = 13
         REGS_RDI      = 14
         REGS_ORIG_RAX = 15
         REGS_RIP      = 16
*
-PUBLIC REGS_CS, REGS_EFLAGS, REGS_RSP, REGS_SS, REGS_FS_BASE
*
         REGS_CS       = 17
         REGS_EFLAGS   = 18
         REGS_RSP      = 19
         REGS_SS       = 20
         REGS_FS_BASE  = 21
*
-PUBLIC REGS_GS_BASE, REGS_DS, REGS_ES, REGS_FS, REGS_GS
*
         REGS_GS_BASE  = 22
         REGS_DS       = 23
         REGS_ES       = 24
         REGS_FS       = 25
         REGS_GS       = 26
*
* FP REGS. THESE ARE BYTE OFFSETS (user.h)
*
* FIXME: NOT PUBLISHED YET AS -PUBLIC, WAIT UNTIL TESTED!
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
         FFI_SET_CALLP(FFI_PTRACE, DLSYM(0, 'ptrace'))
*
-PUBLIC PTRACE()
*
         DEFINE('PTRACE(REQUEST,PID,ADDR,DATA)')
*
* NOTE: CSNOBOL4 CALLS OPENING AN ARBITRARY FD BUT DOESN'T ALLOW
* USING A FILE*, AT LEAST IN A DOCUMENTED WAY. io_getfp(int) ALLOWS
* RECOVERY OF FILE* FROM A UNIT, AND io_mkfile(int, FILE*, char*)
* ASSOCIATES A UNIT WITH A FILE*. THE FINAL char* IS THE NAME OF
* THE FILE (FOR ERRORS).
*
* WE DEFINE OPEN_MEMSTREAM TO CREATE A FILE* THAT REFERS TO MEMORY.
* THIS COULD BE ASSOCIATED WITH A UNIT, BUT WE DON'T HAVE TO, GIVEN
* THAT THE ONLY USE HERE IS TO PASS THIS FILE* TO LIBOPCODES.
*
         FFI_OPEN_MEMSTREAM = FFI_NEW('P', 'P,P')
         FFI_SET_CALLP(FFI_OPEN_MEMSTREAM, DLSYM(0, 'open_memstream'))
*
-PUBLIC OPEN_MEMSTREAM()
*
         DEFINE('OPEN_MEMSTREAM(PS,PL)')
*
         FFI_FCLOSE = FFI_NEW('I', 'P')
         FFI_SET_CALLP(FFI_FCLOSE, DLSYM(0, 'fclose'))
*
-PUBLIC FCLOSE()
*
         DEFINE('FCLOSE(F)')
*
* LINK TO DISASSEMBLER
*
-PUBLIC DISASSEMBLE_INFO_ENDIAN, BFD_ENDIAN_BIG, BFD_ENDIAN_LITTLE
-PUBLIC BFD_ENDIAN_UNKNOWN, BFD_DISASSEMBLE_INFO_MACH, BFD_MACH_X86_64
-PUBLIC BFD_MACH_I386_SYNTAX, DISASSEMBLE_INFO_BUFFER
-PUBLIC DISASSEMBLE_INFO_BUFFER_LENGTH, INIT_DISASSEMBLE_INFO()
-PUBLIC PRINT_INSN_I386()
*
         DISASSEMBLE_INFO_ENDIAN        = 40  ;* 4 BYTES
         BFD_ENDIAN_BIG                 = 0
         BFD_ENDIAN_LITTLE              = 1
         BFD_ENDIAN_UNKNOWN             = 2
         DISASSEMBLE_INFO_MACH          = 32  ;* 8 BYTES
         BFD_MACH_X86_64                = 8
         BFD_MACH_I386_INTEL_SYNTAX     = 1
         DISASSEMBLE_INFO_BUFFER        = 152 ;* 8 BYTES
         DISASSEMBLE_INFO_BUFFER_VMA    = 160 ;* 8 BYTES
         DISASSEMBLE_INFO_BUFFER_LENGTH = 168 ;* 4 BYTES
* DDT()
*
* FIXME - FIND A BETTER WAY TO LINK TO DISASSEMBLER LIBRARY.  RIGHT
* NOW WE HAVE TWO PATHS - THE FIRST IS FOR FEDORA 20, AND THE SECOND
* FOR FEDORA 19 -- WE NEED TO FIND ANOTHER WAY TO SELECT THIS WITHOUT
* EDITING THE MBUG SOURCE.
*
         H_LOP = DLOPEN('/usr/lib64/libopcodes-2.23.2.so', RTLD_NOW)
         H_LOP = EQ(H_LOP)
+        DLOPEN('/usr/lib64/libopcodes-2.23.52.0.1-9.fc19.so', RTLD_NOW)
         FFI_INIT_DISASSEMBLE_INFO = FFI_NEW('V', 'P,P,P')
         (DIFFER(H_LOP) FFI_SET_CALLP(FFI_INIT_DISASSEMBLE_INFO,
+           DLSYM(H_LOP, 'init_disassemble_info')))
         DEFINE('INIT_DISASSEMBLE_INFO(DINFO,FILEP,FFUNC)')
         FFI_PRINT_INSN_I386 = FFI_NEW('I', 'P,P')
         (DIFFER(H_LOP)
+   FFI_SET_CALLP(FFI_PRINT_INSN_I386, DLSYM(H_LOP, 'print_insn_i386')))
         DEFINE('PRINT_INSN_I386(VMADDR,DINFO)')
*
         DEFINE('DISASSEMBLE(ADDR)F,P,N,PTR,SIZ,DINFO,DIS,S,I,S2')
*
         DEFINE('MBUG_ARG(S)')
         MBUG_REGS = MALLOC(256)
* ORIG_RAX=15 - ORIGINAL RAX ON SYSCALL
         MBUG_RNAMES = #('R15=0,R14=1,R13=2,R12=3,RBP=4,RBX=5,R11=6,'
+                        'R10=7,R9=8,R8=9,RAX=10,RCX=11,RDX=12,RSI=13,'
+                        'RDI=14,RIP=16,EFLAGS=18,RSP=19')
         MBUG_R2 = KEYST(MBUG_RNAMES)                        :(MBUG_END)
*
* AN ARGUMENT IS A REGISTER, A SYMBOL NAME, OR A HEX VALUE. IF REGISTER,
* THE VALUE OF THE REGISTER IS USED. THE ARGUMENT MAY BE EMPTY, IN
* WHICH CASE THE LAST ARGUMENT IS USED. THE ARGUMENT MAY BE FOLLOWED
* BY + OR - AND A HEX VALUE. FOR EXAMPLE:
*
* D STRINGS, +10
*
* WILL DUMP FROM SYMBOL STRINGS TO STRINGS+10 BYTES.  THE RETAINED
* ARGUMENT IS RETAINED BETWEEN COMMANDS.
*
MBUG_ARG S = TRIMB(S)
         OP =
         R = 0
         S BRKREM('+-') . S REM . R
         R LEN(1) . OP REM . R
         LA = VDIFFER(S)
         S = IDENT(S) LA
         U = REPLACE(S, &LCASE, &UCASE)
         MBUG_ARG = PEEK_P(MBUG_REGS + 8 * VDIFFER(MBUG_RNAMES<U>))
+                                                           :S(MBUG_AR2)
         MBUG_ARG = VDIFFER(SYMTAB<S>)                      :S(MBUG_AR2)
         MBUG_ARG = VDIFFER(SYMTAB<U>)                      :S(MBUG_AR2)
         MBUG_ARG = HI(S)                                      :(RETURN)
MBUG_AR2 IDENT(OP)                                            :S(RETURN)
         R = HI(VDIFFER(R))
         MBUG_ARG = EVAL(MBUG_ARG ' ' OP ' ' R)                :(RETURN)
*
PTRACE   FFI_PAR_N_INTEGER(FFI_PTRACE, 1, REQUEST)
         FFI_PAR_N_INTEGER(FFI_PTRACE, 2, PID)
         FFI_PAR_N_PTR(FFI_PTRACE, 3, ADDR)
         FFI_PAR_N_PTR(FFI_PTRACE, 4, DATA)
         PTRACE = FFI_CALL_PTR(FFI_PTRACE)                     :(RETURN)
*
FCLOSE   FFI_PAR_N_PTR(FFI_FCLOSE, 1, F)
         FCLOSE = FFI_CALL_INTEGER(FFI_FCLOSE)                 :(RETURN)
*
OPEN_MEMSTREAM
         FFI_PAR_N_PTR(FFI_OPEN_MEMSTREAM, 1, PS)
         FFI_PAR_N_PTR(FFI_OPEN_MEMSTREAM, 2, PL)
         OPEN_MEMSTREAM = FFI_CALL_PTR(FFI_OPEN_MEMSTREAM)     :(RETURN)
*
INIT_DISASSEMBLE_INFO
         FFI_PAR_N_PTR(FFI_INIT_DISASSEMBLE_INFO, 1, DINFO)
         FFI_PAR_N_PTR(FFI_INIT_DISASSEMBLE_INFO, 2, FILEP)
         FFI_PAR_N_PTR(FFI_INIT_DISASSEMBLE_INFO, 3, FFUNC)
         FFI_CALL_VOID(FFI_INIT_DISASSEMBLE_INFO)              :(RETURN)
*
PRINT_INSN_I386
         FFI_PAR_N_PTR(FFI_PRINT_INSN_I386, 1, VMADDR)
         FFI_PAR_N_PTR(FFI_PRINT_INSN_I386, 2, DINFO)
         PRINT_INSN_I386 = FFI_CALL_INTEGER(FFI_PRINT_INSN_I386)
+                                                              :(RETURN)
*
DISASSEMBLE
         IDENT(H_LOP)                                         :S(RETURN)
         S = LPAD(IH(ADDR), 16, '0') ': '
         DIS = MALLOC(16)
         DINFO = MALLOC(1024)
         PTR = MALLOC(16)
         SIZ = MALLOC(16)
*
* COPY 16 BYTES FROM DEBUG PROCESS TO DIS BUFFER
*
         N = PTRACE(PTRACE_PEEKTEXT, PID, ADDR + 0, 0)
         POKE_P(DIS + 0, N)
         N = PTRACE(PTRACE_PEEKTEXT, PID, ADDR + 8, 0)
         POKE_P(DIS + 8, N)
*
* CREATE MEMORY STREAM FOR DISASSEMBLY RESULTS
*
         POKE_P(PTR, 0)
         POKE_P(SIZ, 0)
         F = OPEN_MEMSTREAM(PTR, SIZ)
*
         INIT_DISASSEMBLE_INFO(DINFO, F, DLSYM(0, 'fprintf'))
         POKE_P(DINFO + DISASSEMBLE_INFO_MACH, BFD_MACH_X86_64)
         POKE_I(DINFO + DISASSEMBLE_INFO_ENDIAN, BFD_ENDIAN_LITTLE)
         POKE_P(DINFO + DISASSEMBLE_INFO_BUFFER, DIS)
*
* FIXME: NOTE THAT DISASSEMBLE OF RELATIVE BRANCHES NEEDS A BASE
* ADDRESS, CURRENTLY, 0 IS USED, AND THE BRANCH THEN COMPUTES FROM
* THE IDEA THAT THE INSTRUCTION IS LOCATED AT LOCATION 0. THIS IS
* WRONG. WE KNOW THAT THAT THE INSTRUCTION IS ACTUALLY BASED AT
* LOCATION ADDR. BUT, HOW DO WE TELL THE DISASSEMBLER? SETTING
* BUFFER_VMA TO ADDR DOESN'T DO IT. WE MAY BE FORCED TO ACTUALLY
* READ THE LIBOPCODES CODE TO DETERMINE HOW BEST TO ACCOMPLISH THIS
* FEAT.
*
* 0 IS USED AS THE ADDRESS BECAUSE WE COPY THE INSTRUCTION TO A LOCAL
* BUFFER PRIOR TO DISASSEMBLY. SEEMS BOTH VMA AND THE ADDR PASSED TO
* PRINT_INSN_I386() NEED TO BE SET TO THE ORIGINAL ADDRESS. NEED TO
* VERIFY THAT THIS IS CORRECT
* +++
         POKE_P(DINFO + DISASSEMBLE_INFO_BUFFER_VMA, ADDR)
*        POKE_P(DINFO + DISASSEMBLE_INFO_BUFFER_VMA, 0)
         POKE_I(DINFO + DISASSEMBLE_INFO_BUFFER_LENGTH, 16)
*
* DISASSEMBLE DIS BUFFER
*
         INSTRUCTION_BYTES = PRINT_INSN_I386(ADDR, DINFO)
*        INSTRUCTION_BYTES = PRINT_INSN_I386(0, DINFO)
         FCLOSE(F)
*
* MEMORY STREAM RESULTS, MERGE WITH INSTRUCTION BYTES, AND RETURN
* DISASSEMBLY STRING.
*
         P = PEEK_P(PTR)
         N = PEEK_I(SIZ)
*        TERMINAL = 'INSTRUCTION BYTES: ' INSTRUCTION_BYTES
         I = 0
DIS2     S2 = '  '
         S2 = LT(I, INSTRUCTION_BYTES) LPAD(IH(PEEK_C(DIS + I)), 2, '0')
         S = S S2 ' '
         I = I + 1
         LT(I, 4)                                               :S(DIS2)
         DISASSEMBLE = S PEEK_BUFFER(P, N)
DIS4     GE(I, INSTRUCTION_BYTES)                               :S(DIS3)
         DISASSEMBLE = EQ(REMDR(I, 4))
+           DISASSEMBLE CHAR(10) DUPL(' ', 18)
         S2 = LPAD(IH(PEEK_C(DIS + I)), 2, '0')
         DISASSEMBLE = DISASSEMBLE S2 ' '
         I = I + 1                                               :(DIS4)
DIS3     FREE(DIS)
         FREE(DINFO)
         FREE(P)
         FREE(PTR)
         FREE(SIZ)                                             :(RETURN)
*
* MBUG ENTRY. THE 'MAIN' PROCESS NEVER RETURNS. MBUG FORK()S AND THE
* NEW CHILD PROCESS RETURNS, BUT UNDER MBUG CONTROL.
*
MBUG     TERMINAL = 'MBUG (TUE JUL  8 21:08:00 EDT 2014)'
*
* CONVERT SRC TO ARRAY OF LINES. INDEX BY ADDRESS. THE ADDRESSES ARE
* ABSOLUTE ADDRESSES. ON THE 'L' COMMAND AND ON BREAK, ISSUE SOURCE
* IF POSSIBLE.
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
*
* TABLE OF BREAKPOINTS (SEE MBUG.B)
*
         BREAKPOINTS = TABLE()
         BREAKA = ARRAY0
*
* MAP SIGNAL TO SIGNAL NAME
*
         SIGNALS = TABLE(32)
         SIGNALS<SIGHUP>    = 'SIGHUP'
         SIGNALS<SIGINT>    = 'SIGINT'
         SIGNALS<SIGQUIT>   = 'SIGQUIT'
         SIGNALS<SIGILL>    = 'SIGILL'
         SIGNALS<SIGTRAP>   = 'SIGTRAP'
         SIGNALS<SIGABRT>   = 'SIGABRT'
         SIGNALS<SIGBUS>    = 'SIGBUS'
         SIGNALS<SIGFPE>    = 'SIGFPE'
         SIGNALS<SIGKILL>   = 'SIGKILL'
         SIGNALS<SIGUSR1>   = 'SIGUSR1'
         SIGNALS<SIGSEGV>   = 'SIGSEGV'
         SIGNALS<SIGUSR2>   = 'SIGUSR2'
         SIGNALS<SIGPIPE>   = 'SIGPIPE'
         SIGNALS<SIGALRM>   = 'SIGALRM'
         SIGNALS<SIGTERM>   = 'SIGTERM'
         SIGNALS<SIGSTKFLT> = 'SIGSTKFLT'
         SIGNALS<SIGCHLD>   = 'SIGCHLD'
         SIGNALS<SIGCONT>   = 'SIGCONT'
         SIGNALS<SIGSTOP>   = 'SIGSTOP'
         SIGNALS<SIGTSTP>   = 'SIGTSTP'
         SIGNALS<SIGTTIN>   = 'SIGTTIN'
         SIGNALS<SIGTTOU>   = 'SIGTTOU'
         SIGNALS<SIGURG>    = 'SIGURG'
         SIGNALS<SIGXCPU>   = 'SIGXCPU'
         SIGNALS<SIGXFSZ>   = 'SIGXFSZ'
         SIGNALS<SIGVTALRM> = 'SIGVTALRM'
         SIGNALS<SIGPROF>   = 'SIGPROF'
         SIGNALS<SIGWINCH>  = 'SIGWINCH'
         SIGNALS<SIGIO>     = 'SIGIO'
         SIGNALS<SIGPWR>    = 'SIGPWR'
         SIGNALS<SIGSYS>    = 'SIGSYS'
*
* TABLE OF ORIGINAL CODE BYTES (SEE MBUG.B, MBUG.G)
*
         ORIGINAL = TABLE()
*
         PID = FORK()
         LT(PID)                                               :F(MBUG2)
         PERROR('FORK')                                           :(END)
MBUG2    EQ(PID)                                               :S(MBUG3)
*
* 'MAIN' PROCESS. ESTABLISH COMMAND HISTORY. FIXME: THINGS LIKE
* BREAKPOINT AND ORIGINAL CAN BE COMPLETELY MOVED HERE, BECAUSE THEY
* SHOULD NEVER BE NEEDED IN THE CHILD.
*
         RLAPPNAME('MBUG')
         READ_HISTORY('.MBUG')
         STIFLE_HISTORY(50)
*
* WAIT FOR SIGSTOP FIRST (19), SINGLE STEP (5), NORMAL EXIT (0).
*
MBUG_TOP WAITPID(-1, 0)
         STATUS = GET_STATUS()
         EC = STATUS / 256
         P = 'MBUG EXITED (Q TO QUIT): '
         EQ(EC)                                             :S(MBUG_CMD)
         MS_DIS = MALLOC(16)
*
         EQ(EC, SIGTRAP)                                     :S(MBUG_RB)
         TERMINAL = 'EC: ' EC ' ' SIGNALS<EC>
*
* REMOVE BREAKPOINTS, REWIND RIP BY ONE BYTE (INT3 IS A ONE BYTE
* INSTRUCTION).
*
MBUG_RB  IDENT(BRKSET)                                       :S(MBUG_PR)
         I = 1
MBUG_NB  BREAKA<I>                                           :F(MBUG_PR)
         V2 = PTRACE(PTRACE_PEEKDATA, PID, BREAKA<I>, 0)
         M = HI('FFFFFFFFFFFFFF00')
         V2 = AND(V2, M)
         V2 = OR(V2, ORIGINAL<BREAKA<I>>)
         N = PTRACE(PTRACE_POKEDATA, PID, BREAKA<I>, V2)
         I = I + 1                                            :(MBUG_NB)
*
MBUG_PR  PTRACE(PTRACE_GETREGS, PID, 0, MBUG_REGS)
         RIP = PEEK_P(MBUG_REGS + 8 * MBUG_RNAMES<'RIP'>)
*
* IF EC IS 5 AND BRKSET, WE HIT A BREAKPOINT (5 COULD ALSO BE SINGLE
* STEP, BUT WE DON'T SET BREAKPOINTS IN THAT CASE). BACK UP RIP BY
* ONE BYTE.
*
         (EQ(EC, SIGTRAP) DIFFER(BRKSET))                    :F(MBUG_P2)
         RIP = RIP - 1
         POKE_P(MBUG_REGS + 8 * MBUG_RNAMES<'RIP'>, RIP)
         PTRACE(PTRACE_SETREGS, PID, 0, MBUG_REGS)
*
* PROMPT CONTAINS RIP (INSTRUCTION POINTER). FIXME: SHOULD MOVE TO
* MBUG_CMD, IN CASE X RIP COMMAND IS USED TO EDIT THE RIP.
*
MBUG_P2  BRKSET =
         P = 'MBUG ' IH(RIP) ': '
         L = SRCIDX<RIP>                                    :F(MBUG_INS)
         TERMINAL = SRC<L>                                  :S(MBUG_CMD)
*
MBUG_INS S = DISASSEMBLE(RIP)
         TERMINAL = S
*
MBUG_CMD MBUG_IN = TRIM(HISTORY_EXPAND(READLINE(P)))             :F(END)
         IDENT(MBUG_IN)                                     :S(MBUG_CMD)
         ADD_HISTORY(MBUG_IN)
         CMD = FENCE NSPAN(' ' CHARS_TAB)
+              ANY('TtDdBbXxLlSsGgEeQqYyRrKkHhUu=?') . C
+              NSPAN(' ' CHARS_TAB) REM . ARGS
         MBUG_IN CMD                                        :F(MBUG_BAD)
         ARGS = TRIM(ARGS)
         C = REPLACE(C, '?=', 'HE')                      :($('MBUG.' C))
MBUG_BAD TERMINAL = 'BAD COMAND, TRY H FOR HELP'             :(MBUG_CMD)
*
* DUMP SYMBOL TABLE. ARGS IS A PATTERN TO APPLY. FIXME: SHOULD
* EVAL() TO BUILD THE PATTERN -- AS IT IS THE PATTERN IS TAKEN AS
* A SIMPLE STRING.
*
MBUG.Y   A = KEYST(SYMTAB)                                  :F(MBUG_CMD)
         A = SORT(A)
         I = 1
MBUG.Y2  A<I>                                               :F(MBUG_CMD)
         TERMINAL = (A<I> ? ARGS)
+           LPAD(IH(SYMTAB<A<I>>), 16, '0') ' ' A<I>
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
MBUG.R2  BREAKA<I>                                          :F(MBUG_CMD)
         TERMINAL = LPAD(IH(BREAKA<I>), 16, '0')
+           ' (' BREAKPOINTS<BREAKA<I>> ')'
         I = I + 1                                            :(MBUG.R2)
*
MBUG.K   CT = 'CLEAR'                                         :(MBUG.B2)
*
MBUG.U   UA = MBUG_ARG(VDIFFER(ARGS))                        :F(MBUG.U3)
         UA = IDENT(UA) RIP
         TERMINAL = '(' ARGS '):'
MBUG.U3  N = 12
MBUG.U2  TERMINAL = DISASSEMBLE(UA)
         UA = UA + INSTRUCTION_BYTES
         N = N - 1
         GT(N)                                    :S(MBUG.U2)F(MBUG_CMD)
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
* FIXME - STRING HAS TWO ISSUES - C STRING VS BUFFER. POSSIBLY 'C
* FOR BYTE ENTRY
*
* NEED REAL EDIT
*
* '/' LEAVES EDIT, MAYBE ADVANCE, BACKUP? Nn> Pp<? 'C?
*
MBUG.S   ARGS BRKREM(',') . ARGS REM . T
         T FENCE ',' =
         T = REPLACE(TRIMB(T), &LCASE, &UCASE)
         TYPEM = TABLE(21)
         TYPEM<''>        = 'BYTE'
         TYPEM<'BYTE'>    = 'BYTE'
         TYPEM<'WORD'>    = 'WORD'
         TYPEM<'DWORD'>   = 'DWORD'
         TYPEM<'QWORD'>   = 'QWORD'
         TYPEM<'INTEGER'> = 'INTEGER'
         TYPEM<'SHORT'>   = 'SHORT'
         TYPEM<'LONG'>    = 'LONG'
         TYPEM<'B'>       = 'BYTE'
         TYPEM<'W'>       = 'WORD'
         TYPEM<'D'>       = 'DWORD'
         TYPEM<'Q'>       = 'QWORD'
         TYPEM<'I'>       = 'INTEGER'
         TYPEM<'S'>       = 'SHORT'
         TYPEM<'L'>       = 'LONG'
         TYPEM<'FLOAT'>   = 'FLOAT'
         TYPEM<'DOUBLE'>  = 'DOUBLE'
         TYPEM<'REAL'>    = 'FLOAT'
         TYPEM<'F'>       = 'FLOAT'
         TYPEM<'R'>       = 'FLOAT'
         TYPEM<'DP'>      = 'DOUBLE'
         EDITT = TABLE(7)
         EDITT<'BYTE'>    = 'HEX'
         EDITT<'WORD'>    = 'HEX'
         EDITT<'DWORD'>   = 'HEX'
         EDITT<'QWORD'>   = 'HEX'
         EDITT<'INTEGER'> = 'INTEGER'
         EDITT<'SHORT'>   = 'INTEGER'
         EDITT<'LONG'>    = 'INTEGER'
         T = TYPEM<T>
         IDENT(MASKS<T>)                                    :S(MBUG_BAD)
         SA = MBUG_ARG(VDIFFER(ARGS))
         MASKS = TABLE(9)
         MASKC = TABLE(9)
         SIZET = TABLE(9)
         SEXM = TABLE(2)
         SEXT = TABLE(2)
         SEXM<2>          = HI('0000000000008000')
         SEXT<2>          = HI('FFFFFFFFFFFF8000')
         SEXM<4>          = HI('0000000080000000')
         SEXT<4>          = HI('FFFFFFFF80000000')
         MASKS<'BYTE'>    = HI('00000000000000FF')
         MASKC<'BYTE'>    = HI('FFFFFFFFFFFFFF00')
         SIZET<'BYTE'>    = 1
         MASKS<'WORD'>    = HI('000000000000FFFF')
         MASKS<'SHORT'>   = HI('000000000000FFFF')
         MASKC<'WORD'>    = HI('FFFFFFFFFFFF0000')
         MASKC<'SHORT'>   = HI('FFFFFFFFFFFF0000')
         SIZET<'WORD'>    = 2
         SIZET<'SHORT'>   = 2
         MASKS<'DWORD'>   = HI('00000000FFFFFFFF')
         MASKS<'INTEGER'> = HI('00000000FFFFFFFF')
         MASKS<'FLOAT'>   = HI('00000000FFFFFFFF')
         MASKC<'DWORD'>   = HI('FFFFFFFF00000000')
         MASKC<'INTEGER'> = HI('FFFFFFFF00000000')
         MASKC<'FLOAT'>   = HI('FFFFFFFF00000000')
         SIZET<'DWORD'>   = 4
         SIZET<'INTEGER'> = 4
         SIZET<'FLOAT'>   = 4
         MASKS<'QWORD'>   = HI('FFFFFFFFFFFFFFFF')
         MASKS<'LONG'>    = HI('FFFFFFFFFFFFFFFF')
         MASKS<'DOUBLE'>  = HI('FFFFFFFFFFFFFFFF')
         MASKC<'QWORD'>   = HI('0000000000000000')
         MASKC<'LONG'>    = HI('0000000000000000')
         MASKC<'DOUBLE'>  = HI('0000000000000000')
         SIZET<'QWORD'>   = 8
         SIZET<'LONG'>    = 8
         SIZET<'DOUBLE'>  = 8
         SBUF = IDENT(SBUF) MALLOC(16)
*
MBUG.S2  V = AND(PTRACE(PTRACE_PEEKDATA, PID, SA, 0), MASKS<T>)
*
         V = IDENT(EDITT<T>, 'HEX') LPAD(IH(V), SIZET<T> * 2, '0')
         V = IDENT(EDITT<T>, 'INTEGER') V
         V = (IDENT(EDITT<T>, 'INTEGER') DIFFER(SEXM<SIZET<T>>)
+             NE(AND(V, SEXM<SIZET<T>>))) OR(V, SEXT<SIZET<T>>)
         IDENT(T, 'FLOAT') POKE_I(SBUF, V)
         V = IDENT(T, 'FLOAT') PEEK_F(SBUF)
         IDENT(T, 'DOUBLE') POKE_P(SBUF, V)
         V = IDENT(T, 'DOUBLE') PEEK_D(SBUF)
*
         V = EDITLINE(LPAD(IH(SA), 16, '0') ': ', V)
         V = TRIMB(V)
         IDENT(V)                                           :S(MBUG_CMD)
         V ANY('/')                                         :S(MBUG_CMD)
*
* FIXME: CAREFUL ABOUT FAILURE HERE
*
         &ERRLIMIT = 1
         V = IDENT(EDITT<T>, 'HEX') HI(V)
         V = IDENT(EDITT<T>, 'INTEGER') +V
         IDENT(T, 'FLOAT') POKE_F(SBUF, V)
         V = IDENT(T, 'FLOAT') PEEK_I(SBUF)
         IDENT(T, 'DOUBLE') POKE_D(SBUF, V)
         V = IDENT(T, 'DOUBLE') PEEK_P(SBUF)
*
         V = AND(V, MASKS<T>)
         V2 = PTRACE(PTRACE_PEEKDATA, PID, SA, 0)
         V2 = AND(V2, MASKC<T>)
         V3 = OR(V2, V)
         PTRACE(PTRACE_POKEDATA, PID, SA, V3)
         SA = SA + SIZET<T>                                   :(MBUG.S2)
*
* G, EXECUTE
*
* ESTABLISH BREAKPOINTS - SAVE ORIGINAL VALUES, PUT IN INT3 CODES
*
MBUG.G   I = 1
         BRKSET = 1
MBUG.G3  BREAKA<I>                                           :F(MBUG.G2)
         V = AND(PTRACE(PTRACE_PEEKTEXT, PID, BREAKA<I>, 0), 255)
         ORIGINAL<BREAKA<I>> = V
         V2 = PTRACE(PTRACE_PEEKTEXT, PID, BREAKA<I>, 0)
         M = HI('FFFFFFFFFFFFFF00')
         V2 = AND(V2, M)
         V2 = OR(V2, INT3)
         N = PTRACE(PTRACE_POKETEXT, PID, BREAKA<I>, V2)
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
         TWIDTH = 72
MBUG.X3  R = MBUG_R2<I>
         N = PEEK_P(MBUG_REGS + 8 * MBUG_RNAMES<R>)
         N = R '=' IH(N)
         X = SIZE(S) + SIZE(N) + 2
         TERMINAL = GE(X, TWIDTH) S
         S = GE(X, TWIDTH)
         S = VDIFFER(S) ', '
         S = S N
         I = I + 1
         MBUG_R2<I>                                          :S(MBUG.X3)
         TERMINAL = VDIFFER(S)                               :(MBUG_CMD)
*
* X REG DISPLAYS SPECIFIC REGISTER, ALLOWS EDIT OF REGISTER VALUE.
*
MBUG.X2  ARGS = REPLACE(TRIMB(ARGS), &LCASE, &UCASE)
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
MBUG.H   TERMINAL = 'MBUG COMMANDS:'
         TERMINAL = 'T           TRACE, SINGLE STEP'
         TERMINAL = 'X [REG]     EXAMINE/CHANGE REGISTERS'
         TERMINAL = 'G           GO'
         TERMINAL = 'E EXPR      EVALUATE EXPRESSION'
         TERMINAL = 'Q           QUIT MBUG - EXIT TO SYSTEM'
         TERMINAL = 'H           HELP'
         TERMINAL = 'D B,E       DISPLAY MEMORY'
         TERMINAL = 'B ADDR      SET BREAKPOINT'
         TERMINAL = 'K ADDR      REMOVE BREAKPOINT'
         TERMINAL = 'R           REPORT BREAKPOINTS'
         TERMINAL = 'L ADDR      LIST CODE'
         TERMINAL = 'S ADDR[,T]  SET/EXAMINE MEMORY TYPE T'
         TERMINAL = '            BYTE/WORD/DWORD/QWORD FLOAT/DOUBLE'
         TERMINAL = '            SHORT/INTEGER/LONG (BWDQFSIL, DP)'
         TERMINAL = 'H           HELP'
         TERMINAL = 'Y PAT       SYMBOLS, MATCHING PAT'
         TERMINAL = 'U ADDR      UNASSEMBLE'
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
