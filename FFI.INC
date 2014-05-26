-LINE 18 "FFI.lss"
-INCLUDE 'P64.INC'
-STITL FFI
-EJECT
-LINE 684 "FFI.lss"
*
************************************************************************
*                                                                      *
*                         #######  #######  ###                        *
*                         #        #         #                         *
*                         #        #         #                         *
*                         #####    #####     #                         *
*                         #        #         #                         *
*                         #        #         #                         *
*                         #        #        ###                        *
*                                                                      *
* FFI                  FOREIGN FUNCTION INTERFACE                      *
*                                                                      *
************************************************************************
*
* FFI.lss
*
-LINE 22 "FFI.lss"
-CASE 1
-PLUSOPS 1
-LINE 29 "FFI.lss"
-LINE 30 "FFI.lss"
-LINE 31 "FFI.lss"
-LINE 32 "FFI.lss"
-LINE 33 "FFI.lss"
-LINE 34 "FFI.lss"
-LINE 35 "FFI.lss"
-LINE 38 "FFI.lss"
         ffi = 'ffi.c'
-LINE 530 "FFI.lss"
-LINE 531 "FFI.lss"
-LINE 532 "FFI.lss"
-LINE 533 "FFI.lss"
-LINE 534 "FFI.lss"
-LINE 535 "FFI.lss"
-LINE 536 "FFI.lss"
-LINE 540 "FFI.lss"
-LINE 541 "FFI.lss"
-LINE 546 "FFI.lss"
         LOAD('FREE_FFI()', 'ffi.so')
         LOAD('CLEAR_FFI()', 'ffi.so')
         LOAD('NEW_FFI(STRING,STRING)', 'ffi.so')
         LOAD('PAR_N_NEEDFREE(INTEGER)', 'ffi.so')
         LOAD('SET_PAR_N_INTEGER(INTEGER,INTEGER)', 'ffi.so')
         LOAD('SET_PAR_N_REAL(INTEGER,REAL)', 'ffi.so')
         LOAD('SET_PAR_N_STRING(INTEGER,STRING)', 'ffi.so')
         LOAD('SET_PAR_N_P(INTEGER)', 'ffi.so')
         LOAD('SET_PAR_N_F(INTEGER)', 'ffi.so')
         LOAD('SET_PAR_N_D(INTEGER)', 'ffi.so')
         LOAD('SET_PAR_N_LD(INTEGER)', 'ffi.so')
         LOAD('SET_CALLP()', 'ffi.so')
         LOAD('CALL_FFI()', 'ffi.so')
         LOAD('CALL_INTEGER_FFI()INTEGER', 'ffi.so')
         LOAD('CALL_REAL_FFI()REAL', 'ffi.so')
         LOAD('CALL_STRING_FFI()STRING', 'ffi.so')
*
         RTLD_LAZY   = 1
         RTLD_NOW    = 2
         RTLD_GLOBAL = 256
         RTLD_LOCAL  = 0
*
         LOAD('DLOPEN_FFI(STRING,INTEGER)', 'ffi.so')
         LOAD('DLERROR_FFI()STRING', 'ffi.so')
         LOAD('DLSYM_FFI(STRING)', 'ffi.so')
         LOAD('DLCLOSE_FFI()INTEGER', 'ffi.so')
*
-LINE 581 "FFI.lss"
         DEFINE('DLOPEN(S,I)')
         DEFINE('DLERROR()')
         DEFINE('DLSYM(H,S)')
         DEFINE('DLCLOSE(H)')
*
         DEFINE('FFI_NEW(RS,PS)')
         DEFINE('FFI_FREE(FFI)')
         DEFINE('FFI_PAR_N_INTEGER(FFI,N,I)')
         DEFINE('FFI_PAR_N_REAL(FFI,N,R)')
         DEFINE('FFI_PAR_N_STRING(FFI,N,S)')
         DEFINE('FFI_PAR_N_PTR(FFI,N,P)')
         DEFINE('FFI_SET_CALLP(FFI,PROC)')
         DEFINE('FFI_CALL_VOID(FFI)')
         DEFINE('FFI_CALL_INTEGER(FFI)')
         DEFINE('FFI_CALL_REAL(FFI)')
         DEFINE('FFI_CALL_STRING(FFI)')
         DEFINE('FFI_CALL_PTR(FFI)')                          :(FFI_END)
*
DLOPEN   DLOPEN_FFI(S, I)
         DLOPEN = GET_P()                                      :(RETURN)
*
DLERROR  DLERROR = DLERROR_FFI()                               :(RETURN)
*
DLSYM    SET_P(H)
         DLSYM_FFI(S)
         DLSYM = GET_P()                                       :(RETURN)
*
DLCLOSE  SET_P(H)
         DLCLOSE = DLCLOSE_FFI()                               :(RETURN)
*
FFI_NEW  NEW_FFI(RS, PS)                                     :F(FRETURN)
         FFI_NEW = GET_P()                                     :(RETURN)
*
FFI_FREE SET_P(FFI)
         FREE_FFI()                                            :(RETURN)
*
FFI_PAR_N_INTEGER
         SET_P(FFI)
         SET_PAR_N_INTEGER(N, I)                    :S(RETURN)F(FRETURN)
*
FFI_PAR_N_REAL
         SET_P(FFI)
         SET_PAR_N_REAL(N, R)                       :S(RETURN)F(FRETURN)
*
FFI_PAR_N_STRING
         SET_P(FFI)
         SET_PAR_N_STRING(N, S)                     :S(RETURN)F(FRETURN)
*
FFI_PAR_N_PTR
         SET_P(FFI)
         P_TO_P2()
         SET_P(P)
         SET_PAR_N_P(N)                             :S(RETURN)F(FRETURN)
*
FFI_SET_CALLP
         SET_P(FFI)
         P_TO_P2()
         SET_P(PROC)
         SET_CALLP()                                           :(RETURN)
*
FFI_CALL_VOID
         SET_P(FFI)
         CALL_FFI()
         CLEAR_FFI()                                           :(RETURN)
*
FFI_CALL_INTEGER
         SET_P(FFI)
         FFI_CALL_INTEGER = CALL_INTEGER_FFI()
         CLEAR_FFI()                                           :(RETURN)
*
FFI_CALL_REAL
         SET_P(FFI)
         FFI_CALL_REAL = CALL_REAL_FFI()
         CLEAR_FFI()                                           :(RETURN)
*
FFI_CALL_STRING
         SET_P(FFI)
         FFI_CALL_STRING = CALL_STRING_FFI()
         CLEAR_FFI()                                           :(RETURN)
*
FFI_CALL_PTR
         SET_P(FFI)
         CALL_FFI()
         FFI_CALL_PTR = GET_P()
         SET_P(FFI)
         CLEAR_FFI()                                           :(RETURN)
*
FFI_END
*
* CE: .F.MSNOBOL4;
