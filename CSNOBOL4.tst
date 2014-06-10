#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'CSNOBOL4.INC'
-LINE 588 "CSNOBOL4.lss"
         &CODE = 1
         OUTPUT(.T_OUT, 10,, '/dev/stdout')
         T_OUT = 'HELLO, WORLD'
         FP = IO_GETFP(10)
         FD = FILENO(FP)
         OUTPUT = 'FILE * = ' FP
         OUTPUT = 'FD     = ' FD
         EQ(FD, 1)                                               :F(END)
         &CODE = 0
END
