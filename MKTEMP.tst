#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'MKTEMP.INC'
-LINE 27 "MKTEMP.lss"
         &CODE = 1
         F = MKTEMP()
         FILE(F)                                                 :F(END)
         DELETE(F)
         &CODE = 0
END
