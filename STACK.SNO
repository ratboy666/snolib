-LINE 11 "STACK.lss"
-INCLUDE 'REPL.INC'
-STITL STACK
-EJECT
-LINE 52 "STACK.lss"
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
-LINE 15 "STACK.lss"
-MODULE STACK
-PUBLIC STACK()
         DEFINE('STACK(SUF)S')
         STACK()
-PUBLIC PUSH(), POP(), TOP()
         OPSYN('PUSH', 'PUSH_')
         OPSYN('POP',  'POP_')
         OPSYN('TOP',  'TOP_')                              :(STACK_END)
*
STACK    S = 'PUSH_SUF STACK_SUF = LINK(V, STACK_SUF)         ;'
+            '         PUSH_SUF = .VALUE(STACK_SUF) :(NRETURN);'
+            'POP_SUF  IDENT(STACK_SUF)            :S(FRETURN);'
+            '         POP_SUF = VALUE(STACK_SUF)             ;'
+            '         STACK_SUF = NEXT(STACK_SUF)   :(RETURN);'
+            'TOP_SUF  IDENT(STACK_SUF)            :S(FRETURN);'
+            '         TOP_SUF = .VALUE(STACK_SUF)  :(NRETURN);'
         CODE(REPL(S, 'SUF', SUF))
         DEFINE('PUSH_' SUF '(V)')
         DEFINE('POP_'  SUF '()' )
         DEFINE('TOP_'  SUF '()' )                             :(RETURN)
*
STACK_END
*
* CE: .MSNOBOL4;
