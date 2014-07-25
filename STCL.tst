#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-TITLE TCL_TEST
-LINE 75 "STCL.lss"
START
-INCLUDE 'STCL.INC'
-STITL
-EJECT
*
         INTERP = STCL_CREATEINTERP()
         TCL_VERSION = STCL_GETVAR(INTERP, "tcl_version")
         OUTPUT = IDENT(TCL_VERSION) "COULD NOT GET TCL_VERSION" :S(END)
         OUTPUT = "TCL VERSION: " TCL_VERSION
*
* CHECK TCL VERSION
         NUM = SPAN('0123456789')
         VPAT = NUM '.' NUM
         TCL_VERSION VPAT . VER                               :S(CHECKV)
         OUTPUT = "COULD NOT PARSE TCL_VERSION"                   :(END)

CHECKV   LT(VER, 8.4)                                        :S(CHECKTK)

* TCL 8.4 AND LATER CAN DYNAMICLY LOAD TK!
         STCL_EVAL(INTERP, "package require Tk")                 :F(END)

* CHECK FOR TK
CHECKTK  TK_VERSION = STCL_GETVAR(INTERP, "tk_version")         :F(NOTK)
         DIFFER(TK_VERSION)                                   :S(HAVETK)
*
NOTK     OUTPUT = "COULD NOT FIND TK_VERSION"                     :(END)
*
HAVETK   OUTPUT = "TK VERSION: " TK_VERSION
*
         STCL_EVAL(INTERP,
+           'button .hello -text "Hello, world" '
+           '              -command {set val hello};'
+           "pack .hello;"
+           'button .other -text "Other Choice" '
+           '              -command {set val other};'
+           "pack .other;"
+           "global val;"
+           "vwait val")
*
         OUTPUT = STCL_GETVAR(INTERP, "val")
*
END START
