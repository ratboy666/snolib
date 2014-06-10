-MODULE APPENDA
-IN72
-LINE 11 "APPENDA.lss"
-INCLUDE 'SEQ.INC'
-INCLUDE 'SIZEA.INC'
-LINE 40 "APPENDA.lss"
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
-LINE 16 "APPENDA.lss"
-PUBLIC APPENDA
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
