#!/usr/bin/bash
         exec "snobol4" "-r" "-s" "$0" "$@" 
-TITLE ASM
-INCLUDE 'FFI.INC'
-INCLUDE 'JIT.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'KEYST.INC'
-INCLUDE 'FASBOL.INC'
-INCLUDE 'LINK.INC'
-STITL ASM
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
* THE BASIC IDEA IS THAT EACH ASSEMBLER LINE IS EXAMINED, AND LABEL,
* OPCODE AND UP TO THREE PARAMETERS EXTRACTED. THE OPCODE MAY MATCH
* A FUNCTIION IN THE ASSEMBLER, OR, WITH JIT_ PREPENDED, A JIT
* GENERATION INSTRUCTION. THE FUNCTION IS THEN CALLED WITH UP TO
* THREE PARAMETERS. EACH PARAMETER IS A STRING, A NUMBER, A SYMBOL
* REFERENCE OR A REGISTER. EACH LABEL ON A JIT_ OPCODE IS ENTERED
* INTO A LOCAL SYMBOL TABLE. CEXTERN WILL ADD LABELS TO THE CSYMTB.
* AT THE END, THE SYMBOLS REQUIRED ARE WALKED AND FILLED FROM THE
* TWO SYMBOL TABLES.
*
* CE: .MSNOBOL4;
*
-CASE 1
-PLUSOPS 1
*
         OUTPUT = 'ASM'
*
         DATA('ASM(CODE,PATCHES)')
         DEFINE('ASM(SRC)'
+           'ASYMTB,APATCHES,'
+           'ASET,AWHT,ASM_PAT,APEMPTY,APSYMB,'
+           'LAB,OP,P1,P2,P3,ASYMB')
         ASYMTB = TABLE()
         APATCHES = TABLE()
         CSYMTB = TABLE()
         ASET = &UCASE &LCASE &DIGITS '_.'
         AWHT = NSPAN(' ' CHARS_TAB)
         ASM_PAT = FENCE NSPAN(ASET) . LAB
+                  AWHT SPAN(ASET '_.') . OP
+                  AWHT ((BREAKQ(',') . P1 ',') | NULL)
+                  AWHT ((BREAKQ(',') . P2 ',') | NULL)
+                  AWHT ((BREAKQ(',') . P3 ',') | NULL)
+                  REM . CMNT
*
         DEFINE('SEXEC(P1)')
         DEFINE('CEXTERN(P1)')
*
         APEMPTY = TABLE()
         APSYMB = TABLE()
         DEFINE('APARM(X)')                                 :(END_APARM)
*
SEXEC    SEXEC = EVAL(P1)                           :S(RETURN)F(FRETURN)
*
* FIXME - SHOULD GO INTO LOCAL SYMBOL TABLE
*
CEXTERN  CSYMTB<LAB> = DLSYM(0, P1)                            :(RETURN)
*
APARM    APARM = APEMPTY
         IDENT(X)                                             :S(RETURN)
         X FENCE '.' REM . X                                   :S(ASREG)
         X FENCE ANY('"' "'")                                  :S(ASTRG)
         APARM = +X                                           :S(RETURN)
         APARM = APSYMB
         ASYMB = X                                             :(RETURN)
ASTRG    APARM = EVAL(X)                            :S(RETURN)F(FRETURN)
ASREG    FUNCTION(X '_')                                     :F(FRETURN)
         APARM = APPLY(X '_',)                                 :(RETURN)
END_APARM
*
         INIT_JIT('/usr/local/bin/snobol4')
         JIT = JIT_NEW_STATE()
         JIT_SET_STATE(JIT)
*
ASTOP    LINE = TRIM(INPUT)                                   :F(APATCH)
         IDENT(LINE)                                           :S(ASTOP)
         ELINE = LINE
         LINE = LINE ',,,'
         LAB = OP = P1 = P2 = P3 = ASYMB =
         LINE FENCE ANY(';*')                                  :S(ASTOP)
         LINE ASM_PAT                                          :S(ASTOK)
         IDENT(OP, 'END')                                     :S(APATCH)
ASYNTAX  OUTPUT = 'ERROR IN: ' ELINE                            :(ASTOP)
ASTOK    OP = FUNCTION('JIT_' OP) 'JIT_' OP                    :S(ASLAB)
         FUNCTION(OP)                              :S(DOAPARM)F(ASYNTAX)
ASLAB    IDENT(LAB)                                          :S(DOAPARM)
         ASYMTB<LAB> = JIT_LABEL()
DOAPARM  P1 = APARM(P1)                                      :F(ASYNTAX)
         P1 = IDENT(P1, APSYMB) 0
         P2 = APARM(P2)                                      :F(ASYNTAX)
         P2 = IDENT(P2, APSYMB) 0
         P3 = APARM(P3)                                      :F(ASYNTAX)
         P3 = IDENT(P3, APSYMB) APEMPTY
         &ERRLIMIT = 1
         DIFFER(P1, APEMPTY)                                    :S(AAP2)
         R = APPLY(OP,)                            :S(ASYMRES)F(ASYNTAX)
AAP2     DIFFER(P2, APEMPTY)                                    :S(AAP3)
         R = APPLY(OP, P1,)                        :S(ASYMRES)F(ASYNTAX)
AAP3     DIFFER(P3, APEMPTY)                                    :S(AAP4)
         R = APPLY(OP, P1, P2,)                    :S(ASYMRES)F(ASYNTAX)
AAP4     R = APPLY(OP, P1, P2, P3)                 :S(ASYMRES)F(ASYNTAX)
ASYMRES  IDENT(ASYMB)                                          :S(ASTOP)
         APATCHES<ASYMB> = LINK(R, APATCHES<ASYMB>)             :(ASTOP)
*
APATCH   A = KEYST(APATCHES)                                 :F(APATCH3)
         I = 1
APATCH2  P = APATCHES<A<I>>                                  :F(APATCH3)
         R = ASYMTB<A<I>>
         R = IDENT(R) CSYMTB<A<I>>
         IDENT(R)                                            :S(APATCH5)
         JIT_PATCH_AT(VALUE(P), R)
APATCH4  IDENT(P)                                            :S(APATCH5)
         P = NEXT(P)                                          :(APATCH4)
APATCH5  I = I + 1                                            :(APATCH2)
APATCH3
*
         JIT_PRINT()
         PROC = JIT_EMIT()
         JIT_DISASSEMBLE()
         JIT_CLEAR_STATE()
         T = TIME()
         FFI = FFI_NEW('V', 'V')
         FFI_SET_CALLP(FFI, PROC)
         FFI_CALL_VOID(FFI)
         OUTPUT = 'JIT TIME ' TIME() - T
         JIT_SET_STATE(JIT)
         JIT_DESTROY_STATE()
         FFI_FREE(FFI)
*
         FINISH_JIT()
*
END
;
; TEST JIT ASM (ASSEMBLER/LOADER)
;
; THIS IS THE CODE GENERATOR TARGET FORMAT FOR FASBOL
;
         SEXEC     'OUTPUT = "TEST ASM"'
         NAME      'SPEED'
PRINTF   CEXTERN   'printf'
         PROLOG
         MOVI      .R1, 10000000
         MOVI      .R2, 0
L        ADDI      .R2, .R2, 1
         BLER      .R2, .R1, L
         RET
         EPILOG
         END
