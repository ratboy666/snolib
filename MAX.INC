-MODULE MAX
-LINE 9 "MAX.lss"
-STITL MAX
-LINE 24 "MAX.lss"
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
