-MODULE JSON
-IN72
-LINE 39 "JSON.lss"
-INCLUDE 'CH.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'HEX.INC'
-INCLUDE 'SDIFF.INC'
-INCLUDE 'SEQ.INC'
-INCLUDE 'SIZEA.INC'
-LINE 380 "JSON.lss"
-STITL JSON
-EJECT
*
************************************************************************
*                                                                      *
*                        #   #####   #######  #     #                  *
*                        #  #     #  #     #  ##    #                  *
*                        #  #        #     #  # #   #                  *
*                        #   #####   #     #  #  #  #                  *
*                  #     #        #  #     #  #   # #                  *
*                  #     #  #     #  #     #  #    ##                  *
*                   #####    #####   #######  #     #                  *
*                                                                      *
* JSON                  CONVERT TO AND FROM JSON                       *
*                                                                      *
************************************************************************
*
* JSON.lss
*
-LINE 49 "JSON.lss"
-PUBLIC JSON_ENCODE(), JSON_DECODE()
         DEFINE('JSON_ENCODE(X)L')
         DEFINE('JSON_DECODE(X)')
*
         DEFINE('JSON_DECODE_STRING()S')
         DEFINE('JSON_DECODE_VALUE()')
         DEFINE('JSON_DECODE_OBJECT()T,T2')
         DEFINE('JSON_DECODE_ARRAY()T,I')
         DEFINE('JSON_ESCAPE(C)')
         DEFINE('JSON_INDENT()')
         DEFINE('JSON_ENCODE_OBJECT(X)K,I')
         DEFINE('JSON_ENCODE_ARRAY(X)I')
         DEFINE('JSON_ENCODE_STRING(S)L,C')
         DEFINE('JSON_ENCODE_VALUE(X)')
*
* JSON WHITESPACE. THIS CAN BE BETWEEN TOKENS, AND WILL BE IGNORED
*
* ALSO EATS 'COMMENTS' DEFINED AS # TO END OF LINE, // TO END OF
* LINE AND /* TO */
*
         JSON_WS2 = SPAN(CHARS_TAB CHARS_SPACE CHARS_FF CHARS_LF
+                        CHARS_CR) |
+                   ('#' BREAK(CHARS_LF CHARS_CR) LEN(1)) |
+                   ('//' BREAK(CHARS_LF CHARS_CR) LEN(1)) |
+                   ('/*' BREAK('*') '*/')
         JSON_WS = (JSON_WS2 *JSON_WS) |
+                  NULL
*
* A JSON NUMBER. PATTERN JSON_NUMBER IS ONLY USED TO DECODE JSON.
* ENCODING USES THE NORMAL OUTPUT FORMATTING, WITH THE RULE THAT
* A TRAILING '0' IS ADDED IF THE NUMBER OUTPUT ENDS IN '.'
*
         JSON_DIGIT19 = ANY("123456789")
         JSON_DIGIT = ANY("0123456789")
         JSON_DIGITS = JSON_DIGIT (*JSON_DIGITS | NULL)
         JSON_E = 'e+' | 'e-' | 'E+' | 'E-' | 'e' | 'E'
         JSON_EXP = JSON_E JSON_DIGITS
         JSON_FRAC = "." JSON_DIGITS
         JSON_INT = ("-" | NULL)
+                   ((JSON_DIGIT19 JSON_DIGITS) | JSON_DIGIT)
         JSON_NUMBER = JSON_INT (JSON_FRAC | NULL) (JSON_EXP | NULL)
*
* JSON CONSTANTS. THESE ARE NOT IN THE SNOBOL4 LEXICON, SO WE
* CREATE A TYPE THAT REPRESENT THESE VALUES UNIQUELY.
*
-PUBLIC JSON_NULL, JSON_TRUE, JSON_FALSE
         DATA('JSON_CONSTANT(VALUE)')
         JSON_NULL = JSON_CONSTANT('null')
         JSON_TRUE = JSON_CONSTANT('true')
         JSON_FALSE = JSON_CONSTANT('false')
*
* JSON_NL AND JSON_IN ARE PRODUCED FOR NEWLINE AND INDENT SEPARATION.
* DEFAULT IS A NEWLINE AND TWO SPACES. TO PRODUCE COMPACT JSON, REPLACE
* WITH NULL.
*
-PUBLIC JSON_NL, JSON_IN
         JSON_NL = CHARS_NL
         JSON_IN = '  '
*
* JSON_REST IS THE REST OF THE INPUT AFTER PARSING A JSON DOCUMENT
* FROM THE FRONT. THIS IS MEANT TO ALLOW CONCATENATION OF JSON
* DOCUMENTS.
*
-PUBLIC JSON_REST
         JSON_REST =
*
* JSON_HEX IS A HEX DIGIT USED BY THE \u CHARACTER IS A JSON STRING.
* JSON_NSET IS THE SET OF CHARACTERS WHICH CAN BE SIMPLY ACCEPTED IN
* A STRING. ANY CHARACTER NOT IN JSON_NSET (NORMAL SET) IS ESCAPED.
*
         JSON_HEX = ANY('0123456789abcdefABCDEF')
         JSON_NSET = SDIFF(CHARS_PRINTABLE, '"\/')           :(JSON_END)
*
JSON_ESCAPE
         JSON_ESCAPE = IDENT(C, '"') '\"'                     :S(RETURN)
         JSON_ESCAPE = IDENT(C, '\') '\\'                     :S(RETURN)
         JSON_ESCAPE = IDENT(C, '/') '\/'                     :S(RETURN)
         JSON_ESCAPE = IDENT(C, CHARS_BS) '\b'                :S(RETURN)
         JSON_ESCAPE = IDENT(C, CHARS_FF) '\f'                :S(RETURN)
         JSON_ESCAPE = IDENT(C, CHARS_NL) '\n'                :S(RETURN)
         JSON_ESCAPE = IDENT(C, CHARS_HT) '\t'                :S(RETURN)
         JSON_ESCAPE = IDENT(C, CHARS_CR) '\r'                :S(RETURN)
*
* FIXME: NOT RIGHT. SHOULD PASS THROUGH UTF-8, AND ONLY CONVERT CONTROL
*        WE ARE CHEATING BY JUST USING THIS TO CONVERT BYTES.
*
         JSON_ESCAPE = '\u00' HEX(C)                           :(RETURN)
*
JSON_ENCODE_STRING
         L =
         S (SPAN(JSON_NSET) | NULL) . L REM . S
         JSON_ENCODE_STRING = JSON_ENCODE_STRING L
         IDENT(S)                               :S(JSON_ENCODE_STRING_2)
         S LEN(1) . C REM . S
         JSON_ENCODE_STRING = JSON_ENCODE_STRING JSON_ESCAPE(C)
+                                                  :(JSON_ENCODE_STRING)
JSON_ENCODE_STRING_2
         JSON_ENCODE_STRING = '"' JSON_ENCODE_STRING '"'       :(RETURN)
*
* CAREFUL WITH REAL VALUES. CSNOBOL4 WILL PRINT '4.' (FOR EXAMPLE).
* BY THE SYNTAX SPECIFIED, THIS IS NOT LEGAL. '4.0' IS THE LEGAL
* FORM. FIX THIS BY APPENDING A '0' IF THE FINAL CHARACTER OF A REAL
* CONVERSION IS '.'.
*
* BOTH TABLE AND ARRAY TYPES CAUSE A RECURSION. DATA() TYPES CANNOT
* BE SERIALIZED.
*
JSON_ENCODE_VALUE
         JSON_ENCODE_VALUE = IDENT(X, JSON_NULL) 'null'       :S(RETURN)
         JSON_ENCODE_VALUE = IDENT(X, JSON_TRUE) 'true'       :S(RETURN)
         JSON_ENCODE_VALUE = IDENT(X, JSON_FALSE) 'false'     :S(RETURN)
         JSON_ENCODE_VALUE = IDENT(X) '""'                    :S(RETURN)
         JSON_ENCODE_VALUE = IDENT(DATATYPE(X), 'INTEGER') X  :S(RETURN)
         JSON_ENCODE_VALUE = IDENT(DATATYPE(X), 'REAL') X
+                                                :F(JSON_ENCODE_VALUE_2)
*
* THE FOLLOWING CONDITION WILL NOT HAPPEN WITH SPITBOL.EXE
*
         JSON_ENCODE_VALUE 'nan' | 'inf'         :S(JSON_ENCODE_VALUE_3)
         JSON_ENCODE_VALUE RTAB(1) '.'                        :F(RETURN)
         JSON_ENCODE_VALUE = JSON_ENCODE_VALUE '0'             :(RETURN)
JSON_ENCODE_VALUE_2
         JSON_ENCODE_VALUE = IDENT(DATATYPE(X), 'STRING')
+                            JSON_ENCODE_STRING(X)            :S(RETURN)
         JSON_ENCODE_VALUE = IDENT(DATATYPE(X), 'TABLE')
+                            JSON_ENCODE_OBJECT(X)            :S(RETURN)
         JSON_ENCODE_VALUE = IDENT(DATATYPE(X), 'ARRAY')
+                            JSON_ENCODE_ARRAY(X)             :S(RETURN)
JSON_ENCODE_VALUE_3
         TERMINAL = 'JSON_ENCODE_VALUE: CANNOT ENCODE: '
+                   DATATYPE(X) ' ' X
                                                                  :(END)
*
JSON_INDENT
         JSON_INDENT = DUPL(JSON_IN, L)                        :(RETURN)
*
JSON_ENCODE_ARRAY
         JSON_ENCODE_ARRAY = '['
         L = L + 1
         DIFFER(DATATYPE(X), 'ARRAY')            :S(JSON_ENCODE_ARRAY_2)
         I = 1
         X<I>                                    :F(JSON_ENCODE_ARRAY_2)
JSON_ENCODE_ARRAY_1
         JSON_ENCODE_ARRAY = JSON_ENCODE_ARRAY JSON_NL
+                            JSON_INDENT()
+                            JSON_ENCODE_VALUE(X<I>)
         I = I + 1
         X<I>                                    :F(JSON_ENCODE_ARRAY_2)
         JSON_ENCODE_ARRAY = JSON_ENCODE_ARRAY ','
+                                                 :(JSON_ENCODE_ARRAY_1)
JSON_ENCODE_ARRAY_2
         L = L - 1
         JSON_ENCODE_ARRAY = JSON_ENCODE_ARRAY JSON_NL
+                            JSON_INDENT() ']'                 :(RETURN)
*
JSON_ENCODE_OBJECT
         JSON_ENCODE_OBJECT = '{'
         L = L + 1
         DIFFER(DATATYPE(X), 'TABLE')           :S(JSON_ENCODE_OBJECT_2)
         K = KEYST(X)                           :F(JSON_ENCODE_OBJECT_2)
         I = 1
JSON_ENCODE_OBJECT_1
         JSON_ENCODE_OBJECT = JSON_ENCODE_OBJECT JSON_NL
+                             JSON_INDENT()
+                             JSON_ENCODE_STRING(K<I>) ': '
+                             JSON_ENCODE_VALUE(X<K<I>>)
         I = I + 1
         K<I>                                   :F(JSON_ENCODE_OBJECT_2)
         JSON_ENCODE_OBJECT = JSON_ENCODE_OBJECT ','
+                                                :(JSON_ENCODE_OBJECT_1)
JSON_ENCODE_OBJECT_2
         L = L - 1
         JSON_ENCODE_OBJECT = JSON_ENCODE_OBJECT JSON_NL
+                             JSON_INDENT() '}'                :(RETURN)
*
JSON_ENCODE
         L = 0
         JSON_ENCODE = JSON_ENCODE_VALUE(X)                    :(RETURN)
*
JSON_DECODE_STRING
         X BREAK('\"') . S =                                 :F(FRETURN)
         JSON_DECODE_STRING = JSON_DECODE_STRING S
         X POS(0) '"' =                                       :S(RETURN)
         JSON_DECODE_STRING = ?(X ? POS(0) '\b' =)
+                     JSON_DECODE_STRING CHARS_BS :S(JSON_DECODE_STRING)
         JSON_DECODE_STRING = ?(X ? POS(0) '\f' =)
+                     JSON_DECODE_STRING CHARS_FF :S(JSON_DECODE_STRING)
         JSON_DECODE_STRING = ?(X ? POS(0) '\n' =)
+                     JSON_DECODE_STRING CHARS_NL :S(JSON_DECODE_STRING)
         JSON_DECODE_STRING = ?(X ? POS(0) '\t' =)
+                     JSON_DECODE_STRING CHARS_HT :S(JSON_DECODE_STRING)
         JSON_DECODE_STRING = ?(X ? POS(0) '\r' =)
+                     JSON_DECODE_STRING CHARS_CR :S(JSON_DECODE_STRING)
         JSON_DECODE_STRING = ?(X ? POS(0) '\"' =)
+                     JSON_DECODE_STRING '"'      :S(JSON_DECODE_STRING)
         JSON_DECODE_STRING = ?(X ? POS(0) '\\' =)
+                     JSON_DECODE_STRING '\'      :S(JSON_DECODE_STRING)
         JSON_DECODE_STRING = ?(X ? POS(0) '\/' =)
+                     JSON_DECODE_STRING '/'      :S(JSON_DECODE_STRING)
* FIXME: HANDLE UTF SEQUENCES PROPERLY
         X POS(0) '\u00' (JSON_HEX JSON_HEX) . C =
+                                               :F(JSON_DECODE_STRING_2)
         JSON_DECODE_STRING = JSON_DECODE_STRING CH(C)
+                                                  :(JSON_DECODE_STRING)
JSON_DECODE_STRING_2
         TERMINAL = 'JSON_DECODE_STRING: ' X                      :(END)
*
JSON_DECODE_VALUE
         X POS(0) JSON_WS =
         IDENT(X)                                            :S(FRETURN)
         JSON_DECODE_VALUE = ?(X ? POS(0) 'null' =) JSON_NULL
+                                                             :S(RETURN)
         JSON_DECODE_VALUE = ?(X ? POS(0) 'true' =) JSON_TRUE
+                                                             :S(RETURN)
         JSON_DECODE_VALUE = ?(X ? POS(0) 'false' =) JSON_FALSE
+                                                             :S(RETURN)
         X POS(0) '"' =                          :F(JSON_DECODE_VALUE_2)
         JSON_DECODE_VALUE =  JSON_DECODE_STRING()  :S(RETURN)F(FRETURN)
JSON_DECODE_VALUE_2
         X POS(0) '{' =                          :F(JSON_DECODE_VALUE_3)
         JSON_DECODE_VALUE = JSON_DECODE_OBJECT()   :S(RETURN)F(FRETURN)
JSON_DECODE_VALUE_3
         X POS(0) '[' =                          :F(JSON_DECODE_VALUE_4)
         JSON_DECODE_VALUE = JSON_DECODE_ARRAY()    :S(RETURN)F(FRETURN)
JSON_DECODE_VALUE_4
         X JSON_NUMBER . JSON_DECODE_VALUE =                 :F(FRETURN)
         JSON_DECODE_VALUE = +JSON_DECODE_VALUE                :(RETURN)
*
JSON_DECODE_ARRAY
         T = TABLE()
         I = 0
JSON_DECODE_ARRAY_1
         X POS(0) JSON_WS =
         IDENT(X)                                            :S(FRETURN)
         X POS(0) ']' =                          :S(JSON_DECODE_ARRAY_2)
         I = I + 1
         T<I> = JSON_DECODE_VALUE()                          :F(FRETURN)
         X POS(0) JSON_WS ',' =                   :(JSON_DECODE_ARRAY_1)
JSON_DECODE_ARRAY_2
         JSON_DECODE_ARRAY = EQ(I) ARRAY0                     :S(RETURN)
         JSON_DECODE_ARRAY = ARRAY(I)
         SEQ(' JSON_DECODE_ARRAY<I> = T<I> ', .I)              :(RETURN)
*
JSON_DECODE_OBJECT
         JSON_DECODE_OBJECT = TABLE()
JSON_DECODE_OBJECT_1
         X POS(0) JSON_WS =
         IDENT(X)                                            :S(FRETURN)
         X POS(0) '}' =                                       :S(RETURN)
         X POS(0) '"' =                                      :F(FRETURN)
         T = JSON_DECODE_STRING()                            :F(FRETURN)
         X POS(0) JSON_WS ':' =                              :F(FRETURN)
         T2 = JSON_DECODE_VALUE()                            :F(FRETURN)
         JSON_DECODE_OBJECT<T> = T2
         X POS(0) JSON_WS ',' =                  :(JSON_DECODE_OBJECT_1)
*
JSON_DECODE
         X = X CHARS_NL
         JSON_DECODE = JSON_DECODE_VALUE()                   :F(FRETURN)
         JSON_REST = X                                         :(RETURN)
*
JSON_END
*
*
* CE: .F.MSNOBOL4;
