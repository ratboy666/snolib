-LINE 11 "ATOL.lss"
-INCLUDE 'LINK.INC'
-INCLUDE 'SEQ.INC'
-INCLUDE 'REVL.INC'
-MODULE ATOL
-USES LINK()
-LINE 40 "ATOL.lss"
-IN72
-STITL ATOL
-EJECT
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
-PUBLIC ATOL()
*
         DEFINE('ATOL(A)I')                                  :(END_ATOL)
*
ATOL     SEQ(' ATOL = LINK(A<I>, ATOL)', .I)
         ATOL = REVL(ATOL)                                     :(RETURN)
*
END_ATOL
*
* CE: .MSNOBOL4;
