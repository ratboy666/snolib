-MODULE JIT
-LINE 17 "JIT.lss"
-INCLUDE 'CRACK.INC'
-INCLUDE 'P64.INC'
-INCLUDE 'SEQ.INC'
-STITL JIT
-LINE 2203 "JIT.lss"
-EJECT
*
************************************************************************
*                                                                      *
*                              #  ###  #######                         *
*                              #   #      #                            *
*                              #   #      #                            *
*                              #   #      #                            *
*                        #     #   #      #                            *
*                        #     #   #      #                            *
*                         #####   ###     #                            *
*                                                                      *
* JIT                JUST-IN-TIME CODE GENERATION                      *
*                                                                      *
************************************************************************
*
* QMUL/QDIV NOT YET SUPPORTED
*
* JIT.lss
*
-LINE 23 "JIT.lss"
-CASE 1
-PLUSOPS 1
-LINE 26 "JIT.lss"
-LINE 27 "JIT.lss"
-LINE 28 "JIT.lss"
-LINE 29 "JIT.lss"
-LINE 30 "JIT.lss"
-LINE 33 "JIT.lss"
         jit = 'jit.c'
-LINE 469 "JIT.lss"
-LINE 470 "JIT.lss"
-LINE 471 "JIT.lss"
-LINE 472 "JIT.lss"
-LINE 473 "JIT.lss"
-LINE 474 "JIT.lss"
-LINE 482 "JIT.lss"
         LOAD('INIT_JIT(STRING)', 'jit.so')
         LOAD('R_NUM_JIT()INTEGER', 'jit.so')
         LOAD('V_NUM_JIT()INTEGER', 'jit.so')
         LOAD('F_NUM_JIT()INTEGER', 'jit.so')
         LOAD('FINISH_JIT()', 'jit.so')
*
         LOAD('GET_STATE_JIT()', 'jit.so')
         LOAD('SET_STATE_JIT()', 'jit.so')
         LOAD('NEW_STATE_JIT()', 'jit.so')
         LOAD('DESTROY_STATE_JIT()', 'jit.so')
         LOAD('CLEAR_STATE_JIT()', 'jit.so')
*
         LOAD('PROLOG_JIT()', 'jit.so')
         LOAD('EPILOG_JIT()', 'jit.so')
         LOAD('NOTE_JIT(STRING,INTEGER)', 'jit.so')
         LOAD('NAME_JIT(STRING)', 'jit.so')
         LOAD('ADDRESS_JIT()', 'jit.so')
         LOAD('DISASSEMBLE_JIT()', 'jit.so')
         LOAD('EMIT_JIT()', 'jit.so')
         LOAD('PRINT_JIT()', 'jit.so')
         LOAD('LABEL_JIT()', 'jit.so')
         LOAD('ELLIPSIS_JIT()', 'jit.so')
         LOAD('GET_NOTE_JIT()INTEGER', 'jit.so')
         LOAD('POINTER_P_JIT()', 'jit.so')
         LOAD('CALLEE_SAVE_P_JIT(INTEGER)', 'jit.so')
         LOAD('PATCH_AT_JIT()', 'jit.so')
         LOAD('PATCH_ABS_JIT()', 'jit.so')
         LOAD('PATCH_JIT()', 'jit.so')
         LOAD('PREPARE_JIT()', 'jit.so')
         LOAD('ALLOCAI_JIT(INTEGER)INTEGER', 'jit.so')
         LOAD('DATA_JIT(INTEGER,INTEGER)', 'jit.so')
         LOAD('FORWARD_JIT()', 'jit.so')
         LOAD('LIVE_JIT(INTEGER)', 'jit.so')
         LOAD('LINK_JIT()', 'jit.so')
*
* WE DO R0..R3, V0..V3, F0..F7 AND FP, EVEN THOUGH NOT ALL OF THESE
* REGISTERS MAY EXIST. THE ONES THAT DON'T WILL BE -1. USE JIT_R_NUM(),
* JIT_V_NUM() AND JIT_F_NUM() TO DETERMINE THE ACTUAL NUMBER OF
* REGISTERS. NOTE THAT WORST CASE, R0..R2, V0..V2 AND F0..F5 ARE
* USABLE.
*
         L = 'R0 R1 R2 R3 V0 V1 V2 V3 F0 F1 F2 F3 F4 F5 F6 F7 FP'
         A = CRACK(L, ' ')
         SEQ(" LOAD('GET_' A<I> '_JIT()INTEGER', 'jit.so'); "
+            " $('JIT_' A<I>) = EVAL('GET_' A<I> '_JIT()') ", .I)
*
         L = 'ADDR ADDCR ADDXR SUBR SUBCR SUBXR MULR DIVR DIVR_U '
+            'REMR REMR_U ANDR ORR XORR LSHR RSHR RSHR_U '
+            'LTR LTR_U LER LER_U GER GER_U GTR GTR_U EQR NER '
+            'ADDR_F ADDR_D SUBR_F SUBR_D MULR_F MULR_D DIVR_F DIVR_D '
+            'LTR_F LER_F EQR_F GER_F GTR_F NER_F UNLTR_F UNLER_F '
+            'UNEQR_F UNGER_F UNGTR_F LTGTR_F ORDR_F UNORDR_F '
+            'LTR_D LER_D EQR_D GER_D GTR_D NER_D UNLTR_D UNLER_D '
+            'UNEQR_D UNGER_D UNGTR_D LTGTR_D ORDR_D UNORDR_D '
+            'LDXR_C LDXR_UC LDXR_S LDXR_US LDXR_I LDXR_UI LDXR_L '
+            'LDXR LDXR_F LDXR_D '
+            'STXR_C STXR_S STXR_I STXR STXR_L STXR_F STXR_D '
         A = CRACK(L, ' ')
         SEQ(" LOAD(A<I> '_JIT(INTEGER,INTEGER,INTEGER)', 'jit.so') "
+            , .I)
*
         L = 'ADDI ADDCI ADDXI SUBI SUBCI SUBXI MULI DIVI DIVI_U '
+            'REMI REMI_U ANDI ORI XORI LSHI RSHI RSHI_U '
+            'LTI LTI_U LEI LEI_U GEI GEI_U GTI GTI_U EQI NEI '
+            'ADDI_F SUBI_F MULI_F DIVI_F '
+            'ADDI_D SUBI_D MULI_D DIVI_D '
+            'LDXI_C LDXI_UC LDXI_S LDXI_US LDXI_I LDXI_UI LDXI_L LDXI '
+            'LDXI_F LDXI_D '
+            'STXI_C STXI_S STXI_I STXI_L STXI STXI_F STXI_D '
         A = CRACK(L, ' ')
         SEQ(" LOAD(A<I> '_JIT(INTEGER,INTEGER)', 'jit.so') "
+            , .I)
*
         L = 'BLTR BLTR_U BLER BLER_U BGTR BGTR_U BGER BGER_U '
+            'BEQR BNER BMSR BMCR BOADDR BXADDR BOSUBR BXSUBR'
+            'BOADDR_U BXADDR_U BOSUBR_U BXSUBR_U '
+            'BLTR_F BLER_F BGTR_F BGER_F BEQR_F BNER_R '
+            'BUNLTR_F BUNLER_F BUNEQR_F BUNGER_F BUNGTR_F '
+            'BLTGTR_F BORDR_F BUNORDR_F '
+            'BLTR_D BLER_D BGTR_D BGER_D BEQR_D BNER_D '
+            'BUNLTR_D BUNLER_D BUNEQR_D BUNGER_D BUNGTR_D '
+            'BLTGTR_D BORDR_D BUNORDR_D '
         A = CRACK(L, ' ')
         SEQ(" LOAD(A<I> '_JIT(INTEGER,INTEGER)', 'jit.so') "
+            , .I)
*
         L = 'MOVR MOVR_F MOVR_D MOVR_F_W MOVR_W_F MOVR_D_W MOVR_W_D '
+            'HTONR NTOHR COMR NEGR NEGR_F NEGR_D ABSR_F ABSR_D '
+            'SQRTR_F SQRTR_D '
+            'EXTR_C EXTR_UC EXTR_S EXTR_US EXTR_I EXTR_UI '
+            'EXTR_F EXTR_D_F EXTR_D EXTR_F_D '
+            'TRUNCR_F_I TRUNCR_F TRUNCR_F_L TRUNCR_D_I TRUNCR_D '
+            'TRUNCR_D_L '
+            'LDR_C LDR_UC LDR_S LDR_US LDR_I LDR LDR_UI LDR_L '
+            'LDR_F LDR_D '
+            'STR_C STR_S STR_I STR STR_L STR_F STR_D'
         A = CRACK(L, ' ')
         SEQ(" LOAD(A<I> '_JIT(INTEGER,INTEGER)', 'jit.so') "
+            , .I)
*
         L = 'MOVR_D_WW MOVR_WW_D'
         A = CRACK(L, ' ')
         SEQ(" LOAD(A<I> '_JIT(INTEGER,INTEGER,INTEGER)', 'jit.so') "
+            , .I)
*
         LOAD('MOVI_JIT(INTEGER)', 'jit.so')
         LOAD('MOVI_F_JIT(INTEGER)', 'jit.so')
         LOAD('MOVI_D_JIT(INTEGER)', 'jit.so')
         LOAD('MOVI_F_W_JIT(INTEGER,INTEGER)', 'jit.so')
         LOAD('MOVI_D_W_JIT(INTEGER,INTEGER)', 'jit.so')
         LOAD('MOVI_D_WW_JIT(INTEGER,INTEGER)', 'jit.so')
*
         L = 'ARG ARG_F ARG_D'
         A = CRACK(L, ' ')
         SEQ(" LOAD(A<I> '_JIT()', 'jit.so') ", .I)
*
         L = 'GETARG GETARG_C GETARG_UC GETARG_S GETARG_US GETARG_I '
+            'GETARG_UI GETARG_L GETARG_F GETARG_D '
+            'LDI_C LDI_UC LDI_S LDI_US LDI_I LDI LDI_UI LDI_L LDI_F '
+            'LDI_D STI_C STI_S STI_I STI STI_L STI_F STI_D '
+            'BLTI BLTI_U BLEI BLEI_U BEQI BGEI BGEI_U BGTI BGTI_U '
+            'BNEI BMSI BMCI BOADDI BOADDI_U BXADDI BXADDI_U '
+            'BOSUBI BOSUBI_U BXSUBI BXSUBI_U '
         A = CRACK(L, ' ')
         SEQ(" LOAD(A<I> '_JIT(INTEGER)', 'jit.so') ", .I)
*
         L = 'PUSHARGR PUSHARGR_F PUSHARGR_D '
+            'RETR RETVAL_C RETVAL_UC RETVAL_S RETVAL_US RETVAL_I '
+            'RETVAL RETVAL_UI RETVAL_L RETR_F RETVAL_F '
+            'RETR_D RETVAL_D '
         A = CRACK(L, ' ')
         SEQ(" LOAD(A<I> '_JIT(INTEGER)', 'jit.so') ", .I)
         LOAD('PUSHARGI_JIT()', 'jit.so')
         LOAD('PUSHARGI_F_JIT()', 'jit.so')
         LOAD('PUSHARGI_D_JIT()', 'jit.so')
*
         LOAD('JMPR_JIT(INTEGER)', 'jit.so')
         LOAD('JMPI_JIT()', 'jit.so')
*
         LOAD('CALLR_JIT(INTEGER)', 'jit.so')
         LOAD('CALLI_JIT()', 'jit.so')
*
         LOAD('FINISHR_JIT(INTEGER)', 'jit.so')
         LOAD('FINISHI_JIT()', 'jit.so')
*
         LOAD('RET_JIT()', 'jit.so')
         LOAD('RETI_JIT()', 'jit.so')
         LOAD('RETI_F_JIT()', 'jit.so')
         LOAD('RETI_D_JIT()', 'jit.so')
*
* PROXY FUNCTIONS TO HIDE SET_P()/GET_P(). THESE ARE SHORT FUNCTIONS (1
* OR 2 LINES). USE THESE FUNCTIONS TO USE JIT, RATHER THAN THE ..._JIT
* FUNCTIONS. THESE FUNCTIONS TAKE CARE OF ANY INT/POINTER ISSUES,
* WHEREAS USING THE UNDERLYING FUNCTIONS WILL NOT, AND THE CODE WILL BE
* NOT BE PORTABLE.
*
JIT_DEFINE
*
-PUBLIC JIT_R_NUM(), JIT_V_NUM(), JIT_FNUM()
         DEFINE('JIT_R_NUM()')
         DEFINE('JIT_V_NUM()')
         DEFINE('JIT_F_NUM()')
-PUBLIC JIT_ARG(), JIT_ARG_F(), JIT_ARG_D()
         DEFINE('JIT_ARG()')
         DEFINE('JIT_ARG_F()')
         DEFINE('JIT_ARG_D()')
-PUBLIC JIT_RET(), JIT_RETI(), JIT_RETI_F(), JIT_RETI_D()
         DEFINE('JIT_RET()')
         DEFINE('JIT_RETI(P)')
         DEFINE('JIT_RETI_F(F)')
         DEFINE('JIT_RETI_D(D)')
-PUBLIC JIT_FINISHR(), JIT_FINISHI(), JIT_INIT(), JIT_FINISH()
         DEFINE('JIT_FINISHR(R)')
         DEFINE('JIT_FINISHI(P)')
         DEFINE('JIT_INIT(S)')
         DEFINE('JIT_FINISH()')
-PUBLIC JIT_MOVI(), JIT_MOVI_F(), JIT_MOVI_D()
         DEFINE('JIT_MOVI(R,P)')
         DEFINE('JIT_MOVI_F(R,F)')
         DEFINE('JIT_MOVI_D(R,D)')
-PUBLIC JIT_GETARG(), JIT_GETARG_C(), JIT_GETARG_UC(), JIT_GETARG_S()
-PUBLIC JIT_GETARG_US(), JIT_GETARG_I(), JIT_GETARG_UI(), JIT_GETARG_L()
-PUBLIC JIT_GETARG_F(), JIT_GETARG_D()
         DEFINE('JIT_GETARG(R,A)')
         DEFINE('JIT_GETARG_C(R,A)')
         DEFINE('JIT_GETARG_UC(R,A)')
         DEFINE('JIT_GETARG_S(R,A)')
         DEFINE('JIT_GETARG_US(R,A)')
         DEFINE('JIT_GETARG_I(R,A)')
         DEFINE('JIT_GETARG_UI(R,A)')
         DEFINE('JIT_GETARG_L(R,A)')
         DEFINE('JIT_GETARG_F(R,A)')
         DEFINE('JIT_GETARG_D(R,A)')
-PUBLIC JIT_PROLOG(), JIT_EPILOG(), JIT_PRINT(), JIT_DISASSEMBLE()
-PUBLIC JIT_LABEL(), JIT_ELLIPSIS(), JIT_EMIT(), JIT_ADDRESS()
         DEFINE('JIT_PROLOG()')
         DEFINE('JIT_EPILOG()')
         DEFINE('JIT_PRINT()')
         DEFINE('JIT_DISASSEMBLE()')
         DEFINE('JIT_LABEL()')
         DEFINE('JIT_ELLIPSIS()')
         DEFINE('JIT_EMIT()')
         DEFINE('JIT_ADDRESS(P)')
-PUBLIC JIT_RETR(), JIT_RETR_F(), JIT_RETR_D()
         DEFINE('JIT_RETR(R)')
         DEFINE('JIT_RETR_F(R)')
         DEFINE('JIT_RETR_D(R)')
-PUBLIC JIT_GETSTATE(), JIT_SET_STATE(), JIT_NEW_STATE()
-PUBLIC JIT_DESTROY_STATE(), JIT_CLEAR_STATE()
         DEFINE('JIT_GET_STATE()')
         DEFINE('JIT_SET_STATE(JIT)')
         DEFINE('JIT_NEW_STATE()')
         DEFINE('JIT_DESTROY_STATE()')
         DEFINE('JIT_CLEAR_STATE()')
-PUBLIC JIT_JMPR(), JIT_JMPI()
         DEFINE('JIT_JMPR(R)')
         DEFINE('JIT_JMPI(P)')
-PUBLIC JIT_CALLR(), JIT_CALLI()
         DEFINE('JIT_CALLR(R)')
         DEFINE('JIT_CALLI(P)')
-PUBLIC JIT_NOTE(), JIT_NAME(), JIT_PREPARE(), JIT_ALLOCAI()
         DEFINE('JIT_NOTE(S,N)')
         DEFINE('JIT_NAME(S)')
         DEFINE('JIT_PREPARE()')
         DEFINE('JIT_ALLOCAI(N)')
-PUBLIC JIT_PATCH_AT, JIT_PATCH_ABS(), JIT_PATCH()
         DEFINE('JIT_PATCH_AT(P,P2)')
         DEFINE('JIT_PATCH_ABS(P,P2)')
         DEFINE('JIT_PATCH(P)')
-PUBLIC JIT_ADDR(), JIT_ADDCR(), JIT_ADDXR()
         DEFINE('JIT_ADDR(R1,R2,R3)')
         DEFINE('JIT_ADDCR(R1,R2,R3)')
         DEFINE('JIT_ADDXR(R1,R2,R3)')
-PUBLIC JIT_SUBR(), JIT_SUBCR(), JIT_SUBXR()
         DEFINE('JIT_SUBR(R1,R2,R3)')
         DEFINE('JIT_SUBCR(R1,R2,R3)')
         DEFINE('JIT_SUBXR(R1,R2,R3)')
-PUBLIC JIT_MULR(), JIT_DIVR(), JIT_DIVR_U(), JIT_REMR(), JIT_REMR_U()
         DEFINE('JIT_MULR(R1,R2,R3)')
         DEFINE('JIT_DIVR(R1,R2,R3)')
         DEFINE('JIT_DIVR_U(R1,R2,R3)')
         DEFINE('JIT_REMR(R1,R2,R3)')
         DEFINE('JIT_REMR_U(R1,R2,R3)')
-PUBLIC JIT_ANDR(), JIT_ORR(), JIT_XORR(), JIT_LSHR(), JIT_RSHR()
-PUBLIC JIT_RSHR_U()
         DEFINE('JIT_ANDR(R1,R2,R3)')
         DEFINE('JIT_ORR(R1,R2,R3)')
         DEFINE('JIT_XORR(R1,R2,R3)')
         DEFINE('JIT_LSHR(R1,R2,R3)')
         DEFINE('JIT_RSHR(R1,R2,R3)')
         DEFINE('JIT_RSHR_U(R1,R2,R3)')
-PUBLIC JIT_LTR(), JIT_LTR_U()
         DEFINE('JIT_LTR(R1,R2,R3)')
         DEFINE('JIT_LTR_U(R1,R2,R3)')
-PUBLIC JIT_LER(), JIT_LER_U()
         DEFINE('JIT_LER(R1,R2,R3)')
         DEFINE('JIT_LER_U(R1,R2,R3)')
-PUBLIC JIT_GER(), JIT_GER_U()
         DEFINE('JIT_GER(R1,R2,R3)')
         DEFINE('JIT_GER_U(R1,R2,R3)')
-PUBLIC JIT_GTR(), GTR_U()
         DEFINE('JIT_GTR(R1,R2,R3)')
         DEFINE('JIT_GTR_U(R1,R2,R3)')
-PUBLIC JIT_EQR(), JIT_NER()
         DEFINE('JIT_EQR(R1,R2,R3)')
         DEFINE('JIT_NER(R1,R2,R3)')
-PUBLIC JIT_ADDR_F(), JIT_ADDR_D()
         DEFINE('JIT_ADDR_F(R1,R2,R3)')
         DEFINE('JIT_ADDR_D(R1,R2,R3)')
-PUBLIC JIT_SUBR_F(), JIT_SUBR_D()
         DEFINE('JIT_SUBR_F(R1,R2,R3)')
         DEFINE('JIT_SUBR_D(R1,R2,R3)')
-PUBLIC JIT_MULR_F(), JIT_MULR_D()
         DEFINE('JIT_MULR_F(R1,R2,R3)')
         DEFINE('JIT_MULR_D(R1,R2,R3)')
-PUBLIC JIT_DIVR_F(), JIT_DIVR_D()
         DEFINE('JIT_DIVR_F(R1,R2,R3)')
         DEFINE('JIT_DIVR_D(R1,R2,R3)')
-PUBLIC JIT_LTR_F(), JIT_LER_F(), JIT_EQR_F(), JIT_GER_F(), JIT_GTR_F()
-PUBLIC JIT_NER_F()
         DEFINE('JIT_LTR_F(R1,R2,R3)')
         DEFINE('JIT_LER_F(R1,R2,R3)')
         DEFINE('JIT_EQR_F(R1,R2,R3)')
         DEFINE('JIT_GER_F(R1,R2,R3)')
         DEFINE('JIT_GTR_F(R1,R2,R3)')
         DEFINE('JIT_NER_F(R1,R2,R3)')
-PUBLIC JIT_UNLTR_F(), JIT_UNLER_F(), JIT_UNEQR_F(), JIT_UNGER_F()
-PUBLIC JIT_UNGTR_F(), JIT_LTGTR_F(), JIT_ORDR_F(), JIT_UNORDR_F()
         DEFINE('JIT_UNLTR_F(R1,R2,R3)')
         DEFINE('JIT_UNLER_F(R1,R2,R3)')
         DEFINE('JIT_UNEQR_F(R1,R2,R3)')
         DEFINE('JIT_UNGER_F(R1,R2,R3)')
         DEFINE('JIT_UNGTR_F(R1,R2,R3)')
         DEFINE('JIT_LTGTR_F(R1,R2,R3)')
         DEFINE('JIT_ORDR_F(R1,R2,R3)')
         DEFINE('JIT_UNORDR_F(R1,R2,R3)')
-PUBLIC JIT_LTR_D(), JIT_LER_D(), JIT_EQR_D(), JIT_GER_D(), JIT_GTR_D()
-PUBLIC JIT_NER_D()
-PUBLIC JIT_UNLTR_D(), JIT_UNLER_D(), JIT_UNEQR_D(), JIT_UNGER_D()
-PUBLIC JIT_UNGTR_D(), JIT_LTGTR_D(), JIT_ORDR_D(), JIT_UNORDR_D(),
         DEFINE('JIT_LTR_D(R1,R2,R3)')
         DEFINE('JIT_LER_D(R1,R2,R3)')
         DEFINE('JIT_EQR_D(R1,R2,R3)')
         DEFINE('JIT_GER_D(R1,R2,R3)')
         DEFINE('JIT_GTR_D(R1,R2,R3)')
         DEFINE('JIT_NER_D(R1,R2,R3)')
         DEFINE('JIT_UNLTR_D(R1,R2,R3)')
         DEFINE('JIT_UNLER_D(R1,R2,R3)')
         DEFINE('JIT_UNEQR_D(R1,R2,R3)')
         DEFINE('JIT_UNGER_D(R1,R2,R3)')
         DEFINE('JIT_UNGTR_D(R1,R2,R3)')
         DEFINE('JIT_LTGTR_D(R1,R2,R3)')
         DEFINE('JIT_ORDR_D(R1,R2,R3)')
         DEFINE('JIT_UNORDR_D(R1,R2,R3)')
-PUBLIC JIT_LDXR_C(), JIT_LDXR_UC(), JIT_LDXR_S(), JIT_LDXR_US()
-PUBLIC JIT_LDXR_I(), JIT_LDXR_UI(), JIT_LDXR_L(), JIT_LDXR()
-PUBLIC JIT_LDXR_F(), JIT_LDXR_D()
         DEFINE('JIT_LDXR_C(R1,R2,R3)')
         DEFINE('JIT_LDXR_UC(R1,R2,R3)')
         DEFINE('JIT_LDXR_S(R1,R2,R3)')
         DEFINE('JIT_LDXR_US(R1,R2,R3)')
         DEFINE('JIT_LDXR_I(R1,R2,R3)')
         DEFINE('JIT_LDXR_UI(R1,R2,R3)')
         DEFINE('JIT_LDXR_L(R1,R2,R3)')
         DEFINE('JIT_LDXR(R1,R2,R3)')
         DEFINE('JIT_LDXR_F(R1,R2,R3)')
         DEFINE('JIT_LDXR_D(R1,R2,R3)')
-PUBLIC JIT_STXR_C(), JIT_STXR_S(), JIT_STXR_I(), JIT_STXR()
-PUBLIC JIT_STXR_L(), JIT_STXR_F(), JIT_STXR_D()
         DEFINE('JIT_STXR_C(R1,R2,R3)')
         DEFINE('JIT_STXR_S(R1,R2,R3)')
         DEFINE('JIT_STXR_I(R1,R2,R3)')
         DEFINE('JIT_STXR(R1,R2,R3)')
         DEFINE('JIT_STXR_L(R1,R2,R3)')
         DEFINE('JIT_STXR_F(R1,R2,R3)')
         DEFINE('JIT_STXR_D(R1,R2,R3)')
-PUBLIC JIT_BLTR(), JIT_BLTR_U(), JIT_BLER(), JIT_BLER_U()
         DEFINE('JIT_BLTR(R1,R2)')
         DEFINE('JIT_BLTR_U(R1,R2)')
         DEFINE('JIT_BLER(R1,R2)')
         DEFINE('JIT_BLER_U(R1,R2)')
-PUBLIC JIT_BGTR(), JIT_BGTR_U(), JIT_BGER(), JIT_BGER_U()
         DEFINE('JIT_BGTR(R1,R2)')
         DEFINE('JIT_BGTR_U(R1,R2)')
         DEFINE('JIT_BGER(R1,R2)')
         DEFINE('JIT_BGER_U(R1,R2)')
-PUBLIC JIT_BEQR(), JIT_BNER(), JIT_BMSR(), JIT_BMCR()
         DEFINE('JIT_BEQR(R1,R2)')
         DEFINE('JIT_BNER(R1,R2)')
         DEFINE('JIT_BMSR(R1,R2)')
         DEFINE('JIT_BMCR(R1,R2)')
-PUBLIC JIT_BOADDR(), JIT_BXADDR(), JIT_BOSUBR(), JIT_BXSUBR()
         DEFINE('JIT_BOADDR(R1,R2)')
         DEFINE('JIT_BXADDR(R1,R2)')
         DEFINE('JIT_BOSUBR(R1,R2)')
         DEFINE('JIT_BXSUBR(R1,R2)')
-PUBLIC JIT_BOADDR_U(), JIT_BXADDR_U(), JIT_BOSUBR_U(), JIT_BXSUBR_U()
         DEFINE('JIT_BOADDR_U(R1,R2)')
         DEFINE('JIT_BXADDR_U(R1,R2)')
         DEFINE('JIT_BOSUBR_U(R1,R2)')
         DEFINE('JIT_BXSUBR_U(R1,R2)')
-PUBLIC JIT_BLTR_F(), JIT_BLER_F(), JIT_BGTR_F(), JIT_BGER_F()
-PUBLIC JIT_BEQR_F(), JIT_BNER_R()
         DEFINE('JIT_BLTR_F(R1,R2)')
         DEFINE('JIT_BLER_F(R1,R2)')
         DEFINE('JIT_BGTR_F(R1,R2)')
         DEFINE('JIT_BGER_F(R1,R2)')
         DEFINE('JIT_BEQR_F(R1,R2)')
         DEFINE('JIT_BNER_R(R1,R2)')
-PUBLIC JIT_BUNLTR_F(), JIT_BUNLER_F(), JIT_BUNEQR_F()
-PUBLIC JIT_BUNGER_F(), JIT_BUNGTR_F(), JIT_BLTGTR_F()
         DEFINE('JIT_BUNLTR_F(R1,R2)')
         DEFINE('JIT_BUNLER_F(R1,R2)')
         DEFINE('JIT_BUNEQR_F(R1,R2)')
         DEFINE('JIT_BUNGER_F(R1,R2)')
         DEFINE('JIT_BUNGTR_F(R1,R2)')
         DEFINE('JIT_BLTGTR_F(R1,R2)')
-PUBLIC JIT_BORDR_F(), JIT_BUNORDR_F()
         DEFINE('JIT_BORDR_F(R1,R2)')
         DEFINE('JIT_BUNORDR_F(R1,R2)')
-PUBLIC JIT_BLTR_D(), JIT_BLER_D(), JIT_BGTR_D(), JIT_BGER_D()
-PUBLIC JIT_BEQR_D(), JIT_BNER_D()
         DEFINE('JIT_BLTR_D(R1,R2)')
         DEFINE('JIT_BLER_D(R1,R2)')
         DEFINE('JIT_BGTR_D(R1,R2)')
         DEFINE('JIT_BGER_D(R1,R2)')
         DEFINE('JIT_BEQR_D(R1,R2)')
         DEFINE('JIT_BNER_D(R1,R2)')
-PUBLIC JIT_BUNLTR_D(), JIT_BUNLER_D(), JIT_BUNEQR_D()
         DEFINE('JIT_BUNLTR_D(R1,R2)')
         DEFINE('JIT_BUNLER_D(R1,R2)')
         DEFINE('JIT_BUNEQR_D(R1,R2)')
-PUBLIC JIT_BUNGER_D(), JIT_BUNGTR_D(), JIT_BLTGTR_D()
         DEFINE('JIT_BUNGER_D(R1,R2)')
         DEFINE('JIT_BUNGTR_D(R1,R2)')
         DEFINE('JIT_BLTGTR_D(R1,R2)')
-PUBLIC JIT_BORDR_D(), JIT_BUNORDR_D()
         DEFINE('JIT_BORDR_D(R1,R2)')
         DEFINE('JIT_BUNORDR_D(R1,R2)')
-PUBLIC JIT_ADDI(), JIT_ADDCI(), JIT_ADDXI()
         DEFINE('JIT_ADDI(R1,R2,P)')
         DEFINE('JIT_ADDCI(R1,R2,P)')
         DEFINE('JIT_ADDXI(R1,R2,P)')
-PUBLIC JIT_SUBI(), JIT_SUBCI(), JIT_SUBXI()
         DEFINE('JIT_SUBI(R1,R2,P)')
         DEFINE('JIT_SUBCI(R1,R2,P)')
         DEFINE('JIT_SUBXI(R1,R2,P)')
-PUBLIC JIT_MULI(), JIT_DIVI(), JIT_DIVI_U(), JIT_REMI(), JIT_REMI_U()
         DEFINE('JIT_MULI(R1,R2,P)')
         DEFINE('JIT_DIVI(R1,R2,P)')
         DEFINE('JIT_DIVI_U(R1,R2,P)')
         DEFINE('JIT_REMI(R1,R2,P)')
         DEFINE('JIT_REMI_U(R1,R2,P)')
-PUBLIC JIT_ANDI(), JIT_ORI(), JIT_XORI(), JIT_LSHI()
-PUBLIC JIT_RSHI(), JIT_RSHI_U(),
         DEFINE('JIT_ANDI(R1,R2,P)')
         DEFINE('JIT_ORI(R1,R2,P)')
         DEFINE('JIT_XORI(R1,R2,P)')
         DEFINE('JIT_LSHI(R1,R2,P)')
         DEFINE('JIT_RSHI(R1,R2,P)')
         DEFINE('JIT_RSHI_U(R1,R2,P)')
-PUBLIC JIT_LTI(), JIT_LTI_U(), JIT_LEI(), JIT_LEI_U()
         DEFINE('JIT_LTI(R1,R2,P)')
         DEFINE('JIT_LTI_U(R1,R2,P)')
         DEFINE('JIT_LEI(R1,R2,P)')
         DEFINE('JIT_LEI_U(R1,R2,P)')
-PUBLIC JIT_GEI(), JIT_GEI_U(), JIT_GTI(), JIT_GTI_U()
         DEFINE('JIT_GEI(R1,R2,P)')
         DEFINE('JIT_GEI_U(R1,R2,P)')
         DEFINE('JIT_GTI(R1,R2,P)')
         DEFINE('JIT_GTI_U(R1,R2,P)')
-PUBLIC JIT_EQI(), JIT_NEI()
         DEFINE('JIT_EQI(R1,R2,P)')
         DEFINE('JIT_NEI(R1,R2,P)')
-PUBLIC JIT_LDXI_C(), JIT_LDXI_UC(), JIT_LDXI_S(), JIT_LDXI_US()
         DEFINE('JIT_LDXI_C(R1,R2,P)')
         DEFINE('JIT_LDXI_UC(R1,R2,P)')
         DEFINE('JIT_LDXI_S(R1,R2,P)')
         DEFINE('JIT_LDXI_US(R1,R2,P)')
-PUBLIC JIT_LDXI_I(), JIT_LDXI_UI(), JIT_LDXI_L()
         DEFINE('JIT_LDXI_I(R1,R2,P)')
         DEFINE('JIT_LDXI_UI(R1,R2,P)')
         DEFINE('JIT_LDXI_L(R1,R2,P)')
-PUBLIC JIT_LDXI(), JIT_LDXI_F(), JIT_LDXI_D()
         DEFINE('JIT_LDXI(R1,R2,P)')
         DEFINE('JIT_LDXI_F(R1,R2,P)')
         DEFINE('JIT_LDXI_D(R1,R2,P)')
-PUBLIC JIT_STXI_C(), JIT_STXI_S(), JIT_STXI_I()
         DEFINE('JIT_STXI_C(R1,P,R2)')
         DEFINE('JIT_STXI_S(R1,P,R2)')
         DEFINE('JIT_STXI_I(R1,P,R2)')
-PUBLIC JIT_STXI_L(), JIT_STXI(), JIT_STXI_F(), JIT_STXI_D()
         DEFINE('JIT_STXI_L(R1,P,R2)')
         DEFINE('JIT_STXI(R1,P,R2)')
         DEFINE('JIT_STXI_F(R1,P,R2)')
         DEFINE('JIT_STXI_D(R1,P,R2)')
-PUBLIC JIT_ADDI_F(), JIT_SUBI_F(), JIT_MULI_F(), JIT_DIVI_F()
         DEFINE('JIT_ADDI_F(R1,R2,F)')
         DEFINE('JIT_SUBI_F(R1,R2,F)')
         DEFINE('JIT_MULI_F(R1,R2,F)')
         DEFINE('JIT_DIVI_F(R1,R2,F)')
-PUBLIC JIT_ADDI_D(), JIT_SUBI_D(), JIT_MULI_D(), JIT_DIVI_D()
         DEFINE('JIT_ADDI_D(R1,R2,D)')
         DEFINE('JIT_SUBI_D(R1,R2,D)')
         DEFINE('JIT_MULI_D(R1,R2,D)')
         DEFINE('JIT_DIVI_D(R1,R2,D)')
-PUBLIC JIT_MOVR(), JIT_MOVR_F(), JIT_MOVR_D()
         DEFINE('JIT_MOVR(R1,R2)')
         DEFINE('JIT_MOVR_F(R1,R2)')
         DEFINE('JIT_MOVR_D(R1,R2)')
-PUBLIC JIT_HTONR(), JIT_NTOHR()
         DEFINE('JIT_HTONR(R1,R2)')
         DEFINE('JIT_NTOHR(R1,R2)')
-PUBLIC JIT_COMR()
         DEFINE('JIT_COMR(R1,R2)')
-PUBLIC JIT_NEGR(), JIT_NEGR_F(), JIT_NEGR_D()
         DEFINE('JIT_NEGR(R1,R2)')
         DEFINE('JIT_NEGR_F(R1,R2)')
         DEFINE('JIT_NEGR_D(R1,R2)')
-PUBLIC JIT_ABSR_F(), JIT_ABSR_D()
         DEFINE('JIT_ABSR_F(R1,R2)')
         DEFINE('JIT_ABSR_D(R1,R2)')
-PUBLIC JIT_SQRTR_F(), JIT_SQRTR_D()
         DEFINE('JIT_SQRTR_F(R1,R2)')
         DEFINE('JIT_SQRTR_D(R1,R2)')
-PUBLIC JIT_EXTR_C(), JIT_EXTR_UC(), JIT_EXTR_S(), JIT_EXTR_US()
         DEFINE('JIT_EXTR_C(R1,R2)')
         DEFINE('JIT_EXTR_UC(R1,R2)')
         DEFINE('JIT_EXTR_S(R1,R2)')
         DEFINE('JIT_EXTR_US(R1,R2)')
-PUBLIC JIT_EXTR_I(), JIT_EXTR_UI(), JIT_EXTR_F(), JIT_EXTR_D_F()
         DEFINE('JIT_EXTR_I(R1,R2)')
         DEFINE('JIT_EXTR_UI(R1,R2)')
         DEFINE('JIT_EXTR_F(R1,R2)')
         DEFINE('JIT_EXTR_D_F(R1,R2)')
-PUBLIC JIT_EXTR_D(), JIT_EXTR_F_D()
         DEFINE('JIT_EXTR_D(R1,R2)')
         DEFINE('JIT_EXTR_F_D(R1,R2)')
-PUBLIC JIT_TRUNCR_F_I(), JIT_TRUNCR_F(), JIT_TRUNCR_F_L()
-PUBLIC JIT_TRUNCR_D_I(), JIT_TRUNCR_D(), JIT_TRUNCR_D_L()
         DEFINE('JIT_TRUNCR_F_I(R1,R2)')
         DEFINE('JIT_TRUNCR_F(R1,R2)')
         DEFINE('JIT_TRUNCR_F_L(R1,R2)')
         DEFINE('JIT_TRUNCR_D_I(R1,R2)')
         DEFINE('JIT_TRUNCR_D(R1,R2)')
         DEFINE('JIT_TRUNCR_D_L(R1,R2)')
-PUBLIC JIT_LDR_C(), JIT_LDR_UC(), JIT_LDR_S(), JIT_LDR_US()
         DEFINE('JIT_LDR_C(R1,R2)')
         DEFINE('JIT_LDR_UC(R1,R2)')
         DEFINE('JIT_LDR_S(R1,R2)')
         DEFINE('JIT_LDR_US(R1,R2)')
-PUBLIC JIT_LDR_I(), JIT_LDR(), JIT_LDR_UI(), JIT_LDR_L()
         DEFINE('JIT_LDR_I(R1,R2)')
         DEFINE('JIT_LDR(R1,R2)')
         DEFINE('JIT_LDR_UI(R1,R2)')
         DEFINE('JIT_LDR_L(R1,R2)')
-PUBLIC JIT_LDR_F(), JIT_LDR_D()
         DEFINE('JIT_LDR_F(R1,R2)')
         DEFINE('JIT_LDR_D(R1,R2)')
-PUBLIC JIT_STR_C(), JIT_STR_S(), JIT_STR_I(), JIT_STR()
         DEFINE('JIT_STR_C(R1,R2)')
         DEFINE('JIT_STR_S(R1,R2)')
         DEFINE('JIT_STR_I(R1,R2)')
         DEFINE('JIT_STR(R1,R2)')
-PUBLIC JIT_STR_L(), JIT_STR_F(), JIT_STR_D()
         DEFINE('JIT_STR_L(R1,R2)')
         DEFINE('JIT_STR_F(R1,R2)')
         DEFINE('JIT_STR_D(R1,R2)')
-PUBLIC JIT_LDI_C(), JIT_LDI_UC(), JIT_LDI_S(), JIT_LDI_US()
         DEFINE('JIT_LDI_C(R,P)')
         DEFINE('JIT_LDI_UC(R,P)')
         DEFINE('JIT_LDI_S(R,P)')
         DEFINE('JIT_LDI_US(R,P)')
-PUBLIC JIT_LDI_I(), JIT_LDI(), JIT_LDI_UI(), JIT_LDI_L()
         DEFINE('JIT_LDI_I(R,P)')
         DEFINE('JIT_LDI(R,P)')
         DEFINE('JIT_LDI_UI(R,P)')
         DEFINE('JIT_LDI_L(R,P)')
-PUBLIC JIT_LDI_F(), JIT_LDI_D()
         DEFINE('JIT_LDI_F(R,P)')
         DEFINE('JIT_LDI_D(R,P)')
-PUBLIC JIT_PUSHARGI(), JIT_PUSHARGI_F(), JIT_PUSHARGI_D()
         DEFINE('JIT_PUSHARGI(P)')
         DEFINE('JIT_PUSHARGI_F(F)')
         DEFINE('JIT_PUSHARGI_D(D)')
-PUBLIC JIT_BLTI(), JIT_BLTI_U(), JIT_BLEI(), JIT_BLEI_U()
         DEFINE('JIT_BLTI(R,P)')
         DEFINE('JIT_BLTI_U(R,P)')
         DEFINE('JIT_BLEI(R,P)')
         DEFINE('JIT_BLEI_U(R,P)')
-PUBLIC JIT_BEQI(), JIT_BGEI(), JIT_BGEI_U(), JIT_BGTI()
         DEFINE('JIT_BEQI(R,P)')
         DEFINE('JIT_BGEI(R,P)')
         DEFINE('JIT_BGEI_U(R,P)')
         DEFINE('JIT_BGTI(R,P)')
-PUBLIC JIT_BGTI_U(), JIT_BNEI(), JIT_BMSI(), JIT_BMCI()
         DEFINE('JIT_BGTI_U(R,P)')
         DEFINE('JIT_BNEI(R,P)')
         DEFINE('JIT_BMSI(R,P)')
         DEFINE('JIT_BMCI(R,P)')
-PUBLIC JIT_BOADDI(), JIT_BOADDI_U(), JIT_BXADDI()
         DEFINE('JIT_BOADDI(R,P)')
         DEFINE('JIT_BOADDI_U(R,P)')
         DEFINE('JIT_BXADDI(R,P)')
-PUBLIC JIT_BXADDI_U(), JIT_BOSUBI(), JIT_BOSUBI_U()
         DEFINE('JIT_BXADDI_U(R,P)')
         DEFINE('JIT_BOSUBI(R,P)')
         DEFINE('JIT_BOSUBI_U(R,P)')
-PUBLIC JIT_BXSUBI(), JIT_BXSUBI_U()
         DEFINE('JIT_BXSUBI(R,P)')
         DEFINE('JIT_BXSUBI_U(R,P)')
-PUBLIC JIT_STI_C(), JIT_STI_S(), JIT_STI_I(), JIT_STI(), JIT_STI_L()
-PUBLIC JIT_STI_F(), JIT_STI_D()
         DEFINE('JIT_STI_C(P,R)')
         DEFINE('JIT_STI_S(P,R)')
         DEFINE('JIT_STI_I(P,R)')
         DEFINE('JIT_STI(P,R)')
         DEFINE('JIT_STI_L(P,R)')
         DEFINE('JIT_STI_F(P,R)')
         DEFINE('JIT_STI_D(P,R)')
-PUBLIC JIT_PUSHARGR(), JIT_PUSHARGR_F(), JIT_PUSHARGR_D()
         DEFINE('JIT_PUSHARGR(R)')
         DEFINE('JIT_PUSHARGR_F(R)')
         DEFINE('JIT_PUSHARGR_D(R)')
-PUBLIC JIT_RETVAL_C(), JIT_RETVAL_UC(), JIT_RETVAL_S(), JIT_RETVAL_US()
-PUBLIC JIT_RETVAL_I(), JIT_RETVAL(), JIT_RETVAL_UI(), JIT_RETVAL_L()
-PUBLIC JIT_RETVAL_F(), JIT_RETVAL_D()
         DEFINE('JIT_RETVAL_C(R)')
         DEFINE('JIT_RETVAL_UC(R)')
         DEFINE('JIT_RETVAL_S(R)')
         DEFINE('JIT_RETVAL_US(R)')
         DEFINE('JIT_RETVAL_I(R)')
         DEFINE('JIT_RETVAL(R)')
         DEFINE('JIT_RETVAL_UI(R)')
         DEFINE('JIT_RETVAL_L(R)')
         DEFINE('JIT_RETVAL_F(R)')
         DEFINE('JIT_RETVAL_D(R)')                            :(JIT_END)
*
JIT_R_NUM
         JIT_R_NUM = R_NUM_JIT()                               :(RETURN)
*
JIT_V_NUM
         JIT_V_NUM = V_NUM_JIT()                               :(RETURN)
*
JIT_F_NUM
         JIT_F_NUM = F_NUM_JIT()                               :(RETURN)
*
JIT_ARG  ARG_JIT()
         JIT_ARG = GET_P()                                     :(RETURN)
*
JIT_ARG_F
         ARG_F_JIT()
         JIT_ARG_F = GET_P()                                   :(RETURN)
*
JIT_ARG_D
         ARG_D_JIT()
         JIT_ARG_D = GET_P()                                   :(RETURN)
*
JIT_RET  RET_JIT()                                             :(RETURN)
*
JIT_RETI SET_P(P)
         RETI_JIT()                                            :(RETURN)
*
JIT_RETI_F
         SET_F(F)
         RETI_F_JIT()                                          :(RETURN)
*
JIT_RETI_D
         SET_D(D)
         RETI_D_JIT()                                          :(RETURN)
*
JIT_FINISHR
         FINISHR_JIT(R)                                        :(RETURN)
*
JIT_FINISHI
         SET_P(P)
         FINISHI_JIT()                                         :(RETURN)
*
JIT_INIT INIT_JIT(S)                                           :(RETURN)
*
JIT_FINISH
         FINISH_JIT()                                          :(RETURN)
*
JIT_MOVI SET_P(P)
         MOVI_JIT(R)
         JIT_MOVI = GET_P()                                    :(RETURN)
*
JIT_MOVI_F
         SET_F(F)
         MOVI_F_JIT(R)                                         :(RETURN)
*
JIT_MOVI_D(R,D)
         SET_D(D)
         MOVI_D_JIT(R)                                         :(RETURN)
*
JIT_GETARG
         SET_P(A)
         GETARG_JIT(R)                                         :(RETURN)
*
JIT_GETARG_C
         SET_P(A)
         GETARG_C_JIT(R)                                       :(RETURN)
*
JIT_GETARG_UC
         SET_P(A)
         GETARG_UC_JIT(R)                                      :(RETURN)
*
JIT_GETARG_S
         SET_P(A)
         GETARG_S_JIT(R)                                       :(RETURN)
*
JIT_GETARG_US
         SET_P(A)
         GETARG_US_JIT(R)                                      :(RETURN)
*
JIT_GETARG_I
         SET_P(A)
         GETARG_I_JIT(R)                                       :(RETURN)
*
JIT_GETARG_UI
         SET_P(A)
         GETARG_UI_JIT(R)                                      :(RETURN)
*
JIT_GETARG_L
         SET_P(A)
         GETARG_L_JIT(R)                                       :(RETURN)
*
JIT_GETARG_F
         SET_P(A)
         GETARG_F_JIT(R)                                       :(RETURN)
*
JIT_GETARG_D
         SET_P(A)
         GETARG_D_JIT(R)                                       :(RETURN)
*
JIT_PROLOG
         PROLOG_JIT()                                          :(RETURN)
*
JIT_EPILOG
         EPILOG_JIT()                                          :(RETURN)
*
JIT_PRINT
         PRINT_JIT()                                           :(RETURN)
*
JIT_DISASSEMBLE
         DISASSEMBLE_JIT()                                     :(RETURN)
*
JIT_LABEL
         LABEL_JIT()
         JIT_LABEL = GET_P()                                   :(RETURN)
*
JIT_ELLIPSIS
         ELLIPSIS_JIT()                                        :(RETURN)
*
JIT_EMIT EMIT_JIT()
         JIT_EMIT = GET_P()                                    :(RETURN)
*
JIT_ADDRESS
         SET_P(P)
         ADDRESS_JIT()
         JIT_ADDRESS = GET_P()                                 :(RETURN)
*
JIT_RETR RETR_JIT(R)                                           :(RETURN)
*
JIT_RETR_F
         RETR_F_JIT(R)                                         :(RETURN)
*
JIT_RETR_D
         RETR_D_JIT(R)                                         :(RETURN)
*
JIT_GET_STATE
         GET_STATE_JIT()
         JIT_GET_STATE = GET_P()                               :(RETURN)
*
JIT_SET_STATE
         SET_P(JIT)
         SET_STATE_JIT()                                       :(RETURN)
*
JIT_NEW_STATE
         NEW_STATE_JIT()
         JIT_NEW_STATE = GET_P()                               :(RETURN)
*
JIT_DESTROY_STATE
         DESTROY_STATE_JIT()                                   :(RETURN)
*
JIT_CLEAR_STATE
         CLEAR_STATE_JIT()                                     :(RETURN)
*
JIT_JMPR JMPR_JIT(R)                                           :(RETURN)
*
JIT_JMPI SET_P(P)
         JMPI_JIT()
         JIT_JMPI = GET_P()                                    :(RETURN)
*
JIT_CALLR
         CALLR_JIT(R)                                          :(RETURN)
*
JIT_CALLI
         SET_P(P)
         CALLI_JIT()
         JIT_CALLI = GET_P()                                   :(RETURN)
*
JIT_NOTE NOTE_JIT(S, N)
         JIT_NOTE = GET_P()                                    :(RETURN)
*
JIT_NAME NAME_JIT(S)
         JIT_NAME = GET_P()                                    :(RETURN)
*
JIT_PREPARE
         PREPARE_JIT()                                         :(RETURN)
*
JIT_ALLOCAI
         JIT_ALLOCAI = ALLOCAI_JIT(N)                          :(RETURN)
*
JIT_PATCH_AT
         SET_P(P2)
         P_TO_P2()
         SET_P(P)
         PATCH_AT_JIT()                                        :(RETURN)
*
JIT_PATCH_ABS
         SET_P(P2)
         P_TO_P2()
         SET_P(P)
         PATCH_ABS_JIT()                                       :(RETURN)
*
JIT_PATCH
         SET_P(P)
         PATCH_JIT()                                           :(RETURN)
*
JIT_ADDR ADDR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_ADDCR
         ADDCR_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_ADDXR
         ADDXR_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_SUBR SUBR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_SUBCR
         SUBCR_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_SUBXR
         SUBXR_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_MULR MULR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_DIVR DIVR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_DIVR_U
         DIVR_U_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_REMR REMR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_REMR_U
         REMR_U_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_ANDR ANDR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_ORR  ORR_JIT(R1, R2, R3)                                   :(RETURN)
*
JIT_XORR XORR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_LSHR LSHR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_RSHR RSHR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_RSHR_U
         RSHR_U_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_LTR  LTR_JIT(R1, R2, R3)                                   :(RETURN)
*
JIT_LTR_U
         LTR_U_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_LER  LER_JIT(R1, R2, R3)                                   :(RETURN)
*
JIT_LER_U
         LER_U_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_GER  GER_JIT(R1, R2, R3)                                   :(RETURN)
*
JIT_GER_U
         GER_U_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_GTR  GTR_JIT(R1, R2, R3)                                   :(RETURN)
*
JIT_GTR_U
         GTR_U_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_EQR  EQR_JIT(R1, R2, R3)                                   :(RETURN)
*
JIT_NER  NER_JIT(R1, R2, R3)                                   :(RETURN)
*
JIT_ADDR_F
         ADDR_F_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_ADDR_D
         ADDR_D_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_SUBR_F
         SUBR_F_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_SUBR_D
         SUBR_D(R1, R2, R3)                                    :(RETURN)
*
JIT_MULR_F
         MULR_F_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_MULR_D
         MULR_D_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_DIVR_F
         DIVR_F_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_DIVR_D
         DIVR_D_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_LTR_F
         LTR_F_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_LER_F
         LER_F_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_EQR_F
         EQR_F_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_GER_F
         GER_F_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_GTR_F
         GTR_F_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_NER_F
         NER_F_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_UNLTR_F
         UNLTR_F_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_UNLER_F
         UNLER_F_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_UNEQR_F
         UNEQR_F_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_UNGER_F
         UNGER_F_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_UNGTR_F
         UNGTR_F_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_LTGTR_F
         LTGTR_F_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_ORDR_F
         ORDR_F_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_UNORDR_F
         UNORDR_F_JIT(R1, R2, R3)                              :(RETURN)
*
JIT_LTR_D
         LTR_D_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_LER_D
         LER_D_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_EQR_D
         EQR_D_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_GER_D
         GER_D_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_GTR_D
         GTR_D_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_NER_D
         NER_D_JIT(R1, R2, R3)                                 :(RETURN)
*
JIT_UNLTR_D
         UNLTR_D_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_UNLER_D
         UNLER_D_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_UNEQR_D
         UNEQR_D_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_UNGER_D
         UNGER_D_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_UNGTR_D
         UNGTR_D_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_LTGTR_D
         LTGTR_D_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_ORDR_D
         ORDR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_UNORDR_D
         UNORDR_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_LDXR_C
         LDXR_C_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_LDXR_UC
         LDXR_UC_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_LDXR_S
         LDXR_S_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_LDXR_US
         LDXR_US_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_LDXR_I
         LDXR_I_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_LDXR_UI
         LDXR_UI_JIT(R1, R2, R3)                               :(RETURN)
*
JIT_LDXR_L
         LDXR_L_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_LDXR LDXR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_LDXR_F
         LDXR_F_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_LDXR_D
         LDXR_D_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_STXR_C
         STXR_C_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_STXR_S
         STRX_S_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_STXR_I
         STXR_I_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_STXR STXR_JIT(R1, R2, R3)                                  :(RETURN)
*
JIT_STXR_L
         STXR_L_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_STXR_F
         SRXR_F_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_STXR_D
         STXR_D_JIT(R1, R2, R3)                                :(RETURN)
*
JIT_BLTR BLTR_JIT(R1, R2)
         JIT_BLTR = GET_P()                                    :(RETURN)
*
JIT_BLTR_U
         BLTR_U_JIT(R1, R2)
         JIT_BLTR_U = GET_P()                                  :(RETURN)
*
JIT_BLER BLER_JIT(R1, R2)
         JIT_BLER = GET_P()                                    :(RETURN)
*
JIT_BLER_U
         BLER_U_JIT(R1, R2)
         JIT_BLER_U = GET_P()                                  :(RETURN)
*
JIT_BGTR BGTR_JIT(R1, R2)
         JIT_BGTR = GET_P()                                    :(RETURN)
*
JIT_BGTR_U
         BGTR_U_JIT(R1, R2)
         JIT_BGTR_U = GET_P()                                  :(RETURN)
*
JIT_BGER BGER_JIT(R1, R2)
         JIT_BGER = GET_P()                                    :(RETURN)
*
JIT_BGER_U
         BGER_U_JIT(R1, R2)
         JIT_BGER_U = GET_P()                                  :(RETURN)
*
JIT_BEQR BEQR_JIT(R1, R2)
         JIT_BEQR = GET_P()                                    :(RETURN)
*
JIT_BNER BNER_JIT(R1, R2)
         JIT_BNER = GET_P()                                    :(RETURN)
*
JIT_BMSR BMSR_JIT(R1, R2)
         JIT_BMSR = GET_P()                                    :(RETURN)
*
JIT_BMCR BMCR_JIT(R1, R2)
         JIT_BMCR = GET_P()                                    :(RETURN)
*
JIT_BOADDR
         BOADDR_JIT(R1, R2)
         JIT_BOADDR = GET_P()                                  :(RETURN)
*
JIT_BXADDR
         BXADDR_JIT(R1, R2)
         JIT_BXADDR = GET_P()                                  :(RETURN)
*
JIT_BOSUBR
         BOSUBR_JIT(R1, R2)
         JIT_BOSUBR = GET_P()                                  :(RETURN)
*
JIT_BXSUBR
         BXSUBR_JIT(R1, R2)
         JIT_BXSUBR = GET_P()                                  :(RETURN)
*
JIT_BOADDR_U
         BOADDR_U_JIT(R1, R2)
         JIT_BOADDR_U = GET_P()                                :(RETURN)
*
JIT_BXADDR_U
         BXADDR_U_JIT(R1, R2)
         JIT_BXADDR_U = GET_P()                                :(RETURN)
*
JIT_BOSUBR_U
         BOSUBR_U_JIT(R1, R2)
         JIT_BOSUBR_U = GET_P()                                :(RETURN)
*
JIT_BXSUBR_U
         BXSUBR_U_JIT(R1, R2)
         JIT_BXSUBR_U = GET_P()                                :(RETURN)
*
JIT_BLTR_F
         BLTR_F_JIT(R1, R2)
         JIT_BLTR_F = GET_P()                                  :(RETURN)
*
JIT_BLER_F
         BLER_F_JIT(R1, R2)
         JIT_BLER_F = GET_P()                                  :(RETURN)
*
JIT_BGTR_F
         BGTR_F_JIT(R1, R2)
         JIT_BGTR_F = GET_P()                                  :(RETURN)
*
JIT_BGER_F
         BGER_F_JIT(R1, R2)
         JIT_BGER_F = GET_P()                                  :(RETURN)
*
JIT_BEQR_F
         BEQR_F_JIT(R1, R2)
         JIT_BEQR_F = GET_P()                                  :(RETURN)
*
JIT_BNER_R
         BNER_R_JIT(R1, R2)
         JIT_BNER_R = GET_P()                                  :(RETURN)
*
JIT_BUNLTR_F
         BUNLTR_F_JIT(R1, R2)
         JIT_BUNLTR_F = GET_P()                                :(RETURN)
*
JIT_BUNLER_F
         BUNLER_F_JIT(R1, R2)
         JIT_BUNLER_F = GET_P()                                :(RETURN)
*
JIT_BUNEQR_F
         BUNEQR_F_JIT(R1, R2)
         JIT_BUNEQR_F = GET_P()                                :(RETURN)
*
JIT_BUNGER_F
         BUNGER_F_JIT(R1, R2)
         JIT_BUNGER_F = GET_P()                                :(RETURN)
*
JIT_BUNGTR_F
         BUNGTR_F_JIT(R1, R2)
         JIT_BUNGTR_F = GET_P()                                :(RETURN)
*
JIT_BLTGTR_F
         BLTGTR_F_JIT(R1, R2)
         JIT_BLTGTR_F = GET_P()                                :(RETURN)
*
JIT_BORDR_F
         BORDR_F_JIT(R1, R2)
         JIT_BORDR_F = GET_P()                                 :(RETURN)
*
JIT_BUNORDR_F
         BUNORDR_F_JIT(R1, R2)
         JIT_BUNORDR_F = GET_P()                               :(RETURN)
*
JIT_BLTR_D
         BLTR_D_JIT(R1, R2)
         JIT_BLTR_D = GET_P()                                  :(RETURN)
*
JIT_BLER_D
         BLER_D_JIT(R1, R2)
         JIT_BLER_D = GET_P()                                  :(RETURN)
*
JIT_BGTR_D
         BGTR_D_JIT(R1, R2)
         JIT_BGTR_D = GET_P()                                  :(RETURN)
*
JIT_BEQR_D
         BEQR_D_JIT(R1, R2)
         JIT_BEQR_D = GET_P()                                  :(RETURN)
*
JIT_BNER_D
         BNER_D_JIT(R1, R2)
         JIT_BNER_D = GET_P()                                  :(RETURN)
*
JIT_BUNLTR_D
         BUNLTR_D_JIT(R1, R2)
         JIT_BUNLTR_D = GET_P()                                :(RETURN)
*
JIT_BUNLER_D
         BUNLER_D_JIT(R1, R2)
         JIT_BUNLER_D = GET_P()                                :(RETURN)
*
JIT_BUNEQR_D
         BUNEQR_D_JIT(R1, R2)
         JIT_BUNEQR_D = GET_P()                                :(RETURN)
*
JIT_BUNGER_D
         BUNGER_D_JIT(R1, R2)
         JIT_BUNGER_D = GET_P()                                :(RETURN)
*
JIT_BUNGTR_D
         BUNGTR_D_JIT(R1, R2)
         JIT_BUNGTR_D = GET_P()                                :(RETURN)
*
JIT_BLTGTR_D
         BLTGTR_D_JIT(R1, R2)
         JIT_BLTGTR_D = GET_P()                                :(RETURN)
*
JIT_BORDR_D
         BORDR_D_JIT(R1, R2)
         JIT_BORDR_D = GET_P()                                 :(RETURN)
*
JIT_BUNORDR_D
         BUNORDR_D_JIT(R1, R2)
         JIT_BUNORDR_D = GET_P()                               :(RETURN)
*
JIT_ADDI SET_P(P)
         ADDI_JIT(R1, R2)                                      :(RETURN)
*
JIT_ADDCI
         SET_P(P)
         ADDCI_JIT(R1, R2)                                     :(RETURN)
*
JIT_ADDXI
         SET_P(P)
         ADDXI_JIT(R1, R2)                                     :(RETURN)
*
JIT_SUBI SET_P(P)
         SUBI_JIT(R1, R2)                                      :(RETURN)
*
JIT_SUBCI
         SET_P(P)
         SUBCI_JIT(R1, R2)                                     :(RETURN)
*
JIT_SUBXI
         SET_P(P)
         SUBXI_JIT(R1, R2)                                     :(RETURN)
*
JIT_MULI SET_P(P)
         MULI_JIT(R1, R2)                                      :(RETURN)
*
JIT_DIVI SET_P(P)
         DIVI_JIT(R1, R2)                                      :(RETURN)
*
JIT_DIVI_U
         SET_P(P)
         DIVI_U_JIT(R1, R2)                                    :(RETURN)
*
JIT_REMI SET_P(P)
         REMI_JIT(R1, R2)                                      :(RETURN)
*
JIT_REMI_U
         SET_P(P)
         REMI_U_JIT(R1, R2)                                    :(RETURN)
*
JIT_ANDI SET_P(P)
         ANDI_JIT(R1, R2)                                      :(RETURN)
*
JIT_ORI  SET_P(P)
         ORI_JIT(R1, R2)                                       :(RETURN)
*
JIT_XORI SET_P(P)
         XORI_JIT(R1, R2)                                      :(RETURN)
*
JIT_LSHI SET_P(P)
         LSHI_JIT(R1, R2)                                      :(RETURN)
*
JIT_RSHI SET_P(P)
         RSHI_JIT(R1, R2)                                      :(RETURN)
*
JIT_RSHI_U
         SET_P(P)
         RSHI_U_JIT(R1, R2)                                    :(RETURN)
*
JIT_LTI  SET_P(P)
         LTI_JIT(R1, R2)                                       :(RETURN)
*
JIT_LTI_U
         SET_P(P)
         LTI_U_JIT(R1, R2)                                     :(RETURN)
*
JIT_LEI  SET_P(P)
         LEI_JIT(R1, R2)                                       :(RETURN)
*
JIT_LEI_U
         SET_P(P)
         LEI_U_JIT(R1, R2)                                     :(RETURN)
*
JIT_GEI  SET_P(P)
         GEI_JIT(R1, R2)                                       :(RETURN)
*
JIT_GEI_U
         SET_P(P)
         GEI_U_JIT(R1, R2)                                     :(RETURN)
*
JIT_GTI  SET_P(P)
         GTI_JIT(R1, R2)                                       :(RETURN)
*
JIT_GTI_U
         SET_P(P)
         GTI_U_JIT(R1, R2)                                     :(RETURN)
*
JIT_EQI  SET_P(P)
         EQI_JIT(R1, R2)                                       :(RETURN)
*
JIT_NEI  SET_P(P)
         NEI_JIT(R1, R2)                                       :(RETURN)
*
JIT_LDXI_C
         SET_P(P)
         LDXI_C_JIT(R1, R2)                                    :(RETURN)
*
JIT_LDXI_UC
         SET_P(P)
         LDXI_UC_JIT(R1, R2)                                   :(RETURN)
*
JIT_LDXI_S
         SET_P(P)
         LDXI_S_JIT(R1, R2)                                    :(RETURN)
*
JIT_LDXI_US
         SET_P(P)
         LDXI_US_JIT(R1, R2)                                   :(RETURN)
*
JIT_LDXI_I
         SET_P(P)
         LDXI_I_JIT(R1, R2)                                    :(RETURN)
*
JIT_LDXI_UI
         SET_P(P)
         LDXI_UI_JIT(R1, R2)                                   :(RETURN)
*
JIT_LDXI_L
         SET_P(P)
         LDXI_L_JIT(R1, R2)                                    :(RETURN)
*
JIT_LDXI SET_P(P)
         LDXI_JIT(R1, R2)                                      :(RETURN)
*
JIT_LDXI_F
         SET_P(P)
         LDXI_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_LDXI_D
         SET_P(P)
         LDXI_D_JIT(R1, R2)                                    :(RETURN)
*
JIT_STXI_C
         SET_P(P)
         STXI_C_JIT(R1, R2)                                    :(RETURN)
*
JIT_STXI_S
         SET_P(P)
         STXI_S_JIT(R1, R2)                                    :(RETURN)
*
JIT_STXI_I
         SET_P(P)
         STXI_I_JIT(R1, R2)                                    :(RETURN)
*
JIT_STXI_L
         SET_P(P)
         STXI_L_JIT(R1, R2)                                    :(RETURN)
*
JIT_STXI
         SET_P(P)
         STXI_JIT(R1, R2)                                      :(RETURN)
*
JIT_STXI_F
         SET_P(P)
         STXI_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_STXI_D
         SET_P(P)
         STXI_D_JIT(R1, R2)                                    :(RETURN)
*
JIT_ADDI_F
         SET_F(F)
         ADDI_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_SUBI_F
         SET_F(F)
         SUBI_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_MULI_F
         SET_F(F)
         MULI_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_DIVI_F
         SET_F(F)
         DIVI_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_ADDI_D
         SET_D(D)
         ADDI_D_JIT(R1, R2)                                    :(RETURN)
*
JIT_SUBI_D
         SET_D(D)
         SUBI_D_JIT(R1, R2)                                    :(RETURN)
*
JIT_MULI_D
         SET_D(D)
         MULI_D_JIT(R1, R2)                                    :(RETURN)
*
JIT_DIVI_D
         SET_D(D)
         DIVI_D_JIT(R1, R2)                                    :(RETURN)
*
JIT_MOVR MOVR_JIT(R1, R2)                                      :(RETURN)
*
JIT_MOVR_F
         MOVR_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_MOVR_D
         MOVR_D_JIT(R1, R2)                                    :(RETURN)
*
JIT_HTONR
         HTONR_JIT(R1, R2)                                     :(RETURN)
*
JIT_NTOHR
         NTOHR_JIT(R1, R2)                                     :(RETURN)
*
JIT_COMR COMR_JIT(R1, R2)                                      :(RETURN)
*
JIT_NEGR NEGR_JIT(R1, R2)                                      :(RETURN)
*
JIT_NEGR_F
         NEGR_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_NEGR_D
         NEGR_D_JIT(R1, R2)                                    :(RETURN)
*
JIT_ABSR_F
         ABSR_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_ABSR_D
         ABSR_D_JIT(R1, R2)                                    :(RETURN)
JIT_SQRTR_F
         SQRTR_F_JIT(R1, R2)                                   :(RETURN)
*
JIT_SQRTR_D
         SQRTR_D_JIT(R1, R2)                                   :(RETURN)
*
JIT_EXTR_C
         EXTR_C_JIT(R1, R2)                                    :(RETURN)
*
JIT_EXTR_UC
         EXTR_UC_JIT(R1, R2)                                   :(RETURN)
*
JIT_EXTR_S
         EXTR_S_JIT(R1, R2)                                    :(RETURN)
*
JIT_EXTR_US
         EXTR_US_JIT(R1, R2)                                   :(RETURN)
*
JIT_EXTR_I
         EXTR_I_JIT(R1, R2)                                    :(RETURN)
*
JIT_EXTR_UI
         EXTR_UI_JIT(R1, R2)                                   :(RETURN)
*
JIT_EXTR_F
         EXTR_F_JIT(R1, R2)                                    :(RETURN)
*
JIT_EXTR_D_F
         EXTR_D_F_JIT(R1, R2)                                  :(RETURN)
*
JIT_EXTR_D
         EXTR_D_JIT(R1, R2)                                    :(RETURN)
*
JIT_EXTR_F_D
         EXTR_F_D_JIT(R1, R2)                                  :(RETURN)
*
JIT_TRUNCR_F_I
         TRUNCR_F_I_JIT(R1, R2)                                :(RETURN)
*
JIT_TRUNCR_F
         TRUNCR_F_JIT(R1, R2)                                  :(RETURN)
*
JIT_TRUNCR_F_L
         TRUNCR_F_L_JIT(R1, R2)                                :(RETURN)
*
JIT_TRUNCR_D_I
         TRUNCR_D_I_JIT(R1, R2)                                :(RETURN)
*
JIT_TRUNCR_D
         TRUNCR_D_JIT(R1, R2)                                  :(RETURN)
*
JIT_TRUNCR_D_L
         TRUNCR_D_L_JIT(R1, R2)                                :(RETURN)
*
JIT_LDR_C
         LDR_C_JIT(R1, R2)                                     :(RETURN)
*
JIT_LDR_UC
         LDR_UC_JIT(R1, R2)                                    :(RETURN)
*
JIT_LDR_S
         LDR_S_JIT(R1, R2)                                     :(RETURN)
*
JIT_LDR_US
         LDR_US_JIT(R1, R2)                                    :(RETURN)
*
JIT_LDR_I
         LDR_I_JIT(R1, R2)                                     :(RETURN)
*
JIT_LDR
         LDR_JIT(R1, R2)                                       :(RETURN)
*
JIT_LDR_UI
         LDR_UI_JIT(R1, R2)                                    :(RETURN)
*
JIT_LDR_L
         LDR_L_JIT(R1, R2)                                     :(RETURN)
*
JIT_LDR_F
         LDR_F_JIT(R1, R2)                                     :(RETURN)
*
JIT_LDR_D
         LDR_D_JIT(R1, R2)                                     :(RETURN)
*
JIT_STR_C
         STR_C_JIT(R1, R2)                                     :(RETURN)
*
JIT_STR_S
         STR_S_JIT(R1, R2)                                     :(RETURN)
*
JIT_STR_I
         STR_I_JIT(R1, R2)                                     :(RETURN)
*
JIT_STR  STR_JIT(R1, R2)                                       :(RETURN)
*
JIT_STR_L
         STR_L_JIT(R1, R2)                                     :(RETURN)
*
JIT_STR_F
         STR_F_JIT(R1, R2)                                     :(RETURN)
*
JIT_STR_D
         STR_D_JIT(R1, R2)                                     :(RETURN)
*
JIT_LDI_C
         SET_P(P)
         LDI_C_JIT(R)                                          :(RETURN)
*
JIT_LDI_UC
         SET_P(P)
         LDI_UC_JIT(R)                                         :(RETURN)
*
JIT_LDI_S
         SET_P(P)
         LDI_S_JIT(R)                                          :(RETURN)
*
JIT_LDI_US
         SET_P(P)
         LDI_US_JIT(R)                                         :(RETURN)
*
JIT_LDI_I
         SET_P(P)
         LDI_I_JIT(R)                                          :(RETURN)
*
JIT_LDI  SET_P(P)
         LDI_JIT(R)                                            :(RETURN)
*
JIT_LDI_UI
         SET_P(P)
         LDI_UI_JIT(R)                                         :(RETURN)
*
JIT_LDI_L
         SET_P(P)
         LDI_L_JIT(R)                                          :(RETURN)
*
JIT_LDI_F
         SET_P(P)
         LDI_F_JIT(R)                                          :(RETURN)
*
JIT_LDI_D
         SET_P(P)
         LDI_D_JIT(R)                                          :(RETURN)
*
JIT_PUSHARGI
         SET_P(P)
         PUSHARGI_JIT()                                        :(RETURN)
*
JIT_PUSHARGI_F
         SET_F(F)
         PUSHARGI_F_JIT()                                      :(RETURN)
*
JIT_PUSHARGI_D
         SET_D(D)
         PUSHARGI_D_JIT()                                      :(RETURN)
*
JIT_BLTI SET_P(P)
         BLTI_JIT(R)                                           :(RETURN)
*
JIT_BLTI_U
         SET_P(P)
         BLTI_U_JIT(R)                                         :(RETURN)
*
JIT_BLEI SET_P(P)
         BLEI_JIT(R)                                           :(RETURN)
*
JIT_BLEI_U
         SET_P(P)
         BLEI_U_JIT(R)                                         :(RETURN)
*
JIT_BEQI SET_P(P)
         BEQI_JIT(R)                                           :(RETURN)
*
JIT_BGEI SET_P(P)
         BGEI_JIT(R)                                           :(RETURN)
*
JIT_BGEI_U
         SET_P(P)
         BGEI_U_JIT(R)                                         :(RETURN)
*
JIT_BGTI SET_P(P)
         BGTI_JIT(R)                                           :(RETURN)
*
JIT_BGTI_U
         SET_P(P)
         BGTI_U_JIT(R)                                         :(RETURN)
*
JIT_BNEI SET_P(P)
         BNEI_JIT(R)                                           :(RETURN)
*
JIT_BMSI SET_P(P)
         BMSI_JIT(R)                                           :(RETURN)
*
JIT_BMCI SET_P(P)
         BMCI_JIT(R)                                           :(RETURN)
*
JIT_BOADDI
         SET_P(P)
         BOADDI_JIT(R)                                         :(RETURN)
*
JIT_BOADDI_U
         SET_P(P)
         BOADDI_U_JIT(R)                                       :(RETURN)
*
JIT_BXADDI
         SET_P(P)
         BXADDI_JIT(R)                                         :(RETURN)
*
JIT_BXADDI_U
         SET_P(P)
         BXADDI_U_JIT(R)                                       :(RETURN)
*
JIT_BOSUBI
         SET_P(P)
         BOSUBI_JIT(R)                                         :(RETURN)
*
JIT_BOSUBI_U
         SET_P(P)
         BOSUBI_U_JIT(R)                                       :(RETURN)
*
JIT_BXSUBI
         SET_P(P)
         BXSUBI_JIT(R)                                         :(RETURN)
*
JIT_BXSUBI_U
         SET_P(P)
         BXSUBI_U_JIT(R)                                       :(RETURN)
*
JIT_STI_C
         SET_P(P)
         STI_C_JIT(R)                                          :(RETURN)
*
JIT_STI_S
         SET_P(P)
         STI_S_JIT(R)                                          :(RETURN)
*
JIT_STI_I
         SET_P(P)
         STI_I_JIT(R)                                          :(RETURN)
*
JIT_STI  SET_P(P)
         STI_JIT(R)                                            :(RETURN)
*
JIT_STI_L
         SET_P(P)
         STI_L_JIT(R)                                          :(RETURN)
*
JIT_STI_F
         SET_P(P)
         STI_F_JIT(R)                                          :(RETURN)
*
JIT_STI_D
         SET_P(P)
         STI_D_JIT(R)                                          :(RETURN)
*
JIT_PUSHARGR
         PUSHARGR_JIT(R)                                       :(RETURN)
*
JIT_PUSHARGR_F
         PUSHARGR_F_JIT(R)                                     :(RETURN)
*
JIT_PUSHARGR_D
         PUSHARGR_D_JIT(R)                                     :(RETURN)
*
JIT_RETVAL_C
         RETVAL_C_JIT(R)                                       :(RETURN)
*
JIT_RETVAL_UC
         RETVAL_UC_JIT(R)                                      :(RETURN)
*
JIT_RETVAL_S
         RETVAL_S_JIT(R)                                       :(RETURN)
*
JIT_RETVAL_US
         RETVAL_US_JIT(R)                                      :(RETURN)
*
JIT_RETVAL_I
         RETVAL_I_JIT(R)                                       :(RETURN)
*
JIT_RETVAL
         RETVAL_JIT(R)                                         :(RETURN)
*
JIT_RETVAL_UI
         RETVAL_UI_JIT(R)                                      :(RETURN)
*
JIT_RETVAL_L
         RETVAL_L_JIT(R)                                       :(RETURN)
*
JIT_RETVAL_F
         RETVAL_F_JIT(R)                                       :(RETURN)
*
JIT_RETVAL_D
         RETVAL_D_JIT(R)                                       :(RETURN)
*
JIT_END  CODE('JIT_DEFINE')
*
* CE: .MSNOBOL4;
