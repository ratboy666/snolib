-MODULE ARRAY0
-LINE 11 "ARRAY0.lss"
-INCLUDE 'SYSTEM.INC'
-IN72
-LINE 35 "ARRAY0.lss"
-STITL ARRAY0
-EJECT
*
************************************************************************
*                                                                      *
*            #     ######   ######      #     #     #   ####           *
*           # #    #     #  #     #    # #     #   #   #   ##          *
*          #   #   #     #  #     #   #   #     # #    #  # #          *
*         #     #  ######   ######   #     #     #     # #  #          *
*         #######  #   #    #   #    #######     #     ##   #          *
*         #     #  #    #   #    #   #     #     #     #    #          *
*         #     #  #     #  #     #  #     #     #      ####           *
*                                                                      *
* ARRAY0                      ARRAY OF SIZE 0                          *
*                                                                      *
************************************************************************
*
* ARRAY0.lss
*
-LINE 15 "ARRAY0.lss"
-PUBLIC ARRAY0
*
         ARRAY0 = ARRAY('-10000:-10000')
         ARRAY0 = ?(SYSTEM() ? 'CSNOBOL4') ARRAY('0:-1')
*
* CE: .F.MSNOBOL4;
