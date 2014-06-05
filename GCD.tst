#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'GCD.INC'
-LINE 29 "GCD.lss"
         &CODE = 1
         EQ(GCD(1071, 1029), 21)                                 :F(END)
         &CODE = 0
END
