-MODULE CATA
-LINE 11 "CATA.lss"
-INCLUDE 'SEQ.INC'
-IN72
-LINE 50 "CATA.lss"
-STITL CATA
-EJECT
*
************************************************************************
*                                                                      *
*                    #####      #     #######     #                    *
*                   #     #    # #       #       # #                   *
*                   #         #   #      #      #   #                  *
*                   #        #     #     #     #     #                 *
*                   #        #######     #     #######                 *
*                   #     #  #     #     #     #     #                 *
*                    #####   #     #     #     #     #                 *
*                                                                      *
* CATA                     CONCATENATE ARRAYS                          *
*                                                                      *
************************************************************************
*
* CATA.lss
*
-LINE 15 "CATA.lss"
-PUBLIC CATA()
*
         DEFINE('CATA(A1,A2)I,N1')                           :(CATA_END)
*
CATA     N1 = PROTOTYPE(A1)
         CATA = ARRAY(N1 + PROTOTYPE(A2))
         SEQ(' CATA<I> = A1<I> ', .I)
         SEQ(' CATA<N1 + I> = A2<I> ', .I)                     :(RETURN)
*
CATA_END
*
* CE: .MSNOBOL4;
