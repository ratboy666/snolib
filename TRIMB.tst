#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'TRIMB.INC'
-LINE 25 "TRIMB.lss"
         &CODE = 1
         IDENT(TRIMB(' ABC '), 'ABC')                            :F(END)
         &CODE = 0
*
END
