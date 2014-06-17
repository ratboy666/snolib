-MODULE FORMAT
-LINE 8 "FORMAT.lss"
-IN72
-LINE 359 "FORMAT.lss"
-STITL FORMAT
-EJECT
*
************************************************************************
*                                                                      *
*         #######  #######  ######   #     #     #     #######         *
*         #        #     #  #     #  ##   ##    # #       #            *
*         #        #     #  #     #  # # # #   #   #      #            *
*         #####    #     #  ######   #  #  #  #     #     #            *
*         #        #     #  #   #    #     #  #######     #            *
*         #        #     #  #    #   #     #  #     #     #            *
*         #        #######  #     #  #     #  #     #     #            *
*                                                                      *
* FORMAT                 FORTRAN IV FORMAT()                           *
*                                                                      *
************************************************************************
*
* FORMAT.lss
*
-LINE 11 "FORMAT.lss"
-LINE 12 "FORMAT.lss"
-LINE 13 "FORMAT.lss"
-LINE 14 "FORMAT.lss"
-LINE 15 "FORMAT.lss"
-LINE 16 "FORMAT.lss"
-LINE 17 "FORMAT.lss"
-LINE 20 "FORMAT.lss"
         format = 'format.c'
-LINE 271 "FORMAT.lss"
-LINE 272 "FORMAT.lss"
-LINE 273 "FORMAT.lss"
-LINE 274 "FORMAT.lss"
-LINE 275 "FORMAT.lss"
-LINE 276 "FORMAT.lss"
-LINE 341 "FORMAT.lss"
-PUBLIC FTN_FORMAT()
*
         LOAD('FTN_FORMAT(STRING,STRING)STRING', 'format.so')
*
* CE: .MSNOBOL4;
