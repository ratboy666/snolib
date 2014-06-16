#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'MD5.INC'
-LINE 35 "MD5.lss"
         &CODE = 1
         R = 'e4d7f1b4ed2e42d15898f4b27b019da4'
         IDENT(R, MD5('hello, world'))                           :F(END)
         &CODE = 0
END
