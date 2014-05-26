#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'CH.INC'
-LINE 35 "CH.lss"
         &CODE = 1
         IDENT(CH('414243'), 'ABC')                              :F(END)
         &CODE = 0
END
