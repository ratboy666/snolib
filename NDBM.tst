#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'NDBM.INC'
-LINE 44 "NDBM.lss"
         &CODE = 1
         HANDLE = DBM_OPEN('db', 'CW', '0660')                   :F(END)
         OUTPUT = HANDLE
         DBM_CLOSE(HANDLE)                                       :F(END)
         HANDLE = DBM_OPEN('db', 'W')                            :F(END)
         DDD = '++' DUPL(' ', 1100) '++'
         DBM_STORE(HANDLE, 'KEY1', DDD, DBM_REPLACE)             :F(END)
         DBM_STORE(HANDLE, 'KEY2', 'DATA2', DBM_INSERT)          :F(END)
         OUTPUT = DBM_FETCH(HANDLE, 'KEY1')                      :F(END)
         OUTPUT = DBM_FETCH(HANDLE, 'KEY2')                      :F(END)
         OUTPUT = DBM_FIRSTKEY(HANDLE)                           :F(END)
NXTK     OUTPUT = DBM_NEXTKEY(HANDLE)                           :S(NXTK)
         DBM_CLOSE(HANDLE)                                       :F(END)
         DELETE('db.db')
         &CODE = 0
END
