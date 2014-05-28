-STITL ORDER
-EJECT
*
-LINE 30 "ORDER.lss"
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
-LINE 7 "ORDER.lss"
         DEFINE('ORDER(S)T,HIGHS,S1')                       :(ORDER_END)
*
ORDER    S LEN(1) . T =                                       :F(RETURN)
         &ALPHABET BREAK(T) REM . HIGHS
         ORDER (BREAK(HIGHS) | REM) . S1 = S1 T                 :(ORDER)
*
ORDER_END
*
* CE: .MSNOBOL4;
