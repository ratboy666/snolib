#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'AGT.INC'
-LINE 34 "MD5.lss"
         &CODE = 1
         OUTPUT = MD5('hello, world')
         &CODE = 0
END
