#!/usr/bin/bash
         exec "/usr/local/bin/snobol4" "-b" "$0" "$@"
-INCLUDE 'SIZEA.INC'
-LINE 65 "SIZEA.lss"
*
         &CODE = 1
         OUTPUT = 'SIZEA/LOWA ARRAY(10)'
         OUTPUT = SIZEA(ARRAY(10))
         OUTPUT = LOWA(ARRAY(10))
         OUTPUT = 'SIZEA/LOWA NULL'
         OUTPUT = SIZEA('')
         OUTPUT = LOWA('')
         OUTPUT = 'SIZEA/LOWA ARRAY(-10:10)'
         OUTPUT = SIZEA(ARRAY('-10:10'))
         OUTPUT = LOWA(ARRAY('-10:10'))
         OUTPUT = 'SIZEA/LOWA ARRAY0'
         OUTPUT = SIZEA(ARRAY0)
         OUTPUT = LOWA(ARRAY0)
         &CODE = 0
END
