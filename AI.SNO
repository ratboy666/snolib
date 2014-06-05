-LINE 19 "AI.lss"
-INCLUDE 'SEQ.INC'
-STITL AI
-EJECT
-LINE 57 "AI.lss"
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
-LINE 23 "AI.lss"
-MODULE AI
-PUBLIC AI()
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
