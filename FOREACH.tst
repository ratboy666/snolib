#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'FOREACH.INC'
-LINE 55 "FOREACH.lss"
-INCLUDE 'DEXP.INC'
-INCLUDE 'CRACK.INC'
         &CODE = 1
         X = %'1,2,3'
         DEXP('F(X) = (S = S + X)')
         S = 0
         FOREACH(X, .F)
         EQ(S, 6)                                                :F(END)
         &CODE = 0                                                :(END)
END
