#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'HEX.INC'
-LINE 39 "HEX.lss"
         &CODE = 1
         OUTPUT = HEX('0')
         OUTPUT = HEX(&ALPHABET)
         &CODE = 0
END
