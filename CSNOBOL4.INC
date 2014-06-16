-MODULE CSNOBOL4
-LINE 24 "CSNOBOL4.lss"
-INCLUDE 'FFI.INC'
-INCLUDE 'P64.INC'
-IN72
-LINE 316 "CSNOBOL4.lss"
-STITL CSNOBOL4
-EJECT
*
************************************************************************
*                                                                      *
*  #####    #####   #     #  #######  ######   #######  #        #   # *
* #     #  #     #  ##    #  #     #  #     #  #     #  #        #   # *
* #        #        # #   #  #     #  #     #  #     #  #        #   # *
* #         #####   #  #  #  #     #  ######   #     #  #        ##### *
* #              #  #   # #  #     #  #     #  #     #  #            # *
* #     #  #     #  #    ##  #     #  #     #  #     #  #            # *
*  #####    #####   #     #  #######  ######   #######  #######      # *
*                                                                      *
* CSNOBOL4         FUNCTIONS SPECIFIC TO CSNOBOL4                      *
*                                                                      *
************************************************************************
*
* CSNOBOL4.lss
*
-LINE 29 "CSNOBOL4.lss"
-LINE 30 "CSNOBOL4.lss"
-LINE 31 "CSNOBOL4.lss"
-LINE 32 "CSNOBOL4.lss"
-LINE 33 "CSNOBOL4.lss"
-LINE 34 "CSNOBOL4.lss"
-LINE 35 "CSNOBOL4.lss"
-LINE 38 "CSNOBOL4.lss"
         csnobol4 = 'csnobol4.c'
-LINE 164 "CSNOBOL4.lss"
-LINE 165 "CSNOBOL4.lss"
-LINE 166 "CSNOBOL4.lss"
-LINE 167 "CSNOBOL4.lss"
-LINE 168 "CSNOBOL4.lss"
-LINE 169 "CSNOBOL4.lss"
-LINE 180 "CSNOBOL4.lss"
-PUBLIC FORK()
         LOAD('FORK()INTEGER')
-LINE 188 "CSNOBOL4.lss"
-PUBLIC WAIT()
         LOAD('WAIT()INTEGER')
-LINE 209 "CSNOBOL4.lss"
-PUBLIC SPRINTF()
         LOAD('SPRINTF(STRING,)STRING')
-LINE 214 "CSNOBOL4.lss"
-PUBLIC CREATEPIPE(), GETPIPEFD(), GET_ERRNO()
-PUBLIC CLEAR_ERRNO(), WAITPID(), GET_STATUS(), SIZEOF_TIMEVAL()
-PUBLIC SET_TIMEVAL(), SIZEOF_FD_SET(), FD_ZERO(), FD_CLR(), FD_SET()
-PUBLIC FD_ISSET()
*
         LOAD('CREATEPIPE()INTEGER', 'csnobol4.so')
         LOAD('GETPIPEFD(INTEGER)INTEGER', 'csnobol4.so')
         LOAD('GET_ERRNO()INTEGER', 'csnobol4.so')
         LOAD('CLEAR_ERRNO()', 'csnobol4.so')
         LOAD('WAITPID_(INTEGER,INTEGER)INTEGER', 'csnobol4.so')
         LOAD('GET_STATUS()INTEGER', 'csnobol4.so')
         LOAD('SIZEOF_TIMEVAL()INTEGER', 'csnobol4.so')
         LOAD('SET_TIMEVAL(INTEGER,INTEGER,INTEGER)', 'csnobol4.so')
         LOAD('SIZEOF_FD_SET()INTEGER', 'csnobol4.so')
         LOAD('FD_ZERO_(INTEGER)', 'csnobol4.so')
         LOAD('FD_CLR_(INTEGER,INTEGER)', 'csnobol4.so')
         LOAD('FD_SET_(INTEGER,INTEGER)', 'csnobol4.so')
         LOAD('FD_ISSET_(INTEGER,INTEGER)INTEGER', 'csnobol4.so')
         DEFINE('FD_ZERO(FD_SET)')
         DEFINE('FD_CLR(FD,FD_SET)')
         DEFINE('FD_ISSET(FD,FD_SET)')
         DEFINE('FD_SET(FD,FD_SET)')
-LINE 249 "CSNOBOL4.lss"
-PUBLIC CLOSE(), SELECT(), IO_GETFP(), FILENO()
*
         CLOSE_FFI = FFI_NEW('I', 'I')
         FFI_SET_CALLP(CLOSE_FFI, DLSYM(0, 'close'))
         DEFINE('CLOSE(FD)')
         SELECT_FFI = FFI_NEW('I', 'I,P,P,P,P')
         FFI_SET_CALLP(SELECT_FFI, DLSYM(0, 'select'))
         DEFINE('SELECT(NFDS,READFDS,WRITEFDS,EXCEPTFDS,TIMEOUT)')
         IO_GETFP_FFI = FFI_NEW('P', 'I')
         FFI_SET_CALLP(IO_GETFP_FFI, DLSYM(0, 'io_getfp'))
         FILENO_FFI = FFI_NEW('I', 'P')
         FFI_SET_CALLP(FILENO_FFI, DLSYM(0, 'fileno'))
         DEFINE('IO_GETFP(UNIT)')
         DEFINE('FILENO(FP)')                            :(CSNOBOL4_END)
*
CLOSE    FFI_PAR_N_INTEGER(CLOSE_FFI, 1, FD)
         CLOSE = FFI_CALL_INTEGER(CLOSE_FFI)                   :(RETURN)
*
FD_CLR   FD_CLR_(FD, FD_SET)                                   :(RETURN)
*
FD_ISSET FD_ISSET = FD_ISSET_(FD, FD_SET)                      :(RETURN)
*
FD_SET   FD_SET_(FD, FD_SET)                                   :(RETURN)
*
FD_ZERO  FD_ZERO_(FD_SET)                                      :(RETURN)
*
IO_GETFP FFI_PAR_N_INTEGER(IO_GETFP_FFI, 1, UNIT)
         IO_GETFP = FFI_CALL_PTR(IO_GETFP_FFI)                 :(RETURN)
*
FILENO   FFI_PAR_N_PTR(FILENO_FFI, 1, FP)
         FILENO = FFI_CALL_INTEGER(FILENO_FFI)                 :(RETURN)
*
SELECT   FFI_PAR_N_INTEGER(SELECT_FFI, 1, NFDS)
         FFI_PAR_N_PTR(SELECT_FFI, 2, READFDS)
         FFI_PAR_N_PTR(SELECT_FFI, 3, WRITEFDS)
         FFI_PAR_N_PTR(SELECT_FFI, 4, EXCEPTFDS)
         FFI_PAR_N_PTR(SELECT_FFI, 5, TIMEOUT)
         SELECT = FFI_CALL_INTEGER(SELECT_FFI)                 :(RETURN)
*
CSNOBOL4_END
*
* CE: .MSNOBOL4;
