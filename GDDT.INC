-HIDE
*
* CE: .MSNOBOL4;
*
* GDDT GUI Debugger
*
* THE SOURCE LISTING WILL NOT BE LOADED INTO THE DDT INSTANCE, BUT
* INTO THE FRONT-END.
*
-INCLUDE 'STCL.INC'
-INCLUDE 'REPL.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'DDT.INC'
-EJECT
-STITL GDDT
*
         DEFINE('DDT_HOOK_FUNC(F,ARG)')                  :(DDT_HOOK_END)
*
* F IS DISPLAY, BREAK, READ
DDT_HOOK_FUNC
*
* DISPLAY ADDS THE LINE TO THE LOG
*
         F 'DISPLAY'                                      :F(DDT_HOOK_2)
DDT_HOOK_6
         ARG = REPL(ARG, '\', '\\')
         ARG = REPL(ARG, '$', '\$')
         ARG = REPL(ARG, '"', '\"') '\n'
         STCL_EVAL(TCL, '.f2.log configure -state normal')
         STCL_EVAL(TCL, '.f2.log insert end "' ARG '"')
         STCL_EVAL(TCL, '.f2.log see end')
         STCL_EVAL(TCL, '.f2.log configure -state disabled')
                                                           :(DDT_HOOK_9)
*
* BREAK REMOVES ANY HIGHLIGHT, HIGHLIGHTS THE NEW LINE AND REPOSITIONS
* THE SOURCE WINDOW
*
DDT_HOOK_2
         F 'BREAK'                                        :F(DDT_HOOK_4)
         IDENT(DDT_BL)                                    :S(DDT_HOOK_3)
         STCL_EVAL(TCL, '.f1.src tag delete bl')
         DDT_BL =
DDT_HOOK_3
         DDT_BL = SRC<+ARG>
         IDENT(DDT_BL)                                    :S(DDT_HOOK_5)
* FIXME - used lineend?
         STCL_EVAL(TCL, '.f1.src tag configure bl -background blue')
         STCL_EVAL(TCL, '.f1.src tag add bl ' DDT_BL '.0 ' DDT_BL + 1 '.0')
         STCL_EVAL(TCL, '.f1.src see ' DDT_BL '.0')        :(DDT_HOOK_9)
DDT_HOOK_5
         ARG = 'BREAK STNO ' ARG                           :(DDT_HOOK_6)
*
* READ COMMAND
*
* RETURN COMMAND. DDT_USE_R MUST BE NON-NULL (= 2). WE SHOULD HAVE
* AN "UNLOCK" ICON TO INDICATE READY FOR COMMAND.
* SEE LINE 370 IN DDT.lss FOR THE GORY DETAILS.
*
DDT_HOOK_4
         F 'READ'                                         :F(DDT_HOOK_9)
         STCL_SETVAR(TCL, 'command', '')
         STCL_EVAL(TCL, 'focus .f3.cmd')
         STCL_EVAL(TCL, 'vwait go')
*
* EXTRACT COMMAND AND RETURN IT.
*
         DDT_HOOK_FUNC = STCL_GETVAR(TCL, 'command')           :(RETURN)
DDT_HOOK_9
         STCL_EVAL(TCL, 'update')                              :(RETURN)
*
DDT_HOOK_END
*
         DEFINE('GDDT(LSTF)') :(GDDT_END)
*
* ESTABLISH HOOK FUNCTION FOR DDT
*
GDDT     DDT_HOOK = 'DDT_HOOK_FUNC'
         DDT_USE_R = 2
         DETACH(.DDT_T)
         ENDFILE(DDT_T_UNIT)
*
* CREATE TCL INTERPRETER FOR DDT GUI
*
         TCL = STCL_CREATEINTERP()
         TCL_VERSION = STCL_GETVAR(TCL, 'tcl_version')
         TERMINAL = IDENT(TCL_VERSION) 'COULD NOT GET TCL_VERSION'
+                                                                :S(END)
*        OUTPUT = 'TCL VERSION: ' TCL_VERSION
         NUM = SPAN('0123456789')
         VPAT = NUM '.' NUM
         TCL_VERSION VPAT . VER                               :S(CHECKV)
         TERMINAL = 'COULD NOT PARSE TCL_VERSION'                 :(END)
CHECKV   LT(VER, 8.4)                                        :S(CHECKTK)
         STCL_EVAL(TCL, 'package require Tk')                    :F(END)
CHECKTK  TK_VERSION = STCL_GETVAR(TCL, 'tk_version')            :F(NOTK)
         DIFFER(TK_VERSION)                                   :S(HAVETK)
NOTK     TERMINAL = 'COULD NOT FIND TK_VERSION'                   :(END)
HAVETK
*        OUTPUT = 'TK VERSION: ' TK_VERSION
*
* GDDT DEBUGGER
*
         STCL_EVAL(TCL, 'wm title . GDDT')
*
* FONT TO BE USED
*
         STCL_EVAL(TCL, 'font create mono -family Courier -size 16')
*
* LISTING VIEW WINDOW
*
         STCL_EVAL(TCL, 'frame .f1')
         STCL_EVAL(TCL, 'text .f1.src -width 80 -height 24'
+                       ' -borderwidth 2 -relief raised -setgrid 2'
+                       ' -wrap none -tabs 8 -font mono'
+                       ' -yscrollcommand {.f1.scroll set}')
         STCL_EVAL(TCL, 'scrollbar .f1.scroll -command {.f1.src yview}')
         STCL_EVAL(TCL, 'pack .f1.scroll -side right -fill y')
         STCL_EVAL(TCL, 'pack .f1.src -side left -fill both'
+                       '  -expand true')
         STCL_EVAL(TCL, 'pack .f1 -side top -fill both -expand true')
*
* COMMAND FEEDBACK WINDOW
*
         STCL_EVAL(TCL, 'frame .f2')
         STCL_EVAL(TCL, 'text .f2.log -width 80 -height 5'
+                       ' -borderwidth 2 -relief raised -setgrid 2'
+                       ' -font mono'
+                       ' -yscrollcommand {.f2.scroll set}')
         STCL_EVAL(TCL, 'scrollbar .f2.scroll -command {.f2.log yview}')
         STCL_EVAL(TCL, 'pack .f2.scroll -side right -fill y')
         STCL_EVAL(TCL, 'pack .f2.log -side left -fill both'
+                       '  -expand true')
         STCL_EVAL(TCL, 'pack .f2 -side top -fill both -expand true')
*
* COMMAND ENTRY AREA
*
         STCL_EVAL(TCL, 'global go')
         STCL_EVAL(TCL, 'frame .f3 -borderwidth 10')
         STCL_EVAL(TCL, 'pack .f3 -side top -fill x')
         STCL_EVAL(TCL, 'button .f3.go -text Cmd'
+                       ' -command {set go exec}')
         STCL_EVAL(TCL, 'pack .f3.go -side right')
         STCL_EVAL(TCL, 'label .f3.l -text Command: -padx 0')
         STCL_EVAL(TCL, 'entry .f3.cmd -relief sunken '
+                        '-textvariable command -font mono')
         STCL_EVAL(TCL, 'global command')
         STCL_EVAL(TCL, 'pack .f3.l -side left')
         STCL_EVAL(TCL, 'pack .f3.cmd -side left -fill x -expand true')
         STCL_EVAL(TCL, 'bind .f3.cmd <Return> {set go exec}') 
*
* LOAD LISTING
*
         U = IO_FINDUNIT()
         INPUT(.IN, U,, LSTF)
         SRC = TABLE()
         STCL_EVAL(TCL, 'global p')
LSTNXT   S = TRIM(IN)                                         :F(LSTEND)
         STNO =
         S FENCE SPAN(&DIGITS) . STNO
         S = REPL(S, CHARS_FF)
         S = REPL(S, '\', '\\')
         S = REPL(S, '$', '\$')
         S = REPL(S, '"', '\"')
         STCL_EVAL(TCL, 'set p [.f1.src index end]')
         P = STCL_GETVAR(TCL, 'p')
         P '.0' =
         SRC<+STNO> = DIFFER(STNO) P - 1
         STCL_EVAL(TCL, '.f1.src insert end "' S '\n"')        :(LSTNXT)
LSTEND   DETACH(.IN)
         ENDFILE(U)
         STCL_EVAL(TCL, '.f1.src configure -state disabled')
*
         S = 'GDDT - EXPERIMENTAL'
         STCL_EVAL(TCL, '.f2.log insert end "' S '\n"')
         STCL_EVAL(TCL, '.f2.log configure -state disabled')   :(RETURN)
*
GDDT_END
-LIST
