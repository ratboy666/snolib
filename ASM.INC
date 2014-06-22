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
* A = ASM_CREATE()
* ASM(A, SRC) :F(ERROR)
* S = ASM_LINK(A)
* IF S IS 'INCOMPLETE', THEN MORE SYMBOLS NEED RESOLVING
* IF IDENT(S), LINK IS COMPLETE.
* ASM_LINK(A,T) WILL LINK A WITH SYMBOL TABEL T. T IS A TABLE OF NAMES,
* EACH OF WHICH IS A VALUE (32 OR 64 BIT).
* ASM_DESTROY(A)
*
* NOTE THAT THIS IS A PART OF A "MACHINE CODE LOADER", AND ENTRY
* AND USAGE ISSUES ARE MEANT TO BE COVERED ELSEWHERE. THIS MODULE
* HANDLES INTEPRETING THE FORMAT, AND RESOLVING (MOST) SYMBOLS,
* PREPARING THE OBJECT FOR EVENTUAL EXECUTION.
*
* JIT(A) WILL RETRIEVE THE JIT STATE, WHICH CAN BE USED WITH JIT
* FUNCTIONS FOR DEBUG, AND TO EMIT CODE WHICH CAN BE PASSED TO
* OTHER FUNCTIONS LIKE FFI TO PREPARE FOR FINAL EXECUTION.
*
* WE ALSO ALLOW DATA DEFINITION AND RESERVATIONS. THESE WILL BE
* LOCATED ON ASM_LINK, AND RESOLVED. D_ AND RES_ TRIGGERS THIS
* NOTE THAT THE RES_ DATA IS BSS, AND D_ IS DSS. THESE HAVE INDEPENDENT
* SYMBOL TABLES. BSS DATA IS SIMPLY MALLOC'D AND THE SYMBOL TABLE
* (BSS) HAS EACH SYMBOL VALUE ADDED TO. SAME FOR DSS, BUT DINIT DATA
* IS COPIED TO THE MALLOC SPACE (FOR EACH BYTE). ONCE LINKED, WE CANNOT
* RELOCATE THE DSS OR BSS SECTION (OR, FOR THAT MATTER, THE CODE).
* TO RELOCATE WE WOULD NEED TO DESTROY AND RE-CREATE THE CODE.
* (RELOAD).
*
* CE: .MSNOBOL4;
*
         DATA('ASM_TYPE(JIT,SYMBOLS,REFERENCES,DSS,BSS,SZBSS,DINIT,'
+                      'DSSBASE,BSSBASE)')
*
         DEFINE('ASM_CREATE()')
         DEFINE('ASM_DESTROY(ASM)')
         DEFINE('ASM_LINK(ASM,SYMBOLS)A,I,P,R,S')
         DEFINE('ASM(ASM,SRC)LINE,ELINE,R,SYMBOL,LAB,OP,P1,P2,P3')
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
         DEFINE('SEXEC(P1)')
         DEFINE('CEXTERN(P1)')
         DEFINE('EQU(P1)')
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
* STORAGE USED FOR DATA CONVERSIONS
*
         ASM_P = MALLOC(128)
*
* NOT USED AS TABLES, THESE ARE SIMPLY UNIQUE NON-STRINGS USED TO
* IDENTIFY EMPTY AND SYMBOL REFERENCE PARAMETERS
* 
         ASM_PEMPTY = TABLE(1, 1)
         ASM_PSYMBOL = TABLE(1, 1)                            :(END_ASM)
*
* STANDARD EXTRA OPERATIONS FOR ASM CODE. OF COURSE, ANY APPLICATION
* SPECIFICS CAN BE DEFINED IN THE USING CODE AND ARE FREELY AVAILABLE
* THIS ALLOWS THE CODE GENERATOR O BE EASILY TAILORED FOR SPECIFIC
* NEEDS. FOR EXAMPLE, MACROS COULD BE DEFINED. ALL THREE OF THE
* PARAMETERS CAN BE STRINGS OR NUMBERS. THE LABEL IS AVAILABLE AS LAB.
*
* BE WARNED THOUGH, THAT THIS IS NOT ONLY AN "ASSEMBLER" FORMAT, IT IS
* ALSO MEANT TO BE USED AS THE RELOCATING LOADER. SO, KEEP AN EYE
* ON PERFORMANCE!
*
SEXEC    SEXEC = EVAL(P1)                           :S(RETURN)F(FRETURN)
*
CEXTERN  SYMBOLS(ASM)<LAB> = DLSYM(0, P1)                      :(RETURN)
*
EQU      $LAB = P1                                             :(RETURN)
*
DB       DINIT = INTEGER(P1) DINIT CHAR(P1)                    :(RETURN)
*
DW       POKE_S(ASM_P, P1)
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 0))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 1))                 :(RETURN)
*
DD       (INTEGER(P1) POKE_I(ASM_P, P1), POKE_F(ASM_P, P1))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 0))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 1))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 2))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 3))                 :(RETURN)
*
DQ       (INTEGER(P1) POKE_P(ASM_P, P1), POKE_D(ASM_P, P1))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 0))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 1))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 2))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 3))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 4))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 5))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 6))
         DINIT = DINIT CHAR(PEEK_C(ASM_P + 7))                 :(RETURN)
*
DS       DINIT = DINIT P1                                      :(RETURN)
*
ALIGN_BSS
         N = REMDR(SZBSS(ASM), A)
         EQ(N)                                                :S(RETURN)
         SZBSS(ASM) = SZBSS(ASM) + A - N                       :(RETURN)
*
RESB     RES(P1, 1)                                            :(RETURN)
RESW     RES(P1, 2)                                            :(RETURN)
RESD     RES(P1, 4)                                            :(RETURN)
RESQ     RES(P1, 8)                                            :(RETURN)
RES      P1 = IDENT(P1) 1
         P2 = IDENT(P2) 1
         ALIGN_BSS(P2)
         BSS(ASM)<LAB> = DIFFER(LAB) SZBSS(ASM)
         SZBSS(ASM) = SZBSS(ASM) + (P1 * P2)                   :(RETURN)
*
ASM_PARM ASM_PARM = ASM_PEMPTY
         IDENT(X)                                             :S(RETURN)
         X FENCE '.' REM . X                                   :S(ASREG)
         X FENCE ANY('"' "'" '(')                              :S(ASTRG)
         ASM_PARM = +X                                        :S(RETURN)
         ASM_PARM = ASM_PSYMBOL
         SYMBOL = X                                            :(RETURN)
ASTRG    ASM_PARM = EVAL(X)                         :S(RETURN)F(FRETURN)
ASREG    FUNCTION(X '_')                                     :F(FRETURN)
         ASM_PARM = APPLY(X '_',)                              :(RETURN)
*
ASM      JIT_SET_STATE(JIT(ASM))
ASM_2    SRC BREAK(CHARS_NL) . LINE CHARS_NL =                :F(RETURN)
*
*        TERMINAL = LINE
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
         OP = FUNCTION('JIT_' OP) 'JIT_' OP                    :F(ASM_3)
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
         REFERENCES(ASM)<SYMBOL> =
+           DIFFER(SYMBOL) DIFFER(R) LINK(R, REFERENCES(ASM)<SYMBOL>)
+                                                               :(ASM_2)
*
ASM_LINK IDENT(SYMBOLS)                                      :S(ASM_L_6)
*
* PROGRAM RELOCATIONS FROM SYMBOL TABLE
*
         A = KEYST(REFERENCES(ASM))                           :F(RETURN)
         I = 1
ASM_L_2  P = REFERENCES(ASM)<A<I>>                           :F(ASM_L_5)
         R = SYMBOLS<A<I>>
         IDENT(R)                                            :S(ASM_L_4)
         REFERENCES(ASM)<A<I>> =
ASM_L_3  IDENT(P)                                            :S(ASM_L_4)
         JIT_PATCH_AT(VALUE(P), R)
         P = NEXT(P)                                          :(ASM_L_3)
ASM_L_4  I = I + 1                                            :(ASM_L_2)
ASM_L_5  A = KEYST(REFERENCES(ASM))                           :F(RETURN)
         ASM_LINK = 'INCOMPLETE'                               :(RETURN)
*
* ALLOCATE BSS, ADJUST BSS SYMBOLS, BSS PROGRAM RELOCATIONS
*
ASM_L_6  NE(BSSBASE(ASM))                                   :S(ASM_L_13)
         BSSBASE(ASM) = NE(SZBSS(ASM)) MALLOC(SZBSS(ASM))
         A = KEYST(BSS(ASM))
         I = 1
ASM_L_7  BSS(ASM)<A<I>> = BSS(ASM)<A<I>> + BSSBASE(ASM)      :F(ASM_L_8)
         I = I + 1                                            :(ASM_L_7)
ASM_L_8  ASM_LINK(ASM, BSS(ASM))
*
* ALLOCATE DSS, COPY IN DATA, ADJUST DSS SYMBOL, DSS PROGRAM
* RELOCATIONS
*
ASM_L_13 NE(DSSBASE(ASM))                                   :S(ASM_L_14)
         DSSBASE(ASM) = MALLOC(SIZE(VDIFFER(DINIT(ASM))))
         S = DINIT(ASM)
         I = 0
ASM_L_11 POKE_C(DSSBASE(ASM) + I, ORD(S))                   :F(ASM_L_12)
         S = SUBSTR(S, 2)
         I = I + 1                                           :(ASM_L_11)
ASM_L_12 A = KEYST(DSS(ASM))                                :F(ASM_L_10)
         I = 1
ASM_L_9  DSS(ASM)<A<I>> = DSS(ASM)<A<I>> + DSSBASE(ASM)     :F(ASM_L_10)
         I = I + 1                                            :(ASM_L_9)
ASM_L_10 ASM_LINK(ASM, DSS(ASM))
*
* PROGRAM RELOCATIONS FOR LOCAL CODE LABELS
*
ASM_L_14 ASM_LINK = ASM_LINK(ASM, SYMBOLS(ASM))                :(RETURN)
*
ASM_CREATE
         ASM_CREATE = ASM_TYPE()
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
