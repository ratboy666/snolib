#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'ORDER.INC'
-LINE 20 "ORDER.lss"
         &CODE = 1
         IDENT(ORDER('DCBA'), 'ABCD')                            :F(END)
         &CODE = 0
END
