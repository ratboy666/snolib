-MODULE GCD
-LINE 8 "GCD.lss"
-IN72
-LINE 39 "GCD.lss"
-STITL GCD
-EJECT
*
************************************************************************
*                                                                      *
*                       #####    #####   ######                        *
*                      #     #  #     #  #     #                       *
*                      #        #        #     #                       *
*                      #  ####  #        #     #                       *
*                      #     #  #        #     #                       *
*                      #     #  #     #  #     #                       *
*                       #####    #####   ######                        *
*                                                                      *
* GCD                   GREATEST COMMON DIVISOR                        *
*                                                                      *
************************************************************************
*
* GCD.lss
*
-LINE 11 "GCD.lss"
-PUBLIC GCD()
*
         DEFINE('GCD(I,J)')                                   :(GCD_END)
*
GCD      EQ(I)                                               :S(FRETURN)
         EQ(J)                                               :S(FRETURN)
GCD.1    GCD = REMDR(I, J)
         GCD = EQ(GCD) J                                      :S(RETURN)
         I = J
         J = GCD                                                :(GCD.1)
*
GCD_END
*
* CE: .MSNOBOL4;
