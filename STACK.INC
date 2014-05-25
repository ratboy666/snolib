-LINE 12 "STACK.lss"
-INCLUDE 'LINK.INC'
-INCLUDE 'REPL.INC'
-STITL STACK
-EJECT
-LINE 48 "STACK.lss"
*
************************************************************************
*                                                                      *
*               #####   #######     #      #####   #    #              *
*              #     #     #       # #    #     #  #   #               *
*              #           #      #   #   #        #  #                *
*               #####      #     #     #  #        ###                 *
*                    #     #     #######  #        #  #                *
*              #     #     #     #     #  #     #  #   #               *
*               #####      #     #     #   #####   #    #              *
*                                                                      *
* STACK                     CREATE STACK                               *
*                                                                      *
************************************************************************
*
* STACK.lss
*
-LINE 17 "STACK.lss"
         DEFINE('STACK(SUF)S')
         STACK()                                            :(STACK_END)
*
STACK    S = 'PUSHSUF STACK_SUF = LINK(V, STACK_SUF)        ;'
+            '        PUSHSUF = .VALUE(STACK_SUF) :(NRETURN);'
+            'POPSUF  IDENT(STACK_SUF)           :S(FRETURN);'
+            '        POPSUF = VALUE(STACK_SUF)             ;'
+            '        STACK_SUF = NEXT(STACK_SUF)  :(RETURN);'
+            'TOPSUF  IDENT(STACK_SUF)           :S(FRETURN);'
+            '        TOPSUF = .VALUE(STACK_SUF)  :(NRETURN);'
         CODE(REPL(S, 'SUF', SUF))
         DEFINE('PUSH' SUF '(V)')
         DEFINE('POP'  SUF '()' )
         DEFINE('TOP'  SUF '()' )                              :(RETURN)
*
STACK_END
*
* CE: .MSNOBOL4;
