#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'COUNT.INC'
-LINE 28 "COUNT.lss"
         &CODE = 1
         EQ(COUNT('ABCABCABC', 'AB'), 3)                         :F(END)
         &CODE = 0
END
