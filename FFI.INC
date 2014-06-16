-MODULE FFI
-CASE 1
-PLUSOPS 1
-LINE 641 "FFI.lss"
-LINE 17 "FFI.lss"
-IN72
-STITL FFI
-EJECT
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
-LINE 23 "FFI.lss"
-LINE 24 "FFI.lss"
-LINE 25 "FFI.lss"
-LINE 26 "FFI.lss"
-LINE 27 "FFI.lss"
-LINE 28 "FFI.lss"
-LINE 31 "FFI.lss"
         ffi = 'ffi.c'
-LINE 528 "FFI.lss"
-LINE 529 "FFI.lss"
-LINE 530 "FFI.lss"
-LINE 531 "FFI.lss"
-LINE 532 "FFI.lss"
-LINE 533 "FFI.lss"
-LINE 543 "FFI.lss"
         LOAD('FFI_FREE(INTEGER)', 'ffi.so')
         LOAD('FFI_CLEAR(INTEGER)', 'ffi.so')
         LOAD('FFI_NEW(STRING,STRING)INTEGER', 'ffi.so')
         LOAD('FFI_PAR_N_NEEDFREE(INTEGER,INTEGER)', 'ffi.so')
         LOAD('FFI_PAR_N_INTEGER(INTEGER,INTEGER,INTEGER)', 'ffi.so')
         LOAD('FFI_PAR_N_PTR(INTEGER,INTEGER,INTEGER)', 'ffi.so')
         LOAD('FFI_PAR_N_REAL(INTEGER,INTEGER,REAL)', 'ffi.so')
         LOAD('FFI_PAR_N_STRING(INTEGER,INTEGER,STRING)', 'ffi.so')
         LOAD('FFI_PAR_N_P(INTEGER,INTEGER,INTEGER)', 'ffi.so')
         LOAD('FFI_PAR_N_F(INTEGER,INTEGER,REAL)', 'ffi.so')
         LOAD('FFI_PAR_N_D(INTEGER,INTEGER,REAL)', 'ffi.so')
         LOAD('FFI_PAR_N_LD(INTEGER,INTEGER,REAL)', 'ffi.so')
         LOAD('FFI_SET_CALLP(INTEGER,INTEGER)', 'ffi.so')
         LOAD('FFI_RESULTP(INTEGER)INTEGER', 'ffi.so')
         LOAD('CALL_FFI(INTEGER)', 'ffi.so')
         LOAD('CALL_INTEGER_FFI(INTEGER)INTEGER', 'ffi.so')
         LOAD('CALL_PTR_FFI(INTEGER)INTEGER', 'ffi.so')
         LOAD('CALL_REAL_FFI(INTEGER)REAL', 'ffi.so')
         LOAD('CALL_STRING_FFI(INTEGER)STRING', 'ffi.so')
*
         RTLD_LAZY   = 1
         RTLD_NOW    = 2
         RTLD_GLOBAL = 256
         RTLD_LOCAL  = 0
*
         LOAD('DLOPEN_(STRING,INTEGER)INTEGER', 'ffi.so')
         LOAD('DLERROR_()STRING', 'ffi.so')
         LOAD('DLSYM_(INTEGER,STRING)', 'ffi.so')
         LOAD('DLCLOSE_(INTEGER)INTEGER', 'ffi.so')
*
-LINE 578 "FFI.lss"
-PUBLIC DLOPEN(), DLERROR(), DLSYM(), DLCLOSE()
*
         DEFINE('DLOPEN(S,I)')
         DEFINE('DLERROR()')
         DEFINE('DLSYM(H,S)')
         DEFINE('DLCLOSE(H)')
*
-PUBLIC FFI_NEW(), FFI_FREE(), FFI_CLEAR(), FFI_PAR_N_NEEDFREE()
-PUBLIC FFI_PAR_N_INTEGER(), FFI_PAR_N_PTR(), FFI_PAR_N_REAL()
-PUBLIC FFI_PAR_N_STRING(),  FFI_SET_CALLP()
-PUBLIC FFI_CALL_VOID(), FFI_CALL_INTEGER(), FFI_CALL_REAL()
-PUBLIC FFI_CALL_STRING(), FFI_CALL_PTR(), CALL_FFI(), FFI_RESULTP()
*
         DEFINE('FFI_CALL_INTEGER(FFI)')
         DEFINE('FFI_CALL_REAL(FFI)')
         DEFINE('FFI_CALL_STRING(FFI)')
         DEFINE('FFI_CALL_PTR(FFI)')
         DEFINE('FFI_CALL_VOID(FFI)')                         :(FFI_END)
*
DLOPEN   DLOPEN = DLOPEN_(S, I)                                :(RETURN)
*
DLERROR  DLERROR = DLERROR_()                                  :(RETURN)
*
DLSYM    DLSYM = DLSYM_(H, S)                                  :(RETURN)
*
DLCLOSE  DLCLOSE = DLCLOSE_(H)                                 :(RETURN)
*
FFI_CALL_VOID
         CALL_FFI(FFI)
         FFI_CLEAR(FFI)                                        :(RETURN)
*
FFI_CALL_INTEGER
         FFI_CALL_INTEGER = CALL_INTEGER_FFI(FFI)
         FFI_CLEAR(FFI)                                        :(RETURN)
*
FFI_CALL_REAL
         FFI_CALL_REAL = CALL_REAL_FFI(FFI)
         FFI_CLEAR(FFI)                                        :(RETURN)
*
FFI_CALL_STRING
         FFI_CALL_STRING = CALL_STRING_FFI(FFI)
         FFI_CLEAR(FFI)                                        :(RETURN)
*
FFI_CALL_PTR
         FFI_CALL_PTR = CALL_PTR_FFI(FFI)
         FFI_CLEAR(FFI)                                        :(RETURN)
*
FFI_END
*
* CE: .F.MSNOBOL4;
