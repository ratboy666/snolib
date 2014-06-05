-PLUSOPS 1 
  :(HTMLTMPL.1)
-LINE 53 "HTMLTMPL.lss" 
-LINE 72 "HTMLTMPL.lss"
  :(tmpl_init.END)
-LINE 76
tmpl_init tmpl_dir = "./"
-LINE 80
 tmpl_ws = span(" " chars_tab) | ""
-LINE 81
 tmpl = ("/" | "") . h any("Tt") any("Mm") any("Pp") any("Ll") "_"
-LINE 83
 tmpl_tag = tmpl span(&ucase &lcase) . tag
-LINE 84
 tmpl_c = "<!-- " tmpl_ws tmpl_tag arb . arg " -->"
-LINE 85
 tmpl_t = "<" tmpl_tag break(">") . arg ">"
-LINE 86
 tmpl_piece = pos(0) breakx("<") . l (tmpl_t | tmpl_c) . p rem . r
-LINE 88
 tmpl_keys = "var if unless else loop include "
-LINE 92
 tmpl_arg_var = tmpl_ws (any(&lcase &ucase) span(&lcase 
+&ucase '0123456789' "_")) . n tmpl_ws
-LINE 94
 tmpl_qval = '"' break('"') . v '"'
-LINE 95
 tmpl_sval = break(" " chars_tab) . v
-LINE 96
 tmpl_arg_p = (tmpl_arg_var "=" | "") tmpl_ws (tmpl_qval 
+| tmpl_sval | rem . v) :(RETURN)
-LINE 103
tmpl_init.END  :(tmpl_compile.END)
-LINE 104
tmpl_compile l = tmpl_tokenize(s) :S(HTMLTMPL.2)F(FRETURN)
-LINE 106
HTMLTMPL.2 l = tmpl_parse(l) :S(HTMLTMPL.3)F(FRETURN)
-LINE 108
HTMLTMPL.3 tmpl_compile = l :(RETURN)
-LINE 115
tmpl_compile.END  :(tmpl_interpret.END)
-LINE 116
tmpl_interpret interpret_tmpl(p,a) :(RETURN)
-LINE 121
tmpl_interpret.END  :(none_escape.END)
-LINE 122
none_escape none_escape = s :(RETURN)
-LINE 127
none_escape.END  :(interpret_tmpl.END)
-LINE 128
interpret_tmpl p
HTMLTMPL.4 DIFFER(p,"") :F(HTMLTMPL.5)
-LINE 129
 v = value(value(p))
-LINE 130
 IDENT(token_type(v),"text") :F(HTMLTMPL.6)
-LINE 132
 tmpl_interpret = tmpl_interpret token_args(v) :(HTMLTMPL.7)
-LINE 134
HTMLTMPL.6 t = token_args(v)
-LINE 135
 n = a<t<"name">>
-LINE 136
 IDENT(token_type(v),"var") :F(HTMLTMPL.8)
-LINE 138
 IDENT(n,"") :F(HTMLTMPL.9)
-LINE 139
 n = t<"default">
-LINE 140
HTMLTMPL.9 e = t<"escape">
-LINE 142
 e = e "_escape"
-LINE 143
 v = &errlimit
 &errlimit = 1
 n = apply(e,n)
 &errlimit = v
-LINE 144
 tmpl_interpret = tmpl_interpret n :(HTMLTMPL.10)
-LINE 145
HTMLTMPL.8 "if unless" ? token_type(v) :F(HTMLTMPL.11)
-LINE 147
 p1 = value(next(value(p)))
-LINE 148
 p2 = next(next(value(p)))
-LINE 149
 IDENT(token_type(v),"unless") :F(HTMLTMPL.12)
-LINE 150
 swap(.p1,.p2)
-LINE 151
HTMLTMPL.12 (DIFFER(n,""),ne(+n,0)) :F(HTMLTMPL.13)
-LINE 152
 interpret_tmpl(p1,a) :(HTMLTMPL.14)
-LINE 154
HTMLTMPL.13 interpret_tmpl(p2,a)
-LINE 155
HTMLTMPL.14  :(HTMLTMPL.15)
HTMLTMPL.11 IDENT(token_type(v),"loop") :F(HTMLTMPL.16)
-LINE 157
 IDENT(datatype(n),"ARRAY") :F(HTMLTMPL.17)
-LINE 158
 p1 = value(next(value(p)))
-LINE 159
 i = 1
HTMLTMPL.18 n<i> :F(HTMLTMPL.19)
-LINE 160
 interpret_tmpl(p1,n<i>)
 i = i + 1 :(HTMLTMPL.18)
HTMLTMPL.19 
HTMLTMPL.17 
HTMLTMPL.16 
HTMLTMPL.15 
HTMLTMPL.10 
-LINE 164
HTMLTMPL.7 p = next(p) :(HTMLTMPL.4)
-LINE 165
HTMLTMPL.5  :(RETURN)
-LINE 170
interpret_tmpl.END  :(tmpl_parse.END)
-LINE 171
tmpl_parse IDENT(l,"") :S(RETURN)F(HTMLTMPL.20)
-LINE 173
HTMLTMPL.20 r = tmpl_seq() :S(HTMLTMPL.21)F(FRETURN)
-LINE 175
HTMLTMPL.21 DIFFER(l,"") :S(FRETURN)F(HTMLTMPL.22)
-LINE 177
HTMLTMPL.22 tmpl_parse = r :(RETURN)
-LINE 183
tmpl_parse.END  :(tmpl_seq.END)
-LINE 184
tmpl_seq DIFFER(l,"") :F(HTMLTMPL.23)
-LINE 185
 v = value(l)
-LINE 186
 "text var" ? token_type(v) :F(HTMLTMPL.24)
-LINE 187
 r = link(link(v),r)
-LINE 188
 l = next(l) :(HTMLTMPL.25)
-LINE 189
HTMLTMPL.24 "if unless loop" ? token_type(v) :F(HTMLTMPL.26)
-LINE 190
 DIFFER(token_end(v),"") :F(HTMLTMPL.27)
-LINE 191
 tmpl_seq = revl(r) :(RETURN)
-LINE 192
HTMLTMPL.27 l = next(l)
-LINE 193
 p1 = tmpl_seq() :S(HTMLTMPL.28)F(FRETURN)
-LINE 195
HTMLTMPL.28 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.29)
-LINE 197
HTMLTMPL.29 p2 = ""
-LINE 198
 v2 = value(l)
-LINE 199
 "if unless loop" ? token_type(v2) :F(HTMLTMPL.30)
-LINE 200
 l = next(l) :(HTMLTMPL.31)
-LINE 201
HTMLTMPL.30 IDENT(token_type(v2),"else") :F(HTMLTMPL.32)
-LINE 202
 l = next(l)
-LINE 203
 p2 = tmpl_seq() :S(HTMLTMPL.33)F(FRETURN)
-LINE 205
HTMLTMPL.33 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.34)
-LINE 207
HTMLTMPL.34 l = next(l) :(HTMLTMPL.35)
-LINE 209
HTMLTMPL.32  :(FRETURN)
HTMLTMPL.35 
-LINE 210
HTMLTMPL.31 r = link(link(v,link(p1,p2)),r) :(HTMLTMPL.36)
-LINE 211
HTMLTMPL.26 IDENT(token_type(v),"else") :F(HTMLTMPL.37)
-LINE 212
 tmpl_seq = revl(r) :(RETURN)
-LINE 214
HTMLTMPL.37  :(FRETURN)
HTMLTMPL.38 
HTMLTMPL.36 
-LINE 215
HTMLTMPL.25  :(tmpl_seq)
-LINE 216
HTMLTMPL.23 tmpl_seq = revl(r) :(RETURN)
-LINE 221
tmpl_seq.END  :(tmpl_tokenize.END)
-LINE 222
tmpl_tokenize n = .tmpl_tokenize
-LINE 223
HTMLTMPL.39 DIFFER(s,"") :F(HTMLTMPL.40)
-LINE 224
 s ? tmpl_piece :F(HTMLTMPL.41)
-LINE 225
 tag = replace(tag,&ucase,&lcase)
-LINE 226
 tmpl_keys ? tag " " :F(HTMLTMPL.42)
-LINE 227
 DIFFER(l,"") :F(HTMLTMPL.43)
-LINE 228
 $n = link(tmpl_token("text","",l))
 n = .next($n)
-LINE 230
HTMLTMPL.43 IDENT(tag,"include") :F(HTMLTMPL.44)
-LINE 235
 t = tmpl_parse_args(arg) :S(HTMLTMPL.45)F(FRETURN)
-LINE 237
HTMLTMPL.45 s = readfile(tmpl_dir t<'name'>) :F(HTMLTMPL.46)
-LINE 238
 $n = tmpl_tokenize(s) :S(HTMLTMPL.47)F(FRETURN)
-LINE 240
HTMLTMPL.47 n = .last(tmpl_tokenize)
-LINE 242
HTMLTMPL.46  :(HTMLTMPL.48)
-LINE 243
HTMLTMPL.44 t = tmpl_token(tag,h,tmpl_parse_args(arg))
-LINE 244
 $n = link(t)
 n = .next($n)
-LINE 246
HTMLTMPL.48  :(HTMLTMPL.49)
-LINE 247
HTMLTMPL.42 $n = link(tmpl_token("text","",l p))
 n = .next($n)
-LINE 249
HTMLTMPL.49 s = r :(HTMLTMPL.50)
-LINE 251
HTMLTMPL.41 $n = link(tmpl_token("text","",s))
 n = .next($n)
-LINE 252
 s = ""
-LINE 254
HTMLTMPL.50  :(HTMLTMPL.39)
-LINE 255
HTMLTMPL.40  :(RETURN)
-LINE 260
tmpl_tokenize.END  :(tmpl_parse_args.END)
-LINE 261
tmpl_parse_args tmpl_parse_args = table()
-LINE 262
HTMLTMPL.51 DIFFER(s,"") :F(HTMLTMPL.52)
-LINE 263
 n = ""
-LINE 264
 v = ""
-LINE 265
 s ? tmpl_arg_p = "" :F(HTMLTMPL.53)
-LINE 266
 n = replace(n,&ucase,&lcase)
-LINE 267
 n = ident(n) "name"
-LINE 268
 tmpl_parse_args<n> = v :(HTMLTMPL.54)
-LINE 270
HTMLTMPL.53  :(FRETURN)
-LINE 271
HTMLTMPL.54  :(HTMLTMPL.51)
-LINE 272
HTMLTMPL.52  :(RETURN)
tmpl_parse_args.END 
-LINE 281 "HTMLTMPL.lss" 
HTMLTMPL.1 
 DATA('tmpl_token(token_type,token_end,token_args)')
-include 'LINK.INC' 
-include 'CHARS.INC' 
-include 'LAST.INC' 
-include 'REVL.INC' 
-include 'SWAP.INC' 
-include 'READFILE.INC' 
-include 'HTMLESC.INC' 
-USES HTML_ESCAPE(), JS_ESCAPE(), URL_ESCAPE() 
-PUBLIC TMPL_INIT() 
 DEFINE('tmpl_init()')
-PUBLIC TMPL_COMPILE() 
 DEFINE('tmpl_compile(s)l')
-PUBLIC TMPL_INTERPRET() 
 DEFINE('tmpl_interpret(p,a)')
 DEFINE('none_escape(s)')
 DEFINE('interpret_tmpl(p,a)p1,p2,v,n,t,e,i')
 DEFINE('tmpl_parse(l)r')
 DEFINE('tmpl_seq()r,v,v2,p1,p2')
 DEFINE('tmpl_tokenize(s)l,r,p,tag,r,h,n,t')
 DEFINE('tmpl_parse_args(s)n,v')
  tmpl_init()
