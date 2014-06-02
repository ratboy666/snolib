-STITL HOST
-EJECT
*
-LINE 147 "HOST.lss"
************************************************************************
*                                                                      *
*                 #     #  #######   #####   #######                   *
*                 #     #  #     #  #     #     #                      *
*                 #     #  #     #  #           #                      *
*                 #######  #     #   #####      #                      *
*                 #     #  #     #        #     #                      *
*                 #     #  #     #  #     #     #                      *
*                 #     #  #######   #####      #                      *
*                                                                      *
* HOST               HOST() FUNCTION CODES                             *
*                                                                      *
************************************************************************
*
* HOST.lss
*
-LINE 6 "HOST.lss"
HOST
-LINE 10 "HOST.lss"
*
* MACRO SPITBOL
*
-PUBLIC HOST_SYSINFO, HOST_PARAMS
* ARCH:OS:SNOBOL_VERSION
         HOST_SYSINFO = ''
* ARGUMENT FROM -u OR ENTIRE COMMAND LINE
         HOST_PARAMS = 0
*
* CATSPAW SPITBOL
*
-PUBLIC HOST_SYSCMD, HOST_ARGN, HOST_FIRSTARG, HOST_GETENV
* EXEC ARG AS SHELL COMMAND, RETURN STATUS
         HOST_SYSCMD = 1
* N'TH TOKEN ON COMMAND LINE (INTEGER)
         HOST_ARGN = 2
* INDEX OF 1ST USER COMMAND LINE ARG TOKEN
         HOST_FIRSTARG = 3
* RETURNS ENVIRONMENT VARIABLE, OR FAILS
         HOST_GETENV = 4
*
-PUBLIC HOST_SNOLIB_DIR
* DEFAULT SNOLIB DIR (-INCLUDE, LOAD())
         HOST_SNOLIB_DIR = 2200
*
-PUBLIC HOST_CC, HOST_COPT
* C COMPILER USED TO BUILD CSNOBOL4
         HOST_CC = 2202
* C OPTIMIZER FLAGS USED TO BUILD CSNOBOL4
         HOST_COPT = 2203
*
-PUBLIC HOST_DL_EXT, HOST_DL_CFLAGS, HOST_DL_LD,HOST_DL_LDFLAGS
* DYNAMIC LOADABLE LIBRARY EXTENSION
         HOST_DL_EXT = 2208
* C COMPILER FLAGS FOR DYNAMIC LOADABLES
         HOST_DL_CFLAGS = 2209
* DYNAMIC LOADABLE FILE LOAD COMMAND
         HOST_DL_LD = 2210
* DYNAMIC LOADABLE FILE LOAD SWITCHES
         HOST_DL_LDFLAGS = 2211
*
-PUBLIC HOST_DIR_SEP, HOST_PATH_SEP
* DIRECTORY SEPARATOR CHAR (MAY BE EMPTY)
         HOST_DIR_SEP = 2212
* PATH SEPARATOR CHARACTER
         HOST_PATH_SEP = 2213
*
* CSNOBOL4 1.5
*
-PUBLIC HOST_DEF_SNOPATH, HOST_INCUDE_DIR
* DEFAULT LIBRARY SEARCH PATH
         HOST_DEF_SNOPATH = 2214
* PATH FOR C HEADERS
         HOST_INCLUDE_DIR = 2215
*
-PUBLIC HOST_INTEGER_BITS, HOST_REAL_BITS, HOST_POINTER_BITS
-PUBLIC HOST_LONG_BITS, HOST_DESCR_BITS, HOST_SPEC_BITS, HOST_CHAR_BITS
* NUMBER OF BITS FOR SNOBOL4 INTEGER TYPE
         HOST_INTEGER_BITS = 2300
* NUMBER OF BITS FOR SNOBOL4 REAL TYPE
         HOST_REAL_BITS = 2301
* NUMBER OF BITS FOR C POINTER TYPE
         HOST_POINTER_BITS = 2302
* NUMBER OF BITS FOR C LONG TYPE
         HOST_LONG_BITS = 2303
* NUMBER OF BITS FOR SIL 'DESCRIPTOR' TYPE
         HOST_DESCR_BITS = 2304
* NUMBER OF BITS FOR SIL 'SPECIFIER' TYPE
         HOST_SPEC_BITS = 2305
* NUMBER OF BITS FOR C CHAR TYPE
         HOST_CHAR_BITS = 2306
*
-PUBLIC HOST_DYNAMIC_SIZE, HOST_PMSTACK_SIZE, HOST_ISTACK_SIZE
* SIZE OF 'DYNAMIC' STORAGE IN DESCRIPTORS
         HOST_DYNAMIC_SIZE = 2400
* SIZE OF PATTERN MATCH STACK IN DESCRS
         HOST_PMSTACK_SIZE = 2401
* SIZE OF INTERPRETER STACK IN DESCRIPTORS
         HOST_ISTACK_SIZE = 2402
*
    CODE('HOST')
*
HOST_END
*
* CE: .MSNOBOL4;
