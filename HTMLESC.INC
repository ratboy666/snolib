-MODULE HTMLESC
-LINE 15 "HTMLESC.lss"
-INCLUDE 'CH.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'HEX.INC'
-INCLUDE 'REPL.INC'
-INCLUDE 'SDIFF.INC'
-STITL HTMLESC
-LINE 111 "HTMLESC.lss"
-EJECT
*
************************************************************************
*                                                                      *
*    #     #  #######  #     #  #        #######   #####    #####      *
*    #     #     #     ##   ##  #        #        #     #  #     #     *
*    #     #     #     # # # #  #        #        #        #           *
*    #######     #     #  #  #  #        #####     #####   #           *
*    #     #     #     #     #  #        #              #  #           *
*    #     #     #     #     #  #        #        #     #  #     #     *
*    #     #     #     #     #  #######  #######   #####    #####      *
*                                                                      *
* HTMLESC             HTML (JS, URL) ESCAPING                          *
*                                                                      *
************************************************************************
*
* HTMLESC.lss
*
-LINE 41 "HTMLESC.lss"
-PUBLIC HTML_ESCAPE()
         DEFINE('HTML_ESCAPE(S)')                     :(END_HTML_ESCAPE)
*
HTML_ESCAPE
         S = REPL(S, '&', '&amp;')
         S = REPL(S, '<', '&lt;',)
         S = REPL(S, '>', '&gt;',)
         S = REPL(S, '"', '&quot;')
         S = REPL(S, "'", '&#39;')
         HTML_ESCAPE = S                                       :(RETURN)
*
END_HTML_ESCAPE
*
-LINE 58 "HTMLESC.lss"
-PUBLIC JS_ESCAPE()
         DEFINE('JS_ESCAPE(S)')                         :(END_JS_ESCAPE)
*
JS_ESCAPE
         S = REPL(S, '\', '\\')
         S = REPL(S, "'", "\'")
         S = REPL(S, '"', '\"')
         S = REPL(S, CHARS_NL, '\n')
         S = REPL(S, CHARS_CR, '\r')
         JS_ESCAPE = S                                         :(RETURN)
*
END_JS_ESCAPE
*
-LINE 79 "HTMLESC.lss"
-PUBLIC URL_ESCAPE(), URL_DECODE()
         DEFINE('URL_ESCAPE(S)L,C,R')
         DEFINE('URL_DECODE(S)L,C,R')
         URL_BAD = SDIFF(&ALPHABET, &UCASE &LCASE '0123456789' '_-~.')
         URL_HEX = ANY('0123456789abcdefABCDEF')
+                                                      :(END_URL_ESCAPE)
*
URL_DECODE_2
         S = R
URL_DECODE
         C =
         S BREAK("+%") . L LEN(1) . C REM . R
         URL_DECODE = IDENT(C) URL_DECODE S                   :S(RETURN)
         URL_DECODE = IDENT(C, '+') URL_DECODE L ' '    :S(URL_DECODE_2)
         URL_DECODE = URL_DECODE L
         R (URL_HEX URL_HEX) . C =                      :F(URL_DECODE_2)
         URL_DECODE = URL_DECODE CH(C)                   :(URL_DECODE_2)
*
URL_ESCAPE
         S BREAK(URL_BAD) . L LEN(1) . C REM . R             :F(URLESC2)
         URL_ESCAPE = IDENT(C, ' ') URL_ESCAPE L '+'
         URL_ESCAPE = DIFFER(C, ' ') URL_ESCAPE L '%' HEX(C)
         S = R                                             :(URL_ESCAPE)
URLESC2  URL_ESCAPE = URL_ESCAPE S                             :(RETURN)
*
END_URL_ESCAPE
*
* CE: .MSNOBOL4;
