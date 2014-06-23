#!/usr/bin/bash
         exec "snobol4" "-r" "-s" "$0" "$@" 
-TITLE ASM
-INCLUDE 'FFI.INC'
-INCLUDE 'ASM.INC'
-INCLUDE 'READFILE.INC'
-INCLUDE 'DDT.INC'
*
*        DDT()
*
* FOR DISASSEMBLY. REFERENCE TO SNOBOL4 EXECUTABLE, PREFERABLY NOT
* STRIPPED.
*
         INIT_JIT('/usr/local/bin/snobol4')
         SRC = READFILE('TEST.JIT')
*
         CT = TIME()
         ASM = ASM_CREATE()
         ASM(ASM, SRC)                                           :F(END)
         CT = TIME() - CT
*
         JIT_SET_STATE(JIT(ASM))
         JIT_PRINT()
         PROC = JIT_EMIT()
         JIT_DISASSEMBLE()
*
         JIT_CLEAR_STATE()
         T = TIME()
         FFI = FFI_NEW('I', 'V')
         FFI_SET_CALLP(FFI, PROC)
         I = FFI_CALL_INTEGER(FFI)
         OUTPUT = 'JIT TIME ' TIME() - T
         OUTPUT = 'ASM TIME ' CT
         OUTPUT = 'RESULT ' I
*
         FFI_FREE(FFI)
         ASM_DESTROY(ASM)
*
         FINISH_JIT()
*
END
