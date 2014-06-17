-MODULE CSNOBOL4
-LINE 15 "CSNOBOL4.lss"
-INCLUDE 'FFI.INC'
-IN72
-LINE 81 "CSNOBOL4.lss"
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
-LINE 27 "CSNOBOL4.lss"
-PUBLIC SPRINTF()
*
         LOAD('SPRINTF(STRING,)STRING')
-LINE 42 "CSNOBOL4.lss"
*
-PUBLIC IO_GETFP()
*
         IO_GETFP_FFI = FFI_NEW('P', 'I')
         FFI_SET_CALLP(IO_GETFP_FFI, DLSYM(0, 'io_getfp'))
         DEFINE('IO_GETFP(UNIT)')                        :(CSNOBOL4_END)
*
IO_GETFP FFI_PAR_N_INTEGER(IO_GETFP_FFI, 1, UNIT)
         IO_GETFP = FFI_CALL_PTR(IO_GETFP_FFI)                 :(RETURN)
*
CSNOBOL4_END
*
* CE: .MSNOBOL4;
