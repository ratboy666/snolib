-MODULE AI
-IN72
-LINE 18 "AI.lss"
-INCLUDE 'SEQ.INC'
-LINE 56 "AI.lss"
-STITL AI
-EJECT
*
************************************************************************
*                                                                      *
*                                #     ###                             *
*                               # #     #                              *
*                              #   #    #                              *
*                             #     #   #                              *
*                             #######   #                              *
*                             #     #   #                              *
*                             #     #  ###                             *
*                                                                      *
* AI                          APPLY INDEX                              *
*                                                                      *
************************************************************************
*
* AI.lss
*
-LINE 22 "AI.lss"
-PUBLIC AI()
*
         DEFINE('AI(A,I)J')                                    :(AI_END)
*
AI       IDENT(DATATYPE(I), 'ARRAY')                            :F(AI_1)
         AI = ARRAY(PROTOTYPE(I))
         SEQ(' AI<J> = A<I<J>> ', .J)                          :(RETURN)
AI_1     AI = A<I>                                  :S(RETURN)F(FRETURN)
*
AI_END
*
* CE: .MSNOBOL4;
