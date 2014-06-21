-MODULE ASM
-INCLUDE 'JIT.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'KEYST.INC'
-INCLUDE 'BREAKQ.INC'
-INCLUDE 'NSPAN.INC'
-INCLUDE 'LINK.INC'
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
* CE: .MSNOBOL4;
*
         DATA('ASM_TYPE(JIT,SYMBOLS,REFERENCES)')
*
         DEFINE('ASM_CREATE()')
         DEFINE('ASM_DESTROY(ASM)')
         DEFINE('ASM_LINK(ASM,SYMBOLS)A,I,P,R')
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
         DEFINE('SEXEC(P1)')
         DEFINE('CEXTERN(P1)')
*
         ASM_PEMPTY = TABLE()
         ASM_PSYMBOL = TABLE()                                :(END_ASM)
*
* STANDARD EXTRA OPERATIONS FOR ASM CODE. OF COURSE, ANY APPLICATION
* SPECIFICS CAN BE DEFINED IN THE USING CODE AND ARE FREELY AVAILABLE
* THIS ALLOWS THE CODE GENERATOR O BE EASILY TAILORED FOR SPECIFIC
* NEEDS. FOR EXAMPLE, MACROS COULD BE DEFINED. ALL THREE OF THE
* PARAMETERS CAN BE STRINGS, AND ALL PARAMETERS ARE AVAILABLE:
* P1, P2, P3. THE LABEL IS AVAILABLE AS LAB.
*
* BE WARNED THOUGH, THAT THIS IS NOT ONLY AN "ASSEMBLER" FORMAT, IT IS
* ALSO MEANT TO BE USED AS THE RELOCATING LOADER. SO, KEEP AN EYE
* ON PERFORMANCE!
*
SEXEC    SEXEC = EVAL(P1)                           :S(RETURN)F(FRETURN)
*
CEXTERN  SYMBOLS(ASM)<LAB> = DLSYM(0, P1)                      :(RETURN)
*
ASM_PARM ASM_PARM = ASM_PEMPTY
         IDENT(X)                                             :S(RETURN)
         X FENCE '.' REM . X                                   :S(ASREG)
         X FENCE ANY('"' "'")                                  :S(ASTRG)
         ASM_PARM = +X                                        :S(RETURN)
         ASM_PARM = ASM_PSYMBOL
         SYMBOL = X                                            :(RETURN)
ASTRG    ASM_PARM = EVAL(X)                         :S(RETURN)F(FRETURN)
ASREG    FUNCTION(X '_')                                     :F(FRETURN)
         ASM_PARM = APPLY(X '_',)                              :(RETURN)
*
ASM      JIT_SET_STATE(JIT(ASM))
ASM_2    SRC BREAK(CHARS_NL) . LINE CHARS_NL =                :F(RETURN)
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
ASM_LINK SYMBOLS = IDENT(SYMBOLS) SYMBOLS(ASM)
         A = KEYST(REFERENCES(ASM))                           :F(RETURN)
         I = 1
ASM_L_2  P = REFERENCES(ASM)<A<I>>                           :F(ASM_L_5)
         R = SYMBOLS(ASM)<A<I>>
         IDENT(R)                                            :S(ASM_L_4)
         REFERENCES(ASM)<A<I>> =
ASM_L_3  JIT_PATCH_AT(VALUE(P), R)
         IDENT(P)                                            :S(ASM_L_4)
         P = NEXT(P)                                          :(ASM_L_3)
ASM_L_4  I = I + 1                                            :(ASM_L_2)
ASM_L_5  A = KEYST(REFERENCES(ASM))                           :F(RETURN)
         ASM_LINK = 'INCOMPLETE'                               :(RETURN)
*
ASM_CREATE
         ASM_CREATE = ASM_TYPE()
         SYMBOLS(ASM_CREATE) = TABLE()
         REFERENCES(ASM_CREATE) = TABLE()
         JIT(ASM_CREATE) = JIT_NEW_STATE()
         JIT_SET_STATE(JIT(ASM_CREATE))                        :(RETURN)
*
ASM_DESTROY
         SYMBOLS(ASM) =
         REFERENCES(ASM) =
         JIT_SET_STATE(JIT(ASM))
         JIT_DESTROY_STATE()                                   :(RETURN)
*
END_ASM
