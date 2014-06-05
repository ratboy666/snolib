-LINE 11 "COPYL.lss"
-INCLUDE 'LINK.INC'
-STITL COPYL
-EJECT
-LINE 48 "COPYL.lss"
*
************************************************************************
*                                                                      *
*                 #####   #######  ######   #     #  #                 *
*                #     #  #     #  #     #   #   #   #                 *
*                #        #     #  #     #    # #    #                 *
*                #        #     #  ######      #     #                 *
*                #        #     #  #           #     #                 *
*                #     #  #     #  #           #     #                 *
*                 #####   #######  #           #     #######           *
*                                                                      *
* COPYL                        COPY LIST                               *
*                                                                      *
************************************************************************
*
* COPYL.lss
*
-LINE 15 "COPYL.lss"
-MODULE COPYL
-PUBLIC COPYL()
         DEFINE('COPYL(L)T')                                :(COPYL_END)
*
COPYL    DEFINE('COPYL(L)', 'COPYL_1')
         T = TABLE(100)
         COPYL = COPYL(L)
         DEFINE('COPYL(L)T')                                   :(RETURN)
COPYL_1  COPYL = L
         IDENT(DATATYPE(L), 'LINK')                           :F(RETURN)
         COPYL = T<L>
         DIFFER(COPYL, NULL)                                  :S(RETURN)
         COPYL = COPY(L)
         T<L> = COPYL
         VALUE(COPYL) = COPYL(VALUE(L))
         NEXT(COPYL) = COPYL(NEXT(L))                          :(RETURN)
*
COPYL_END
*
* CE: .MSNOBOL4;
