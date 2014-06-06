#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'HTMLESC.INC'
-LINE 25 "HTMLESC.lss"
         &CODE = 1
         IDENT(HTML_ESCAPE('&<>"' "'"), '&amp;&lt;&gt;&quot;&#39;')
+                                                                :F(END)
         IDENT(JS_ESCAPE('\' "'" '"' CHARS_NL CHARS_CR),
+                        '\\' "\'" '\"\n\r')                     :F(END)
         IDENT(URL_ESCAPE(' +!@#'), '+%2B%21%40%23')             :F(END)
         IDENT(URL_DECODE('AB%20+%21'), 'AB  !')                 :F(END)
         &CODE = 0
END
