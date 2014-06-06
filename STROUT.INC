-STITL STROUT
-EJECT
*
-LINE 43 "STROUT.lss"
************************************************************************
*                                                                      *
*            #####   #######  ######   #######  #     #  #######       *
*           #     #     #     #     #  #     #  #     #     #          *
*           #           #     #     #  #     #  #     #     #          *
*            #####      #     ######   #     #  #     #     #          *
*                 #     #     #   #    #     #  #     #     #          *
*           #     #     #     #    #   #     #  #     #     #          *
*            #####      #     #     #  #######   #####      #          *
*                                                                      *
* STROUT                    ARRAY TO STRING                            *
*                                                                      *
************************************************************************
*
* STROUT.lss
*
-LINE 16 "STROUT.lss"
-MODULE STROUT
-PUBLIC STRINGOUT()
         DEFINE('STRINGOUT(A,SEP)I')                    :(STRINGOUT_END)
*
STRINGOUT
         I = 1
         STRINGOUT = A<1>                                     :F(RETURN)
STRINGOUT_1
         I = I + 1
         STRINGOUT = STRINGOUT SEP A<I>         :S(STRINGOUT_1)F(RETURN)
*
STRINGOUT_END
*
* CE: .MSNOBOL4;
