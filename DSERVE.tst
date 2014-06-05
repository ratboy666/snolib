#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'DSERVE.INC'
-LINE 138 "DSERVE.lss"
         &CODE = 1
         DSERVE_INIT('TEST', 54321, 'magic')
LUP      DSERVE()
         MAJOR = MAJOR + 1
         TERMINAL = 'MAJOR = ' MAJOR
         N = 0
LUP2     N = N + 1
         LT(N, 10000000)                                  :S(LUP2)F(LUP)
         &CODE = 0
END
