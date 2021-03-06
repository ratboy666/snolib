#!/usr/bin/bash 
 exec "snobol4" "-b" "$0" "$@" 
-PLUSOPS 1 
MAIN. CODE('MAIN.')
-LINE 12 "sc.sc"
 label_lead = "L."
-LINE 13
 label_lead = HOST(4,"LABEL")
-LINE 14
 gl_options = ""
-LINE 15
 IDENT(.A,'A') :F(L.2)
-LINE 17
 OPSYN("MB_INPUT","INPUT")
-LINE 18
 OPSYN("MB_OUTPUT","OUTPUT")
-LINE 19
 CODE("SETEXIT :(RETURN)")
-LINE 20
 CODE("INPUT MB_INPUT(n,u,,fn) :S(RETURN)F(FRETURN)")
-LINE 21
 CODE("OUTPUT MB_OUTPUT(n,u,,fn) :S(RETURN)F(FRETURN)")
-LINE 22
 DEFINE("SETEXIT()")
-LINE 23
 DEFINE("INPUT(n,u,fn)")
-LINE 24
 DEFINE("OUTPUT(n,u,fn)")
-LINE 25
 gl_options = "-+ "
-LINE 28
L.2 DATA("b(op,l,r)")
-LINE 29
 DATA("u(op,r)")
-LINE 30
 DATA("i_fcall(name,head,tail)")
-LINE 31
 DATA("fcall(name,args,l,r)")
-LINE 32
 DATA("argexp(expr,next)")
-LINE 34
 stack = TABLE()
-LINE 35
 bconv = TABLE(30)
-LINE 36
 deflist = TABLE(50)
-LINE 37
 inctab = TABLE()
-LINE 38
 stno_tab = TABLE(100)
-LINE 55
 DATA("binfo(out,lp,rp,slp,srp,fn)")
-LINE 59
 bconv<'('> = par_binfo = binfo('',0)
-LINE 61
 bconv<'='> = binfo('=',1,2,0,1)
-LINE 62
 bconv<'?'> = binfo('?',2,2,1,1)
-LINE 63
 bconv<'|'> = binfo('|',3,3,2,2)
-LINE 64
 bconv<'||'> = or_binfo = binfo('',4,4,0,0,1)
-LINE 65
 bconv<'&&'> = cat_binfo = binfo(' ',5,5,4,4)
-LINE 66
 bconv<'>'> = binfo('GT',6,6,0,0,1)
-LINE 67
 bconv<'<'> = binfo('LT',6,6,0,0,1)
-LINE 68
 bconv<'>='> = binfo('GE',6,6,0,0,1)
-LINE 69
 bconv<'<='> = binfo('LE',6,6,0,0,1)
-LINE 70
 bconv<'=='> = binfo('EQ',6,6,0,0,1)
-LINE 71
 bconv<'!='> = binfo('NE',6,6,0,0,1)
-LINE 72
 bconv<'::'> = binfo('IDENT',6,6,0,0,1)
-LINE 73
 bconv<':!:'> = binfo('DIFFER',6,6,0,0,1)
-LINE 74
 bconv<':>:'> = binfo('LGT',6,6,0,0,1)
-LINE 75
 bconv<':<:'> = binfo('LLT',6,6,0,0,1)
-LINE 76
 bconv<':>=:'> = binfo('LGE',6,6,0,0,1)
-LINE 77
 bconv<':<=:'> = binfo('LLE',6,6,0,0,1)
-LINE 78
 bconv<':==:'> = binfo('LEQ',6,6,0,0,1)
-LINE 79
 bconv<':!=:'> = binfo('LNE',6,6,0,0,1)
-LINE 80
 bconv<'+'> = binfo('+',7,7,5,5)
-LINE 81
 bconv<'-'> = binfo('-',7,7,5,5)
-LINE 82
 bconv<'/'> = binfo('/',8,8,7,7)
-LINE 83
 bconv<'*'> = binfo('*',8,8,8,8)
-LINE 84
 bconv<'%'> = binfo('REMDR',8,8,0,0,1)
-LINE 85
 bconv<'^'> = binfo('**',9,10,10,11)
-LINE 86
 bconv<'.'> = binfo('.',10,10,11,11)
-LINE 87
 bconv<'$'> = binfo('$',10,10,11,11)
-LINE 89
 ht = char(9)
-LINE 90
 optblank = nspan(" " ht)
-LINE 91
 blank = SPAN(" " ht)
-LINE 92
 digits = "0123456789"
-LINE 93
 letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
-LINE 95
 integer = SPAN(digits)
-LINE 96
 exponent = ANY("eEdD") (ANY("+-") | "") integer
-LINE 97
 real = integer "." (integer | "") (exponent | "") 
+| integer exponent | "." integer (exponent | "")
-LINE 99
 number = real | integer
-LINE 101
 string = ANY("'" '"') $ squote BREAK(*squote) LEN(1)
-LINE 103
 constant = number | string
-LINE 104
 identifier = ANY(letters) nspan(letters digits)
-LINE 105
 unaryop = ANY("+-*&@~?.$^%|")
-LINE 106
 binaryop = "==" | "!=" | "<=" | ">=" | "&&" | "||"
+ | ":==:" | ":!=:" | ":>:" | ":<:" | ":>=" | ":<=:"
+ | "::" | ":!:" | ANY("+-*/<>=^.$?|%")
-LINE 110
 fcall = identifier . *mkfcall() optblank ("(" list(*expr 
+. *invoke(.mkarg),optblank ",") optblank ")" . *invoke(.endfc) 
+| "[" list(*expr . *invoke(.mkarg),optblank ",") optblank 
+"]" . *invoke(.endfc) . *invoke(.mkarray))
-LINE 116
 term = optblank (constant . *push() . *dotck() | identifier 
+. *push() | "(" *expr optblank ")" | fcall)
-LINE 118
 operand = term | optblank unaryop . *push() *operand 
+. *invoke(.unop)
-LINE 120
 expr = "" . *begexp() *operand ARBNO(optblank binaryop 
+. *push() . *invoke(.mkbinfo) *operand . *invoke(.binop)) 
+"" . *endexp()
-LINE 124
 label = optblank identifier . lab . *emitlab(lab) optblank ":"
-LINE 126
 clausend = ANY("{}") . del | RPOS(0)
-LINE 128
 clause = FENCE ARBNO(label) optblank ("if" . cl_type 
+optblank "(" *expr optblank ")" | "while" . cl_type 
+optblank "(" *expr optblank ")" | (kw("return") | 
+kw("freturn") | kw("nreturn")) . cl_type optblank 
+("" . *push() | *expr) optblank clausend | "go" optblank 
+"to" blank identifier . dest . *invoke(.gocl) | ("{"
+ | "}") . cl_type | ("do" | kw("else")) . cl_type 
+(SPAN(" " ht) | RPOS(0)) | "procedure" . cl_type blank 
+identifier . fname | "struct" . cl_type blank identifier 
+. stname | "for" . cl_type optblank "(" *expr optblank 
+"," *expr optblank "," *expr optblank ")" | RPOS(0) 
+. cl_type *invoke(.emiteos) | *expr optblank clausend 
+. *invoke(.expcl))
-LINE 146
 gl_files = TABLE()
-LINE 147
 gl_lines = TABLE()
-LINE 148
 gl_index = 9
-LINE 149
 gl_first = 10
-LINE 151
 emit_stno = 0
-LINE 153
 &STLIMIT = -1
-LINE 158
 HOST() ? FENCE BREAKX(":") (":MS-DOS" | ":OS/2" | 
+":WinNT" | ":Win95") :F(L.3)
-LINE 160
 gl_extension = ".exe"
-LINE 161
 gl_delete = "del " :(L.4)
-LINE 164
L.3 gl_extension = ""
-LINE 165
 gl_delete = "rm "
-LINE 167
L.4 EXIT(3,"snocone" gl_extension)
-LINE 170
 gl_arg = HOST(3) - 1
-LINE 171
 HOST(2,HOST(3)) :S(L.5)
-LINE 172
 OUTPUT = "snocone: nothing to compile" :(END)
-LINE 176
L.5 gl_nextfile() :S(L.6)F(END)
-LINE 181
L.6 outfile = IDENT(outfile) "a"
-LINE 182
 &ERRLIMIT = &ERRLIMIT + 1
-LINE 183
 savexit = SETEXIT()
-LINE 184
 gl_options ? "-+" :F(L.7)
-LINE 185
 extension = ".sno" :(L.8)
-LINE 187
L.7 extension = ".spt"
-LINE 188
L.8 gl_options ? "-m" :F(L.9)
-LINE 189
 module = 1 :(L.10)
-LINE 191
L.9 module = 0
-LINE 192
L.10 OUTPUT(.outf,9,outfile extension) :S(L.11)
-LINE 193
 OUTPUT = "cannot write " outfile extension :(END)
-LINE 196
L.11 &ERRLIMIT = &ERRLIMIT - 1
-LINE 197
 SETEXIT(savexit)
-LINE 206
 options = ""
-LINE 207
 n
-LINE 208
 EQ(module,1) :F(L.12)
-LINE 209
 IDENT(label_lead,"L.") :F(L.13)
-LINE 210
 label_lead = outfile "."
L.13 
-LINE 212
L.12 initial_label = newlab()
-LINE 213
 gl_options ? "-+" :F(L.14)
-LINE 214
 EQ(module,0) :F(L.15)
-LINE 215
 emitlab("#!/usr/bin/bash")
-LINE 216
 emitlab(' exec "snobol4" ' options '"-b" "$0" "$@"')
-LINE 218
L.15 emitlab("-PLUSOPS 1")
-LINE 219
 emiteos()
-LINE 221
L.14 EQ(module,1) :F(L.16)
-LINE 222
 emitg(initial_label)
-LINE 223
 emiteos() :(L.17)
-LINE 225
L.16 emitlab("MAIN.")
-LINE 226
 emit("CODE('MAIN.')")
-LINE 227
 emiteos()
-LINE 231
L.17 nclause(1) :F(L.18)
-LINE 232
 IDENT(cl_type,"procedure") :F(L.19)
-LINE 233
 funct() :(L.20)
-LINE 234
L.19 IDENT(cl_type,"struct") :F(L.21)
-LINE 235
 dostruct() :(L.22)
-LINE 237
L.21 dostmt()
L.22 
-LINE 238
L.20  :(L.17)
L.18 
-LINE 242
EXIT EQ(module,1) :F(L.23)
-LINE 244
 emitlab(initial_label) :(L.24)
-LINE 246
L.23 emitg("END")
-LINE 247
 emitlab("START.")
-LINE 248
 emit("CODE('START.')")
-LINE 250
L.24 i = 1
L.25 LE(i,deflist<0>) :F(L.26)
-LINE 251
 emiteos()
-LINE 252
 deflist<i> ? pos(0) any("+-*") :F(L.27)
-LINE 253
 emitlab(deflist<i>) :(L.28)
-LINE 255
L.27 emit(deflist<i>)
-LINE 256
L.28 i = i + 1 :(L.25)
-LINE 259
L.26 emiteos()
-LINE 260
 gl_options ? "-+" :S(L.29)
-LINE 261
 emit("EXIT(3,'" outfile gl_extension "')")
-LINE 263
L.29 EQ(module,0) :F(L.30)
-LINE 266
 emit("&FULLSCAN = 1")
-LINE 267
 emiteos()
-LINE 268
 emit("&TRIM = 1")
-LINE 269
 emitg("MAIN.")
-LINE 270
 emiteos()
-LINE 273
L.30 EQ(module,0) :F(L.31)
-LINE 274
 outf = "END	START."
-LINE 275
L.31 ENDFILE(9)
-LINE 276
 EQ(module,0) :F(L.32)
-LINE 277
 HOST(1,"chmod +x " outfile extension)
-LINE 298
L.32  :(nspan.END)
-LINE 299
nspan nspan = SPAN(str) | "" :(RETURN)
-LINE 304
nspan.END  :(list.END)
-LINE 305
list list = item ARBNO(delim item) | "" :(RETURN)
-LINE 310
list.END  :(kw.END)
-LINE 311
kw kw = SPAN(letters) $ dummy CONVERT("ident(dummy,'"
+ s "')","EXPRESSION") :(RETURN)
-LINE 316
kw.END  :(push.END)
-LINE 317
push stackptr = stackptr + 1
-LINE 318
 push = .stack<stackptr> :(NRETURN)
-LINE 322
push.END  :(pop.END)
-LINE 323
pop pop = stack<stackptr>
-LINE 324
 stack<stackptr> = ""
-LINE 325
 stackptr = stackptr - 1 :(RETURN)
-LINE 329
pop.END  :(peek.END)
-LINE 330
peek GE(n,stackptr) :S(err)
-LINE 332
 peek = .stack<stackptr - n> :(NRETURN)
-LINE 337
peek.END  :(top.END)
-LINE 338
top top = .stack<stackptr> :(NRETURN)
-LINE 346
top.END  :(isbin.END)
-LINE 347
isbin (DIFFER(DATATYPE(x),'B'),DIFFER(fn(op(x)))) :S(FRETURN)F(L.33)
-LINE 349
L.33  :(RETURN)
-LINE 353
isbin.END  :(isneg.END)
-LINE 354
isneg (DIFFER(DATATYPE(x),'U'),DIFFER(op(x),'~')) :S(FRETURN)F(L.34)
-LINE 356
L.34  :(RETURN)
-LINE 360
isneg.END  :(dprint.END)
-LINE 361
dprint d = DATATYPE(x)
-LINE 362
 IDENT(d,'STRING') :F(L.35)
-LINE 363
 emit(x) :(RETURN)
-LINE 367
L.35 IDENT(d,'U') :F(L.36)
-LINE 369
 emit(op(x))
-LINE 370
 isbin(r(x)) :F(L.37)
-LINE 371
 emit('(')
-LINE 372
L.37 dprint(r(x))
-LINE 373
 isbin(r(x)) :F(L.38)
-LINE 374
 emit(')')
-LINE 375
L.38  :(RETURN)
-LINE 379
L.36 IDENT(d,'FCALL') :F(L.39)
-LINE 381
 emit(name(x))
-LINE 382
 emit(l(x))
-LINE 383
 r = args(x)
-LINE 384
L.40 DIFFER(r) :F(L.41)
-LINE 385
 emit(del)
-LINE 386
 dprint(expr(r))
-LINE 387
 del = ','
-LINE 388
 r = next(r) :(L.40)
-LINE 390
L.41 emit(r(x)) :(RETURN)
-LINE 394
L.39 IDENT(d,'B') :F(L.42)
-LINE 396
 op = op(x)
-LINE 397
 IDENT(op,or_binfo) :F(L.43)
-LINE 398
 emit('(')
-LINE 399
 bprint(x)
-LINE 400
 emit(')') :(RETURN)
-LINE 403
L.43 l = (isbin(l(x)) LT(slp(op(l(x))),srp(op)) 1,"")
-LINE 404
 r = (isbin(r(x)) GT(slp(op),srp(op(r(x)))) 1,"")
-LINE 407
 DIFFER(fn(op)) :F(L.44)
-LINE 408
 emit(out(op))
-LINE 409
 emit('(')
-LINE 410
 dprint(l(x))
-LINE 411
 emit(',')
-LINE 412
 dprint(r(x))
-LINE 413
 emit(')') :(RETURN)
-LINE 418
L.44 DIFFER(l) :F(L.45)
-LINE 419
 emit('(')
-LINE 420
L.45 dprint(l(x))
-LINE 421
 DIFFER(l) :F(L.46)
-LINE 422
 emit(')')
-LINE 423
L.46 emitb(out(op))
-LINE 424
 DIFFER(r) :F(L.47)
-LINE 425
 emit('(')
-LINE 426
L.47 dprint(r(x))
-LINE 427
 DIFFER(r) :F(L.48)
-LINE 428
 emit(')')
-LINE 429
L.48  :(RETURN)
-LINE 433
L.42 i = 1
-LINE 434
 emit(d)
-LINE 435
 emit('(')
-LINE 436
L.49 dprint(APPLY(FIELD(d,i),x)) :F(L.50)
-LINE 437
 i = i + 1
-LINE 438
 emit(',') :(L.49)
-LINE 440
L.50 emit(')') :(RETURN)
-LINE 448
dprint.END  :(bprint.END)
-LINE 449
bprint (DIFFER(DATATYPE(x),'B'),DIFFER(op(x),or_binfo)) :F(L.51)
-LINE 450
 dprint(x) :(RETURN)
-LINE 453
L.51 bprint(l(x))
-LINE 454
 emit(',')
-LINE 455
 bprint(r(x)) :(RETURN)
-LINE 464
bprint.END  :(sprint.END)
-LINE 465
sprint (IDENT(DATATYPE(x),'B') IDENT(op(x),cat_binfo)) :F(L.52)
-LINE 466
 emit('(')
-LINE 467
L.52 dprint(x)
-LINE 468
 (IDENT(DATATYPE(x),'B') IDENT(op(x),cat_binfo)) :F(L.53)
-LINE 469
 emit(')')
-LINE 470
L.53 emiteob() :(RETURN)
-LINE 476
sprint.END  :(invoke.END)
-LINE 477
invoke APPLY(f,'')
-LINE 478
 invoke = .dummy :(NRETURN)
-LINE 482
invoke.END  :(unop.END)
-LINE 483
unop r = pop()
-LINE 484
 op = pop()
-LINE 485
 push() = u(op,r) :(RETURN)
-LINE 490
unop.END  :(mkfcall.END)
-LINE 491
mkfcall push() = i_fcall()
-LINE 492
 mkfcall = .name(top()) :(NRETURN)
-LINE 496
mkfcall.END  :(mkarg.END)
-LINE 497
mkarg x = argexp(pop(),"")
-LINE 498
 f = top()
-LINE 499
 DIFFER(tail(f)) :F(L.54)
-LINE 500
 next(tail(f)) = x
-LINE 501
L.54 tail(f) = x
-LINE 502
 head(f) = IDENT(head(f)) x :(RETURN)
-LINE 506
mkarg.END  :(endfc.END)
-LINE 507
endfc f = pop()
-LINE 508
 push() = fcall(name(f),head(f),'(',')') :(RETURN)
-LINE 512
endfc.END  :(mkarray.END)
-LINE 513
mkarray t = top()
-LINE 514
 l(t) = '<'
-LINE 515
 r(t) = '>' :(RETURN)
-LINE 519
mkarray.END  :(begexp.END)
-LINE 520
begexp push() = bconv<'('>
-LINE 521
 begexp = .dummy :(NRETURN)
-LINE 527
begexp.END  :(binop.END)
-LINE 528
binop GE(lp(peek(3)),rp(peek(1))) :F(L.55)
-LINE 529
 newr = pop()
-LINE 530
 newop = pop()
-LINE 531
 r = pop()
-LINE 532
 op = pop()
-LINE 533
 l = pop()
-LINE 534
 push() = b(op,l,r)
-LINE 535
 push() = newop
-LINE 536
 push() = newr :(binop)
-LINE 538
L.55  :(RETURN)
-LINE 541
binop.END  :(endexp.END)
-LINE 542
endexp DIFFER(peek(1),par_binfo) :F(L.56)
-LINE 543
 r = pop()
-LINE 544
 op = pop()
-LINE 545
 l = pop()
-LINE 546
 push() = b(op,l,r) :(endexp)
-LINE 548
L.56 r = pop()
-LINE 549
 pop()
-LINE 550
 push() = r
-LINE 551
 endexp = .dummy :(NRETURN)
-LINE 557
endexp.END  :(mkbinfo.END)
-LINE 558
mkbinfo op = bconv<pop()>
-LINE 559
 IDENT(op) :S(err)
-LINE 561
 push() = op :(RETURN)
-LINE 569
mkbinfo.END  :(dotck.END)
-LINE 570
dotck top() ? FENCE '.' = '0.'
-LINE 571
 dotck = .dummy :(NRETURN)
-LINE 575
dotck.END  :(emitlab.END)
-LINE 576
emitlab DIFFER(l) :F(L.57)
-LINE 577
 emiteos()
-LINE 578
 st_lab = l
-LINE 580
L.57 emitlab = .dummy :(NRETURN)
-LINE 584
emitlab.END  :(emit.END)
-LINE 585
emit DIFFER(emit_eob) :F(L.58)
-LINE 586
 emiteos()
-LINE 587
L.58 st_body = st_body s :(RETURN)
-LINE 591
emit.END  :(emiteob.END)
-LINE 592
emiteob IDENT(emit_eob) :F(L.59)
-LINE 593
 buildstab(emit_stno,gi_file,gi_line)
-LINE 594
 emit_eob = 1
-LINE 596
L.59  :(RETURN)
-LINE 599
emiteob.END  :(emits.END)
-LINE 600
emits emiteob()
-LINE 601
 st_s = l :(RETURN)
-LINE 606
emits.END  :(emitf.END)
-LINE 607
emitf emiteob()
-LINE 608
 st_f = l :(RETURN)
-LINE 612
emitf.END  :(emitg.END)
-LINE 613
emitg emiteob()
-LINE 614
 st_s = IDENT(st_s) l
-LINE 615
 st_f = IDENT(st_f) l :(RETURN)
-LINE 619
emitg.END  :(emitb.END)
-LINE 620
emitb emit(' ')
-LINE 621
 DIFFER(s,' ') :F(L.60)
-LINE 622
 emit(s)
-LINE 623
 emit(' ')
-LINE 625
L.60  :(RETURN)
-LINE 629
emitb.END  :(emiteos.END)
-LINE 630
emiteos emit_eob = ""
-LINE 631
 (DIFFER(st_lab),DIFFER(st_body),DIFFER(st_s),DIFFER(st_f)) :F(L.61)
-LINE 632
 emit_stno = emit_stno + 1
-LINE 633
 out = st_lab " " st_body
-LINE 634
 (DIFFER(st_s),DIFFER(st_f)) :F(L.62)
-LINE 635
 goto = " :"
-LINE 636
 IDENT(st_s,st_f) :F(L.63)
-LINE 637
 goto = goto "(" st_s ")" :(L.64)
-LINE 639
L.63 DIFFER(st_s) :F(L.65)
-LINE 640
 goto = goto "S(" st_s ")"
-LINE 641
L.65 DIFFER(st_f) :F(L.66)
-LINE 642
 goto = goto "F(" st_f ")"
L.66 
L.64 
-LINE 645
L.62 out = out goto
-LINE 646
L.67 (GE(SIZE(out),70) (out ? FENCE (ARBNO(BREAK(" '"
+ '"') (" " | ANY("'" '"') $ del BREAK(*del) LEN(1))) 
+$ s *GT(SIZE(s),50)) . outf = "+")) :S(L.67)F(L.68)
-LINE 652
L.68 outf = out
-LINE 653
 st_lab = st_body = st_s = st_f = ""
-LINE 655
L.61  :(RETURN)
-LINE 658
emiteos.END  :(getline.END)
getline 
-LINE 661
next_line x = gl_in :F(L.69)
-LINE 665
 gl_line = gl_line + 1
-LINE 668
 x ? FENCE "-" :F(L.70)
-LINE 669
 emitlab(x)
-LINE 670
 emiteos()
-LINE 673
 x_ln = -1
-LINE 674
 x_fn = ""
-LINE 675
 x ? FENCE "-LINE" SPAN(" ") BREAK SPAN(&DIGITS) . x_ln REM . x_file
-LINE 676
 x_file ? '"' BREAK('"') . x_fn
-LINE 677
 GT(x_ln,0) :F(L.71)
-LINE 678
 gl_line = x_ln
-LINE 679
L.71 gl_file = VDIFFER(x_fn) :(next_line)
-LINE 683
L.70 x ? FENCE "////" :F(L.72)
-LINE 684
 x ? FENCE "////" REM . x
-LINE 685
 emitlab(x)
-LINE 686
 emiteos() :(next_line)
-LINE 690
L.72 x ? FENCE "//" :F(L.73)
-LINE 691
 x ? FENCE "//" REM . x
-LINE 692
 deflist<deflist<0> = deflist<0> + 1> = x :(next_line)
-LINE 697
L.73 x ? FENCE "#" *optblank "include" *optblank ANY('"<{'
+ "'") $ del BREAK(*REPLACE(del,'<{','>}')) . file 
+LEN(1) *optblank RPOS(0) :S(L.74)
-LINE 701
 getline = x :(RETURN)
-LINE 708
L.74 "'" '"' ? del :F(L.75)
-LINE 709
 LNE(SUBSTR(file,1,1),'/') :F(L.76)
-LINE 710
 gl_file '/' ? FENCE (BREAKX('/') LEN(1)) . dir BREAK('/'
+) LEN(1) RPOS(0) :F(L.77)
-LINE 713
 file = dir file
L.77 
-LINE 715
L.76  :(L.78)
-LINE 716
L.75 file = "/export/home/fred/snolib/" file
-LINE 723
L.78 ('"<' ? del,IDENT(inctab<file>)) :F(L.79)
-LINE 724
 inctab<file> = 1
-LINE 725
 gl_open(file)
-LINE 727
L.79  :(next_line)
-LINE 730
L.69 ENDFILE(gl_index)
-LINE 731
 gl_close()
-LINE 732
 (GE(gl_index,gl_first),gl_nextfile()) :S(getline)F(FRETURN)
-LINE 739
getline.END  :(gl_nextfile.END)
-LINE 740
gl_nextfile gl_arg = gl_arg + 1
-LINE 741
L.80 IDENT(SUBSTR(HOST(2,gl_arg),1,1),"-") :F(L.81)
-LINE 742
 gl_options = gl_options HOST(2,gl_arg) " "
-LINE 743
 gl_arg = gl_arg + 1 :(L.80)
-LINE 745
L.81 gl_open(HOST(2,gl_arg)) :S(L.82)F(FRETURN)
-LINE 747
L.82  :(RETURN)
-LINE 749
gl_nextfile.END  :(gl_close.END)
-LINE 750
gl_close gl_index = gl_index - 1
-LINE 751
 gl_file = gl_files<gl_index>
-LINE 752
 gl_line = gl_lines<gl_index>
-LINE 753
 GE(gl_index,gl_first) :F(L.83)
-LINE 754
 INPUT(.gl_in,gl_index)
-LINE 755
L.83 gl_files<gl_index> = gl_lines<gl_index> = "" :(RETURN)
-LINE 758
gl_close.END  :(gl_open.END)
-LINE 759
gl_open gl_files<gl_index> = gl_file
-LINE 760
 gl_lines<gl_index> = gl_line
-LINE 761
 gl_index = gl_index + 1
-LINE 762
 gl_line = 0
-LINE 763
 gl_file = file
-LINE 764
 &ERRLIMIT = &ERRLIMIT + 1
-LINE 765
 t = SETEXIT()
-LINE 766
 (INPUT(.gl_in,gl_index,file),INPUT(.gl_in,gl_index,gl_file 
+= file ".sc")) :F(L.84)
-LINE 768
 SETEXIT(t)
-LINE 769
 &ERRLIMIT = &ERRLIMIT - 1
-LINE 770
 file ? IDENT(outfile) (BREAK(".") | REM) . outfile :(RETURN)
-LINE 773
L.84 SETEXIT(t)
-LINE 774
 gl_close()
-LINE 775
 error("cannot read " file) :(FRETURN)
-LINE 781
gl_open.END  :(getinput.END)
-LINE 784
getinput DIFFER(gi_eof) :S(FRETURN)F(L.85)
-LINE 787
L.85 line = line getline() :F(L.86)
-LINE 790
 IDENT(recur) :F(L.87)
-LINE 791
 gi_file = gl_file
-LINE 792
 gi_line = gl_line
-LINE 796
L.87 line ? FENCE (ARBNO(BREAK("'" '"') LEN(1) $ del 
+BREAK(*del) LEN(1)) BREAK("'" '"#')) . line "#"
-LINE 803
 line ? ANY("@$%^&*(-+=[<>|~,?:") optblank RPOS(0) :F(L.88)
-LINE 804
 line = line getinput(1)
-LINE 806
L.88 getinput = line :(RETURN)
-LINE 810
L.86 gi_eof = 1 :(FRETURN)
-LINE 816
getinput.END  :(phrase.END)
-LINE 817
phrase ph_buf ? FENCE optblank RPOS(0) :F(L.89)
-LINE 818
 ph_buf = phbuf getinput() :F(L.90)
-LINE 819
 phrase = phrase() :(RETURN)
-LINE 821
L.90  :(FRETURN)
L.91 
-LINE 824
L.89 ph_buf ? FENCE (ARBNO(BREAK('"' "'") LEN(1) $ 
+del BREAK(*del) LEN(1)) BREAK('"' "';")) . phrase 
+';' = '' :S(RETURN)F(L.92)
-LINE 829
L.92 phrase = ph_buf
-LINE 830
 ph_buf = '' :(RETURN)
-LINE 834
phrase.END  :(newlab.END)
-LINE 835
newlab nl_count = nl_count + 1
-LINE 837
 newlab = label_lead nl_count :(RETURN)
-LINE 842
newlab.END  :(marklab.END)
-LINE 843
marklab (DIFFER(st_lab) IDENT(emit_eob)) :F(L.93)
-LINE 844
 marklab = st_lab :(RETURN)
-LINE 845
L.93 marklab = newlab()
-LINE 846
 emitlab(marklab) :(RETURN)
-LINE 852
marklab.END  :(expcl.END)
-LINE 853
expcl cl_type = "expr" :(RETURN)
-LINE 857
expcl.END  :(gocl.END)
-LINE 858
gocl cl_type = "goto" :(RETURN)
-LINE 865
gocl.END  :(nclause.END)
nclause 
-LINE 866
nclause_start DIFFER(rep_clause) :F(L.94)
-LINE 868
 rep_clause = ""
-LINE 869
 IDENT(eof) :S(RETURN)F(L.95)
-LINE 872
L.95  :(FRETURN)
L.96 
-LINE 874
L.94 linebuf ? FENCE *optblank RPOS(0) :F(L.97)
-LINE 875
 linebuf = phrase() :S(nclause_start)
-LINE 879
 IDENT(okeof) :F(L.98)
-LINE 880
 error('premature EOF') :(EXIT)
-LINE 883
L.98 eof = 1 :(FRETURN)
-LINE 888
L.97 linebuf ? clause = del :S(RETURN)F(L.99)
-LINE 890
L.99 error("syntax error")
-LINE 891
 linebuf = "" :(nclause_start)
-LINE 895
nclause.END  :(error.END)
-LINE 896
error IDENT(gl_file) :F(L.100)
-LINE 897
 prefix = "snocone" :(L.101)
-LINE 899
L.100 prefix = gl_file "(" gl_line ")"
-LINE 900
L.101 terminal = prefix ": " msg
-LINE 901
 &CODE = 1 :(RETURN)
-LINE 905
error.END  :(dostmt.END)
-LINE 907
dostmt IDENT(cl_type,"expr") :F(L.102)
-LINE 910
 sprint(pop()) :(RETURN)
-LINE 915
L.102 IDENT(cl_type,"{") :F(L.103)
-LINE 916
 nclause()
-LINE 917
L.104 DIFFER(cl_type,"}") :F(L.105)
-LINE 918
 dostmt()
-LINE 919
 nclause() :(L.104)
-LINE 921
L.105  :(RETURN)
-LINE 925
L.103 IDENT(cl_type,"goto") :F(L.106)
-LINE 926
 emitg(dest) :(RETURN)
-LINE 931
L.106 IDENT(cl_type,"if") :F(L.107)
-LINE 932
 e1 = pop()
-LINE 935
 isneg(e1) :F(L.108)
-LINE 936
 flip = 1
-LINE 937
 e1 = r(e1)
-LINE 940
L.108 sprint(e1)
-LINE 943
 nclause()
-LINE 944
 IDENT(cl_type,"goto") :F(L.109)
-LINE 945
 IDENT(flip) :F(L.110)
-LINE 946
 emits(dest) :(L.111)
-LINE 948
L.110 emitf(dest)
-LINE 952
L.111 (~nclause(1),DIFFER(cl_type,"else")) :F(L.112)
-LINE 953
 rep_clause = 1
-LINE 954
 emitlab(lab) :(RETURN)
-LINE 957
L.112 nclause()
-LINE 958
 dostmt() :(RETURN)
-LINE 964
L.109 lab = newlab()
-LINE 965
 IDENT(flip) :F(L.113)
-LINE 966
 emitf(lab) :(L.114)
-LINE 968
L.113 emits(lab)
-LINE 969
L.114 dostmt()
-LINE 972
 (nclause(1) IDENT(cl_type,"else")) :F(L.115)
-LINE 975
 lab2 = newlab()
-LINE 976
 emitg(lab2)
-LINE 977
 emitlab(lab)
-LINE 978
 nclause()
-LINE 979
 dostmt()
-LINE 980
 emitlab(lab2) :(RETURN)
-LINE 985
L.115 rep_clause = 1
-LINE 986
 emitlab(lab) :(RETURN)
-LINE 991
L.107 IDENT(cl_type,"while") :F(L.116)
-LINE 992
 lab = marklab()
-LINE 995
 e1 = pop()
-LINE 996
 isneg(e1) :F(L.117)
-LINE 997
 flip = 1
-LINE 998
 e1 = r(e1)
-LINE 1001
L.117 sprint(e1)
-LINE 1002
 lab2 = newlab()
-LINE 1003
 IDENT(flip) :F(L.118)
-LINE 1004
 emitf(lab2) :(L.119)
-LINE 1006
L.118 emits(lab2)
-LINE 1007
L.119 nclause()
-LINE 1008
 dostmt()
-LINE 1009
 emitg(lab)
-LINE 1010
 emitlab(lab2) :(RETURN)
-LINE 1015
L.116 IDENT(cl_type,"do") :F(L.120)
-LINE 1016
 lab = marklab()
-LINE 1017
 nclause()
-LINE 1018
 dostmt()
-LINE 1019
 nclause()
-LINE 1020
 DIFFER(cl_type,"while") :F(L.121)
-LINE 1021
 error("expected 'while', found " cl_type)
-LINE 1022
 rep_clause = 1 :(RETURN)
-LINE 1025
L.121 e1 = pop()
-LINE 1026
 isneg(e1) :F(L.122)
-LINE 1027
 flip = 1
-LINE 1028
 e1 = r(e1)
-LINE 1030
L.122 sprint(e1)
-LINE 1031
 IDENT(flip) :F(L.123)
-LINE 1032
 emits(lab) :(L.124)
-LINE 1034
L.123 emitf(lab)
-LINE 1035
L.124  :(RETURN)
-LINE 1039
L.120 IDENT(cl_type,"for") :F(L.125)
-LINE 1040
 e3 = pop()
-LINE 1041
 e2 = pop()
-LINE 1042
 e1 = pop()
-LINE 1043
 sprint(e1)
-LINE 1044
 emiteob()
-LINE 1045
 lab = marklab()
-LINE 1046
 lab2 = newlab()
-LINE 1047
 isneg(e2) :F(L.126)
-LINE 1048
 flip = 1
-LINE 1049
 e2 = r(e2)
-LINE 1051
L.126 sprint(e2)
-LINE 1052
 IDENT(flip) :F(L.127)
-LINE 1053
 emitf(lab2) :(L.128)
-LINE 1055
L.127 emits(lab2)
-LINE 1056
L.128 nclause()
-LINE 1057
 dostmt()
-LINE 1058
 sprint(e3)
-LINE 1059
 emitg(lab)
-LINE 1060
 emitlab(lab2) :(RETURN)
-LINE 1065
L.125 cl_type ? "return" :F(L.129)
-LINE 1066
 e1 = pop()
-LINE 1067
 DIFFER(e1) :F(L.130)
-LINE 1068
 DIFFER(fname) :F(L.131)
-LINE 1069
 e1 = b(bconv<"=">,fname,e1)
-LINE 1070
L.131 sprint(e1)
-LINE 1072
L.130 emitg(REPLACE(cl_type,"abcdefghijklmnopqrstuvwxyz"
+,"ABCDEFGHIJKLMNOPQRSTUVWXYZ")) :(RETURN)
-LINE 1079
L.129 IDENT(cl_type) :S(RETURN)F(L.132)
-LINE 1082
L.132 error("bad " cl_type " clause, ignored") :(RETURN)
-LINE 1086
dostmt.END  :(dostruct.END)
-LINE 1087
dostruct expect('{') :F(L.133)
-LINE 1088
 args = getlist('}')
-LINE 1089
 deflist<deflist<0> = deflist<0> + 1> = "DATA('" stname 
+"(" args ")')" :(L.134)
-LINE 1092
L.133 error("bad structure definition")
-LINE 1093
L.134 expect('}') :(RETURN)
-LINE 1097
dostruct.END  :(funct.END)
-LINE 1098
funct expect('(') :F(L.135)
-LINE 1099
 args = getlist(')') :F(fu_error)
-LINE 1101
 expect(')')
-LINE 1102
 locals = getlist('{') :F(fu_error)
-LINE 1106
L.135 deflist<deflist<0> = deflist<0> + 1> = "DEFINE('"
+ fname '(' args ')' locals "')"
-LINE 1111
 IDENT(emit_eob) st_lab ? ".END" :F(L.136)
-LINE 1112
 flabel = st_lab
-LINE 1113
 st_lab = ""
-LINE 1114
 emitlab(fname)
-LINE 1115
 nclause()
-LINE 1116
 dostmt()
-LINE 1117
 emitg("RETURN")
-LINE 1118
 emitlab(flabel) :(RETURN)
-LINE 1122
L.136 emitg(fname '.END')
-LINE 1123
 emitlab(fname)
-LINE 1124
 nclause()
-LINE 1125
 dostmt()
-LINE 1126
 emitg("RETURN")
-LINE 1127
 emitlab(fname '.END') :(RETURN)
-LINE 1130
fu_error error("bad function definition") :(RETURN)
-LINE 1136
funct.END  :(expect.END)
-LINE 1139
expect linebuf ? FENCE optblank RPOS(0) :F(L.137)
-LINE 1140
 linebuf = phrase() :S(L.138)F(FRETURN)
-LINE 1142
L.138  :(expect)
-LINE 1145
L.137 linebuf ? FENCE optblank *p = "" :S(RETURN)F(L.139)
-LINE 1149
L.139  :(FRETURN)
-LINE 1153
expect.END  :(getid.END)
-LINE 1154
getid expect(*identifier . getid) :S(RETURN)F(L.140)
-LINE 1156
L.140  :(FRETURN)
-LINE 1160
getid.END  :(getlist.END)
getlist 
-LINE 1161
getlist_start expect(tail) :F(L.141)
-LINE 1163
 linebuf = tail linebuf :(RETURN)
-LINE 1166
L.141 getlist = getlist del getid() :F(L.142)
-LINE 1167
 expect(',')
-LINE 1168
 del = ',' :(getlist_start)
-LINE 1171
L.142 expect(tail) :S(RETURN)F(L.143)
-LINE 1173
L.143  :(FRETURN)
-LINE 1179
getlist.END  :(buildstab.END)
-LINE 1180
buildstab DIFFER(file,bst_file) :F(L.144)
-LINE 1181
 outf = "-LINE " line ' "' file '"' :(L.145)
-LINE 1182
L.144 DIFFER(line,bst_line) :F(L.146)
-LINE 1183
 outf = "-LINE " line
L.146 
-LINE 1194
L.145 bst_stmt = stmt
-LINE 1195
 bst_file = file
-LINE 1196
 bst_line = line :(RETURN)
-LINE 1197
buildstab.END  :(END)
START. CODE('START.')
 DEFINE('nspan(str)')
 DEFINE('list(item,delim)')
 DEFINE('kw(s)')
 DEFINE('push()')
 DEFINE('pop()')
 DEFINE('peek(n)')
 DEFINE('top()')
 DEFINE('isbin(x)')
 DEFINE('isneg(x)')
 DEFINE('dprint(x)op,l,r,d,i,del')
 DEFINE('bprint(x)')
 DEFINE('sprint(x)')
 DEFINE('invoke(f)')
 DEFINE('unop()r,op')
 DEFINE('mkfcall()')
 DEFINE('mkarg()x,f')
 DEFINE('endfc()f')
 DEFINE('mkarray()t')
 DEFINE('begexp()')
 DEFINE('binop()l,r,op,newr,newop')
 DEFINE('endexp()l,r,op')
 DEFINE('mkbinfo()op')
 DEFINE('dotck()')
 DEFINE('emitlab(l)')
 DEFINE('emit(s)')
 DEFINE('emiteob()')
 DEFINE('emits(l)')
 DEFINE('emitf(l)')
 DEFINE('emitg(l)')
 DEFINE('emitb(s)')
 DEFINE('emiteos()out,goto,s,del')
 DEFINE('getline()x,file,del,dir')
 DEFINE('gl_nextfile()')
 DEFINE('gl_close()')
 DEFINE('gl_open(file)t')
 DEFINE('getinput(recur)del,line')
 DEFINE('phrase()del')
 DEFINE('newlab()')
 DEFINE('marklab()')
 DEFINE('expcl()')
 DEFINE('gocl()')
 DEFINE('nclause(okeof)del')
 DEFINE('error(msg)prefix')
 DEFINE('dostmt()lab,lab2,e1,e2,e3,flip')
 DEFINE('dostruct()args')
 DEFINE('funct()args,locals,flabel')
 DEFINE('expect(p)')
 DEFINE('getid()')
 DEFINE('getlist(tail)del')
 DEFINE('buildstab(stmt,file,line)desc,pad')
 &FULLSCAN = 1
 &TRIM = 1 :(MAIN.)
END	START.
