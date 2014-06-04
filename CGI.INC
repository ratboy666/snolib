-LINE 52 "CGI.lss"
-USES CRACK()
-WEAK USE_FCGI, FCGI_ENV, FCGI_IN, FCGI_REQUEST_COMPLETE
-WEAK FCGI_SEND(), FCGI_END()
-INCLUDE 'SCOOP.INC'
-INCLUDE 'COOKIE.INC'
-INCLUDE 'HOST.INC'
-INCLUDE 'CRACK.INC'
-INCLUDE 'SEQ.INC'
-INCLUDE 'HTMLESC.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'UNIQUE.INC'
-INCLUDE 'JSON.INC'
-STITL CGI
-EJECT
-LINE 574 "CGI.lss"
*
************************************************************************
*                                                                      *
*                                                                      *
*                         #####    #####   ###                         *
*                        #     #  #     #   #                          *
*                        #        #         #                          *
*                        #        #  ####   #                          *
*                        #        #     #   #                          *
*                        #     #  #     #   #                          *
*                         #####    #####   ###                         *
*                                                                      *
* CGI                    CGI SUPPORT FUNCTIONS                         *
*                                                                      *
************************************************************************
*
* CGI.lss
*
-LINE 68 "CGI.lss"
-PUBLIC CLASS:CGI_CLASS
         CGI_CLASS = SEND(CLASS, 'NEW_CLASS', 'CGI_CLASS')
         DEFINE('CGI_INIT()A,C')
-PUBLIC CGI_CLASS:'INIT'
         SEND(CGI_CLASS, 'ADD_METHOD', 'INIT', 'CGI_INIT')
-PUBLIC CGI_CLASS:'GET_COOKIE_JAR'
         SEND(CGI_CLASS, 'ADD_METHOD', 'GET_COOKIE_JAR', CODE(
+           ' SEND = |.COOKIE_JAR :(RETURN)'))
-PUBLIC CGI_CLASS:'GET_HEADER'
         SEND(CGI_CLASS, 'ADD_METHOD', 'GET_HEADER', CODE(
+           ' SEND = |.HEADER :(RETURN)'))
         DEFINE('CGI_SEND()S')
-PUBLIC CGI_CLASS:'SEND'
         SEND(CGI_CLASS, 'ADD_METHOD', 'SEND', 'CGI_SEND')
-PUBLIC CGI_CLASS:'GET_LOG'
         SEND(CGI_CLASS, 'ADD_METHOD', 'GET_LOG', CODE(
+           ' SEND = |.LOG :(RETURN)'))
-PUBLIC CGI_CLASS:'GET_CONTENT'
         SEND(CGI_CLASS, 'ADD_METHOD', 'GET_CONTENT', CODE(
+           ' SEND = |.CONTENT :(RETURN)'))
-PUBLIC CGI_CLASS:'SET_CONTENT'
         SEND(CGI_CLASS, 'ADD_METHOD', 'SET_CONTENT', CODE(
+           ' |.CONTENT = A1 :(RETURN)'))
         DEFINE('CGI_CLOSE()A')
-PUBLIC CGI_CLASS:'CLOSE'
         SEND(CGI_CLASS, 'ADD_METHOD', 'CLOSE', 'CGI_CLOSE')
-PUBLIC CGI_CLASS:'GET_ENV'
         SEND(CGI_CLASS, 'ADD_METHOD', 'GET_ENV', CODE(
+           ' SEND = |.ENV :(RETURN)'))
-PUBLIC CGI_CLASS:'GET_QUERY'
         SEND(CGI_CLASS, 'ADD_METHOD', 'GET_QUERY', CODE(
+           ' SEND = |.QUERY :(RETURN)'))
*
                                                       :(CGI_OBJECT_END)
*
* CLOSE CGI OBJECT
*
CGI_CLOSE
         ENDFILE(|.OUT_UNIT)
         DETACH(|.OUT)
         ENDFILE(|.LOG_UNIT)
         DETACH(|.LOG)                                         :(RETURN)
*
* INITIALIZE CGI OBJECT
*
CGI_INIT CGI_INIT = SUPER('INIT')
*
* CREATE LOG CHANNEL
*
         |.LOG_UNIT = IO_FINDUNIT()                          :F(FRETURN)
         |.LOG = UNIQUE()
*
* WITH ALL THE CHANGES GOING TO SYSTEMD, LOGGING APPEARS TO HAVE
* SUFFERED. SPECIFICALLY, IF THE LOGGING IS ONLY FORWARDED TO
* RSYSLOG, LOGGER LOCAL DOESN'T WORK. WE ENABLE RSYSLOG TO LISTEN TO
* THE NETWORK, AND THEN LOGGER CAN LOG TO LOCALHOST. STRANGE, AND
* PROBABLY NOT SUITABLE FOR PRODUCTION.
*
* IF USING SYSTEMD LOGGER, DON'T USE -n localhost
*
         OUTPUT(|.LOG, |.LOG_UNIT, 'W',
+               '|/usr/bin/logger -n localhost -t CGI')      :F(FRETURN)
*+              '|/usr/bin/logger -t CGI')                   :F(FRETURN)
*
* CREATE OUT CHANNEL
*
         |.OUT_UNIT = IO_FINDUNIT()                          :F(FRETURN)
         |.OUT = UNIQUE()
         OUTPUT(|.OUT, |.OUT_UNIT, 'B', '/dev/stdout')       :F(FRETURN)
*
* COLLECT ENVIRONMENT VARIABLES INTO INSTANCE VARIABLE ENV. WE ONLY
* GATHER UP "KNOWN" ENVIRONMENT VARIABLES.
*
         |.ENV = DIFFER(USE_FCGI) FCGI_ENV                 :S(CGI_ENV_2)
*
         |.ENV = TABLE(38)
         A = %('AUTH_TYPE,CONTENT_LENGTH,CONTENT_TYPE,'
+              'CONTEXT_DOCUMENT_ROOT,CONTEXT_PREFIX,DOCUMENT_ROOT,'
+              'GATEWAY_INTERFACE,HTTP_ACCEPT,HTTP_ACCEPT_CHARSET,'
+              'HTTP_ACCEPT_ENCODING,HTTP_ACCEPT_LANGUAGE,'
+              'HTTP_CACHE_CONTROL,HTTP_CONNECTION,HTTP_COOKIE,'
+              'HTTP_HOST,HTTP_REFERER,HTTP_USER_AGENT,LIB_PATH,PATH,'
+              'PATH_INFO,PATH_TRANSLATED,QUERY_STRING,REMOTE_ADDR,'
+              'REMOTE_HOST,REMOTE_IDENT,REMOTE_PORT,REQUEST_METHOD,'
+              'REQUEST_SCHEME,REQUEST_URI,SCRIPT_FILENAME,SCRIPT_NAME,'
+              'SERVER_ADDR,SERVER_ADMIN,SERVER_NAME,SERVER_PORT,'
+              'SERVER_PROTOCOL,SERVER_SIGNATURE,SERVER_SOFTWARE')
         SEQ(' (|.ENV)<A<I>> = HOST(HOST_GETENV, A<I>); A<I> ', .I)
CGI_ENV_2
         $|.LOG = 'FCGI_ENV IN CGI'
         $|.LOG = JSON_ENCODE(FCGI_ENV)
         $|.LOG = 'QUERY_STRING: ' (|.ENV)<'QUERY_STRING'>
*
* FOR POST METHOD, READ (|.ENV)<'CONTENT_LENGTH'>. READ THAT NUMBER OF
* BYTES, AND ONLY THAT NUMBER. NOTE THAT THIS MAY BE VERY LARGE. THIS
* MAY FAIL DUE TO MEMORY EXHAUSTION. WE KNOW THAT WE CAN READ A LARGE
* NUMBER OF BYTES, BUT I HAVE TO DETERMINE THE LIMIT.
*
* FOR FCGI, USE FCGI_IN. FIXME: SHOULD TEST CONTENT_LENGTH
*
         (|.ENV)<'QUERY_STRING'> = DIFFER(USE_FCGI) VDIFFER(FCGI_IN)
+                                                         :S(CGI_INIT_3)
         T3 = (|.ENV)<'CONTENT_LENGTH'>
         IDENT(T3)                                        :S(CGI_INIT_3)
         (INTEGER(T3) GT(T3))                             :F(CGI_INIT_3)
         T1 = IO_FINDUNIT()                                  :F(FRETURN)
         INPUT('T2', T1, 'B,' T3, '/dev/stdin')              :F(FRETURN)
         (|.ENV)<'QUERY_STRING'> = T2
         ENDFILE(T1)
         DETACH('T2')
CGI_INIT_3
*
* PARSE QUERY_STRING INTO QUERY TABLE. HASH() IS USED TO PARSE
* QUERY_STRING, BREAKING INTO NAME=VALUE SEPARATED BY &. EACH VALUE IS
* PROCESSED WITH URL_DECODE().
*
* MULTI-VALUE FIELDS ARE SEPARATED BY 0. USED BY CHECKBOXES
*
         |.QUERY = HASH((|.ENV)<'QUERY_STRING'>, '=', '&',,,,
+                        'URL_DECODE', CHARS_NUL)
         $|.LOG = 'QUERY TABLE'
         $|.LOG = JSON_ENCODE(|.QUERY)
*
* PARSE HTTP_COOKIE INTO A COOKIE JAR. THERE MAY NOT BE ANY COOKIES,
* IN WHICH CASE WE CREATE AN EMPTY COOKIE JAR. THE VALUES OF THE
* COOKIES ARE NOT VALIDATED. HASH() PARSES THE COOKIE STRING. AFTER
* THE TABLE IS GENERATED, IT IS CONVERTED TO AN ARRAY. SEQ() ADDS
* EACH ELEMENT INTO THE COOKIE JAR.
*
         |.COOKIE_JAR = NEW_COOKIE_JAR()
         A = HASH((|.ENV)<'HTTP_COOKIE'>, '=', ';',,,
+                  'COOKIE_FIX_NAME', 'URL_DECODE')
         A = CONVERT(A, 'ARRAY')                          :F(CGI_INIT_2)
         SEQ(' PUT_COOKIE_IN_JAR(|.COOKIE_JAR,'
+                               'A<I,1>, NEW_COOKIE(A<I,2>)) ', .I)
CGI_INIT_2
*
* INITIALIZE HEADER. THE HEADER IS A TABLE() WITH AT LEAST CONTENT_TYPE
* ENTRY.
*
         |.HEADER = #'CONTENT_TYPE=TEXT/HTML,CHARSET='
*
* INITIALIZE CONTENT
*
         |.CONTENT =
*
* WE NEED ROUTING IMPLEMENTED.
*
* WE NEED TO DO FURTHER PROCESSING ON THE FOLLOWING CGI ENVIRONMENT
* VARIABLES.
*
* <ISINDEX> value1+value2+..
* HTTP_ACCEPT
*   ='TEXT/HTML,APPLICATION/XHTML+XML,APPLICATION/XML;Q=0.9,*/*;Q=0.8'
* HTTP_ACCEPT_ENCODING='GZIP, DEFLATE'
* HTTP_ACCEPT_LANGUAGE='EN-US,EN;Q=0.5'
*
                                                               :(RETURN)
*
* OUTPUT THE HEADER AND CONTENT
*
CGI_SEND
*
* FIRST, OUTPUT THE CONTENT-TYPE. IF CHARSET HAS BEEN SPECIFIED,
* ADD THIS TO THE CONTENT-TYPE.
*
         S = 'Content-type: ' (|.HEADER)<'CONTENT_TYPE'>
         S = S '; charset=' VDIFFER((|.HEADER)<'CHARSET'>)
         S = S CHARS_CR CHARS_NL
*
* GENERATE THE COOKIE STRING AND OUTPUT IF WE HAVE COOKIES TO SEND.
*
         S = S VDIFFER(COOKIE_STRING(|.COOKIE_JAR))
*
* THE HEADER FINISHES WITH A CR/LF
*
         S = S CHARS_CR CHARS_NL
         $|.OUT = IDENT(USE_FCGI) S
         DIFFER(USE_FCGI) FCGI_SEND(S)
*
* SEND CONTENT
*
         $|.OUT = IDENT(USE_FCGI) |.CONTENT
         DIFFER(USE_FCGI) FCGI_SEND(|.CONTENT)
         DIFFER(USE_FCGI) FCGI_SEND('')
         DIFFER(USE_FCGI) FCGI_END(0, FCGI_REQUEST_COMPLETE)
                                                               :(RETURN)
*
CGI_OBJECT_END
*
*
* CE: .F.MSNOBOL4;
