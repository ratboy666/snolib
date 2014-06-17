#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'DSERVE.INC'
-LINE 197 "DSERVE.lss"
         &CODE = 1
*
* INITIALIZE DSERVE WITH APPLICATION NAME, PORT, AND SIGNON KEY
*
         DSERVE_INIT('DSERVE TEST', 54321, 'magic')
*
* THE APPLICATION. A SIMPLE COUNTING LOOP. AT THE BEGINNING OF EACH
* MAJOR LOOP, POLL DSERVE(), WHICH POSSIBLY ENTERS THE DEBUGGER.
*
LUP      DSERVE()
         MAJOR = MAJOR + 1
         TERMINAL = 'MAJOR = ' MAJOR
         N = 0
LUP2     N = N + 1
         LT(N, 10000000)                                  :S(LUP2)F(LUP)
         &CODE = 0
END
