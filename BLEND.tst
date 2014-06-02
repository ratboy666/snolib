#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'BLEND.INC'
-LINE 34 "BLEND.lss"
         &CODE = 1
         IDENT(BLEND('ABC', '123'), 'A1B2C3')                    :F(END)
         &CODE = 0
END
