-MODULE COPYT
-LINE 8 "COPYT.lss"
-IN72
-LINE 34 "COPYT.lss"
-STITL COPYT
-EJECT
*
************************************************************************
*                                                                      *
*              #####   #######  ######   #     #  #######              *
*             #     #  #     #  #     #   #   #      #                 *
*             #        #     #  #     #    # #       #                 *
*             #        #     #  ######      #        #                 *
*             #        #     #  #           #        #                 *
*             #     #  #     #  #           #        #                 *
*              #####   #######  #           #        #                 *
*                                                                      *
* COPYT                      COPY A TABLE                              *
*                                                                      *
************************************************************************
*
* COPYT.lss
*
-LINE 11 "COPYT.lss"
-PUBLIC COPYT()
*
         DEFINE('COPYT(T)')                                 :(COPYT_END)
*
COPYT    COPYT = TABLE()
         COPYT = CONVERT(CONVERT(T, 'ARRAY'), 'TABLE')         :(RETURN)
*
COPYT_END
*
* CE: .MSNOBOL4;
