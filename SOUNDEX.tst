#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'SOUNDEX.INC'
-LINE 29 "SOUNDEX.lss"
         &CODE = 1
         IDENT(SOUNDEX('washington'), 'W252')                    :F(END)
         &CODE = 0
END
