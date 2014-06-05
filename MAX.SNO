-MODULE MAX
-LINE 10 "MAX.lss"
-STITL MAX
-LINE 25 "MAX.lss"
-EJECT
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
-PUBLIC MAX(), MIN()
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
