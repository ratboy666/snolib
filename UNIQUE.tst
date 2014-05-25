#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'UNIQUE.INC'
-LINE 48 "UNIQUE.lss"
         &CODE = 1
         U1 = UNIQUE()
         IDENT($U1)                                              :F(END)
         $U1 = 1
         U2 = UNIQUE()
         IDENT($U2)                                              :F(END)
         $U2 = 2
         NE($U1, $U2)                                            :F(END)
         U3 = 'U3_'
         $U3 = 3
         UNIQUE('CLEAR')
         IDENT($U1)                                              :F(END)
         IDENT($U2)                                              :F(END)
         EQ($U3, 3)                                              :F(END)
         &CODE = 0
END
