-LINE 49 "COOKIE.lss"
-INCLUDE 'HASH.INC'
-INCLUDE 'TIME.INC'
-INCLUDE 'DEXP.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'TRIMB.INC'
-INCLUDE 'VDIFFER.INC'
-STITL COOKIE
-EJECT
-LINE 211 "COOKIE.lss"
*
************************************************************************
*                                                                      *
*            #####   #######  #######  #    #  ###  #######            *
*           #     #  #     #  #     #  #   #    #   #                  *
*           #        #     #  #     #  #  #     #   #                  *
*           #        #     #  #     #  ###      #   #####              *
*           #        #     #  #     #  #  #     #   #                  *
*           #     #  #     #  #     #  #   #    #   #                  *
*            #####   #######  #######  #    #  ###  #######            *
*                                                                      *
* COOKIE                    HANDLE COOKIES                             *
*                                                                      *
************************************************************************
*
* COOKIE.lss
*
-LINE 58 "COOKIE.lss"
-PUBLIC NEW_COOKIE_JAR(), NEW_COOKIE(), COOKIE_SET_VALUE()
-PUBLIC COOKIE_VALUE(), COOKIE_SET_CRUMB(), COOKIE_GET_CRUMB()
-PUBLIC PUT_COOKIE_IN_JAR(), GET_COOKIE_FROM_JAR(), COOKIES_IN_JAR()
-PUBLIC CRUMBS_IN_COOKIE(), COOKIE_EXPIRY(), COOKIE_STRING()
-PuBLIC COOKIE_FIX_NAME()
         DEFINE('NEW_COOKIE_JAR()')
         DEFINE('NEW_COOKIE(VALUE)')
         DEFINE('COOKIE_SET_VALUE(COOKIE,VALUE)')
         DEFINE('COOKIE_VALUE(COOKIE)')
         DEFINE('COOKIE_SET_CRUMB(COOKIE,CRUMB_NAME,VALUE)')
         DEFINE('COOKIE_GET_CRUMB(COOKIE,CRUMB_NAME)')
         DEFINE('PUT_COOKIE_IN_JAR(COOKIE_JAR,COOKIE_NAME,COOKIE)')
         DEFINE('GET_COOKIE_FROM_JAR(COOKIE_JAR,COOKIE_NAME)')
         DEFINE('COOKIES_IN_JAR(COOKIE_JAR)')
         DEFINE('CRUMBS_IN_COOKIE(COOKIE)')
         DEFINE('COOKIE_EXPIRY(N)T,D,M,S')
         DEXP('L20_(S) = LPAD(S, 2, "0")')
         DEFINE('COOKIE_STRING(COOKIE_JAR)A,B,C,I,J,S,V')
         DEFINE('COOKIE_FIX_NAME(S)')
                                                           :(COOKIE_END)
*
* RETURN COOKIE STRING
*
COOKIE_STRING
         A = COOKIES_IN_JAR(COOKIE_JAR)                       :F(RETURN)
COOKIE_STRING_2
         I = I + 1
         C = GET_COOKIE_FROM_JAR(COOKIE_JAR, A<I>)   :F(COOKIE_STRING_5)
         B = CRUMBS_IN_COOKIE(C)                     :F(COOKIE_STRING_2)
         S = S 'Set-Cookie: ' A<I> '=' COOKIE_VALUE(C)
         J = 1
COOKIE_STRING_3
         J = J + 1
         V = COOKIE_GET_CRUMB(C, B<J>)               :F(COOKIE_STRING_4)
         S = S '; ' B<J>
         S = S '=' VDIFFER(V)                         :(COOKIE_STRING_3)
COOKIE_STRING_4
         S = S CHARS_CR CHARS_NL                      :(COOKIE_STRING_2)
COOKIE_STRING_5
         COOKIE_STRING = S                                     :(RETURN)
*
* RETURN EXPIRES STRING FOR N SECONDS IN THE FUTURE. THIS STRING IS
* IN THE FORMAT:
* Wed, 09 Jun 2021 10:18:14 GMT
* ALL COOKIE EXPIRY IS IN GMT.
*
COOKIE_EXPIRY
         T = TV_SEC(GETTIMEOFDAY()) + N
         T = GMTIME(T)
         '0Sun1Mon2Tue3Wed4Thu5Fri6Sat' TM_WDAY(T) LEN(3) . D
         '0Jan1Feb2Mar3Apr4May5Jun6Jul7Aug8Sep9Oct10Nov11Dec'
+           TM_MON(T) LEN(3) . M
         S = D ', ' L20_(TM_MDAY(T)) ' ' M ' ' (TM_YEAR(T) + 1900)
+        ' ' L20_(TM_HOUR(T)) ':' L20_(TM_MIN(T)) ':' L20_(TM_SEC(T))
+        ' GMT'
         COOKIE_EXPIRY = S                                     :(RETURN)
*
* MAKE A NEW COOKIE JAR
*
NEW_COOKIE_JAR
         NEW_COOKIE_JAR = TABLE()                              :(RETURN)
*
* MAKE A NEW COOKIE
*
NEW_COOKIE
         NEW_COOKIE = TABLE()
         NEW_COOKIE<''> = VDIFFER(VALUE)                       :(RETURN)
*
* SET THE VALUE OF THE COOKIE (ATRIBUTE '')
*
COOKIE_SET_VALUE
         COOKIE<''> = VALUE                                    :(RETURN)
*
* RETURN THE VALUE OF THE COOKIE (ATTRIBUTE '')
*
COOKIE_VALUE
         COOKIE_VALUE = COOKIE<''>                             :(RETURN)
*
COOKIE_FIX_NAME
         S = TRIMB(S)
         S POS(0) '$' REM . S
         COOKIE_FIX_NAME = S                                   :(RETURN)
*
* SET AN ATTRIBUTE ON THE COOKIE
*
COOKIE_SET_CRUMB
         CRUMB_NAME = COOKIE_FIX_NAME(CRUMB_NAME)
         COOKIE<CRUMB_NAME> = VALUE                            :(RETURN)
*
* GET VALUE OF AN ATTRIBUTE FROM THE COOKIE
*
COOKIE_GET_CRUMB
         CRUMB_NAME = COOKIE_FIX_NAME(CRUMB_NAME)
         COOKIE_GET_CRUMB = COOKIE<CRUMB_NAME>                 :(RETURN)
*
* PUT THE COOKIE INTO THE COOKIE JAR, WITH NAME COOKIE_NAME
*
PUT_COOKIE_IN_JAR
         COOKIE_NAME = COOKIE_FIX_NAME(COOKIE_NAME)
         COOKIE_JAR<COOKIE_NAME> = COOKIE                      :(RETURN)
*
* GET COOKIE NAMED COOKIE_NAME FROM THE COOKIE JAR
*
GET_COOKIE_FROM_JAR
         COOKIE_NAME = COOKIE_FIX_NAME(COOKIE_NAME)
         GET_COOKIE_FROM_JAR = COOKIE_JAR<COOKIE_NAME>         :(RETURN)
*
* RETURN ARRAY OF COOKIE NAMES IN THE COOKIE JAR, SORTED.
*
COOKIES_IN_JAR
         COOKIES_IN_JAR = KEYS_IN_TABLE(COOKIE_JAR)          :F(FRETURN)
         COOKIES_IN_JAR = SORT(COOKIES_IN_JAR)                 :(RETURN)
*
* RETURN ARRAY OF CRUMBS IN THE COOKIE, SORTED. THE FIRST CRUMB WILL
* BE THE UNAMED VALUE OF THE COOKIE.
*
CRUMBS_IN_COOKIE
         CRUMBS_IN_COOKIE = KEYS_IN_TABLE(COOKIE)            :F(FRETURN)
         CRUMBS_IN_COOKIE = SORT(CRUMBS_IN_COOKIE)             :(RETURN)
*
COOKIE_END
*
*
* CE: .F.MSNOBOL4;
