#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'CATA.INC'
-LINE 30 "CATA.lss"
-INCLUDE 'CRACK.INC'
         &CODE = 1
         A = %'5,6,7'
         B = %'3,2,1'
         C = CATA(A, B)
         EQ(C<1>, 5)                                             :F(END)
         EQ(C<2>, 6)                                             :F(END)
         EQ(C<3>, 7)                                             :F(END)
         EQ(C<4>, 3)                                             :F(END)
         EQ(C<5>, 2)                                             :F(END)
         EQ(C<6>, 1)                                             :F(END)
         &CODE = 0
END
