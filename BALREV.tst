#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'BALREV.INC'
-LINE 27 "BALREV.lss"
         &CODE = 1
         IDENT(BALREV('F(X)'), '(X)F')                           :F(END)
         &CODE = 0
END
