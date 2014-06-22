-MODULE KEYST
-LINE 10 "KEYST.lss"
-INCLUDE 'ARRAY0.INC'
-INCLUDE 'SEQ.INC'
-IN72
-LINE 40 "KEYST.lss"
-STITL KEYST
-EJECT
*
************************************************************************
*                                                                      *
*              #    #  #######  #     #   #####   #######              *
*              #   #   #         #   #   #     #     #                 *
*              #  #    #          # #    #           #                 *
*              ###     #####       #      #####      #                 *
*              #  #    #           #           #     #                 *
*              #   #   #           #     #     #     #                 *
*              #    #  #######     #      #####      #                 *
*                                                                      *
* KEYST                      KEYS IN TABLE                             *
*                                                                      *
************************************************************************
*
* KEYST.lss
*
-LINE 15 "KEYST.lss"
-PUBLIC KEYST()
*
         DEFINE('KEYST(T)A,N,I')                            :(KEYST_END)
*
KEYST    A = (CONVERT(T, 'ARRAY'), ARRAY0)
         PROTOTYPE(A) BREAK(',') . N                         :F(FRETURN)
         KEYST = (NE(N) ARRAY(N), ARRAY0)
         SEQ(' KEYST<I> = A<I,1> ', .I)                        :(RETURN)
*
KEYST_END
*
* CE: .MSNOBOL4;
