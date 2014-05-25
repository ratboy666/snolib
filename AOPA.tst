#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'AOPA.INC'
-LINE 41 "AOPA.lss"
-INCLUDE 'CRACK.INC'
         &CODE = 1
         A = %'1,2,3'
         B = %'10,20,30'
* ARRAY OPERATION ARRAY
         C = AOPA(A, '+', B)
         EQ(C<1>, 11)                                            :F(END)
         EQ(C<2>, 22)                                            :F(END)
         EQ(C<3>, 33)                                            :F(END)
* ARRAY OPERATION SCALAR
         C = AOPA(A, '-', 1)
         EQ(C<1>, 0)                                             :F(END)
         EQ(C<2>, 1)                                             :F(END)
         EQ(C<3>, 2)                                             :F(END)
* SCALAR OPERATION SCALAR
         C = AOPA(3, '*', B)
         EQ(C<1>, 30)                                            :F(END)
         EQ(C<2>, 60)                                            :F(END)
         EQ(C<3>, 90)                                            :F(END)
* SCALAR OPERATION SCALAR
         EQ(AOPA(6, '/', 3), 2)                                  :F(END)
         &CODE = 0
END
