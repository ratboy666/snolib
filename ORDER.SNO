-MODULE ORDER
-LINE 9 "ORDER.lss"
-IN72
-LINE 37 "ORDER.lss"
-STITL ORDER
-EJECT
*
************************************************************************
*                                                                      *
*                #######  ######   ######   #######  ######            *
*                #     #  #     #  #     #  #        #     #           *
*                #     #  #     #  #     #  #        #     #           *
*                #     #  ######   #     #  #####    ######            *
*                #     #  #   #    #     #  #        #   #             *
*                #     #  #    #   #     #  #        #    #            *
*                #######  #     #  ######   #######  #     #           *
*                                                                      *
* ORDER                   ORDER CHARACTERS IN STRING                   *
*                                                                      *
************************************************************************
*
* ORDER.lss
*
-LINE 12 "ORDER.lss"
-PUBLIC ORDER()
*
         DEFINE('ORDER(S)T,HIGHS,S1')                       :(ORDER_END)
*
ORDER    S LEN(1) . T =                                       :F(RETURN)
         &ALPHABET BREAK(T) REM . HIGHS
         ORDER (BREAK(HIGHS) | REM) . S1 = S1 T                 :(ORDER)
*
ORDER_END
*
* CE: .MSNOBOL4;
