-LINE 78 "SESSION.lss"
-INCLUDE 'BQ.INC'
-INCLUDE 'NDBM.INC'
-INCLUDE 'SEQ.INC'
-INCLUDE 'CRACK.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'TIME.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'REPL.INC'
-INCLUDE 'CSNOBOL4.INC'
-STITL SESSION
-EJECT
-LINE 225 "SESSION.lss"
*
************************************************************************
*                                                                      *
*       #####   #######   #####    #####   ###  #######  #     #       *
*      #     #  #        #     #  #     #   #   #     #  ##    #       *
*      #        #        #        #         #   #     #  # #   #       *
*       #####   #####     #####    #####    #   #     #  #  #  #       *
*            #  #              #        #   #   #     #  #   # #       *
*      #     #  #        #     #  #     #   #   #     #  #    ##       *
*       #####   #######   #####    #####   ###  #######  #     #       *
*                                                                      *
* SESSION               SESSION SUPPORT FOR CGI                        *
*                                                                      *
************************************************************************
*
* SESSION.lss
*
-LINE 90 "SESSION.lss"
         DEFINE('SESSION_CREATE(EXPIRE_TIME)')
         DEFINE('SESSION_DELETE(SESSION)')
         DEFINE('SESSION_TOUCH(SESSION)')
         DEFINE('SESSION_PERSIST(SESSION)FILE,HANDLE,A,I')
         DEFINE('SESSION_LOAD(UUID)FILE,HANDLE,KEY,DATA,I')
         DEFINE('SESSION_EXPIRE()SESSION,TIME,UUID,L,I,S,P')
*
         SESSION_PERSIST_DIR = '/var/lib/SESSION/'
                                                          :(SESSION_END)
*
* CREATE NEW SESSION. GENERATE UUID FOR SESSION. DEFAULT SESSION
* EXPIRATION TO 10 MINUTES (UNLESS SPECIFIED).
*
SESSION_CREATE
         SESSION_CREATE = TABLE()
         SESSION_CREATE<'UUID'> = BQ('/usr/bin/uuid -v1')    :F(FRETURN)
         EXPIRE_TIME = IDENT(EXPIRE_TIME) 600
         SESSION_CREATE<'EXPIRE_TIME'> = EXPIRE_TIME           :(RETURN)
*
* TOUCH THE SESSION; SETS THE 'EXPIRE' TIME FOR NOW + EXPIRE_TIME.
*
SESSION_TOUCH
         IDENT(SESSION)                                      :S(FRETURN)
         SESSION<'EXPIRE'> = TV_SEC(GETTIMEOFDAY()) +
+                               SESSION<'EXPIRE_TIME'>        :S(RETURN)
*
* PERSIST SESSION TO DISK. SCALAR VARIABLES ONLY. ARRAYS AND TABLES
* ARE NOT PERSISTED (ONLY AS THEY PRINT).
*
SESSION_PERSIST
         FILE = SESSION_PERSIST_DIR 'session_' SESSION<'UUID'>
         SESSION_DELETE(SESSION)
         SESSION_TOUCH(SESSION)                              :F(FRETURN)
         A = CONVERT(SESSION, 'ARRAY')                       :F(FRETURN)
         HANDLE = DBM_OPEN(FILE, 'CW', '0660')               :F(FRETURN)
         SEQ(' DBM_STORE('
+                 'HANDLE, A<I, 1>, VDIFFER(A<I, 2>), DBM_INSERT) ', .I)
         A<I>                                                :S(FRETURN)
         DBM_CLOSE(HANDLE)                          :S(RETURN)F(FRETURN)
*
* DELETE SESSION
*
SESSION_DELETE
         DELETE(SESSION_PERSIST_DIR 'session_' SESSION<'UUID'> '.db')
+                                                              :(RETURN)
*
* LOAD SESSION GIVEN UUID. USUALLY, THE UUID COMES FROM A COOKIE.
*
SESSION_LOAD
         UUID = REPL(UUID, ' ', '')
         UUID = REPL(UUID, CHARS_TAB, '')
         UUID = REPLACE(UUID, &UCASE, &LCASE)
         UUID POS(0) ANY('"' "'") REM . UUID
         UUID POS(0) SPAN(&DIGITS 'abcdef-') . UUID
*
         SESSION_LOAD = TABLE()
         FILE = SESSION_PERSIST_DIR 'session_' UUID
         HANDLE = DBM_OPEN(FILE, 'R')                        :F(FRETURN)
         KEY = DBM_FIRSTKEY(HANDLE)                    :F(SESSION_LOAD2)
         SEQ(' DATA = DBM_FETCH(HANDLE, KEY);'
+            ' SESSION_LOAD<KEY> = DATA;'
+            ' KEY = DBM_NEXTKEY(HANDLE) ', .I)
         DBM_CLOSE(HANDLE)                                   :F(FRETURN)
         IDENT(UUID, SESSION_LOAD<'UUID'>)          :S(RETURN)F(FRETURN)
SESSION_LOAD2
         DBM_CLOSE(HANDLE)                                    :(FRETURN)
*
* REMOVE EXPIRED SESSIONS FROM DISK.
*
SESSION_EXPIRE
         L = BQ('ls ' SESSION_PERSIST_DIR 'session_*.db 2>/dev/null')
+                                                             :F(RETURN)
         TIME = TV_SEC(GETTIMEOFDAY())
         L = CRACK(L, ' ')
         P = SESSION_PERSIST_DIR 'session_' BREAK('.') . UUID '.db'
SESSION_EXPIRE2
         I = I + 1
         S = L<I>                                             :F(RETURN)
         S P                                                  :F(RETURN)
         SESSION = SESSION_LOAD(UUID)                :F(SESSION_EXPIRE2)
         GE(SESSION<'EXPIRE'>, TIME)                 :S(SESSION_EXPIRE2)
         SESSION_DELETE(SESSION)                      :(SESSION_EXPIRE2)
*
SESSION_END
*
* CE: .F.MSNOBOL4;
