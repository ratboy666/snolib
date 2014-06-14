-MODULE PRUNET
-LINE 14 "PRUNET.lss"
-INCLUDE 'KEYST.INC'
-INCLUDE 'SEQ.INC'
-IN72
-LINE 43 "PRUNET.lss"
-STITL PRUNET
-EJECT
*
************************************************************************
*                                                                      *
*         ######   ######   #     #  #     #  #######  #######         *
*         #     #  #     #  #     #  ##    #  #           #            *
*         #     #  #     #  #     #  # #   #  #           #            *
*         ######   ######   #     #  #  #  #  #####       #            *
*         #        #   #    #     #  #   # #  #           #            *
*         #        #    #   #     #  #    ##  #           #            *
*         #        #     #   #####   #     #  #######     #            *
*                                                                      *
* PRUNET                       PRUNE TABLE                             *
*                                                                      *
************************************************************************
*
* PRUNET.lss
*
-LINE 19 "PRUNET.lss"
-PUBLIC PRUNET()
*
         DEFINE('PRUNET(T)A,I')                            :(PRUNET_END)
*
PRUNET   PRUNET = TABLE()
         A = KEYST(T)                                         :F(RETURN)
         SEQ(' PRUNET<A<I>> = VDIFFER(T<A<I>>)', .I)           :(RETURN)
*
PRUNET_END
*
* CE: .MSNOBOL4;
