-STITL MAX
-EJECT
-LINE 20 "MAX.lss"
*
************************************************************************
*                                                                      *
*                      #     #     #     #     #                       *
*                      ##   ##    # #     #   #                        *
*                      # # # #   #   #     # #                         *
*                      #  #  #  #     #     #                          *
*                      #     #  #######    # #                         *
*                      #     #  #     #   #   #                        *
*                      #     #  #     #  #     #                       *
*                                                                      *
* MAX                      MAX/MIN FUNCTIONS                           *
*                                                                      *
************************************************************************
*
* MAX.lss
*
         DEFINE('MAX(X,Y)')
         DEFINE('MIN(X,Y)')                                   :(MAX_END)
*
MAX      MAX = GT(X, Y) X                                     :S(RETURN)
         MAX = Y                                               :(RETURN)
*
MIN      MIN = LT(X, Y) X                                     :S(RETURN)
         MIN = Y                                               :(RETURN)
*
MAX_END
*
* CE: .MSNOBOL4;
