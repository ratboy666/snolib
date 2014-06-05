#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'RESOL.INC'
-LINE 41 "RESOL.lss"
         &CODE = 1
         OUTPUT = RESOLUTION()
         &CODE = 0
END
