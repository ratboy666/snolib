-MODULE CSNOBOL4
-LINE 24 "CSNOBOL4.lss"
-INCLUDE 'FFI.INC'
-INCLUDE 'P64.INC'
-STITL CSNOBOL4
-LINE 613 "CSNOBOL4.lss"
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
         format = 'format.c'
-LINE 396 "CSNOBOL4.lss"
-LINE 397 "CSNOBOL4.lss"
-LINE 398 "CSNOBOL4.lss"
-LINE 399 "CSNOBOL4.lss"
-LINE 400 "CSNOBOL4.lss"
-LINE 401 "CSNOBOL4.lss"
-LINE 412 "CSNOBOL4.lss"
-PUBLIC FORK()
         LOAD('FORK()INTEGER')
-LINE 420 "CSNOBOL4.lss"
-PUBLIC WAIT()
         LOAD('WAIT()INTEGER')
-LINE 441 "CSNOBOL4.lss"
-PUBLIC SPRINTF()
         LOAD('SPRINTF(STRING,)STRING')
-LINE 503 "CSNOBOL4.lss"
-PUBLIC FTN_FORMAT(), CREATEPIPE(), GETPIPEFD(), GET_ERRNO()
-PUBLIC CLEAR_ERRNO(), WAITPID(), GET_STATUS(), SIZEOF_TIMEVAL()
-PUBLIC SET_TIMEVAL(), SIZEOF_FD_SET, FD_ZERO(), FD_CLR(), FD_SET()
-PUBLIC FD_ISSET()
         LOAD('FTN_FORMAT(STRING,STRING)STRING', 'format.so')
         LOAD('CREATEPIPE()INTEGER', 'format.so')
         LOAD('GETPIPEFD(INTEGER)INTEGER', 'format.so')
         LOAD('GET_ERRNO()INTEGER', 'format.so')
         LOAD('CLEAR_ERRNO()', 'format.so')
         LOAD('WAITPID_(INTEGER,INTEGER)INTEGER', 'format.so')
         LOAD('GET_STATUS()INTEGER', 'format.so')
         LOAD('SIZEOF_TIMEVAL()INTEGER', 'format.so')
         LOAD('SET_TIMEVAL_()', 'format.so')
         LOAD('SIZEOF_FD_SET()INTEGER', 'format.so')
         LOAD('FD_ZERO_()', 'format.so')
         LOAD('FD_CLR_(INTEGER)', 'format.so')
         LOAD('FD_SET_(INTEGER)', 'format.so')
         LOAD('FD_ISSET_(INTEGER)INTEGER', 'format.so')
         DEFINE('FD_ZERO(FD_SET)')
         DEFINE('FD_CLR(FD,FD_SET)')
         DEFINE('FD_ISSET(FD,FD_SET)')
         DEFINE('FD_SET(FD,FD_SET)')
         DEFINE('SET_TIMEVAL(TV,SEC,USEC)')
-LINE 539 "CSNOBOL4.lss"
-PUBLIC CLOSE(), SELECT(), IO_GETFP(), FILENO()
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

SET_TIMEVAL
         SET_P(TV)
         SET_TIMEVAL_(SEC, USEC)                               :(RETURN)

FD_CLR   SET_P(FD_SET)
         FD_CLR_(FD)                                           :(RETURN)
*
FD_ISSET SET_P(FD_SET)
         FD_ISSET = FD_ISSET_(FD)                              :(RETURN)
*
FD_SET   SET_P(FD_SET)
         FD_SET_(FD)                                           :(RETURN)
*
FD_ZERO  SET_P(FD_SET)
         FD_ZERO_()                                            :(RETURN)
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
