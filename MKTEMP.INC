-MODULE MKTEMP
-LINE 10 "MKTEMP.lss"
-INCLUDE 'BQ.INC'
-IN72
-LINE 39 "MKTEMP.lss"
-STITL MKTEMP
-EJECT
*
************************************************************************
*                                                                      *
*         #     #  #    #  #######  #######  #     #  ######           *
*         ##   ##  #   #      #     #        ##   ##  #     #          *
*         # # # #  #  #       #     #        # # # #  #     #          *
*         #  #  #  ###        #     #####    #  #  #  ######           *
*         #     #  #  #       #     #        #     #  #                *
*         #     #  #   #      #     #        #     #  #                *
*         #     #  #    #     #     #######  #     #  #                *
*                                                                      *
* MKTEMP               CREATE TEMPORARY FILE                           *
*                                                                      *
************************************************************************
*
* MKTEMP.lss
*
-LINE 14 "MKTEMP.lss"
-PUBLIC MKTEMP()
*
         DEFINE('MKTEMP()')                                :(MKTEMP_END)
*
MKTEMP   MKTEMP = BQ('mktemp')                                 :(RETURN)

MKTEMP_END
*
* CE: .MSNOBOL4;
