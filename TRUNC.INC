-LINE 12 "TRUNC.lss"
-INCLUDE 'SEQ.INC'
-STITL TRUNC
-EJECT
-LINE 40 "TRUNC.lss"
*
************************************************************************
*                                                                      *
*             #######  ######   #     #  #     #   #####               *
*                #     #     #  #     #  ##    #  #     #              *
*                #     #     #  #     #  # #   #  #                    *
*                #     ######   #     #  #  #  #  #                    *
*                #     #   #    #     #  #   # #  #                    *
*                #     #    #   #     #  #    ##  #     #              *
*                #     #     #   #####   #     #   #####               *
*                                                                      *
* TRUNC                     TRUNCATE ARRAY                             *
*                                                                      *
************************************************************************
*
* TRUNC.lss
*
-LINE 16 "TRUNC.lss"
-MODULE TRUNC
-PUBLIC TRUNC()
         DEFINE('TRUNC(A,L,H)')                             :(TRUNC_END)
*
TRUNC    TRUNC = ARRAY(H - L + 1)
         L = L - 1
         SEQ(' TRUNC<I> = A<L + I> ',.I)                       :(RETURN)
*
TRUNC_END
*
* CE: .MSNOBOL4;
