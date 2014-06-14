-MODULE APPENDA
-LINE 12 "APPENDA.lss"
-INCLUDE 'SEQ.INC'
-INCLUDE 'SIZEA.INC'
-IN72
-LINE 41 "APPENDA.lss"
-STITL AI
-EJECT
*
************************************************************************
*                                                                      *
*       #     ######   ######   #######  #     #  ######      #        *
*      # #    #     #  #     #  #        ##    #  #     #    # #       *
*     #   #   #     #  #     #  #        # #   #  #     #   #   #      *
*    #     #  ######   ######   #####    #  #  #  #     #  #     #     *
*    #######  #        #        #        #   # #  #     #  #######     *
*    #     #  #        #        #        #    ##  #     #  #     #     *
*    #     #  #        #        #######  #     #  ######   #     #     *
*                                                                      *
* APPENDA              APPEND ELEMENT TO ARRRAY                        *
*                                                                      *
************************************************************************
*
* APPENDA.lss
*
-LINE 17 "APPENDA.lss"
-PUBLIC APPENDA()
*
         DEFINE('APPENDA(A,V)I')                          :(END_APPENDA)
*
APPENDA  APPENDA = ARRAY(SIZEA(A) + 1)
         SEQ(' APPENDA<I> = A<I>', .I)
         APPENDA<I> = V                                        :(RETURN)
*
END_APPENDA
*
* CE: .MSNOBOL4;
