#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'REDEFINE.INC'
-LINE 50 "REDEFINE.lss"
         &CODE = 1
         &CODE = 0
END
