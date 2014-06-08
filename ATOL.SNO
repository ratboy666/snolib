-LINE 11 "ATOL.lss"
-INCLUDE 'LINK.INC'
-INCLUDE 'SEQ.INC'
-INCLUDE 'REVL.INC'
-STITL ATOL
-EJECT
-LINE 42 "ATOL.lss"
*
************************************************************************
*                                                                      *
*                     #     #######  #######  #                        *
*                    # #       #     #     #  #                        *
*                   #   #      #     #     #  #                        *
*                  #     #     #     #     #  #                        *
*                  #######     #     #     #  #                        *
*                  #     #     #     #     #  #                        *
*                  #     #     #     #######  #######                  *
*                                                                      *
* ATOL                      ARRAY TO LIST                              *
*                                                                      *
************************************************************************
*
* ATOL.lss
*
-LINE 17 "ATOL.lss"
-MODULE ATOL
-PUBLIC ATOL()
-USES LINK()

         DEFINE('ATOL(A)I')                                  :(END_ATOL)

ATOL     SEQ(' ATOL = LINK(A<I>, ATOL)', .I)
         ATOL = REVL(ATOL)                                     :(RETURN)

END_ATOL
*
* CE: .MSNOBOL4;
