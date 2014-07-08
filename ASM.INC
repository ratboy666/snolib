-MODULE ASM
-INCLUDE 'JIT.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'KEYST.INC'
-INCLUDE 'BREAKQ.INC'
-INCLUDE 'NSPAN.INC'
-INCLUDE 'LINK.INC'
-INCLUDE 'CRACK.INC'
-INCLUDE 'UNIX.INC'
-INCLUDE 'P64.INC'
-INCLUDE 'LOGIC.INC'
-INCLUDE 'COPYT.INC'
-INCLUDE 'TRIMB.INC'
-INCLUDE 'FFI.INC'
-IN72
-STITL ASM
-CASE 1
-PLUSOPS 1
-EJECT
*
************************************************************************
*                                                                      *
*                         #      #####   #     #                       *
*                        # #    #     #  ##   ##                       *
*                       #   #   #        # # # #                       *
*                      #     #   #####   #  #  #                       *
*                      #######        #  #     #                       *
*                      #     #  #     #  #     #                       *
*                      #     #   #####   #     #                       *
*                                                                      *
* ASM                  ASSEMBLER/LOADER FOR JIT                        *
*                                                                      *
************************************************************************
*
* ASM.INC
*
* A SIMPLE ASSEMBLER/LOADER FOR JIT CODE. THIS IS A BIT BRITTLE.
*
* THE BASIC IDEA IS THAT EACH ASSEMBLER LINE IS EXAMINED, AND LABEL,
* OPCODE AND UP TO THREE PARAMETERS EXTRACTED. THE OPCODE MAY MATCH
* A FUNCTION IN THE ASSEMBLER (WITH '__' APPENDED), OR, WITH JIT_
* PREPENDED, A JIT GENERATION INSTRUCTION. THE FUNCTION IS THEN CALLED
* WITH UP TO THREE PARAMETERS. EACH PARAMETER IS A STRING, A NUMBER, A
* SYMBOL REFERENCE OR A REGISTER. EACH LABEL ON A JIT_ OPCODE IS ENTERED
* INTO A LOCAL SYMBOL TABLE.
*
* ASM() WORKS IN TWO PHASES - THE FIRST PHASE CREATES SYMBOLS IN
* THE SYMBOLS1 TABLE. AFTER PHASE1, WE PREPARE THE DSS AND BSS AREAS
* (THIS COULD BE CONSIDERED PHASE1A - BUT WE ONLY COUNT SOURCE SCANS
* AS PHASES). THE SECOND PHASE ACTUALLY GENERATES CODE, USING THE
* SYMBOLS CREATED IN PHASE1. ON COMPLETIION OF PHASE2, WE RESOLVE
* INTERNAL LOCAL SYMBOLS (BRANCHES IN THE CODE -- THIS IS PHASE 2A).
* NOTE THAT 'EXTERN' SYMBOLS ARE PUT INTO THE EXPORTS TABLE. THESE
* CAN BE DSS, BSS OR ADDRESS SYMBOLS. THIS TABLE CAN BE MERGED WITH
* OTHER EXPORT TABLES (USING MERGET), AND PASSED TO ASM_CREATE TO
* ESTABLISH THE IMPORTS NEEDED. EXPORTS(ASM) ACCESSES THIS TABLE
* FOR A MODULE.
*
* A = ASM_CREATE()
* S = ASM(A, SRC) :F(ERROR)
* ASM_DESTROY(A)
*
* THIS IS A PART OF A "MACHINE CODE LOADER", AND ENTRY AND USAGE ISSUES
* ARE MEANT TO BE COVERED ELSEWHERE. THIS MODULE HANDLES INTEPRETING THE
* FORMAT, AND RESOLVING (MOST) SYMBOLS, PREPARING THE OBJECT FOR
* EVENTUAL EXECUTION.
*
* THE ASM_TYPE() OBJECT IS CREATED AND IS SOMEWHAT INDEPENDENT OF THE
* ASM SOURCE AND ASM() CALL. THIS ALLOWS THE ACTUAL ASM RESULTS TO BE
* USED INDEPENDENTLY WITH (MOST) USING CODE BEING UNAWARE OF THE
* IMPLEMENTATION USING JIT. AS FAR AS THE USING CODE IS CONCERNED,
* ASM MAY HAVE BEEN IMPLEMENTED USING AN INTERPRETER.
*
* FOR FINAL USE OF THE ASM JIT CODE, JIT(A) WILL RETRIEVE THE JIT STATE,
* WHICH CAN BE USED WITH JIT FUNCTIONS FOR DEBUG, AND TO EMIT CODE WHICH
* CAN BE PASSED TO OTHER FUNCTIONS LIKE FFI TO PREPARE FOR FINAL
* EXECUTION.
*
* CE: .MSNOBOL4;
*
-PUBLIC JIT(), EXPORTS(), OBJ(), ASM_CREATE(), ASM_DESTROY(), ASM()
-PUBLIC DSSBASE(), BSSBASE()
*
         DATA('ASM_TYPE(JIT,SYMBOLS1,SYMBOLS,REFERENCES,DSS,BSS,SZBSS,'
+                      'DINIT,DSSBASE,BSSBASE,ENTRIES,SRC,OBJ,DAREFS,'
+                      'DPREFS,EXPORTS)')
*
         DEFINE('ASM_CREATE(SYMBOLS1)')
         DEFINE('ASM_DESTROY(ASM)')
         DEFINE('ASM(ASM,SRC)')
*
         DEFINE('ASM_EMIT()')
         DEFINE('ASM_BSS()A,I')
         DEFINE('ASM_DA()A,I,P')
         DEFINE('ASM_DSS()A,I,S')
         DEFINE('ASM_LINK()SYMBOLS,A,I,P,R,S')
         DEFINE('ASM_PHASE(ASM_PHASE)'
+               'SRC,LINE,ELINE,R,SYMBOL,LAB,OP,P1,P2,P3,S,OP1')
*
         ASET = &UCASE &LCASE &DIGITS '_.$'
         AWHT = NSPAN(' ' CHARS_TAB)
         ASM_PAT = FENCE NSPAN(ASET) . LAB
+                  AWHT NSPAN(ASET) . OP
+                  AWHT ((BREAKQ(',') . P1 ',') | NULL)
+                  AWHT ((BREAK(',') . P2 ',') | NULL)
+                  AWHT ((BREAK(',') . P3 ',') | NULL)
*
         DEFINE('ASM_PARM(X)OFFSET,S,SIGN')
         DEFINE('ALIGN_BSS(A),N')
*
         DEFINE('PHASE1__(P1)')
         DEFINE('PHASE2__(P2)')
         DEFINE('EXTERN__(P1,P2,P3)H')
         DEFINE('DEFINE__(P1,P2,P3)H')
         DEFINE('USES__(P1)A')
         DEFINE('EQU__(P1)')
         DEFINE('ADDRESS__()')
         DEFINE('EXPORT__()')
*
         DEFINE('COMMON__(P1)')
         DEFINE('RESB__(P1)')
         DEFINE('RESW__(P1)')
         DEFINE('RESD__(P1)')
         DEFINE('RESQ__(P1)')
         DEFINE('RES(P1,P2)')
*
         DEFINE('DB__(P1)')
         DEFINE('DW__(P1)')
         DEFINE('DD__(P1)')
         DEFINE('DQ__(P1)')
         DEFINE('DA__(P1)')
         DEFINE('DP__(P1)')
         DEFINE('DS__(P1)')
*
* SET TO NON-NULL TO HAVE ASM GIVE DEBUG OUTPUT
*
         ASM_DEBUG =
*
* FOR REGISTER LOOKUP - OPTIMIZATION
*
         AS_REGS = TABLE()
*
* SIZES OF TYPES
*
         BYTE = 1
         WORD = 2
         DWORD = 4
         QWORD = 8
         FLOAT = 4
         DOUBLE = 8
*
* STORAGE USED FOR DATA CONVERSIONS.
*
         ASM_P = MALLOC(128)
*
* TABLE FOR OPEN SHARED OBJECTS.
*
         DL_TABLE = TABLE()
         DL_TABLE<0> = 0
*
* NOT USED AS TABLES, THESE ARE SIMPLY UNIQUE NON-STRINGS USED TO
* IDENTIFY EMPTY AND SYMBOL REFERENCE PARAMETERS.
* 
         ASM_PEMPTY = TABLE(1, 1)
         ASM_PSYMBOL = TABLE(1, 1)                            :(END_ASM)
*
* STANDARD EXTRA OPERATIONS FOR ASM CODE. OF COURSE, ANY APPLICATION
* SPECIFICS CAN BE DEFINED IN THE USING CODE AND ARE FREELY AVAILABLE
* THIS ALLOWS THE CODE GENERATOR TO BE EASILY TAILORED FOR SPECIFIC
* NEEDS. FOR EXAMPLE, MACROS COULD BE DEFINED. ALL THREE OF THE
* PARAMETERS CAN BE STRINGS OR NUMBERS. THE LABEL IS AVAILABLE AS LAB.
*
* BE WARNED THOUGH, THAT THIS IS NOT ONLY AN "ASSEMBLER" FORMAT, IT IS
* ALSO MEANT TO BE USED AS THE RELOCATING LOADER. SO, KEEP AN EYE
* ON PERFORMANCE!
*
* USES - DECLARES OBJECT CODE USES GIVEN LIST OF REGISTERS. IF A NEEDED
* REGISTER IS NOT AVAIABLE, GIVES A MESSAGES, AND FAILS. IF ALL
* REGISTERS ARE AVAILABLE, RETURNS SUCCESS.
*
* (FIXME - THERE ARE SOME MINOR DIFFERENCES BETWEEN 32 BIT AND 64 BIT
* CODE GENERATION THAT SHOULD ALSO BE "HIDDEN").
*
USES__   NE(ASM_PHASE, 1)                                     :S(RETURN)
USES2    P1 ANY('%') =                                         :S(USES2)
         P1 = CRACK(P1, ',')
         I = 1
USES3    P1<I>                                                :F(RETURN)
         FUNCTION(P1<I> '_')                                   :F(USES4)
         EQ(APPLY(P1<I> '_',), -1)                             :S(USES4)
         I = I + 1                                              :(USES3)
USES4    TERMINAL = 'REGISTER ' P1<I> ' NOT AVAILABLE'        :(FRETURN)
*
* ADDRESS - ADDS SYMBOL(ASM) ENTRY ON PHASE2 THAT CAN BE EVALUATED
* TO AN ADDRESS WITH JIT_ADDRESS(). USEFUL FOR ENTRY POINTS AND
* CONSTRUCTING JUMP TABLES. COULD USE NOTE(NULL, 0) HERE AS WELL.
*
ADDRESS__
         NE(ASM_PHASE, 2)                                     :S(RETURN)
         ENTRIES(ASM)<LAB> = SYMBOLS(ASM)<LAB> = JIT_INDIRECT()
+                                                              :(RETURN)
*
* SYMBOL TO BE EXPORTED. BSS, DSS OR ADDRESS. JUST MAKE THE TABLE
* ENTRY NON-NULL.
*
EXPORT__ SYMBOL = NE(ASM_PHASE, 1)                            :S(RETURN)
         EXPORTS(ASM)<SYMBOL> = ' '
         EXPORTS(ASM)<SYMBOL> = VDIFFER(SYMBOLS1(ASM)<SYMBOL>)
         SYMBOL =                                              :(RETURN)
*
* PHASE1 EVALUATION ONLY. EVAL P1 DURING PHASE1.
*
PHASE1__ NE(ASM_PHASE, 1)                                     :S(RETURN)
         PHASE1 = EVAL(P1)                          :S(RETURN)F(FRETURN)
*
* PHASE2 EVALUATION ONLY. EVAL P1 DURING PHASE2.
*
PHASE2__ NE(ASM_PHASE, 2)                                     :S(RETURN)
         PHASE2 = EVAL(P1)                          :S(RETURN)F(FRETURN)
*
* ENTER VALUE INTO SYMBOLS1 TABLE. THIS MAY BE INTEGER OR REAL.
* ALSO NOTE THAT VALUE WILL BE ENTERED INTO THE EXPORTS TABLE IF NEEDED.
*
* NOTE THAT EXTERN ADDS TO EXPORTS ON THE DA RESOLUTION PASS, SO IT
* ISN'T DONE HERE.
*
DEFINE__ NE(ASM_PHASE, 1)                                     :S(RETURN)
         SYMBOLS1(ASM)<LAB> = INTEGER(P1) +P1               :S(DEFINE_2)
         SYMBOLS1(ASM)<LAB> = REAL(P1) +P1                   :F(FRETURN)
DEFINE_2 EXPORTS(ASM)<LAB> = DIFFER(EXPORTS(ASM)<LAB>)
+           SYMBOLS1(ASM)<LAB>                                 :(RETURN)
*
* ENTER EXTERNAL LINK INTO SYMBOLS1 TABLE. THERE ARE THREE FORMS FOR
* THIS DIRECTIVE:
*
* LABEL EXTERN 'NAME' ; DEFINE LABEL AS DLSYM(, 'NAME')
* LABEL EXTERN 'NAME','SO' ; 'NAME' IN 'SO'
* LABEL EXTERN 'NAME','SO',FLAGS ; IN 'SO' OPEN WITH FLAGS
*
* P1 = ENTRY NAME, P2 = MODULE NAME, P3 = OPEN FLAGS
*
EXTERN__ NE(ASM_PHASE, 1)                                     :S(RETURN)
         P2 = IDENT(P2) 0
         P3 = IDENT(P3) RTLD_NOW
         H = DL_TABLE<P2>
         DIFFER(H)                                           :S(EXTERN2)
         H = DIFFER(P2) DLOPEN(P2, P3)
         NE(+H, 0)                                           :S(EXTERN3)
         TERMINAL = 'DLOPEN FAILED: ' DLERROR()               :(FRETURN)
EXTERN3  DL_TABLE<P2> = H
EXTERN2  SYMBOLS1(ASM)<LAB> = DLSYM(H, P1)
*
* WE CAN AMORTIZE DLOPEN/DLSYM. INSTEAD OF EXTERN IN EACH MODULE,
* THESE CAN BE EXPORT, AND THEN WE CAN IMPORT IN ANOTHER ASSEMBLY
*
         EXPORTS(ASM)<LAB> = DIFFER(EXPORTS(ASM)<LAB>)
+           SYMBOLS1(ASM)<LAB>                                 :(RETURN)
*
* ENTER VALUE AS GLOBAL VARIABLE IN PHASE1. CAN BE USED BY
* '(EXPRESSION)' AS PARAMETER.
*
EQU__    NE(ASM_PHASE, 1)                                     :S(RETURN)
         $LAB = P1                                             :(RETURN)
*
* FOR DATA DEFINITION, WE USE POKE AND THEN PEEK BYTES BACK TO ADD
* TO THE DINIT STRING. THIS IS DONE TO TAKE CARE OF ENDIAN ISSUES
* WITH DATA VALUES. EG. POKE_S WILL DEPOSIT THE BYTES IN EITHER
* BIG OR LITTLE ENDIAN, DEPENDING ON THE ARCHITURE. PEEK WITH THEN
* RETRIEVE THE BYTES IN THE CORRECT ORDER FOR THAT MACHINE. WHEN THE
* DSS BLOCK IS POPULATED, DINIT WILL BE READ SIMPLY AS A STREAM OF
* BYTES, WHICH WILL BE TRANSFERRED INTO MEMORY LINEARLY.
*
* FROM NASM - DB/DW/DD/DQ
* DS IS DEFINE STRING
*
* ENTER VALUES INTO DSS
*
DB__     NE(ASM_PHASE, 1)                                     :S(RETURN)
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         DINIT(ASM) = INTEGER(P1) DINIT(ASM) CHAR(P1)          :(RETURN)
*
DW__     NE(ASM_PHASE, 1)                                     :S(RETURN)
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         POKE_S(ASM_P, P1)
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 0))
+                                CHAR(PEEK_C(ASM_P + 1))       :(RETURN)
*
DD__     NE(ASM_PHASE, 1)                                     :S(RETURN)
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         (INTEGER(P1) POKE_I(ASM_P, P1), POKE_F(ASM_P, P1))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 0))
+                                CHAR(PEEK_C(ASM_P + 1))
+                                CHAR(PEEK_C(ASM_P + 2))
+                                CHAR(PEEK_C(ASM_P + 3))       :(RETURN)
*
DQ__     NE(ASM_PHASE, 1)                                     :S(RETURN)
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         (INTEGER(P1) POKE_P(ASM_P, P1), POKE_D(ASM_P, P1))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 0))
+                                CHAR(PEEK_C(ASM_P + 1))
+                                CHAR(PEEK_C(ASM_P + 2))
+                                CHAR(PEEK_C(ASM_P + 3))
+                                CHAR(PEEK_C(ASM_P + 4))
+                                CHAR(PEEK_C(ASM_P + 5))
+                                CHAR(PEEK_C(ASM_P + 6))
+                                CHAR(PEEK_C(ASM_P + 7))       :(RETURN)
*
* DP IS DEFINE POINTER - ADD TO DPREFS TABLE TO BE RESOLVED (FIXED)
* FROM SYMBOLS1 ON COMPLETION.
*
DP__     SYMBOL = NE(ASM_PHASE, 1)                            :S(RETURN)
         SYMBOL =
         OP1 = TRIM(OP1)
         TERMINAL = DIFFER(ASM_DEBUG)
+           'ADDING DP REF ' OP1 ' ' SIZE(DINIT(ASM))
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         DPREFS(ASM)<OP1> = LINK(SIZE(DINIT(ASM)), DPREFS(ASM)<OP1>)
         DINIT(ASM) = DINIT(ASM) DUPL(' ', 8)                  :(RETURN)
*
* DA IS DEFINE ADDRESS - ADD TO DAREFS TABLE TO BE RESOLVED FROM
* ENTRIES ON COMPLETION.
*
DA__     SYMBOL = NE(ASM_PHASE, 1)                            :S(RETURN)
         TERMINAL = DIFFER(ASM_DEBUG) 'ADDING DA REF '
+           SYMBOL ' DSS OFFSET ' SIZE(DINIT(ASM))
       DAREFS(ASM)<SYMBOL> = LINK(SIZE(DINIT(ASM)), DAREFS(ASM)<SYMBOL>)
         SYMBOL =
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         DINIT(ASM) = DINIT(ASM) DUPL(' ', 8)                  :(RETURN)
*
DS__     NE(ASM_PHASE, 1)                                     :S(RETURN)
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         DINIT(ASM) = DINIT(ASM) P1                            :(RETURN)
*
* ALIGN BSS DATA ITEM TO ITS NATURAL SIZE. THIS IS NEEDED ON SOME
* ARCHITECTURES. IT MAY GREATLY INCREASE PERFORMANCE ON OTHERS. WE
* ONLY DO THIS FOR BSS ITEMS, AND NOT FOR DSS. FOR DSS, EITHER ORDER
* THE DECLARATIONS, OR PAD MANUALLY.
*
* IF IT BECOMES IMPORTANT FOR DSS, WE CAN INTRODUCE AN ALIGN OP THAT
* CAN DO IT (ALIGN 1,2,4,8). FIXME - AGAIN, DON'T OVER-IMPLEMENT UNTIL
* IT IS ACTUALLY NEEDED.
*
ALIGN_BSS
         N = REMDR(SZBSS(ASM), A)
         EQ(N)                                                :S(RETURN)
         SZBSS(ASM) = SZBSS(ASM) + A - N                       :(RETURN)
*
* COMMON N - IF LAB IS NOT DEFINED, DEFINE IT IN BSS WITH LENGTH
* N. MAKE IT EXPORT. IF SYMBOL DOES EXIST, IGNORE, WE ARE JUST LINKING
* TO THE SAME THING AGAIN.
*
* WITHIN COMMON, VARIABLES HAVE OFFSETS FROM THE COMMON BASE. USE
* DEFINE TO CREATE THESE.
*
COMMON__ NE(ASM_PHASE, 1)                                     :S(RETURN)
         IDENT(LAB)                                           :S(RETURN)
         DIFFER(SYMBOLS1(ASM)<LAB>)                           :S(RETURN)
         ALIGN_BSS(16)
         BSS(ASM)<LAB> = 
         BSS(ASM)<LAB> = SZBSS(ASM)
         SZBSS(ASM) = SZBSS(ASM) + P1
         SYMBOL = LAB                                        :(EXPORT__)
*
* FROM NASM: RESB/RESW/RESD/RESQ (ADDITIONALLY, RES) TO RESERVE SPACE
* IN BSS.
*
RESB__   RES(P1, 1)                                            :(RETURN)
RESW__   RES(P1, 2)                                            :(RETURN)
RESD__   RES(P1, 4)                                            :(RETURN)
RESQ__   RES(P1, 8)                                            :(RETURN)
RES      NE(ASM_PHASE, 1)                                     :S(RETURN)
         P1 = IDENT(P1) 1
         P2 = IDENT(P2) 1
         ALIGN_BSS(P2)
         BSS(ASM)<LAB> = DIFFER(LAB) SZBSS(ASM)
         SZBSS(ASM) = SZBSS(ASM) + (P1 * P2)                   :(RETURN)
*
* PARSE PARAMETER. THE PARAMETER MAY BE %REGISTER (EG. %R0, %V1, %F2)
* %R0-2, %V0-2 AND %F0-5 ARE ALWAYS AVAILABLE. %R3, %V3, %F6-7 MAY
* BE AVAILABLE. %FP IS THE FRAME POINTER (IF ONE AVAILABLE).
*
* 'STRING' OR "STRING". 1234, -1234, +1234 (INTEGER), OR REAL.
*
* SYMBOL (A SYMBOL OR LABEL NAME). IF THIS CAN BE RESOLVED FROM
* THE SYMBOLS1 TABLE IT WILL BE RETURNED AS A SIMPLE NUMBER. HOWEVER,
* THIS MAY BE A LOCAL LABEL THAT REQUIRES PATCHING.
*
* (EXPRESSION). THE EXPRESSION IS RUN THROUGH EVAL(). IT MAY REFERENCE
* EQU GENERATED SYMBOLS, OR ANY VARIABLES IN THE SNOBOL4 ENVIRONMENT.
*
ASM_PARM ASM_PARM = ASM_PEMPTY
         IDENT(X)                                             :S(RETURN)
         X FENCE '%' REM . X                                   :S(ASREG)
         X FENCE ('0x' | '0X')  REM . X                        :S(ASHEX)
         X FENCE ANY('"' "'" '(')                              :S(ASTRG)
         &ERRLIMIT = 1
*
* SIMPLE INTEGER OR REAL VALUE
*
         ASM_PARM = +X                                        :S(RETURN)
*
* VALUE FROM SYMBOLS1
*
         ASM_PARM = VDIFFER(SYMBOLS1(ASM)<X>)                 :S(RETURN)
*
* SYMBOLS1 SYMBOL + OR - OFFSET
*
         X BREAK('+-') . X (ANY('+-') REM) . OFFSET            :F(ASSYM)
         X = TRIM(X)
         OFFSET FENCE ANY('+-') . SIGN REM . S
         S = TRIMB(S)
         T = ASM_PARM(S)
         S = INTEGER(T) EVAL(SIGN T)                         :F(FRETURN)
         ASM_PARM = SYMBOLS1(ASM)<X> + T                       :(RETURN)
*
* NOT IN SYMBOLS1, THIS SYMBOL REQUIRES PATCHING DURING THE LINK
* PROCESS
*
ASSYM    ASM_PARM = ASM_PSYMBOL
         SYMBOL = X                                            :(RETURN)
*
* PARAMETER IS A STRING DELIMITED BY SINGLE OR DOUBLE QUOTES. MAY
* ALSO BE '(EXPRESSION)' WHICH WILL ALSO BE EVAL'D AND GIVES A
* WAY TO GET SNOBOL ENVIRONMENT EASILY INTO THE ASSEMBLY.
*
ASTRG    ASM_PARM = EVAL(X)                         :S(RETURN)F(FRETURN)
*
* PARAMETER IS A REGISTER. SEE IF ITS CACHED. IF NOT, EVALUATE THE
* JIT PROCEDURE TO DETERMINE THE REGISTER NUMBER. MAY YIELD -1, WHICH
* WOULD MEANS THE REGISTER DOESN'T EXIST. 'USES' MUST BE USED TO
* ELIMINATE THAT CASE.
*
ASREG    ASM_PARM = VDIFFER(AS_REGS<X>)                       :S(RETURN)
         FUNCTION(X '_')                                     :F(FRETURN)
         AS_REGS<X> = ASM_PARM = APPLY(X '_',)                :S(RETURN)
*
* 0XHEX. 0xHEX.
*
ASHEX    ASM_PARM = +HI(X)                                     :(RETURN)
*
* THE DRIVER ASM() FUNCTION. PHASE1 EXTRACTS D?, RES?, EXTERN,
* EXPORT, DEFINE, AND OTHER NEEDED PHASE1 INFORMATION. THEN, THE
* BSS AND DSS SECTIONS ARE CREATED. PHASE2 THEN GENERATES THE CODE.
* LINK RESOLVES INTERNAL BRANCH TARGETS. EMIT ACTUALLY GENERATES THE
* MACHINE CODE. DA THEN FIXES UP DA (ADDRESS TO CODE OBJECTS), AND
* FINAL CODE EXPORTS.
*
ASM      SRC(ASM) = SRC
         JIT_SET_STATE(JIT(ASM))
         ASM_PHASE(1)                                        :F(FRETURN)
         ASM_BSS()                                           :F(FRETURN)
         ASM_DSS()                                           :F(FRETURN)
         ASM_PHASE(2)                                        :F(FRETURN)
         ASM_LINK()                                          :F(FRETURN)
         ASM_EMIT()                                          :F(FRETURN)
         ASM_DA()                                            :F(FRETURN)
*
* CLEAN UP ASM_TYPE STRUCTURE. KEEP JIT, OBJ, EXPORTS, DSSBASE, BSSBASE
*
         SYMBOLS1(ASM) =
         SYMBOLS(ASM) =
         REFERENCES(ASM) =
         DSS(ASM) =
         BSS(ASM) =
         SZBSS(ASM) =
         DINIT(ASM) =
         ENTRIES(ASM) =
         SRC(ASM) =
         DAREFS(ASM) =
         DPREFS(ASM) =
                                                               :(RETURN)
*
* ENTRIES ADJUST. FIXUP DA REFERENCES (JUMP TABLES, CODE REFERENCES
* IN DSS)
*
ASM_DA   TERMINAL = DIFFER(ASM_DEBUG) '*** DA ***'
         A = KEYST(ENTRIES(ASM))
         I = 1
ASM_L_13 ENTRIES(ASM)<A<I>> = JIT_ADDRESS(ENTRIES(ASM)<A<I>>)
+                                                             :F(RETURN)
         EXPORTS(ASM)<A<I>> = DIFFER(EXPORTS(ASM)<A<I>>)
+           ENTRIES(ASM)<A<I>>
         P = DAREFS(ASM)<A<I>>
ASM_L_16 IDENT(P)                                           :S(ASM_L_15)
         TERMINAL = DIFFER(ASM_DEBUG)
+           'DA ' VALUE(P) ' TO ' ENTRIES(ASM)<A<I>>
         POKE_P(DSSBASE(ASM) + VALUE(P), ENTRIES(ASM)<A<I>>)
         P = NEXT(P)                                         :(ASM_L_16)
ASM_L_15 I = I + 1                                           :(ASM_L_13)
*
* ASM_EMIT: PRODUCE OBJECT CODE
*
ASM_EMIT TERMINAL = DIFFER(ASM_DEBUG) '*** EMIT ***'
         OBJ(ASM) = JIT_EMIT()                                 :(RETURN)
*
* ASM_DSS: ALLOCATE AND INITIALIZE DSS SECTION
*
ASM_DSS  TERMINAL = DIFFER(ASM_DEBUG) '*** DSS ALLOCATE ***'
         DSSBASE(ASM) = MALLOC(SIZE(VDIFFER(DINIT(ASM))))
         S = DINIT(ASM)
         I = 0
ASM_L_11 POKE_C(DSSBASE(ASM) + I, ORD(S))                   :F(ASM_L_12)
         S = SUBSTR(S, 2)
         I = I + 1                                           :(ASM_L_11)
ASM_L_12 A = KEYST(DSS(ASM))                                 :F(ASM_DS1)
         I = 1
ASM_L_9  SYMBOLS1(ASM)<A<I>> = DSS(ASM)<A<I>> + DSSBASE(ASM)
+                                                            :F(ASM_DS1)
         EXPORTS(ASM)<A<I>> = DIFFER(EXPORTS(ASM)<A<I>>)
+           SYMBOLS1(ASM)<A<I>>
*
         TERMINAL = DIFFER(ASM_DEBUG)
+           'PHASE 1 DSS SYMBOL ' A<I> ' = ' IH(SYMBOLS1(ASM)<A<I>>)
*
         I = I + 1                                            :(ASM_L_9)
*
* PATCH DSS SECTION POINTERS TO OTHER DSS (OR BSS) VARIABLES.
ASM_DS1  A = KEYST(DPREFS(ASM))                               :F(RETURN)
         I = 1
ASM_DS4  P = DPREFS(ASM)<A<I>>                                :F(RETURN)
ASM_DS2  IDENT(P)                                            :S(ASM_DS3)
         POKE_P(DSSBASE(ASM) + VALUE(P), SYMBOLS1(ASM)<A<I>>)
         P = NEXT(P)                                          :(ASM_DS2)
ASM_DS3  I = I + 1                                            :(ASM_DS4)
*
*
* ALLOCATE BSS SECTION
*
ASM_BSS  TERMINAL = DIFFER(ASM_DEBUG) '*** BSS ALLOCATE ***'
         BSSBASE(ASM) = NE(SZBSS(ASM)) MALLOC(SZBSS(ASM))
         A = KEYST(BSS(ASM))
         I = 1
ASM_L_7  SYMBOLS1(ASM)<A<I>> = BSS(ASM)<A<I>> + BSSBASE(ASM)  :F(RETURN)
         EXPORTS(ASM)<A<I>> = DIFFER(EXPORTS(ASM)<A<I>>)
+           SYMBOLS1(ASM)<A<I>>
*
         TERMINAL = DIFFER(ASM_DEBUG)
+           'PHASE 1 BSS SYMBOL ' A<I> ' = ' IH(SYMBOLS1(ASM)<A<I>>)
*
         I = I + 1                                            :(ASM_L_7)
*
* ASM PHASE 1 OR 2.
*
* INTERPOLATE A FILE OR A VARIABLE. IF ITS A VARIABLE, ADD A NEWLINE
* FOR CONVENIENCE.
*
ASM_INTERPOLATE
         TERMINAL = DIFFER(ASM_DEBUG) 'INTERPOLATE ' P1
         IDENT(P1)                                            :S(RETURN)
         S = (
+              (?(P1 ? FENCE ANY("'" '"')) READFILE(EVAL(P1))),
+              ($P1 CHARS_NL)
+            )
         SRC POS(BL) LEN(0) = S                                 :(ASM_2)
*
ASM_PHASE
         TERMINAL = DIFFER(ASM_DEBUG) '*** PHASE ' ASM_PHASE '***'
         SRC = SRC(ASM)
         BL = 0
         EL = 0
*
* SPEED OPTIMIZATION. DON'T REMOVE EACH LINE FROM SRC AS IT IS
* PROCESSED. ALSO, DON'T DO EVER LONGER 'TAB()' (OR POS) TO EACH LINE.
* INSTEAD, PROCESS EACH LINE, RECORDING THE BEGINNING OF THE NEXT
* LINE. AFTER WE ARE 4096 CHARACTERS (OR MORE) IN THE STRING,
* REMOVE THE LEADING BLOCK. THIS REDUCES GC, AND PERFORMS ABOUT
* TWICE AS WELL AS THE NAIVE CODE. TESTED WITH 10,000 LINES OF
* ASM INPUT.
*
*        SRC FENCE BREAK(CHARS_NL) . LINE CHARS_NL =          :F(RETURN)
ASM_2    SRC FENCE TAB(BL) BREAK(CHARS_NL) CHARS_NL @EL       :F(RETURN)
         LINE = SUBSTR(SRC, BL + 1, EL - BL)
         BL = EL
         LT(BL, 4096)                                         :S(ASM_X1)
         SRC FENCE LEN(BL - 1) =
         BL = 0
*
ASM_X1   TERMINAL = DIFFER(ASM_DEBUG) LINE
*
         LINE FENCE NSPAN(' ' CHARS_TAB) ANY(';*')             :S(ASM_2)
         LINE = TRIM(LINE)
         IDENT(LINE)                                           :S(ASM_2)
         ELINE = LINE
         LINE FENCE BREAKQ(';') . LINE
         LINE = TRIM(LINE) ',,,'
         LAB = OP = P1 = P2 = P3 = SYMBOL =
         LINE ASM_PAT                                          :S(ASM_4)
ASM_3    TERMINAL = 'ASM: ERROR IN: ' ELINE                   :(FRETURN)
ASM_4    IDENT(OP, 'END')                                     :S(RETURN)
         IDENT(OP, 'end')                                     :S(RETURN)
*
* INTERPOLATE A FILE OR STRING INTO THE ASSEMBLY
* INCLUDE 'NAME', OR INCLUDE SYM
*
         IDENT(OP, 'INCLUDE')                        :S(ASM_INTERPOLATE)
         IDENT(OP, 'include')                        :S(ASM_INTERPOLATE)
         OP = FUNCTION(OP '__') OP '__'                        :S(ASM_5)
         OP = EQ(ASM_PHASE, 1)                                 :S(ASM_2)
         OP = (IDENT(OP), FUNCTION('JIT_' OP) 'JIT_' OP)       :F(ASM_3)
         TERMINAL = VDIFFER(SYMBOLS(ASM)<LAB>) 'REDEFINED'     :S(ASM_3)
         SYMBOLS(ASM)<LAB> = DIFFER(LAB) JIT_LABEL()
         IDENT(OP)                                             :S(ASM_2)
ASM_5    OP1 = P1
         P1 = ASM_PARM(P1)                                     :F(ASM_3)
         P1 = IDENT(P1, ASM_PSYMBOL) 0
         P2 = ASM_PARM(P2)                                     :F(ASM_3)
         P2 = IDENT(P2, ASM_PSYMBOL) 0
         P3 = ASM_PARM(P3)                                     :F(ASM_3)
         P3 = IDENT(P3, ASM_PSYMBOL) ASM_PEMPTY
         &ERRLIMIT = 1
         DIFFER(P1, ASM_PEMPTY)                                :S(ASM_6)
         R = APPLY(OP,)                                :S(ASM_9)F(ASM_3)
ASM_6    DIFFER(P2, ASM_PEMPTY)                                :S(ASM_7)
         R = APPLY(OP, P1,)                            :S(ASM_9)F(ASM_3)
ASM_7    DIFFER(P3, ASM_PEMPTY)                                :S(ASM_8)
         R = APPLY(OP, P1, P2,)                        :S(ASM_9)F(ASM_3)
ASM_8    R = APPLY(OP, P1, P2, P3)                     :S(ASM_9)F(ASM_3)
ASM_9
* JIT_ARG...
         IDENT(OP, 'JIT_ARG')                                 :S(ASM_X3)
         IDENT(OP, 'jit_arg')                                 :F(ASM_X2)
ASM_X3   SYMBOLS1(ASM)<LAB> = R
         SYMBOLS(ASM)<LAB> =                                   :S(ASM_2)
ASM_X2   IDENT(SYMBOL)                                         :S(ASM_2)
         EQ(ASM_PHASE, 1)                                      :S(ASM_2)
         TERMINAL = IDENT(R) 'INSTRUCTION NOT PATCHABLE'       :S(ASM_3)
*
         TERMINAL =
+           DIFFER(ASM_DEBUG) 'REFERENCE: AT : ' IH(R) ' TO: ' SYMBOL
*
         REFERENCES(ASM)<SYMBOL> = LINK(R, REFERENCES(ASM)<SYMBOL>)
+                                                               :(ASM_2)
*
ASM_LINK TERMINAL = DIFFER(ASM_DEBUG) '*** LINK ***'
         SYMBOLS = SYMBOLS(ASM)
         A = KEYST(REFERENCES(ASM))                           :F(RETURN)
         I = 1
ASM_L_2  P = REFERENCES(ASM)<A<I>>                           :F(ASM_L_5)
         R = SYMBOLS<A<I>>
         IDENT(R)                                            :S(ASM_L_4)
*
         TERMINAL = DIFFER(ASM_DEBUG)
+           'ASM_LINK: RESOLVING ' A<I> ' TO ' IH(R)
*
         REFERENCES(ASM)<A<I>> =
ASM_L_3  IDENT(P)                                            :S(ASM_L_4)
*
         TERMINAL =
+      DIFFER(ASM_DEBUG) 'ASM_LINK: PATCHING ' IH(VALUE(P)) ' TO ' IH(R)
         JIT_PATCH_AT(VALUE(P), R)
         P = NEXT(P)                                          :(ASM_L_3)
ASM_L_4  I = I + 1                                            :(ASM_L_2)
ASM_L_5  A = KEYST(REFERENCES(ASM))                           :F(RETURN)
         I = 1
ASM_L_U  TERMINAL = 'UNRESOLVED: ' A<I>                      :F(FRETURN)
         I = I + 1                                            :(ASM_L_U)
*
ASM_CREATE
         ASM_CREATE = ASM_TYPE()
         SYMBOLS1(ASM_CREATE) =
+           (DIFFER(SYMBOLS1) COPYT(SYMBOLS1), TABLE())
         EXPORTS(ASM_CREATE) = TABLE()
         SYMBOLS(ASM_CREATE) = TABLE()
         ENTRIES(ASM_CREATE) = TABLE()
         DAREFS(ASM_CREATE) = TABLE()
         DPREFS(ASM_CREATE) = TABLE()
         REFERENCES(ASM_CREATE) = TABLE()
         DSS(ASM_CREATE) = TABLE()
         BSS(ASM_CREATE) = TABLE()
         SZBSS(ASM_CREATE) = 0
         DINIT(ASM_CREATE) =
         DSSBASE(ASM_CREATE) = 0
         BSSBASE(ASM_CREATE) = 0
         JIT(ASM_CREATE) = JIT_NEW_STATE()                     :(RETURN)
*
ASM_DESTROY
         FREE(DSSBASE(ASM))
         FREE(BSSBASE(ASM))
         JIT_SET_STATE(JIT(ASM))
         JIT_DESTROY_STATE()                                   :(RETURN)
*
END_ASM
