#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'HTMLTMPL.INC'
-LINE 22 "HTMLTMPL.lss"
-INCLUDE 'TIMER.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'TIMER.INC'
*
         &CODE = 1
*        TMPL_INIT()
         S = READFILE("sample.tmpl")
         OUTPUT = S
         P = TMPL_COMPILE(S)                                     :F(END)
* VARIABLES ARE IN A TABLE. SCALAR VARIABLES ARE THE SIMPLEST CASE.
* NOTE THAT TEMPLATE VARIABLES MAY BE DEFAULTED.
         A = TABLE()
         A["var"] = "AB"
         A["var2"] = "CD"
* TEMPLATE LOOPS NEED AN ARRAY VARIABLE. EACH ENTRY OF THE ARRAY IS
* A TABLE WITH THE VARIABLES NEEDED.
         R = ARRAY(3)
         R[1] = #'FIRST=F1 x,LAST=L1'
         R[2] = #'FIRST=F2,LAST=L2'
         R[3] = #'FIRST=F3,LAST=L3'
         A["var3"] = R
         S = TMPL_INTERPRET(P, A)                                :F(END)
         OUTPUT = S
         TIMER(' S = READFILE("sample.tmpl") ')
         TIMER(' P = TMPL_COMPILE(S) ')
         TIMER(' S = TMPL_INTERPRET(P, A) ')
         &CODE = 0
END
