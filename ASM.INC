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
* A FUNCTIION IN THE ASSEMBLER, OR, WITH JIT_ PREPENDED, A JIT
* GENERATION INSTRUCTION. THE FUNCTION IS THEN CALLED WITH UP TO
* THREE PARAMETERS. EACH PARAMETER IS A STRING, A NUMBER, A SYMBOL
* REFERENCE OR A REGISTER. EACH LABEL ON A JIT_ OPCODE IS ENTERED
* INTO A LOCAL SYMBOL TABLE.
*
* ASM() WORKS IN TWO PHASES - THE FIRST PHASE CREATES SYMBOLS IN
* THE SYMBOLS1 TABLE. AFTER PHASE1, WE PREPARE THE DSS AND BSS AREAS
* (THIS COULD BE CONSIDERED PHASE1A - BUT WE ONLY COUNT SOURCE SCANS
* AS PHASES). THE SECOND PHASE ACTUALLY GENERATES CODE, USING THE
* SYMBOLS CREATED IN PHASE1. ON COMPLETIION OF PHASE2, WE RESOLVE
* INTERNAL LOCAL SYMBOLS (BRANCHES IN THE CODE -- THIS IS PHASE 2A). 
*
* A = ASM_CREATE()
* S = ASM(A, SRC) :F(ERROR)
* IF S IS 'INCOMPLETE', THEN MORE SYMBOLS NEED RESOLVING
* IF IDENT(S), LINK IS COMPLETE.
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
-PUBLIC JIT(), ASM_CREATE(), ASM_DESTROY() ASM()
*
         DATA('ASM_TYPE(JIT,SYMBOLS1,SYMBOLS,REFERENCES,DSS,BSS,SZBSS,'
+                      'DINIT,DSSBASE,BSSBASE)')
*
         DEFINE('ASM_CREATE(SYMBOLS1)')
         DEFINE('ASM_DESTROY(ASM)')
         DEFINE('ASM_LINK(ASM,SYMBOLS)A,I,P,R,S')
         DEFINE('ASM(ASM,SRC)')
         DEFINE('ASM_PHASE(SRC,ASM_PHASE)'
+               'LINE,ELINE,R,SYMBOL,LAB,OP,P1,P2,P3')
*
         ASET = &UCASE &LCASE &DIGITS '_.'
         AWHT = NSPAN(' ' CHARS_TAB)
         ASM_PAT = FENCE NSPAN(ASET) . LAB
+                  AWHT SPAN(ASET '_.') . OP
+                  AWHT ((BREAKQ(',') . P1 ',') | NULL)
+                  AWHT ((BREAKQ(',') . P2 ',') | NULL)
+                  AWHT ((BREAKQ(',') . P3 ',') | NULL)
*
         DEFINE('ASM_PARM(X)')
         DEFINE('ALIGN_BSS(A),N')
*
         DEFINE('PHASE1(P1)')
         DEFINE('PHASE2(P2)')
         DEFINE('EXTERN(P1,P2,P3)H')
         DEFINE('USES(P1)A')
         DEFINE('EQU(P1)')
         DEFINE('ADDRESS()')
*
         DEFINE('RESB(P1)')
         DEFINE('RESW(P1)')
         DEFINE('RESD(P1)')
         DEFINE('RESQ(P1)')
         DEFINE('RES(P1,P2)')
*
         DEFINE('DB(P1)')
         DEFINE('DW(P1)')
         DEFINE('DD(P1)')
         DEFINE('DQ(P1)')
         DEFINE('DS(P1)')
*
* SET TO NON-NULL TO HAVE ASM GIVE DEBUG OUTPUT
*
         ASM_DEBUG =
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
USES     NE(ASM_PHASE, 1)                                     :S(RETURN)
USES2    P1 ANY('.%') =                                        :S(USES2)
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
ADDRESS  NE(ASM_PHASE, 2)                                     :S(RETURN)
         SYMBOLS(ASM)<LAB> = JIT_INDIRECT()                    :(RETURN)
*
* PHASE1 EVALUATION ONLY. EVAL P1 DURING PHASE1.
*
PHASE1   NE(ASM_PHASE, 1)                                     :S(RETURN)
         PHASE1 = EVAL(P1)                          :S(RETURN)F(FRETURN)
*
* PHASE2 EVALUATION ONLY. EVAL P1 DURING PHASE2.
*
PHASE2   NE(ASM_PHASE, 2)                                     :S(RETURN)
         PHASE2 = EVAL(P1)                          :S(RETURN)F(FRETURN)
*
* ENTER VALUE INTO SYMBOLS1 TABLE. THERE ARE FIVE FORMS FOR THIS
* DIRECTIVE:
*
* LABEL EXTERN REAL_CONSTANT ; DEFINE LABEL AS REAL CONSTANT
* LABEL EXTERN INTEGER_CONSTANT  ; DEFINE LABEL AS INTEGER CONSTANT
* LABEL EXTERN 'NAME' ; DEFINE LABEL AS DLSYM(, 'NAME')
* LABEL EXTERN 'NAME','SO' ; 'NAME' IN 'SO'
* LABEL EXTERN 'NAME','SO',FLAGS ; IN 'SO' OPEN WITH FLAGS
*
EXTERN   NE(ASM_PHASE, 1)                                     :S(RETURN)
         SYMBOLS1(ASM)<LAB> = INTEGER(P1) +P1                 :S(RETURN)
         SYMBOLS1(ASM)<LAB> = REAL(P1) +P1                    :S(RETURN)
*
* P1 = ENTRY NAME, P2 = MODULE NAME, P3 = OPEN FLAGS
*
         P2 = IDENT(P2) 0
         P3 = IDENT(P3) 0
         H = DL_TABLE<P2>
         DIFFER(H)                                           :S(EXTERN2)
         H = IDENT(P2) DLOPEN(P2, P3)
         DL_TABLE<P2> = H
EXTERN2  SYMBOLS1(ASM)<LAB> = DLSYM(H, P1)                     :(RETURN)
*
* ENTER VALUE AS GLOBAL VARIABLE IN PHASE1. CAN BE USED BY
* '(EXPRESSION)' AS PARAMETER.
*
EQU      NE(ASM_PHASE, 1)                                     :S(RETURN)
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
DB       NE(ASM_PHASE, 1)                                     :S(RETURN)
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         DINIT(ASM) = INTEGER(P1) DINIT(ASM) CHAR(P1)          :(RETURN)
*
DW       NE(ASM_PHASE, 1)                                     :S(RETURN)
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         POKE_S(ASM_P, P1)
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 0))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 1))       :(RETURN)
*
DD       NE(ASM_PHASE, 1)                                     :S(RETURN)
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         (INTEGER(P1) POKE_I(ASM_P, P1), POKE_F(ASM_P, P1))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 0))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 1))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 2))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 3))       :(RETURN)
*
DQ       NE(ASM_PHASE, 1)                                     :S(RETURN)
         DSS(ASM)<LAB> = DIFFER(LAB) SIZE(DINIT(ASM))
         (INTEGER(P1) POKE_P(ASM_P, P1), POKE_D(ASM_P, P1))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 0))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 1))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 2))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 3))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 4))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 5))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 6))
         DINIT(ASM) = DINIT(ASM) CHAR(PEEK_C(ASM_P + 7))       :(RETURN)
*
DS       NE(ASM_PHASE, 1)                                     :S(RETURN)
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
* FROM NASM: RESB/RESW/RESD/RESQ (ADDITIONALLY, RES) TO RESERVE SPACE
* IN BSS.
*
RESB     RES(P1, 1)                                            :(RETURN)
RESW     RES(P1, 2)                                            :(RETURN)
RESD     RES(P1, 4)                                            :(RETURN)
RESQ     RES(P1, 8)                                            :(RETURN)
RES      NE(ASM_PHASE, 1)                                     :S(RETURN)
         P1 = IDENT(P1) 1
         P2 = IDENT(P2) 1
         ALIGN_BSS(P2)
         BSS(ASM)<LAB> = DIFFER(LAB) SZBSS(ASM)
         SZBSS(ASM) = SZBSS(ASM) + (P1 * P2)                   :(RETURN)
*
* PARSE PARAMETER. THE PARAMETER MAY BE .REGISTER (EG. .R0, .V1, .F2)
* .R0-2, .V0-2 AND .F0-5 ARE ALWAYS AVAILABLE. .R3, .V3, .F6-7 MAY
* BE AVAILABLE. .FP IS THE FRAME POINTER (IF ONE AVAILABLE).
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
         X FENCE ANY('.%') REM . X                             :S(ASREG)
         X FENCE ANY('"' "'" '(')                              :S(ASTRG)
         ASM_PARM = +X                                        :S(RETURN)
         IDENT(SYMBOLS1(ASM)<X>)                               :S(ASSYM)
         ASM_PARM = SYMBOLS1(ASM)<X>                           :(RETURN)
ASSYM    ASM_PARM = ASM_PSYMBOL
         SYMBOL = X                                            :(RETURN)
ASTRG    ASM_PARM = EVAL(X)                         :S(RETURN)F(FRETURN)
ASREG    FUNCTION(X '_')                                     :F(FRETURN)
         ASM_PARM = APPLY(X '_',)                              :(RETURN)
*
ASM      JIT_SET_STATE(JIT(ASM))
*
         TERMINAL = DIFFER(ASM_DEBUG) '*** PHASE 1 ***'
         ASM_PHASE(SRC, 1)                                   :F(FRETURN)
*
* ALLOCATE BSS, TRANSFER ADJUSTED BSS SYMBOLS TO SYMBOLS1
*
         BSSBASE(ASM) = NE(SZBSS(ASM)) MALLOC(SZBSS(ASM))
         A = KEYST(BSS(ASM))
         I = 1
ASM_L_7  SYMBOLS1(ASM)<A<I>> = BSS(ASM)<A<I>> + BSSBASE(ASM) :F(ASM_L_8)
*
         TERMINAL = DIFFER(ASM_DEBUG)
+           'PHASE 1 BSS SYMBOL ' A<I> ' = ' IH(SYMBOLS1(ASM)<A<I>>)
*
         I = I + 1                                            :(ASM_L_7)
*
* ALLOCATE DSS, COPY IN DATA, ADJUST DSS SYMBOLS TO SYMBOLS1
*
ASM_L_8  DSSBASE(ASM) = MALLOC(SIZE(VDIFFER(DINIT(ASM))))
         S = DINIT(ASM)
         I = 0
ASM_L_11 POKE_C(DSSBASE(ASM) + I, ORD(S))                   :F(ASM_L_12)
         S = SUBSTR(S, 2)
         I = I + 1                                           :(ASM_L_11)
ASM_L_12 A = KEYST(DSS(ASM))                                :F(ASM_L_10)
         I = 1
ASM_L_9  SYMBOLS1(ASM)<A<I>> = DSS(ASM)<A<I>> + DSSBASE(ASM)
+                                                           :F(ASM_L_10)
*
         TERMINAL = DIFFER(ASM_DEBUG)
+           'PHASE 1 DSS SYMBOL ' A<I> ' = ' IH(SYMBOLS1(ASM)<A<I>>)
*
         I = I + 1                                            :(ASM_L_9)
ASM_L_10
*
* ALL NEEDED PHASE 1 SYMBOLS ARE IN SYMBOLS1, RUN PHASE 2 WHICH ACTUALLY
* GENERATES CODE.
*
         TERMINAL = DIFFER(ASM_DEBUG) '*** PHASE 2 ***'
         ASM_PHASE(SRC, 2)                                   :F(FRETURN)
*
         TERMINAL = DIFFER(ASM_DEBUG) '*** LINK ***'
         ASM = ASM_LINK(ASM)                                   :(RETURN)
*
* ASM PHASE 1 OR 2.
*
ASM_PHASE
ASM_2    SRC BREAK(CHARS_NL) . LINE CHARS_NL =                :F(RETURN)
*
         TERMINAL = DIFFER(ASM_DEBUG) LINE
*
         LINE FENCE ANY(';*')                                  :S(ASM_2)
         LINE = TRIM(LINE)
         IDENT(LINE)                                           :S(ASM_2)
         ELINE = LINE
         LINE BREAKQ(';') . LINE
         LINE = TRIM(LINE) ',,,'
         LAB = OP = P1 = P2 = P3 = SYMBOL =
         LINE ASM_PAT                                          :S(ASM_4)
ASM_3    TERMINAL = 'ASM: ERROR IN: ' ELINE                   :(FRETURN)
ASM_4    IDENT(OP, 'END')                                     :S(RETURN)
         FUNCTION(OP)                                          :S(ASM_5)
         OP = EQ(ASM_PHASE, 1)                                 :S(ASM_2)
         OP = FUNCTION('JIT_' OP) 'JIT_' OP                    :F(ASM_3)
         TERMINAL = VDIFFER(SYMBOLS(ASM)<LAB>) 'REDEFINED'     :S(ASM_3)
         SYMBOLS(ASM)<LAB> = DIFFER(LAB) JIT_LABEL()
ASM_5    P1 = ASM_PARM(P1)                                     :F(ASM_3)
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
ASM_9    IDENT(SYMBOL)                                         :S(ASM_2)
         EQ(ASM_PHASE, 1)                                      :S(ASM_2)
         TERMINAL = IDENT(R) 'INSTRUCTION NOT PATCHABLE'       :S(ASM_3)
*
         TERMINAL =
+           DIFFER(ASM_DEBUG) 'REFERENCE: AT : ' IH(R) ' TO: ' SYMBOL
*
         REFERENCES(ASM)<SYMBOL> = LINK(R, REFERENCES(ASM)<SYMBOL>)
+                                                               :(ASM_2)
*
ASM_LINK SYMBOLS = IDENT(SYMBOLS) SYMBOLS(ASM)
*
* PROGRAM RELOCATIONS FROM GIVEN SYMBOL TABLE
*
* NOTE - THESE ARE LOCAL ONLY (TYPICALLY). RESOLUTION BETWEEN
* MODULES SHOULD BE VIA SHARED TABLES. OR EXTERN STATEMENTS.
* THESE ISSUES WILL BE DEALT WITH AS THE CODE GENERATOR REQUIREMENTS
* HARDEN -- THIS IS "JUST IN TIME" DEVELOPMENT. WE REALLY DON'T
* WANT TO OVER-DESIGN THIS STUFF. WORST CASE, WE MAY NEED TO
* "REASSEMBLE" PARTS (FIXME).
*
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
         ASM_LINK = 'INCOMPLETE'                               :(RETURN)
*
ASM_CREATE
         ASM_CREATE = ASM_TYPE()
         SYMBOLS1(ASM_CREATE) =
+           (DIFFER(SYMBOLS1) COPYT(SYMBOLS1), TABLE())
         SYMBOLS(ASM_CREATE) = TABLE()
         REFERENCES(ASM_CREATE) = TABLE()
         DSS(ASM_CREATE) = TABLE()
         BSS(ASM_CREATE) = TABLE()
         SZBSS(ASM_CREATE) = 0
         DINIT(ASM_CREATE) =
         DSSBASE(ASM_CREATE) = 0
         BSSBASE(ASM_CREATE) = 0
         JIT(ASM_CREATE) = JIT_NEW_STATE()
         JIT_SET_STATE(JIT(ASM_CREATE))                        :(RETURN)
*
ASM_DESTROY
         FREE(DSSBASE(ASM))
         FREE(BSSBASE(ASM))
         JIT_SET_STATE(JIT(ASM))
         JIT_DESTROY_STATE()                                   :(RETURN)
*
END_ASM
