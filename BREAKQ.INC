-MODULE BREAKQ
-INCLUDE 'UNIQUE.INC'
-STITL BREAKQ
*
************************************************************************
*                                                                      *
*         ######   ######   #######     #     #    #   #####           *
*         #     #  #     #  #          # #    #   #   #     #          *
*         #     #  #     #  #         #   #   #  #    #     #          *
*         ######   ######   #####    #     #  ###     #     #          *
*         #     #  #   #    #        #######  #  #    #   # #          *
*         #     #  #    #   #        #     #  #   #   #    #           *
*         ######   #     #  #######  #     #  #    #   #### #          *
*                                                                      *
*                                                                      *
* BREAKQ           FASBOL II BREAKQ PATTERN                            *
*                                                                      *
************************************************************************
*
* BREAKQ.INC
*
         DEFINE('BREAKQ(S)NAME,R,P1,P2,P3')                :(END_BREAKQ)
*
BREAKQ   NAME = UNIQUE()
         R = CONVERT(NAME, 'EXPRESSION')
         P1 = BREAK('"' "'" S)
         P2 = "'" BREAK("'") "'" R
         P3 = '"' BREAK('"') '"' R
         BREAKQ = P1 (P2 | P3 | BREAK(S))
         $NAME = BREAKQ                                        :(RETURN)
*
END_BREAKQ
*
* CE: .MSNOBOL4;
*
