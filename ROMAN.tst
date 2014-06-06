#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'ROMAN.INC'
-LINE 42 "ROMAN.lss"
         &CODE = 1
LOOP     I = I + 1
         R = ROMAN(I)
         N = ARABIC(R)
         OUTPUT = NE(I, N) 'FAIL: ' I ' ' R ' ' N
         EQ(I, N)                                                :F(END)
         LT(I, 3999)                                            :S(LOOP)
         &CODE = 0
END
