#!/usr/bin/bash
         exec "/usr/local/bin/snobol4" "-b" "$0" "$@"
-INCLUDE 'COOKIE.INC'
-LINE 186 "COOKIE.lss"
*
         &CODE = 1
         JAR = NEW_COOKIE_JAR()
         COOKIE1 = NEW_COOKIE()
         PUT_COOKIE_IN_JAR(JAR, 'COOKIE-1', COOKIE1)
         COOKIE_SET_VALUE(COOKIE1, 'VALUE-1')
         COOKIE2 = NEW_COOKIE('VALUE-2')
         PUT_COOKIE_IN_JAR(JAR, 'COOKIE-2', COOKIE2)
         A = COOKIES_IN_JAR(JAR)                                 :F(END)
         IDENT(A<1>, 'COOKIE-1')                                 :F(END)
         IDENT(A<2>, 'COOKIE-2')                                 :F(END)
         COOKIE = GET_COOKIE_FROM_JAR(JAR, 'COOKIE-1')
         IDENT(COOKIE, COOKIE1)                                  :F(END)
         COOKIE_SET_CRUMB(COOKIE, 'Expires', COOKIE_EXPIRY(60 * 60))
* UNFORTUNATELY, THIS RESULT IS REALLY THE ONLY ONE THAT MATTERS, AND
* IT HAS TO BE VISUALLY INSPECTED -- I WILL FIX THIS LATER.
         OUTPUT = COOKIE_STRING(JAR)
         &CODE = 0
END
