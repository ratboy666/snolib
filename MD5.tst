#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'MD5.INC'
-LINE 35 "MD5.lss"
         &CODE = 1
         OUTPUT = MD5('hello, world')
         &CODE = 0
END
