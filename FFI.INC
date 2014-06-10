-LINE 17 "FFI.lss"
-STITL FFI
-EJECT
-LINE 647 "FFI.lss"
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
-LINE 20 "FFI.lss"
-MODULE FFI
-CASE 1
-PLUSOPS 1
-LINE 28 "FFI.lss"
-LINE 29 "FFI.lss"
-LINE 30 "FFI.lss"
-LINE 31 "FFI.lss"
-LINE 32 "FFI.lss"
-LINE 33 "FFI.lss"
-LINE 34 "FFI.lss"
-LINE 37 "FFI.lss"
         ffi = 'ffi.c'
-LINE 534 "FFI.lss"
-LINE 535 "FFI.lss"
-LINE 536 "FFI.lss"
-LINE 537 "FFI.lss"
-LINE 538 "FFI.lss"
-LINE 539 "FFI.lss"
-LINE 549 "FFI.lss"
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
-LINE 584 "FFI.lss"
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
