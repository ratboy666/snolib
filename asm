#!/usr/bin/bash
         exec "snobol4" "-r" "-s" "$0" "$@" 
-TITLE ASM
-INCLUDE 'FFI.INC'
-INCLUDE 'ASM.INC'
-INCLUDE 'READFILE.INC'
-INCLUDE 'DDT.INC'
*
         INIT_JIT('/usr/local/bin/snobol4')
         SRC = READFILE('TEST.JIT')
*
         CT = TIME()
         ASM = ASM_CREATE()
         ASM(ASM, SRC)                                           :F(END)
         ASM_LINK(ASM)
         CT = TIME() - CT
*
         JIT_SET_STATE(JIT(ASM))
*        JIT_PRINT()
         PROC = JIT_EMIT()
*        JIT_DISASSEMBLE()
*
         JIT_CLEAR_STATE()
         T = TIME()
         FFI = FFI_NEW('V', 'V')
         FFI_SET_CALLP(FFI, PROC)
         FFI_CALL_VOID(FFI)
         OUTPUT = 'JIT TIME ' TIME() - T
         OUTPUT = 'ASM TIME ' CT
*
         ASM_DESTROY(ASM)
         FFI_FREE(FFI)
*
         FINISH_JIT()
*
END