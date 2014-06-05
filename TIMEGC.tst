#!/usr/bin/bash
         exec "snobol4" "-b" "-s" "$0" "$@"
-INCLUDE 'TIMEGC.INC'
-LINE 58 "TIMEGC.lss"
         &CODE = 1
* DEFAULT MEMORY IS 8MB
         TIMEGC(3500)
         TIMEGC(25)
         &CODE = 0
END
