#!/usr/bin/bash
         exec "/usr/local/bin/snobol4" "-b" "$0" "$@"
-INCLUDE 'DDT.INC'
-LINE 311 "JSON.lss"
-INCLUDE 'JSON.INC'
-INCLUDE 'CRACK.INC'
*
         &CODE = 1
         OUTPUT = JSON_ENCODE()
         OUTPUT = JSON_ENCODE(TABLE())
         OUTPUT = JSON_ENCODE(#'A=1,B=2')
         T = #'A=1,B=2.'
         T2 = TABLE()
         T2<'C'> = 'HELLO'
         T2<'D'> = T
         OUTPUT = JSON_ENCODE(T2)
         T2 = TABLE()
         T2<'INTEGER'> = 42
         T2<'REAL'> = &PI
         T2<'REAL2'> = 1.23456789E23
         T2<'STRING'> = 'Hello world'
         T2<'STRING2'> = '"Hello world' CHARS_BS CHAR(255)
         T2<'STRING3'> = CHARS_PRINTABLE
         T2<'STRING4'> = CHARS_HIGH
         T2<'STRING5'> = CHARS_CONTROL
         T2<'ARRAY EMPTY'> = ARRAY0
         T2<'ARRAY'> = %'1,2,3'
         T2<'NULL'> = ''
         OUTPUT = JSON_ENCODE(T2)
         OUTPUT = JSON_ENCODE('A String')
         OUTPUT = JSON_ENCODE(JSON_NULL)
         OUTPUT = JSON_ENCODE(JSON_TRUE)
         OUTPUT = JSON_ENCODE(JSON_FALSE)
         OUTPUT = JSON_ENCODE(%'1,2,3')
         X = 'hello, world\"\\\/"'
         OUTPUT = JSON_DECODE_STRING()
         X = '0\b\u00FF1"'
         OUTPUT = HEX(JSON_DECODE_STRING())
         X = JSON_DECODE('{ "A": 1, "B": "hello" }')
         OUTPUT = JSON_ENCODE(X)
         X = JSON_DECODE('[ 1, 2, 3 ]')
         OUTPUT = JSON_ENCODE(X)
         X = JSON_DECODE('[[] {}]')
         OUTPUT = JSON_ENCODE(X)
         JSON_DECODE('[')                                        :S(END)
         JSON_DECODE('{')                                        :S(END)
         S = '1 2 3'
         JSON_DECODE(S)                                          :F(END)
         JSON_DECODE(JSON_REST)                                  :F(END)
         JSON_DECODE(JSON_REST)                                  :F(END)
         JSON_DECODE(JSON_REST)                                  :S(END)
*
* FIXME: USE SETEXIT() HERE TO CATCH BRANCH TO END, AND MAKE TEST
* SUCCESSFUL. GENERALLY, WE SHOULD HAVE A HARNESS THAT PERMITS, AND
* CHECKS AND LOGS OUTPUTS. A LIGHTWEIGHT TEST HARNESS FOR UNIT TESTING.
*
         &CODE = 0
         JSON_ENCODE(1E309)                                      :S(END)
         &CODE = 1
END
