#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'FOR.INC'
-LINE 150 "FOR.lss"
-INCLUDE 'TIMER.INC'
-INCLUDE 'DDT.INC'
         &CODE = 1
*
* THE INIT CAN BE IN THE FOR(), OR OUTSIDE. THE STATEMENT MAY BE
* EMPTY, AS MAY BE THE UPDT AND TEST.
*
         FOR(FOR_COMPILE(' I = 1',
+                        ' LT(I, 5)',
+                        ' I = I + 1',
+                        ' OUTPUT = I'))
*
         FOR_S =
+        "FOR(FOR_COMPILE(' I = 1',' LT(I, 5)',' I = I + 1', ' D = I'))"
         TIMER(' ' FOR_S)
*
         F = FOR_COMPILE(
+           ' I = 1',
+           ' LT(I, 5)',
+           ' I = I + 1')
         TIMER(' FOR(F)')
*
         W = WHILE_COMPILE(
+           ' LT(I, 5)',
+           ' OUTPUT = "WHILE: " I; I = I + 1')
         I = 1
         WHILE(W)
*
* IFS IS THE IF STATEMENT.
*
         OUTPUT = '** IF TEST'
         IFS = IF_COMPILE(
+           ' EQ(REMDR(I, 2))',
+           ' OUTPUT = I " is even"',
+           ' OUTPUT = I " is odd"')
         I = 1
         EVAL_CODE_(IFS)
         I = 2
         EVAL_CODE_(IFS)
*
* EVALUATE THE IF STATEMENT 'IFS' IN THE CONTEXT OF A FOR LOOP
*
         OUTPUT = '** IF IN FOR'
         F = FOR_COMPILE(
+           ' I = 1 ',
+           ' LT(I, 5)',
+           ' I = I + 1',
+           IFS)
         EVAL_CODE_(F)
*
* COMPILE AND EVALUATE TWO SIMPLE STATEMENTS
*
         OUTPUT = '** TWO SIMPLE STATEMENTS'
         S1 = STMT_COMPILE(' OUTPUT = "S1"; I = 3')
         S2 = STMT_COMPILE(' OUTPUT = "S2"; I = I + 4')
         EVAL_CODE_(S1)
         OUTPUT = I
         EVAL_CODE_(S2)
         OUTPUT = I
*
* COMPILE AND EVALUATE A VALUE RETURN
*
         OUTPUT = '** RVAL'
         R = STMT_COMPILE(' OUTPUT = "SET_RVAL(" I ")"; SET_RVAL(I)')
         OUTPUT = EVAL_CODE_(R)
*
* COMBINE S1 AND S2 AND EVALUATE
*
         OUTPUT = '** PROG2'
         I = -10
         S3 = PROG2_COMPILE(S1, S2)
         EVAL_CODE_(S3)
         OUTPUT = I
*
* COMBINE WITH VALUE RETURN
*
         OUTPUT = '** PROG2 + RVAL'
         S4 = PROG2_COMPILE(S3, R)
         I = -10
         OUTPUT = EVAL_CODE_(S4)
         OUTPUT = 'I = ' I
*
         &CODE = 0
END
