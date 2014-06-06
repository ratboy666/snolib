#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'LPROG.INC'
-LINE 31 "LPROG.lss"
         &CODE = 1
         EQ(LPROG(), 9)                                          :F(END)
         &CODE = 0
END
