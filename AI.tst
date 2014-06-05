#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'AI.INC'
-LINE 39 "AI.lss"
-INCLUDE 'CRACK.INC'
         &CODE = 1
         A = %'5,6,7'
         I = %'3,2,1'
         A2 = AI(A, I)
         EQ(A2<1>, 7)                                            :F(END)
         EQ(A2<2>, 6)                                            :F(END)
         EQ(A2<3>, 5)                                            :F(END)
         EQ(AI(A, 1), 5)                                         :F(END)
         AI(A, 4)                                                :S(END)
         &CODE = 0
END
