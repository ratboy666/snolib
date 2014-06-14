-MODULE FCGI
-LINE 28 "FCGI.lss"
-INCLUDE 'BQ.INC'
-INCLUDE 'CSNOBOL4.INC'
-INCLUDE 'FFI.INC'
-INCLUDE 'JSON.INC'
-INCLUDE 'LOGIC.INC'
-INCLUDE 'TIME.INC'
-IN72
-LINE 305 "FCGI.lss"
-STITL FCGI
-EJECT
*
************************************************************************
*                                                                      *
*                    #######   #####    #####   ###                    *
*                    #        #     #  #     #   #                     *
*                    #        #        #         #                     *
*                    #####    #        #  ####   #                     *
*                    #        #        #     #   #                     *
*                    #        #     #  #     #   #                     *
*                    #         #####    #####   ###                    *
*                                                                      *
* FCGI                   FCGI SUPPORT FUNCTIONS                        *
*                                                                      *
************************************************************************
*
* FCGI.lss
*
-LINE 37 "FCGI.lss"
         FCGI_LOGUNIT = IO_FINDUNIT()
         OUTPUT(.FCGI_LOG, FCGI_LOGUNIT, 'W',
+               '|/usr/bin/logger -n localhost -t FCGI')
         STDIN_FILENO = 0
         FCGI_LISTENSOCK_FILENO = STDIN_FILENO
*
         FCGI_BEGIN_REQUEST     =  1
         FCGI_ABORT_REQUEST     =  2
         FCGI_END_REQUEST       =  3
         FCGI_PARAMS            =  4
         FCGI_STDIN             =  5
         FCGI_STDOUT            =  6
         FCGI_STDERR            =  7
         FCGI_DATA              =  8
         FCGI_GET_VALUES        =  9
         FCGI_GET_VALUES_RESULT = 10
         FCGI_UNKNOWN_TYPE      = 11
*
         FCGI_RESPONDER  = 1
         FCGI_AUTHORIZER = 2
         FCGI_FILTER     = 3
*
-PUBLIC FCGI_REQUEST_COMPLETE, FCGI_CANT_MPX_CONN, FCGI_OVERLOADED
-PUBLIC FCGI_UNKNOWN_ROLE
         FCGI_REQUEST_COMPLETE = 0
         FCGI_CANT_MPX_CONN    = 1
         FCGI_OVERLOADED       = 2
         FCGI_UNKNOWN_ROLE     = 3
*
* getpeername RETURNS PEER NAME FOR STDIN IF RUNNING UNDER FCGI. IT
* ACTUALLY RETURNS TRANSPORT END-POINT NOT CONNECTED. IF IT ISN'T A
* SOCKET AT ALL, DEFINITELY CGI CASE.
*
         PEER = BQ('/usr/bin/getpeername 2>&1')             :F(NOT_FCGI)
         PEER 'Socket operation on non-socket'              :S(NOT_FCGI)
*
         FCGI_LOG = 'FCGI'
*
* INFORM CGI THAT FAST CGI IS IN USE. DEFINE THE ACCEPT() FUNCTION.
* LISTEN() HAS ALREADY BEEN DONE IN THE WEB SERVER.
*
         USE_FCGI = 1
NOT_FCGI FCGI_LOG = IDENT(USER_FCGI) 'NORMAL CGI'
         FFI_ACCEPT = FFI_NEW('I', 'I,P,P')
         FFI_SET_CALLP(FFI_ACCEPT, DLSYM(0, 'accept'))
-PUBLIC FCGI_ACCEPT(), ACCEPT(), FCGI_SEND(), FCGI_SEND_ERR(),
-PUBLIC FCGI_END()
         DEFINE('FCGI_ACCEPT()')
         DEFINE('ACCEPT(SOCKET,P1,P2)')
         DEFINE('FCGI_NAMES(T,A)')
         DEFINE('FCGI_SEND(S)')
         DEFINE('FCGI_SEND_ERR(S)')
         DEFINE('FCGI_SEND_(D,S)B')
         DEFINE('FCGI_END(APP_STATUS,PROT_STATUS)S,B0,B1,B2,B3')
         DEFINE('FCGI_GET()')                               :(FCGI_END_)
*
ACCEPT   CLEAR_ERRNO()
         FFI_PAR_N_INTEGER(FFI_ACCEPT, 1, SOCKET)
         FFI_PAR_N_PTR(FFI_ACCEPT, 2, P1)
         FFI_PAR_N_PTR(FFI_ACCEPT, 3, P2)
         ACCEPT = FFI_CALL_INTEGER(FFI_ACCEPT)                 :(RETURN)
*
* IF THE DATA TO SEND IS 0...65535 BYTES, SEND IT. IF GREATER,
* SEND THE FIRST 65535, AND LOOP FOR THE REST
*
FCGI_SEND_
         LT(SIZE(S), 65536)                              :S(FCGI_SEND_2)
         S LEN(65535) . B REM . S
         FCGI_SEND_(D, B)                                  :(FCGI_SEND_)
FCGI_SEND_2
         FCGI_LOG = 'FCGI_SEND: '  D ' ' SIZE(S)
         S = CHAR(1) CHAR(D)
+            CHAR(FCGI_REQUESTID / 256) CHAR(REMDR(FCGI_REQUESTID, 256))
+            CHAR(SIZE(S) / 256) CHAR(REMDR(SIZE(S), 256))
+            CHAR(0) CHAR(0) S
         FCGI_OUT = S                                          :(RETURN)
*
FCGI_SEND
         FCGI_SEND_(FCGI_STDOUT, S)                            :(RETURN)
*
FCGI_SEND_ERR
         FCGI_SEND_(FCGI_STDERR, S)                            :(RETURN)
*
FCGI_END FCGI_LOG = 'FCGI_END: ' APP_STATUS ' ' PROT_STATUS
         B3 = APP_STATUS / 16777216
         APP_STATUS = REMDR(APP_STATUS, 16777216)
         B2 = APP_STATUS / 65536
         APP_STATUS = REMDR(APP_STATUS, 65536)
         B1 = APP_STATUS / 256
         B0 = REMDR(APP_STATUS, 256)
         S = CHAR(B3) CHAR(B2) CHAR(B1) CHAR(B0) CHAR(PROT_STATUS)
+            CHAR(0) CHAR(0) CHAR(0)
         B1 = FCGI_REQUESTID / 256
         B0 = REMDR(FCGI_REQUESTID, 256)
         S = CHAR(1) CHAR(FCGI_END_REQUEST) CHAR(B1) CHAR(B0)
+            CHAR(0) CHAR(8) CHAR(0) CHAR(0) S
         FCGI_OUT = S                                          :(RETURN)
*
FCGI_GET VERSION = ORD(FCGI)
         FCGI_LOG = DIFFER(VERSION, 1) 'VERSION <> 1'            :S(END)
         TYPE = ORD(FCGI)
         REQUESTID = ORD(FCGI) * 256
         REQUESTID = REQUESTID + ORD(FCGI)
         CONTENTLENGTH = ORD(FCGI) * 256
         CONTENTLENGTH = CONTENTLENGTH + ORD(FCGI)
         PADDINGLENGTH = ORD(FCGI)
         RESERVED = ORD(FCGI)
*
* WE COULD READ THIS IN ONE GULP, AND AVOID CONVERTING TO ARRAY AND
* THEN BACK INTO STRING.
*
         FCGI_GET = NE(CONTENTLENGTH) ARRAY(CONTENTLENGTH)
         I = 1
FCGI_4   GT(I, CONTENTLENGTH)                                 :S(FCGI_5)
         FCGI_GET<I> = ORD(FCGI)
         I = I + 1                                             :(FCGI_4)
FCGI_5   I = 1
FCGI_6   GT(I, PADDINGLENGTH)                                 :S(RETURN)
         S = FCGI
         I = I + 1                                             :(FCGI_6)
*
* EXTRACT NAMES FROM ARRAY. TWO LENGTH FIELDS, EITHER 1 OR 4 BYTES,
* THEN THE ACTUAL NAME AND DATA.
*
FCGI_NAMES
         I = 1
FCGI_NAMES_7
         NL = A<I>
         EQ(AND(NL, 128))                               :S(FCGI_NAMES_2)
         NL = AND(A<I>, 127) * 16777216 +
+             A<I + 1> * 65536 +
+             A<I + 2> * 256 +
+             A<I + 3>
         I = I + 3
FCGI_NAMES_2
         I = I + 1
         DL = A<I>
         EQ(AND(NL, 128))                               :S(FCGI_NAMES_3)
         DL = AND(A<I>, 127) * 16777216 +
+             A<I + 1> * 65536 +
+             A<I + 2> * 256 +
+             A<I + 3>
         I = I + 3
FCGI_NAMES_3
         I = I + 1
         NM =
         DA =
FCGI_NAMES_4
         EQ(NL)                                         :S(FCGI_NAMES_5)
         NM = NM CHAR(A<I>)
         I = I + 1
         NL = NL - 1                                     :(FCGI_NAMES_4)
FCGI_NAMES_5
         EQ(DL)                                         :S(FCGI_NAMES_6)
         DA = DA CHAR(A<I>)
         I = I + 1
         DL = DL - 1                                     :(FCGI_NAMES_5)
FCGI_NAMES_6
         T<NM> = DA
         A<I>                                  :F(RETURN)S(FCGI_NAMES_7)
*
* MAIN FCGI FUNCTION
*
FCGI_ACCEPT
         IDENT(USE_FCGI)                                      :S(RETURN)
         FCGI_LOG = 'FCGI_ACCEPT: WAITING'
         SOCKET = ACCEPT(FCGI_LISTENSOCK_FILENO, 0, 0)
         FCGI_LOG = 'AFTER ACCEPT'
         GE(SOCKET)                                           :S(FCGI_2)
*
* ON ERROR IN ACCEPT, WE DISPLAY ERRNO AND EXIT THE PROCESS
*
         ERRNO = GET_ERRNO()
         FCGI_LOG = 'ACCEPT: ERRNO = ' ERRNO                      :(END)
*
* READ AND DIGEST PACKETS FROM SOCKET. CLEAN UP OLD INSTANCE I/O
* (FCGI IS GOING TO STAY AROUND EXECUTING REQUESTS). tHEN
* OPEN THE SOCKET PASSED TO US BY ACCEPT().
*
FCGI_2   IDENT(FCGI_INSTANCE_UNIT)                            :S(FCGI_8)
         DETACH(.FCGI)
         DETACH(.FCGI_OUT)
         ENDFILE(FCGI_INSTANCE_UNIT)
FCGI_8   FCGI_LOG = 'SOCKET = ' SOCKET
         FCGI_INSTANCE_UNIT = IO_FINDUNIT()
         FCGI_LOG = 'UNIT = ' FCGI_INSTANCE_UNIT
         INPUT(.FCGI, FCGI_INSTANCE_UNIT, 'U,B,1', '/dev/fd/' SOCKET)
         OUTPUT(.FCGI_OUT, FCGI_INSTANCE_UNIT, 'W,B,1')
*
         FCGI_ENV = TABLE()
         FCGI_IN =
         FCGI_REQUESTID =
*
* PACKET LOOP
*
FCGI_PLOOP
         CONTENT = FCGI_GET()
         FCGI_REQUESTID = IDENT(FCGI_REQUESTID) REQUESTID
         EQ(REQUESTID, FCGI_REQUESTID)                  :S(FCGI_PLOOP_2)
         FCGI_LOG = 'ONLY SINGLE REQUESTID SUPPORTED'             :(END)
*
* WE DO NOT MULTIPLEX REQUESTID, NEED TO SET INDICATION OF THAT
* IN FCGI_GET().
*
FCGI_PLOOP_2
         EQ(TYPE, FCGI_BEGIN_REQUEST)                        :F(FCGI_10)
         FCGI_LOG = 'FCGI_BEGIN_REQUEST'
         FCGI_ROLE = CONTENT<1> * 256 + CONTENT<2>
         FCGI_LOG = NE(FCGI_ROLE, FCGI_RESPONDER)
+           'ROLE NOT RESPONDER'                                 :S(END)
         FCGI_FLAGS = CONTENT<3>
         FCGI_REQUESTID = REQUESTID                        :(FCGI_PLOOP)
*
FCGI_10  EQ(TYPE, FCGI_PARAMS)                               :F(FCGI_11)
         FCGI_LOG = 'FCGI_PARAMS'
         IDENT(CONTENT)                                   :S(FCGI_PLOOP)
         FCGI_NAMES(FCGI_ENV, CONTENT)                     :(FCGI_PLOOP)
*
FCGI_11  EQ(TYPE, FCGI_STDIN)                                :F(FCGI_12)
         FCGI_LOG = 'FCGI_STDIN'
         IDENT(CONTENT)                                      :S(FCGI_GO)
         I = 1
* FIXME: WE READ IT AS A STRING, CONVERT TO ARRAY OF SMALL INTEGERS,
* AND THEN MAKE IT A STRING AGAIN. THIS IS DONE BECAUSE WE ARE GOING
* TO DO PACKET DISASSEMBLY, AND THAT IS ARGUABLY EASIER IN THE SMALL
* INTEGER SPACE. STILL, IT SHOULD BE FIXED.
FCGI_13  FCGI_IN = FCGI_IN CHAR(CONTENT<I>)               :F(FCGI_PLOOP)
         I = I + 1                                            :(FCGI_13)
*
FCGI_12
         FCGI_LOG = 'BAD TYPE: ' TYPE                             :(END)
*
FCGI_GO
         FCGI_LOG = 'FCGI_GO'
*
* HERE WE ILLUSTRATE AN INTERESTING TECHNIQUE. SINCE JSON_ENCODE WILL
* TRAVERSE TABLES AND ARRAYS, WE CAN USE IT TO EXAMINE VARIABLES BY
* SENDING THE JSON ENCODING TO A LOG FILE.
*
         FCGI_LOG = 'FCGI_ENV: '
         FCGI_LOG = JSON_ENCODE(FCGI_ENV)
*
* BUG ALERT: IF THIS IS NOT DONE, GETTIMEOFDAY(), GMTIME() ETC.
* FAULT ON THE SECOND PASS THROUGH FCGI. HAPPENS WITH CSNOBOL4 1.5
*
* TRY TO ISOLATE THIS FURTHER.
*
         T = GETTIMEOFDAY()
                                                               :(RETURN)
*
FCGI_END_
*
* CE: .F.MSNOBOL4;
