#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'ITERDIR.INC'
-LINE 122 "ITERDIR.lss"
         &CODE = 1
         DI = ITER_DIR(FENCE 'W')
TOP1       OUTPUT = VALUE_DIR(DI)                               :F(BTM1)
         DI = NEXT_DIR(DI)                                       :(TOP1)
BTM1
*
         DI = ITER_DIR('c*')
TOP2       OUTPUT = VALUE_DIR(DI)                               :F(BTM2)
         DI = NEXT_DIR(DI)                                       :(TOP2)
BTM2
         &CODE = 0
END
