#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'LOG.INC'
-LINE 19 "LOG.lss"
-INCLUDE 'FLOOR.INC'
         &CODE = 1
         EQ(CEIL(CLOG(1000)), 3)                                 :F(END)
         X = CLOG(EULERS_NUMBER) * LN(10)
         EQ(CEIL(X * 10000), 10000)                              :F(END)
         &CODE = 0
END
