-MODULE RANDOM
-LINE 9 "RANDOM.lss"
-IN72
-LINE 42 "RANDOM.lss"
-STITL RANDOM
-EJECT
*
************************************************************************
*                                                                      *
*         ######      #     #     #  ######   #######  #     #         *
*         #     #    # #    ##    #  #     #  #     #  ##   ##         *
*         #     #   #   #   # #   #  #     #  #     #  # # # #         *
*         ######   #     #  #  #  #  #     #  #     #  #  #  #         *
*         #   #    #######  #   # #  #     #  #     #  #     #         *
*         #    #   #     #  #    ##  #     #  #     #  #     #         *
*         #     #  #     #  #     #  ######   #######  #     #         *
*                                                                      *
* RANDOM                 RANDOM NUMBER FUNCTIONS                       *
*                                                                      *
* PHIL BUDNE <PHIL@ULTIMATE.COM>                                       *
* JANUARY 4, 2011                                                      *
*                                                                      *
************************************************************************
*
* RANDOM.lss
*
-LINE 12 "RANDOM.lss"
-PUBLIC RANDOM(), SRANDOM(), SRANDOMDEV() RANDOMI()
*
         LOAD('RANDOM()INTEGER')
         LOAD('SRANDOM(INTEGER)STRING')
         LOAD('SRANDOMDEV()STRING')
         DEFINE('RANDOMI(N)')                              :(RANDOM_END)
*
* RANDOM() RETURNS INTEGER 0 .. 2 ** 31 - 1
* RETURN 1 .. N
*
RANDOMI  RANDOMI = RANDOM()
         RANDOMI = RANDOMI / 2147483647.0
         RANDOMI = NE(N, 0) CONVERT(RANDOMI * N, 'INTEGER') + 1
                                                               :(RETURN)
RANDOM_END
*
* CE: .MSNOBOL4;
