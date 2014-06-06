#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'ORDER.INC'
-LINE 27 "ORDER.lss"
         &CODE = 1
         IDENT(ORDER('DCBA'), 'ABCD')                            :F(END)
         &CODE = 0
END
