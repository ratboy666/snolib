#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'AGT.INC'
-LINE 24 "AGT.lss"
         &CODE = 1
         AGT('abd', 'ABC')                                       :F(END)
         AGT('abc', 'ABC')                                       :S(END)
         &CODE = 0
END
