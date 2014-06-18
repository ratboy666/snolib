-MODULE DSERVE
-LINE 48 "DSERVE.lss"
-INCLUDE 'CHARS.INC'
-INCLUDE 'REPL.INC'
-INCLUDE 'CSNOBOL4.INC'
-INCLUDE 'TRIMB.INC'
-INCLUDE 'P64.INC'
-INCLUDE 'UNIX.INC'
-INCLUDE 'DDT.INC'
-IN72
-LINE 252 "DSERVE.lss"
-STITL DSERVE
-EJECT
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
* DSERVE                  DDT TELNET SERVER                            *
*                                                                      *
************************************************************************
*
* DSERVE.lss
*
-LINE 58 "DSERVE.lss"
-PUBLIC DSERVE_INIT(), DSERVE()
-PUBLIC DSERVE_PORT, DSERVE_APPNAME
*
         DEFINE('DSERVE_INIT(APPNAME,PORT,KEY,INTR)') :(DSERVE_INIT_END)
*
DSERVE_INIT
         DSERVE_KEY = KEY
         DSERVE_PORT = PORT
         DSERVE_APPNAME = APPNAME
         DSERVE_INTR = INTR
*
         DSERVE_PID = GETPID()
         P1 = PIPE()                                         :F(DSERVE9)
         DSERVE_P1_RFD = P1<1>
         DSERVE_P1_WFD = P1<2>
         P2 = PIPE()                                         :F(DSERVE9)
         DSERVE_P2_RFD = P2<1>
         DSERVE_P2_WFD = P2<2>
         PID = FORK()                                        :F(DSERVE9)
         LT(PID)                                             :S(DSERVE9)
         EQ(PID)                                             :S(DSERVE2)
*
* PRIMORDIAL PROCESS - POLLS WITH DSERVE() WAITING FOR CONNECTION AND
* DEBUGGER ENTRY
*
* NEEDS FD SET AND TIMEVAL FOR SELECT
*
         DSERVE_FDS = NEW_FD_SET()
         DSERVE_TV = NEW_TIMEVAL()
         IDENT(DSERVE_INTR)                                   :S(RETURN)
*
         &ERRLIMIT = 1
         SETEXIT('DSERVE_TRAP')                                :(RETURN)
*
DSERVE_INIT_END
*
         DEFINE('DSERVE()N,S')                             :(DSERVE_END)
*
* IF DDT IS ALREADY ACTIVE, WE ARE DEBUGGING THROUGH A DSERVE() POLL,
* JUST RETURN. IF DSERVE_APPNAME IS NULL, RETURN, DSERVE HAS NOT
* BEEN SET UP CORRECTLY YET.
*
DSERVE   NE(DDT_ACTIVE)                                       :S(RETURN)
         IDENT(DSERVE_APPNAME)                                :S(RETURN)
*
* SEE IF THERE IS INPUT AVAILABLE FROM THE NET. USE SELECT() TO POLL
* THE READ FILE DESCRIPTOR, WITH A TIMEOUT OF 0 (NO WAIT)
*
         SET_TIMEVAL(DSERVE_TV, 0, 0)
         FD_ZERO(DSERVE_FDS)
         FD_SET(DSERVE_P2_RFD, DSERVE_FDS)
         N = SELECT(DSERVE_P2_RFD + 1, DSERVE_FDS, 0, 0, DSERVE_TV)
         EQ(N)                                                :S(RETURN)
*
* WE HAVE DATA ON THE READ FD. CREATE I/O CHANNELS TO TELNET I/O
* PROCESSES.
*
         OUTPUT(.DDT_T, 10, 'W', '/dev/fd/' DSERVE_P1_WFD)   :F(DSERVE9)
         INPUT(.DDT_R, 11,, '/dev/fd/' DSERVE_P2_RFD)        :F(DSERVE9)
*
* READ MESSAGE FROM NET PROCESS. WE HAVE A MESSAGE TO BE READ
* (BUT IT MAY NOT BE COMPLETE YET). WE RELY ON NORMAL I/O MECHANISM
* TO DELIVER COMPLETE MESSAGE LINE.
*
         S = DDT_R
         IDENT(S, 'DDT')                                     :S(DSERVE7)
         DSERVE = S                                            :(RETURN)
DSERVE7  DDT_T = NE(DDT_ACTIVE) 'APP ALREADY IN DDT'          :S(RETURN)
         DDT_USE_R = 1
         DSERVE = 'DDT'
*
* THE MESSAGE IS 'DDT' WHICH MEANS ENTER DEBUGGER. THE DEBUGGER IS
* NOT YET ACTIVE. WHEN DSERVE() RETURNS, IT WILL BE UNDER DDT CONTROL.
* WE SET DDT_USE_R TO 1 TO INFORM DDT OF THE I/O NEEDED (READLINE
* CANNOT BE USED).
*
         DDT(DSERVE_APPNAME)
                                                               :(RETURN)
*
* SETEXIT() TRAP TO ENTER DDT -- NEED DDT() ENTRY THAT DOES ONE STEP
* COMMAND.
*
DSERVE_TRAP
         OUTPUT(.DDT_T, 10, 'W', '/dev/fd/' DSERVE_P1_WFD)   :F(DSERVE9)
         INPUT(.DDT_R, 11,, '/dev/fd/' DSERVE_P2_RFD)        :F(DSERVE9)
         S = DDT_R
         IDENT(S, 'DDT')                                    :S(DSERVET2)
         DSERVE = S                                          :(DSERVET3)
DSERVET2 DDT_T = NE(DDT_ACTIVE) 'APP ALREADY IN DDT'        :S(DSERVET3)
         DDT_USE_R = 1
         DSERVE = 'DDT'
         DDT(DSERVE_APPNAME)
                                                            :(SCONTINUE)
DSERVET3 SETEXIT('DSERVE_TRAP')
         &ERRLIMIT = 1                                      :(SCONTINUE)
*
* CONNECTION LISTENER PROCESS
*
* CREATE I/O CHANNELS TO PRIMORDIAL PROCESS. THE PRIMORDIAL PROCESS
* WILL POLL WAITING FOR A MESSAGE TO BE WRITTEN TO TO_PRIMORDIAL.
*
DSERVE2  INPUT(.FROM_PRIMORDIAL, 12,, '/dev/fd/' DSERVE_P1_RFD)
+                                                            :F(DSERVE9)
         OUTPUT(.TO_PRIMORDIAL, 13, 'W', '/dev/fd/' DSERVE_P2_WFD)
+                                                            :F(DSERVE9)
*
* WAIT FOR A CONNECTION ON DSERVE_PORT
*
DSERVE3  FDN = SERV_LISTEN('inet', 'stream', DSERVE_PORT)    :F(DSERVE9)
         INPUT(.NET, 9, 'UWT', '/dev/fd/' FDN)               :F(DSERVE9)
         OUTPUT(.NET, 9)                                     :F(DSERVE9)
         CRLF = CHARS_CR CHARS_LF
*
* WE HAVE A CONNECTION. DISPLAY SIGNON, AND REQUEST LOGIN. THE LOGIN
* IS A SIMPLE STRING PASSED AS DSERVE_KEY
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
DSERVE8  NET = 'LOGIN CONFIRMED' CRLF
         NET = 'REDIRECT TO /dev/fd/' DSERVE_P1_WFD ' TO SEND OUTPUT '
+              'TO TELNET USING X (EG ls)' CRLF
*
* THE CORRECT KEY WAS SUPPLIED. SEND MESSAGE TO PRIMORDIAL.
*
         TO_PRIMORDIAL = 'DDT'
*
* SIGNAL TO ENTER DDT
*
         KILL(DIFFER(DSERVE_INTR) DSERVE_PID, 2)
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
