-MODULE FLOOR
-LINE 11 "FLOOR.lss"
-INCLUDE 'DEXP.INC'
-IN72
-LINE 40 "FLOOR.lss"
-STITL FLOOR
-EJECT
*
************************************************************************
*                                                                      *
*              #######  #        #######  #######  ######              *
*              #        #        #     #  #     #  #     #             *
*              #        #        #     #  #     #  #     #             *
*              #####    #        #     #  #     #  ######              *
*              #        #        #     #  #     #  #   #               *
*              #        #        #     #  #     #  #    #              *
*              #        #######  #######  #######  #     #             *
*                                                                      *
* FLOOR              FLOOR AND CEIL FUNCTIONS                          *
*                                                                      *
************************************************************************
*
* FLOOR.lss
*
-LINE 15 "FLOOR.lss"
-PUBLIC FLOOR(), CEIL()
*
         DEFINE('FLOOR(X)')
         DEXP('CEIL(X) = -FLOOR(-X)')                       :(FLOOR_END)
*
FLOOR    FLOOR = CONVERT(X, 'INTEGER')
         GE(X, 0)                                             :S(RETURN)
         FLOOR = NE(X, FLOOR) FLOOR - 1                        :(RETURN)
*
FLOOR_END
*
* CE: .MSNOBOL4;
