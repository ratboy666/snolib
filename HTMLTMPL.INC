-PLUSOPS 1 
  :(HTMLTMPL.1)
-MODULE HTMLTMPL 
-SNOCONE 
-LINE 72 "HTMLTMPL.lss" 
-LINE 84 "HTMLTMPL.lss"
  :(tmpl_init.END)
-LINE 88
tmpl_init tmpl_dir = "./"
-LINE 92
 tmpl_ws = span(" " chars_tab) | ""
-LINE 93
 tmpl = ("/" | "") . h any("Tt") any("Mm") any("Pp") any("Ll") "_"
-LINE 95
 tmpl_tag = tmpl span(&ucase &lcase) . tag
-LINE 96
 tmpl_c = "<!-- " tmpl_ws tmpl_tag arb . arg " -->"
-LINE 97
 tmpl_t = "<" tmpl_tag break(">") . arg ">"
-LINE 98
 tmpl_piece = pos(0) breakx("<") . l (tmpl_t | tmpl_c) . p rem . r
-LINE 100
 tmpl_keys = "var if unless else loop include "
-LINE 104
 tmpl_arg_var = tmpl_ws (any(&lcase &ucase) span(&lcase 
+&ucase '0123456789' "_")) . n tmpl_ws
-LINE 106
 tmpl_qval = '"' break('"') . v '"'
-LINE 107
 tmpl_sval = break(" " chars_tab) . v
-LINE 108
 tmpl_arg_p = (tmpl_arg_var "=" | "") tmpl_ws (tmpl_qval 
+| tmpl_sval | rem . v) :(RETURN)
-LINE 115
tmpl_init.END  :(tmpl_compile.END)
-LINE 116
tmpl_compile l = tmpl_tokenize(s) :S(HTMLTMPL.2)F(FRETURN)
-LINE 118
HTMLTMPL.2 l = tmpl_parse(l) :S(HTMLTMPL.3)F(FRETURN)
-LINE 120
HTMLTMPL.3 tmpl_compile = l :(RETURN)
-LINE 127
tmpl_compile.END  :(tmpl_interpret.END)
-LINE 128
tmpl_interpret interpret_tmpl(p,a) :(RETURN)
-LINE 133
tmpl_interpret.END  :(none_escape.END)
-LINE 134
none_escape none_escape = s :(RETURN)
-LINE 139
none_escape.END  :(interpret_tmpl.END)
-LINE 140
interpret_tmpl p
HTMLTMPL.4 DIFFER(p,"") :F(HTMLTMPL.5)
-LINE 141
 v = value(value(p))
-LINE 142
 IDENT(token_type(v),"text") :F(HTMLTMPL.6)
-LINE 144
 tmpl_interpret = tmpl_interpret token_args(v) :(HTMLTMPL.7)
-LINE 146
HTMLTMPL.6 t = token_args(v)
-LINE 147
 n = a<t<"name">>
-LINE 148
 IDENT(token_type(v),"var") :F(HTMLTMPL.8)
-LINE 150
 IDENT(n,"") :F(HTMLTMPL.9)
-LINE 151
 n = t<"default">
-LINE 152
HTMLTMPL.9 e = t<"escape">
-LINE 154
 e = e "_escape"
-LINE 155
 v = &errlimit
 &errlimit = 1
 n = apply(e,n)
 &errlimit = v
-LINE 156
 tmpl_interpret = tmpl_interpret n :(HTMLTMPL.10)
-LINE 157
HTMLTMPL.8 "if unless" ? token_type(v) :F(HTMLTMPL.11)
-LINE 159
 p1 = value(next(value(p)))
-LINE 160
 p2 = next(next(value(p)))
-LINE 161
 IDENT(token_type(v),"unless") :F(HTMLTMPL.12)
-LINE 162
 swap(.p1,.p2)
-LINE 163
HTMLTMPL.12 (DIFFER(n,""),ne(+n,0)) :F(HTMLTMPL.13)
-LINE 164
 interpret_tmpl(p1,a) :(HTMLTMPL.14)
-LINE 166
HTMLTMPL.13 interpret_tmpl(p2,a)
-LINE 167
HTMLTMPL.14  :(HTMLTMPL.15)
HTMLTMPL.11 IDENT(token_type(v),"loop") :F(HTMLTMPL.16)
-LINE 169
 IDENT(datatype(n),"ARRAY") :F(HTMLTMPL.17)
-LINE 170
 p1 = value(next(value(p)))
-LINE 171
 i = 1
HTMLTMPL.18 n<i> :F(HTMLTMPL.19)
-LINE 172
 interpret_tmpl(p1,n<i>)
 i = i + 1 :(HTMLTMPL.18)
HTMLTMPL.19 
HTMLTMPL.17 
HTMLTMPL.16 
HTMLTMPL.15 
HTMLTMPL.10 
-LINE 176
HTMLTMPL.7 p = next(p) :(HTMLTMPL.4)
-LINE 177
HTMLTMPL.5  :(RETURN)
-LINE 182
interpret_tmpl.END  :(tmpl_parse.END)
-LINE 183
tmpl_parse IDENT(l,"") :S(RETURN)F(HTMLTMPL.20)
-LINE 185
HTMLTMPL.20 r = tmpl_seq() :S(HTMLTMPL.21)F(FRETURN)
-LINE 187
HTMLTMPL.21 DIFFER(l,"") :S(FRETURN)F(HTMLTMPL.22)
-LINE 189
HTMLTMPL.22 tmpl_parse = r :(RETURN)
-LINE 195
tmpl_parse.END  :(tmpl_seq.END)
-LINE 196
tmpl_seq DIFFER(l,"") :F(HTMLTMPL.23)
-LINE 197
 v = value(l)
-LINE 198
 "text var" ? token_type(v) :F(HTMLTMPL.24)
-LINE 199
 r = link(link(v),r)
-LINE 200
 l = next(l) :(HTMLTMPL.25)
-LINE 201
HTMLTMPL.24 "if unless loop" ? token_type(v) :F(HTMLTMPL.26)
-LINE 202
 DIFFER(token_end(v),"") :F(HTMLTMPL.27)
-LINE 203
 tmpl_seq = revl(r) :(RETURN)
-LINE 204
HTMLTMPL.27 l = next(l)
-LINE 205
 p1 = tmpl_seq() :S(HTMLTMPL.28)F(FRETURN)
-LINE 207
HTMLTMPL.28 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.29)
-LINE 209
HTMLTMPL.29 p2 = ""
-LINE 210
 v2 = value(l)
-LINE 211
 "if unless loop" ? token_type(v2) :F(HTMLTMPL.30)
-LINE 212
 l = next(l) :(HTMLTMPL.31)
-LINE 213
HTMLTMPL.30 IDENT(token_type(v2),"else") :F(HTMLTMPL.32)
-LINE 214
 l = next(l)
-LINE 215
 p2 = tmpl_seq() :S(HTMLTMPL.33)F(FRETURN)
-LINE 217
HTMLTMPL.33 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.34)
-LINE 219
HTMLTMPL.34 l = next(l) :(HTMLTMPL.35)
-LINE 221
HTMLTMPL.32  :(FRETURN)
HTMLTMPL.35 
-LINE 222
HTMLTMPL.31 r = link(link(v,link(p1,p2)),r) :(HTMLTMPL.36)
-LINE 223
HTMLTMPL.26 IDENT(token_type(v),"else") :F(HTMLTMPL.37)
-LINE 224
 tmpl_seq = revl(r) :(RETURN)
-LINE 226
HTMLTMPL.37  :(FRETURN)
HTMLTMPL.38 
HTMLTMPL.36 
-LINE 227
HTMLTMPL.25  :(tmpl_seq)
-LINE 228
HTMLTMPL.23 tmpl_seq = revl(r) :(RETURN)
-LINE 233
tmpl_seq.END  :(tmpl_tokenize.END)
-LINE 234
tmpl_tokenize n = .tmpl_tokenize
-LINE 235
HTMLTMPL.39 DIFFER(s,"") :F(HTMLTMPL.40)
-LINE 236
 s ? tmpl_piece :F(HTMLTMPL.41)
-LINE 237
 tag = replace(tag,&ucase,&lcase)
-LINE 238
 tmpl_keys ? tag " " :F(HTMLTMPL.42)
-LINE 239
 DIFFER(l,"") :F(HTMLTMPL.43)
-LINE 240
 $n = link(tmpl_token("text","",l))
 n = .next($n)
-LINE 242
HTMLTMPL.43 IDENT(tag,"include") :F(HTMLTMPL.44)
-LINE 247
 t = tmpl_parse_args(arg) :S(HTMLTMPL.45)F(FRETURN)
-LINE 249
HTMLTMPL.45 s = readfile(tmpl_dir t<'name'>) :F(HTMLTMPL.46)
-LINE 250
 $n = tmpl_tokenize(s) :S(HTMLTMPL.47)F(FRETURN)
-LINE 252
HTMLTMPL.47 n = .last(tmpl_tokenize)
-LINE 254
HTMLTMPL.46  :(HTMLTMPL.48)
-LINE 255
HTMLTMPL.44 t = tmpl_token(tag,h,tmpl_parse_args(arg))
-LINE 256
 $n = link(t)
 n = .next($n)
-LINE 258
HTMLTMPL.48  :(HTMLTMPL.49)
-LINE 259
HTMLTMPL.42 $n = link(tmpl_token("text","",l p))
 n = .next($n)
-LINE 261
HTMLTMPL.49 s = r :(HTMLTMPL.50)
-LINE 263
HTMLTMPL.41 $n = link(tmpl_token("text","",s))
 n = .next($n)
-LINE 264
 s = ""
-LINE 266
HTMLTMPL.50  :(HTMLTMPL.39)
-LINE 267
HTMLTMPL.40  :(RETURN)
-LINE 272
tmpl_tokenize.END  :(tmpl_parse_args.END)
-LINE 273
tmpl_parse_args tmpl_parse_args = table()
-LINE 274
HTMLTMPL.51 DIFFER(s,"") :F(HTMLTMPL.52)
-LINE 275
 n = ""
-LINE 276
 v = ""
-LINE 277
 s ? tmpl_arg_p = "" :F(HTMLTMPL.53)
-LINE 278
 n = replace(n,&ucase,&lcase)
-LINE 279
 n = ident(n) "name"
-LINE 280
 tmpl_parse_args<n> = v :(HTMLTMPL.54)
-LINE 282
HTMLTMPL.53  :(FRETURN)
-LINE 283
HTMLTMPL.54  :(HTMLTMPL.51)
-LINE 284
HTMLTMPL.52  :(RETURN)
tmpl_parse_args.END 
-LINE 293 "HTMLTMPL.lss" 
HTMLTMPL.1 
 DATA('tmpl_token(token_type,token_end,token_args)')
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
