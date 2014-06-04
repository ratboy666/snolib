#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
*
* CE: .MSNOBOL4;
*
* GDDT.tst - test GUI debugger
*
-TITLE GDDT TEST
-INCLUDE 'GDDT.INC'
*
*         GDDT('GDDT.lst')
         DDT()
         TERMINAL = 'GUI DEBUG'
         I = 0
LUP      I = I + 1
         LT(I, 10)                                               :S(LUP)
         TERMINAL = 'LUP DONE'
*
END
