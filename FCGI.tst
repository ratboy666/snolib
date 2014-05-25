#!/usr/bin/bash
         export "SNOLIB=/export/home/fred/snolib/snolib"; export "SNOPATH=/export/home/fred/snolib/snolib"
         exec "/usr/local/bin/snobol4" "-b" "$0" "$@"
-LINE 296 "FCGI.lss"
-INCLUDE 'FCGI.INC'
*
         &CODE = 1
         &CODE = 0
END
