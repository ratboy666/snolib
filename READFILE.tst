#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'READFILE.INC'
-LINE 68 "READFILE.lss"
         &CODE = 1
         OUTPUT = READFILE('sample.tmpl')                        :F(END)
         &CODE = 0
END
