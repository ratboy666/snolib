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
-LINE 164
 seq(' interpret_tmpl(p1, n[i]) ',.i)
HTMLTMPL.16 
HTMLTMPL.15 
HTMLTMPL.14 
HTMLTMPL.9 
-LINE 167
HTMLTMPL.6 p = next(p) :(interpret_tmpl)
-LINE 169
HTMLTMPL.4  :(RETURN)
-LINE 174
interpret_tmpl.END  :(tmpl_parse.END)
-LINE 175
tmpl_parse IDENT(l,"") :S(RETURN)F(HTMLTMPL.17)
-LINE 177
HTMLTMPL.17 r = tmpl_seq() :S(HTMLTMPL.18)F(FRETURN)
-LINE 179
HTMLTMPL.18 DIFFER(l,"") :S(FRETURN)F(HTMLTMPL.19)
-LINE 181
HTMLTMPL.19 tmpl_parse = r :(RETURN)
-LINE 187
tmpl_parse.END  :(tmpl_seq.END)
-LINE 188
tmpl_seq DIFFER(l,"") :F(HTMLTMPL.20)
-LINE 189
 v = value(l)
-LINE 190
 "text var" ? token_type(v) :F(HTMLTMPL.21)
-LINE 191
 r = link(link(v),r)
-LINE 192
 l = next(l) :(HTMLTMPL.22)
-LINE 193
HTMLTMPL.21 "if unless loop" ? token_type(v) :F(HTMLTMPL.23)
-LINE 194
 DIFFER(token_end(v),"") :F(HTMLTMPL.24)
-LINE 195
 tmpl_seq = revl(r) :(RETURN)
-LINE 196
HTMLTMPL.24 l = next(l)
-LINE 197
 p1 = tmpl_seq() :S(HTMLTMPL.25)F(FRETURN)
-LINE 199
HTMLTMPL.25 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.26)
-LINE 201
HTMLTMPL.26 p2 = ""
-LINE 202
 v2 = value(l)
-LINE 203
 "if unless loop" ? token_type(v2) :F(HTMLTMPL.27)
-LINE 204
 l = next(l) :(HTMLTMPL.28)
-LINE 205
HTMLTMPL.27 IDENT(token_type(v2),"else") :F(HTMLTMPL.29)
-LINE 206
 l = next(l)
-LINE 207
 p2 = tmpl_seq() :S(HTMLTMPL.30)F(FRETURN)
-LINE 209
HTMLTMPL.30 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.31)
-LINE 211
HTMLTMPL.31 l = next(l) :(HTMLTMPL.32)
-LINE 213
HTMLTMPL.29  :(FRETURN)
HTMLTMPL.32 
-LINE 214
HTMLTMPL.28 r = link(link(v,link(p1,p2)),r) :(HTMLTMPL.33)
-LINE 215
HTMLTMPL.23 IDENT(token_type(v),"else") :F(HTMLTMPL.34)
-LINE 216
 tmpl_seq = revl(r) :(RETURN)
-LINE 218
HTMLTMPL.34  :(FRETURN)
HTMLTMPL.35 
HTMLTMPL.33 
-LINE 219
HTMLTMPL.22  :(tmpl_seq)
-LINE 220
HTMLTMPL.20 tmpl_seq = revl(r) :(RETURN)
-LINE 225
tmpl_seq.END  :(tmpl_tokenize.END)
-LINE 226
tmpl_tokenize n = .tmpl_tokenize
-LINE 227
HTMLTMPL.36 DIFFER(s,"") :F(HTMLTMPL.37)
-LINE 228
 s ? tmpl_piece :F(HTMLTMPL.38)
-LINE 229
 tag = replace(tag,&ucase,&lcase)
-LINE 230
 tmpl_keys ? tag " " :F(HTMLTMPL.39)
-LINE 231
 DIFFER(l,"") :F(HTMLTMPL.40)
-LINE 232
 $n = link(tmpl_token("text","",l))
 n = .next($n)
-LINE 234
HTMLTMPL.40 IDENT(tag,"include") :F(HTMLTMPL.41)
-LINE 239
 t = tmpl_parse_args(arg) :S(HTMLTMPL.42)F(FRETURN)
-LINE 241
HTMLTMPL.42 s = readfile(tmpl_dir t<'name'>) :F(HTMLTMPL.43)
-LINE 242
 $n = tmpl_tokenize(s) :S(HTMLTMPL.44)F(FRETURN)
-LINE 244
HTMLTMPL.44 n = .last(tmpl_tokenize)
-LINE 246
HTMLTMPL.43  :(HTMLTMPL.45)
-LINE 247
HTMLTMPL.41 t = tmpl_token(tag,h,tmpl_parse_args(arg))
-LINE 248
 $n = link(t)
 n = .next($n)
-LINE 250
HTMLTMPL.45  :(HTMLTMPL.46)
-LINE 251
HTMLTMPL.39 $n = link(tmpl_token("text","",l p))
 n = .next($n)
-LINE 253
HTMLTMPL.46 s = r :(HTMLTMPL.47)
-LINE 255
HTMLTMPL.38 $n = link(tmpl_token("text","",s))
 n = .next($n)
-LINE 256
 s = ""
-LINE 258
HTMLTMPL.47  :(HTMLTMPL.36)
-LINE 259
HTMLTMPL.37  :(RETURN)
-LINE 264
tmpl_tokenize.END  :(tmpl_parse_args.END)
-LINE 265
tmpl_parse_args tmpl_parse_args = table()
-LINE 266
HTMLTMPL.48 DIFFER(s,"") :F(HTMLTMPL.49)
-LINE 267
 n = ""
-LINE 268
 v = ""
-LINE 269
 s ? tmpl_arg_p = "" :F(HTMLTMPL.50)
-LINE 270
 n = replace(n,&ucase,&lcase)
-LINE 271
 n = ident(n) "name"
-LINE 272
 tmpl_parse_args<n> = v :(HTMLTMPL.51)
-LINE 274
HTMLTMPL.50  :(FRETURN)
-LINE 275
HTMLTMPL.51  :(HTMLTMPL.48)
-LINE 276
HTMLTMPL.49  :(RETURN)
tmpl_parse_args.END 
-LINE 285 "HTMLTMPL.lss" 
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
