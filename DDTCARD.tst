#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'DDTCARD.INC'
-LINE 21 "DDTCARD.lss"
START    &CODE = 1
         &CODE = 0
END START
