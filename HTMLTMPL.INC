-PLUSOPS 1 
  :(HTMLTMPL.1)
-MODULE HTMLTMPL 
-SNOCONE 
-LINE 73 "HTMLTMPL.lss" 
-LINE 85 "HTMLTMPL.lss"
  :(tmpl_init.END)
-LINE 89
tmpl_init tmpl_dir = "./"
-LINE 93
 tmpl_ws = span(" " chars_tab) | ""
-LINE 94
 tmpl = ("/" | "") . h any("Tt") any("Mm") any("Pp") any("Ll") "_"
-LINE 96
 tmpl_tag = tmpl span(&ucase &lcase) . tag
-LINE 97
 tmpl_c = "<!-- " tmpl_ws tmpl_tag arb . arg " -->"
-LINE 98
 tmpl_t = "<" tmpl_tag break(">") . arg ">"
-LINE 99
 tmpl_piece = pos(0) breakx("<") . l (tmpl_t | tmpl_c) . p rem . r
-LINE 101
 tmpl_keys = "var if unless else loop include "
-LINE 105
 tmpl_arg_var = tmpl_ws (any(&lcase &ucase) span(&lcase 
+&ucase '0123456789' "_")) . n tmpl_ws
-LINE 107
 tmpl_qval = '"' break('"') . v '"'
-LINE 108
 tmpl_sval = break(" " chars_tab) . v
-LINE 109
 tmpl_arg_p = (tmpl_arg_var "=" | "") tmpl_ws (tmpl_qval 
+| tmpl_sval | rem . v) :(RETURN)
-LINE 116
tmpl_init.END  :(tmpl_compile.END)
-LINE 117
tmpl_compile l = tmpl_tokenize(s) :S(HTMLTMPL.2)F(FRETURN)
-LINE 119
HTMLTMPL.2 l = tmpl_parse(l) :S(HTMLTMPL.3)F(FRETURN)
-LINE 121
HTMLTMPL.3 tmpl_compile = l :(RETURN)
-LINE 128
tmpl_compile.END  :(tmpl_interpret.END)
-LINE 129
tmpl_interpret interpret_tmpl(p,a) :(RETURN)
-LINE 134
tmpl_interpret.END  :(none_escape.END)
-LINE 135
none_escape none_escape = s :(RETURN)
-LINE 140
none_escape.END  :(interpret_tmpl.END)
-LINE 141
interpret_tmpl p
HTMLTMPL.4 DIFFER(p,"") :F(HTMLTMPL.5)
-LINE 142
 v = value(value(p))
-LINE 143
 IDENT(token_type(v),"text") :F(HTMLTMPL.6)
-LINE 145
 tmpl_interpret = tmpl_interpret token_args(v) :(HTMLTMPL.7)
-LINE 147
HTMLTMPL.6 t = token_args(v)
-LINE 148
 n = a<t<"name">>
-LINE 149
 IDENT(token_type(v),"var") :F(HTMLTMPL.8)
-LINE 151
 IDENT(n,"") :F(HTMLTMPL.9)
-LINE 152
 n = t<"default">
-LINE 153
HTMLTMPL.9 e = t<"escape">
-LINE 155
 e = e "_escape"
-LINE 156
 v = &errlimit
 &errlimit = 1
 n = apply(e,n)
 &errlimit = v
-LINE 157
 tmpl_interpret = tmpl_interpret n :(HTMLTMPL.10)
-LINE 158
HTMLTMPL.8 "if unless" ? token_type(v) :F(HTMLTMPL.11)
-LINE 160
 p1 = value(next(value(p)))
-LINE 161
 p2 = next(next(value(p)))
-LINE 162
 IDENT(token_type(v),"unless") :F(HTMLTMPL.12)
-LINE 163
 swap(.p1,.p2)
-LINE 164
HTMLTMPL.12 (DIFFER(n,""),ne(+n,0)) :F(HTMLTMPL.13)
-LINE 165
 interpret_tmpl(p1,a) :(HTMLTMPL.14)
-LINE 167
HTMLTMPL.13 interpret_tmpl(p2,a)
-LINE 168
HTMLTMPL.14  :(HTMLTMPL.15)
HTMLTMPL.11 IDENT(token_type(v),"loop") :F(HTMLTMPL.16)
-LINE 170
 IDENT(datatype(n),"ARRAY") :F(HTMLTMPL.17)
-LINE 171
 p1 = value(next(value(p)))
-LINE 172
 i = 1
HTMLTMPL.18 n<i> :F(HTMLTMPL.19)
-LINE 173
 interpret_tmpl(p1,n<i>)
 i = i + 1 :(HTMLTMPL.18)
HTMLTMPL.19 
HTMLTMPL.17 
HTMLTMPL.16 
HTMLTMPL.15 
HTMLTMPL.10 
-LINE 177
HTMLTMPL.7 p = next(p) :(HTMLTMPL.4)
-LINE 178
HTMLTMPL.5  :(RETURN)
-LINE 183
interpret_tmpl.END  :(tmpl_parse.END)
-LINE 184
tmpl_parse IDENT(l,"") :S(RETURN)F(HTMLTMPL.20)
-LINE 186
HTMLTMPL.20 r = tmpl_seq() :S(HTMLTMPL.21)F(FRETURN)
-LINE 188
HTMLTMPL.21 DIFFER(l,"") :S(FRETURN)F(HTMLTMPL.22)
-LINE 190
HTMLTMPL.22 tmpl_parse = r :(RETURN)
-LINE 196
tmpl_parse.END  :(tmpl_seq.END)
-LINE 197
tmpl_seq DIFFER(l,"") :F(HTMLTMPL.23)
-LINE 198
 v = value(l)
-LINE 199
 "text var" ? token_type(v) :F(HTMLTMPL.24)
-LINE 200
 r = link(link(v),r)
-LINE 201
 l = next(l) :(HTMLTMPL.25)
-LINE 202
HTMLTMPL.24 "if unless loop" ? token_type(v) :F(HTMLTMPL.26)
-LINE 203
 DIFFER(token_end(v),"") :F(HTMLTMPL.27)
-LINE 204
 tmpl_seq = revl(r) :(RETURN)
-LINE 205
HTMLTMPL.27 l = next(l)
-LINE 206
 p1 = tmpl_seq() :S(HTMLTMPL.28)F(FRETURN)
-LINE 208
HTMLTMPL.28 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.29)
-LINE 210
HTMLTMPL.29 p2 = ""
-LINE 211
 v2 = value(l)
-LINE 212
 "if unless loop" ? token_type(v2) :F(HTMLTMPL.30)
-LINE 213
 l = next(l) :(HTMLTMPL.31)
-LINE 214
HTMLTMPL.30 IDENT(token_type(v2),"else") :F(HTMLTMPL.32)
-LINE 215
 l = next(l)
-LINE 216
 p2 = tmpl_seq() :S(HTMLTMPL.33)F(FRETURN)
-LINE 218
HTMLTMPL.33 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.34)
-LINE 220
HTMLTMPL.34 l = next(l) :(HTMLTMPL.35)
-LINE 222
HTMLTMPL.32  :(FRETURN)
HTMLTMPL.35 
-LINE 223
HTMLTMPL.31 r = link(link(v,link(p1,p2)),r) :(HTMLTMPL.36)
-LINE 224
HTMLTMPL.26 IDENT(token_type(v),"else") :F(HTMLTMPL.37)
-LINE 225
 tmpl_seq = revl(r) :(RETURN)
-LINE 227
HTMLTMPL.37  :(FRETURN)
HTMLTMPL.38 
HTMLTMPL.36 
-LINE 228
HTMLTMPL.25  :(tmpl_seq)
-LINE 229
HTMLTMPL.23 tmpl_seq = revl(r) :(RETURN)
-LINE 234
tmpl_seq.END  :(tmpl_tokenize.END)
-LINE 235
tmpl_tokenize n = .tmpl_tokenize
-LINE 236
HTMLTMPL.39 DIFFER(s,"") :F(HTMLTMPL.40)
-LINE 237
 s ? tmpl_piece :F(HTMLTMPL.41)
-LINE 238
 tag = replace(tag,&ucase,&lcase)
-LINE 239
 tmpl_keys ? tag " " :F(HTMLTMPL.42)
-LINE 240
 DIFFER(l,"") :F(HTMLTMPL.43)
-LINE 241
 $n = link(tmpl_token("text","",l))
 n = .next($n)
-LINE 243
HTMLTMPL.43 IDENT(tag,"include") :F(HTMLTMPL.44)
-LINE 248
 t = tmpl_parse_args(arg) :S(HTMLTMPL.45)F(FRETURN)
-LINE 250
HTMLTMPL.45 s = readfile(tmpl_dir t<'name'>) :F(HTMLTMPL.46)
-LINE 251
 $n = tmpl_tokenize(s) :S(HTMLTMPL.47)F(FRETURN)
-LINE 253
HTMLTMPL.47 n = .last(tmpl_tokenize)
-LINE 255
HTMLTMPL.46  :(HTMLTMPL.48)
-LINE 256
HTMLTMPL.44 t = tmpl_token(tag,h,tmpl_parse_args(arg))
-LINE 257
 $n = link(t)
 n = .next($n)
-LINE 259
HTMLTMPL.48  :(HTMLTMPL.49)
-LINE 260
HTMLTMPL.42 $n = link(tmpl_token("text","",l p))
 n = .next($n)
-LINE 262
HTMLTMPL.49 s = r :(HTMLTMPL.50)
-LINE 264
HTMLTMPL.41 $n = link(tmpl_token("text","",s))
 n = .next($n)
-LINE 265
 s = ""
-LINE 267
HTMLTMPL.50  :(HTMLTMPL.39)
-LINE 268
HTMLTMPL.40  :(RETURN)
-LINE 273
tmpl_tokenize.END  :(tmpl_parse_args.END)
-LINE 274
tmpl_parse_args tmpl_parse_args = table()
-LINE 275
HTMLTMPL.51 DIFFER(s,"") :F(HTMLTMPL.52)
-LINE 276
 n = ""
-LINE 277
 v = ""
-LINE 278
 s ? tmpl_arg_p = "" :F(HTMLTMPL.53)
-LINE 279
 n = replace(n,&ucase,&lcase)
-LINE 280
 n = ident(n) "name"
-LINE 281
 tmpl_parse_args<n> = v :(HTMLTMPL.54)
-LINE 283
HTMLTMPL.53  :(FRETURN)
-LINE 284
HTMLTMPL.54  :(HTMLTMPL.51)
-LINE 285
HTMLTMPL.52  :(RETURN)
tmpl_parse_args.END 
-LINE 294 "HTMLTMPL.lss" 
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
