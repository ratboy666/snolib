-PLUSOPS 1 
  :(HTMLTMPL.1)
-LINE 53 "HTMLTMPL.lss" 
-LINE 70 "HTMLTMPL.lss"
  :(tmpl_init.END)
-LINE 74
tmpl_init tmpl_dir = "./"
-LINE 78
 tmpl_ws = span(" " chars_tab) | ""
-LINE 79
 tmpl = ("/" | "") . h any("Tt") any("Mm") any("Pp") any("Ll") "_"
-LINE 81
 tmpl_tag = tmpl span(&ucase &lcase) . tag
-LINE 82
 tmpl_c = "<!-- " tmpl_ws tmpl_tag arb . arg " -->"
-LINE 83
 tmpl_t = "<" tmpl_tag break(">") . arg ">"
-LINE 84
 tmpl_piece = pos(0) breakx("<") . l (tmpl_t | tmpl_c) . p rem . r
-LINE 86
 tmpl_keys = "var if unless else loop include "
-LINE 90
 tmpl_arg_var = tmpl_ws (any(&lcase &ucase) span(&lcase 
+&ucase '0123456789' "_")) . n tmpl_ws
-LINE 92
 tmpl_qval = '"' break('"') . v '"'
-LINE 93
 tmpl_sval = break(" " chars_tab) . v
-LINE 94
 tmpl_arg_p = (tmpl_arg_var "=" | "") tmpl_ws (tmpl_qval 
+| tmpl_sval | rem . v) :(RETURN)
-LINE 100
tmpl_init.END  :(tmpl_compile.END)
-LINE 101
tmpl_compile l = tmpl_tokenize(s) :S(HTMLTMPL.2)F(FRETURN)
-LINE 103
HTMLTMPL.2 l = tmpl_parse(l) :S(HTMLTMPL.3)F(FRETURN)
-LINE 105
HTMLTMPL.3 tmpl_compile = l :(RETURN)
-LINE 111
tmpl_compile.END  :(tmpl_interpret.END)
-LINE 112
tmpl_interpret interpret_tmpl(p,a) :(RETURN)
-LINE 117
tmpl_interpret.END  :(none_escape.END)
-LINE 118
none_escape none_escape = s :(RETURN)
-LINE 123
none_escape.END  :(interpret_tmpl.END)
-LINE 124
interpret_tmpl DIFFER(p,"") :F(HTMLTMPL.4)
-LINE 125
 v = value(value(p))
-LINE 126
 IDENT(token_type(v),"text") :F(HTMLTMPL.5)
-LINE 128
 tmpl_interpret = tmpl_interpret token_args(v) :(HTMLTMPL.6)
-LINE 129
HTMLTMPL.5 IDENT(token_type(v),"var") :F(HTMLTMPL.7)
-LINE 131
 t = token_args(v)
-LINE 132
 n = t<"name">
-LINE 133
 v = a<n>
-LINE 134
 IDENT(v,"") :F(HTMLTMPL.8)
-LINE 135
 v = t<"default">
-LINE 136
HTMLTMPL.8 e = t<"escape">
-LINE 138
 e = e "_escape"
-LINE 139
 n = &errlimit
-LINE 140
 &errlimit = 1
-LINE 141
 v = apply(e,v)
-LINE 142
 &errlimit = n
-LINE 143
 tmpl_interpret = tmpl_interpret v :(HTMLTMPL.9)
-LINE 144
HTMLTMPL.7 "if unless" ? token_type(v) :F(HTMLTMPL.10)
-LINE 146
 t = token_args(v)
-LINE 147
 n = t<"name">
-LINE 148
 n = a<n>
-LINE 149
 p1 = value(next(value(p)))
-LINE 150
 p2 = next(next(value(p)))
-LINE 151
 IDENT(token_type(v),"unless") :F(HTMLTMPL.11)
-LINE 152
 swap(.p1,.p2)
-LINE 153
HTMLTMPL.11 (DIFFER(n,""),ne(+n,0)) :F(HTMLTMPL.12)
-LINE 154
 interpret_tmpl(p1,a) :(HTMLTMPL.13)
-LINE 156
HTMLTMPL.12 interpret_tmpl(p2,a)
-LINE 157
HTMLTMPL.13  :(HTMLTMPL.14)
HTMLTMPL.10 IDENT(token_type(v),"loop") :F(HTMLTMPL.15)
-LINE 159
 t = token_args(v)
-LINE 160
 n = t<"name">
-LINE 161
 n = a<n>
-LINE 162
 IDENT(datatype(n),"ARRAY") :F(HTMLTMPL.16)
-LINE 163
 p1 = value(next(value(p)))
-LINE 165
 i = 1
HTMLTMPL.17 n<i> :F(HTMLTMPL.18)
-LINE 166
 interpret_tmpl(p1,n<i>)
 i = i + 1 :(HTMLTMPL.17)
HTMLTMPL.18 
HTMLTMPL.16 
HTMLTMPL.15 
HTMLTMPL.14 
HTMLTMPL.9 
-LINE 169
HTMLTMPL.6 p = next(p) :(interpret_tmpl)
-LINE 171
HTMLTMPL.4  :(RETURN)
-LINE 176
interpret_tmpl.END  :(tmpl_parse.END)
-LINE 177
tmpl_parse IDENT(l,"") :S(RETURN)F(HTMLTMPL.19)
-LINE 179
HTMLTMPL.19 r = tmpl_seq() :S(HTMLTMPL.20)F(FRETURN)
-LINE 181
HTMLTMPL.20 DIFFER(l,"") :S(FRETURN)F(HTMLTMPL.21)
-LINE 183
HTMLTMPL.21 tmpl_parse = r :(RETURN)
-LINE 189
tmpl_parse.END  :(tmpl_seq.END)
-LINE 190
tmpl_seq DIFFER(l,"") :F(HTMLTMPL.22)
-LINE 191
 v = value(l)
-LINE 192
 "text var" ? token_type(v) :F(HTMLTMPL.23)
-LINE 193
 r = link(link(v),r)
-LINE 194
 l = next(l) :(HTMLTMPL.24)
-LINE 195
HTMLTMPL.23 "if unless loop" ? token_type(v) :F(HTMLTMPL.25)
-LINE 196
 DIFFER(token_end(v),"") :F(HTMLTMPL.26)
-LINE 197
 tmpl_seq = revl(r) :(RETURN)
-LINE 198
HTMLTMPL.26 l = next(l)
-LINE 199
 p1 = tmpl_seq() :S(HTMLTMPL.27)F(FRETURN)
-LINE 201
HTMLTMPL.27 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.28)
-LINE 203
HTMLTMPL.28 p2 = ""
-LINE 204
 v2 = value(l)
-LINE 205
 "if unless loop" ? token_type(v2) :F(HTMLTMPL.29)
-LINE 206
 l = next(l) :(HTMLTMPL.30)
-LINE 207
HTMLTMPL.29 IDENT(token_type(v2),"else") :F(HTMLTMPL.31)
-LINE 208
 l = next(l)
-LINE 209
 p2 = tmpl_seq() :S(HTMLTMPL.32)F(FRETURN)
-LINE 211
HTMLTMPL.32 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.33)
-LINE 213
HTMLTMPL.33 l = next(l) :(HTMLTMPL.34)
-LINE 215
HTMLTMPL.31  :(FRETURN)
HTMLTMPL.34 
-LINE 216
HTMLTMPL.30 r = link(link(v,link(p1,p2)),r) :(HTMLTMPL.35)
-LINE 217
HTMLTMPL.25 IDENT(token_type(v),"else") :F(HTMLTMPL.36)
-LINE 218
 tmpl_seq = revl(r) :(RETURN)
-LINE 220
HTMLTMPL.36  :(FRETURN)
HTMLTMPL.37 
HTMLTMPL.35 
-LINE 221
HTMLTMPL.24  :(tmpl_seq)
-LINE 222
HTMLTMPL.22 tmpl_seq = revl(r) :(RETURN)
-LINE 227
tmpl_seq.END  :(tmpl_tokenize.END)
-LINE 228
tmpl_tokenize n = .tmpl_tokenize
-LINE 229
HTMLTMPL.38 DIFFER(s,"") :F(HTMLTMPL.39)
-LINE 230
 s ? tmpl_piece :F(HTMLTMPL.40)
-LINE 231
 tag = replace(tag,&ucase,&lcase)
-LINE 232
 tmpl_keys ? tag " " :F(HTMLTMPL.41)
-LINE 233
 DIFFER(l,"") :F(HTMLTMPL.42)
-LINE 234
 $n = link(tmpl_token("text","",l))
 n = .next($n)
-LINE 236
HTMLTMPL.42 IDENT(tag,"include") :F(HTMLTMPL.43)
-LINE 241
 t = tmpl_parse_args(arg) :S(HTMLTMPL.44)F(FRETURN)
-LINE 243
HTMLTMPL.44 s = readfile(tmpl_dir t<'name'>) :F(HTMLTMPL.45)
-LINE 244
 $n = tmpl_tokenize(s) :S(HTMLTMPL.46)F(FRETURN)
-LINE 246
HTMLTMPL.46 n = .last(tmpl_tokenize)
-LINE 248
HTMLTMPL.45  :(HTMLTMPL.47)
-LINE 249
HTMLTMPL.43 t = tmpl_token(tag,h,tmpl_parse_args(arg))
-LINE 250
 $n = link(t)
 n = .next($n)
-LINE 252
HTMLTMPL.47  :(HTMLTMPL.48)
-LINE 253
HTMLTMPL.41 $n = link(tmpl_token("text","",l p))
 n = .next($n)
-LINE 255
HTMLTMPL.48 s = r :(HTMLTMPL.49)
-LINE 257
HTMLTMPL.40 $n = link(tmpl_token("text","",s))
 n = .next($n)
-LINE 258
 s = ""
-LINE 260
HTMLTMPL.49  :(HTMLTMPL.38)
-LINE 261
HTMLTMPL.39  :(RETURN)
-LINE 266
tmpl_tokenize.END  :(tmpl_parse_args.END)
-LINE 267
tmpl_parse_args tmpl_parse_args = table()
-LINE 268
HTMLTMPL.50 DIFFER(s,"") :F(HTMLTMPL.51)
-LINE 269
 n = ""
-LINE 270
 v = ""
-LINE 271
 s ? tmpl_arg_p = "" :F(HTMLTMPL.52)
-LINE 272
 n = replace(n,&ucase,&lcase)
-LINE 273
 n = ident(n) "name"
-LINE 274
 tmpl_parse_args<n> = v :(HTMLTMPL.53)
-LINE 276
HTMLTMPL.52  :(FRETURN)
-LINE 277
HTMLTMPL.53  :(HTMLTMPL.50)
-LINE 278
HTMLTMPL.51  :(RETURN)
tmpl_parse_args.END 
-LINE 287 "HTMLTMPL.lss" 
HTMLTMPL.1 
 DATA('tmpl_token(token_type,token_end,token_args)')
-include 'LINK.INC' 
-include 'CHARS.INC' 
-include 'LAST.INC' 
-include 'REVL.INC' 
-include 'SWAP.INC' 
-include 'READFILE.INC' 
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
