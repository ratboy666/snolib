-PLUSOPS 1 
  :(HTMLTMPL.1)
-LINE 52 "HTMLTMPL.lss" 
-LINE 69 "HTMLTMPL.lss"
  :(tmpl_init.END)
-LINE 73
tmpl_init tmpl_dir = "./"
-LINE 77
 tmpl_ws = span(" " chars_tab) | ""
-LINE 78
 tmpl = ("/" | "") . h any("Tt") any("Mm") any("Pp") any("Ll") "_"
-LINE 80
 tmpl_tag = tmpl span(&ucase &lcase) . tag
-LINE 81
 tmpl_c = "<!-- " tmpl_ws tmpl_tag arb . arg " -->"
-LINE 82
 tmpl_t = "<" tmpl_tag break(">") . arg ">"
-LINE 83
 tmpl_piece = pos(0) breakx("<") . l (tmpl_t | tmpl_c) . p rem . r
-LINE 85
 tmpl_keys = "var if unless else loop include "
-LINE 89
 tmpl_arg_var = tmpl_ws (any(&lcase &ucase) span(&lcase 
+&ucase &digits "_")) . n tmpl_ws
-LINE 91
 tmpl_qval = '"' break('"') . v '"'
-LINE 92
 tmpl_sval = break(" " chars_tab) . v
-LINE 93
 tmpl_arg_p = (tmpl_arg_var "=" | "") tmpl_ws (tmpl_qval 
+| tmpl_sval | rem . v) :(RETURN)
-LINE 99
tmpl_init.END  :(tmpl_compile.END)
-LINE 100
tmpl_compile l = tmpl_tokenize(s) :S(HTMLTMPL.2)F(FRETURN)
-LINE 102
HTMLTMPL.2 l = tmpl_parse(l) :S(HTMLTMPL.3)F(FRETURN)
-LINE 104
HTMLTMPL.3 tmpl_compile = l :(RETURN)
-LINE 110
tmpl_compile.END  :(tmpl_interpret.END)
-LINE 111
tmpl_interpret interpret_tmpl(p,a) :(RETURN)
-LINE 116
tmpl_interpret.END  :(none_escape.END)
-LINE 117
none_escape none_escape = s :(RETURN)
-LINE 122
none_escape.END  :(interpret_tmpl.END)
-LINE 123
interpret_tmpl DIFFER(p,"") :F(HTMLTMPL.4)
-LINE 124
 v = value(value(p))
-LINE 125
 IDENT(token_type(v),"text") :F(HTMLTMPL.5)
-LINE 127
 tmpl_interpret = tmpl_interpret token_args(v) :(HTMLTMPL.6)
-LINE 128
HTMLTMPL.5 IDENT(token_type(v),"var") :F(HTMLTMPL.7)
-LINE 130
 t = token_args(v)
-LINE 131
 n = t<"name">
-LINE 132
 v = a<n>
-LINE 133
 IDENT(v,"") :F(HTMLTMPL.8)
-LINE 134
 v = t<"default">
-LINE 135
HTMLTMPL.8 e = t<"escape">
-LINE 137
 e = e "_escape"
-LINE 138
 n = &errlimit
-LINE 139
 &errlimit = 1
-LINE 140
 v = apply(e,v)
-LINE 141
 &errlimit = n
-LINE 142
 tmpl_interpret = tmpl_interpret v :(HTMLTMPL.9)
-LINE 143
HTMLTMPL.7 "if unless" ? token_type(v) :F(HTMLTMPL.10)
-LINE 145
 t = token_args(v)
-LINE 146
 n = t<"name">
-LINE 147
 n = a<n>
-LINE 148
 p1 = value(next(value(p)))
-LINE 149
 p2 = next(next(value(p)))
-LINE 150
 IDENT(token_type(v),"unless") :F(HTMLTMPL.11)
-LINE 151
 swap(.p1,.p2)
-LINE 152
HTMLTMPL.11 (DIFFER(n,""),ne(+n,0)) :F(HTMLTMPL.12)
-LINE 153
 interpret_tmpl(p1,a) :(HTMLTMPL.13)
-LINE 155
HTMLTMPL.12 interpret_tmpl(p2,a)
-LINE 156
HTMLTMPL.13  :(HTMLTMPL.14)
HTMLTMPL.10 IDENT(token_type(v),"loop") :F(HTMLTMPL.15)
-LINE 158
 t = token_args(v)
-LINE 159
 n = t<"name">
-LINE 160
 n = a<n>
-LINE 161
 IDENT(datatype(n),"ARRAY") :F(HTMLTMPL.16)
-LINE 162
 p1 = value(next(value(p)))
-LINE 163
 seq(' interpret_tmpl(p1, n[i]) ',.i)
HTMLTMPL.16 
HTMLTMPL.15 
HTMLTMPL.14 
HTMLTMPL.9 
-LINE 166
HTMLTMPL.6 p = next(p) :(interpret_tmpl)
-LINE 168
HTMLTMPL.4  :(RETURN)
-LINE 173
interpret_tmpl.END  :(tmpl_parse.END)
-LINE 174
tmpl_parse IDENT(l,"") :S(RETURN)F(HTMLTMPL.17)
-LINE 176
HTMLTMPL.17 r = tmpl_seq() :S(HTMLTMPL.18)F(FRETURN)
-LINE 178
HTMLTMPL.18 DIFFER(l,"") :S(FRETURN)F(HTMLTMPL.19)
-LINE 180
HTMLTMPL.19 tmpl_parse = r :(RETURN)
-LINE 186
tmpl_parse.END  :(tmpl_seq.END)
-LINE 187
tmpl_seq DIFFER(l,"") :F(HTMLTMPL.20)
-LINE 188
 v = value(l)
-LINE 189
 "text var" ? token_type(v) :F(HTMLTMPL.21)
-LINE 190
 r = link(link(v),r)
-LINE 191
 l = next(l) :(HTMLTMPL.22)
-LINE 192
HTMLTMPL.21 "if unless loop" ? token_type(v) :F(HTMLTMPL.23)
-LINE 193
 DIFFER(token_end(v),"") :F(HTMLTMPL.24)
-LINE 194
 tmpl_seq = revl(r) :(RETURN)
-LINE 195
HTMLTMPL.24 l = next(l)
-LINE 196
 p1 = tmpl_seq() :S(HTMLTMPL.25)F(FRETURN)
-LINE 198
HTMLTMPL.25 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.26)
-LINE 200
HTMLTMPL.26 p2 = ""
-LINE 201
 v2 = value(l)
-LINE 202
 "if unless loop" ? token_type(v2) :F(HTMLTMPL.27)
-LINE 203
 l = next(l) :(HTMLTMPL.28)
-LINE 204
HTMLTMPL.27 IDENT(token_type(v2),"else") :F(HTMLTMPL.29)
-LINE 205
 l = next(l)
-LINE 206
 p2 = tmpl_seq() :S(HTMLTMPL.30)F(FRETURN)
-LINE 208
HTMLTMPL.30 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.31)
-LINE 210
HTMLTMPL.31 l = next(l) :(HTMLTMPL.32)
-LINE 212
HTMLTMPL.29  :(FRETURN)
HTMLTMPL.32 
-LINE 213
HTMLTMPL.28 r = link(link(v,link(p1,p2)),r) :(HTMLTMPL.33)
-LINE 214
HTMLTMPL.23 IDENT(token_type(v),"else") :F(HTMLTMPL.34)
-LINE 215
 tmpl_seq = revl(r) :(RETURN)
-LINE 217
HTMLTMPL.34  :(FRETURN)
HTMLTMPL.35 
HTMLTMPL.33 
-LINE 218
HTMLTMPL.22  :(tmpl_seq)
-LINE 219
HTMLTMPL.20 tmpl_seq = revl(r) :(RETURN)
-LINE 224
tmpl_seq.END  :(tmpl_tokenize.END)
-LINE 225
tmpl_tokenize n = .tmpl_tokenize
-LINE 226
HTMLTMPL.36 DIFFER(s,"") :F(HTMLTMPL.37)
-LINE 227
 s ? tmpl_piece :F(HTMLTMPL.38)
-LINE 228
 tag = replace(tag,&ucase,&lcase)
-LINE 229
 tmpl_keys ? tag " " :F(HTMLTMPL.39)
-LINE 230
 DIFFER(l,"") :F(HTMLTMPL.40)
-LINE 231
 $n = link(tmpl_token("text","",l))
 n = .next($n)
-LINE 233
HTMLTMPL.40 IDENT(tag,"include") :F(HTMLTMPL.41)
-LINE 238
 t = tmpl_parse_args(arg) :S(HTMLTMPL.42)F(FRETURN)
-LINE 240
HTMLTMPL.42 s = readfile(tmpl_dir t<'name'>) :F(HTMLTMPL.43)
-LINE 241
 $n = tmpl_tokenize(s) :S(HTMLTMPL.44)F(FRETURN)
-LINE 243
HTMLTMPL.44 n = .last(tmpl_tokenize)
-LINE 245
HTMLTMPL.43  :(HTMLTMPL.45)
-LINE 246
HTMLTMPL.41 t = tmpl_token(tag,h,tmpl_parse_args(arg))
-LINE 247
 $n = link(t)
 n = .next($n)
-LINE 249
HTMLTMPL.45  :(HTMLTMPL.46)
-LINE 250
HTMLTMPL.39 $n = link(tmpl_token("text","",l p))
 n = .next($n)
-LINE 252
HTMLTMPL.46 s = r :(HTMLTMPL.47)
-LINE 254
HTMLTMPL.38 $n = link(tmpl_token("text","",s))
 n = .next($n)
-LINE 255
 s = ""
-LINE 257
HTMLTMPL.47  :(HTMLTMPL.36)
-LINE 258
HTMLTMPL.37  :(RETURN)
-LINE 263
tmpl_tokenize.END  :(tmpl_parse_args.END)
-LINE 264
tmpl_parse_args tmpl_parse_args = table()
-LINE 265
HTMLTMPL.48 DIFFER(s,"") :F(HTMLTMPL.49)
-LINE 266
 n = ""
-LINE 267
 v = ""
-LINE 268
 s ? tmpl_arg_p = "" :F(HTMLTMPL.50)
-LINE 269
 n = replace(n,&ucase,&lcase)
-LINE 270
 n = ident(n) "name"
-LINE 271
 tmpl_parse_args<n> = v :(HTMLTMPL.51)
-LINE 273
HTMLTMPL.50  :(FRETURN)
-LINE 274
HTMLTMPL.51  :(HTMLTMPL.48)
-LINE 275
HTMLTMPL.49  :(RETURN)
tmpl_parse_args.END 
-LINE 284 "HTMLTMPL.lss" 
HTMLTMPL.1 
 DATA('tmpl_token(token_type,token_end,token_args)')
-include 'LINK.INC' 
-include 'CHARS.INC' 
-include 'LAST.INC' 
-include 'REVL.INC' 
-include 'SWAP.INC' 
-include 'READFILE.INC' 
-include 'SEQ.INC' 
-include 'HTMLESC.INC' 
 DEFINE('tmpl_init()')
 DEFINE('tmpl_compile(s)l')
 DEFINE('tmpl_interpret(p,a)')
 DEFINE('none_escape(s)')
 DEFINE('interpret_tmpl(p,a)p1,p2,v,n,t,e,i')
 DEFINE('tmpl_parse(l)r')
 DEFINE('tmpl_seq()r,v,v2,p1,p2')
 DEFINE('tmpl_tokenize(s)l,r,p,tag,r,h,n,t')
 DEFINE('tmpl_parse_args(s)n,v')
  tmpl_init()
