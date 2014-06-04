-LINE 20 "DSERVE.lss"
-INCLUDE 'CHARS.INC'
-INCLUDE 'REPL.INC'
-INCLUDE 'CSNOBOL4.INC'
-INCLUDE 'HOST.INC'
-INCLUDE 'MAX.INC'
-INCLUDE 'DDT.INC'
-STITL DSERVE
-EJECT
-LINE 152 "DSERVE.lss"
*
************************************************************************
*                                                                      *
*         ######    #####   #######  ######   #     #  #######         *
*         #     #  #     #  #        #     #  #     #  #               *
*         #     #  #        #        #     #  #     #  #               *
*         #     #   #####   #####    ######   #     #  #####           *
*         #     #        #  #        #   #     #   #   #               *
*         #     #  #     #  #        #    #     # #    #               *
*         ######    #####   #######  #     #     #     #######         *
*                                                                      *
* DSERVE                     DDT SERVER                                *
*                                                                      *
************************************************************************
*
* DSERVE.lss
*
-LINE 29 "DSERVE.lss"
-PUBLIC DSERVE_INIT(), DSERVE()
-PUBLIC DSERVE_PORT, DSERVE_APPNAME
         DEFINE('DSERVE_INIT(APPNAME,PORT,KEY)')      :(DSERVE_INIT_END)
*
DSERVE_INIT
         DSERVE_KEY = KEY
         DSERVE_PORT = PORT
         DSERVE_APPNAME = APPNAME
*
         LT(CREATEPIPE())                                    :S(DSERVE9)
         DSERVE_P1_RFD = GETPIPEFD(0)
         DSERVE_P1_WFD = GETPIPEFD(1)
         LT(CREATEPIPE())                                    :S(DSERVE9)
         DSERVE_P2_RFD = GETPIPEFD(0)
         DSERVE_P2_WFD = GETPIPEFD(1)
         PID = FORK()                                        :F(DSERVE9)
         LT(PID)                                             :S(DSERVE9)
         EQ(PID)                                             :S(DSERVE2)
*
* PRIMORDIAL PROCESS - POLLS WITH DSERVE() WAITING FOR CONNECTION AND
* DEBUGGER ENTRY
*
         DSERVE_FDS = MALLOC(SIZEOF_FD_SET())
         DSERVE_TV = MALLOC(SIZEOF_TIMEVAL())                  :(RETURN)
*
DSERVE_INIT_END
*
         DEFINE('DSERVE()N,S')                             :(DSERVE_END)
DSERVE   NE(DDT_ACTIVE)                                        :(RETURN)
         SET_TIMEVAL(DSERVE_TV, 0, 0)
         FD_ZERO(DSERVE_FDS)
         FD_SET(DSERVE_P2_RFD, DSERVE_FDS)
         N = SELECT(DSERVE_P2_RFD + 1, DSERVE_FDS, 0, 0, DSERVE_TV)
         EQ(N)                                                :S(RETURN)
*
         OUTPUT(.DDT_T, 10, 'W', '/dev/fd/' DSERVE_P1_WFD)   :F(DSERVE9)
         INPUT(.DDT_R, 11,, '/dev/fd/' DSERVE_P2_RFD)        :F(DSERVE9)
*
* WAIT FOR MESSAGE FROM NET PROCESS
*
         S = DDT_R
         IDENT(S, 'DDT')                                     :S(DSERVE7)
         DDT_T = 'OPTION ' S ' NOT AVAILABLE'                  :(RETURN)
DSERVE7  DDT_T = NE(DDT_ACTIVE) 'APP ALREADY IN DDT'          :S(RETURN)
         DDT_USE_R = 1
         DSERVE = 'DDT'
         DDT()
                                                               :(RETURN)
*
* CONNECTION LISTENER PROCESS
*
DSERVE2  INPUT(.FROM_PRIMORDIAL, 12,, '/dev/fd/' DSERVE_P1_RFD)
+                                                            :F(DSERVE9)
         OUTPUT(.TO_PRIMORDIAL, 13, 'W', '/dev/fd/' DSERVE_P2_WFD)
+                                                            :F(DSERVE9)
*
DSERVE3  FDN = SERV_LISTEN('inet', 'stream', DSERVE_PORT)    :F(DSERVE9)
         INPUT(.NET, 9, 'UWT', '/dev/fd/' FDN)               :F(DSERVE9)
         OUTPUT(.NET, 9)                                     :F(DSERVE9)
         CRLF = CHARS_CR CHARS_LF
*
         NET = 'DSERVE ' DSERVE_APPNAME CRLF
         NET = CRLF
         NET = 'LOGIN REQUIRED: ' CRLF
         S = NET
         S = REPL(S, CRLF)
         S = TRIMB(S)
*
* LOGIN IS PLAINTEXT. THIS SHOULD ONLY BE USED OVER TELNET RUNNING ON
* THE SAME HOST AS THE APPLICATION BEING DEBUGGED. THERE IS NO USER
* NAME/PASSWORD -- JUST A SINGLE MAGIC WORD.
*
         IDENT(S, DSERVE_KEY)                                :S(DSERVE8)
         NET = 'BAD LOGIN' CRLF                                   :(END)
DSERVE8  NET = 'LOGIN CONFIRM' CRLF
*
* SEND MESSAGE TO PRIMORDIAL.
*
         TO_PRIMORDIAL = 'DDT'
*
* FORK TO TWO COPY LOOPS: PRIMORDIAL -> NET AND NET -> PRIMORDIAL
*
         PID = FORK()
         LT(PID)                                             :S(DSERVE9)
         EQ(PID)                                            :S(DSERVE12)
*
* PRIMORDIAL -> NET COPY PROCESS
*
DSERVE11 S = FROM_PRIMORDIAL                                     :F(END)
         NET = S CRLF                                        :(DSERVE11)
*
* NET -> PRIMORDIAL COPY PROCESS
*
DSERVE12 S = NET                                                 :F(END)
         S = REPL(S, CHARS_CR)
         S = REPL(S, CHARS_LF)
         TO_PRIMORDIAL = S                                   :(DSERVE12)
*
DSERVE9  TERMINAL = 'DSERVE: INTERNAL FAILURE'                    :(END)
*
DSERVE_END
*
* CE: .MSNOBOL4;
