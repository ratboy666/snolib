#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
         &CODE = 1
-LINE 18 "ENDCARD.lss"
         &CODE = 0
-INCLUDE 'ENDCARD.INC'
