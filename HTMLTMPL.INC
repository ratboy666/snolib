-PLUSOPS 1 
  :(HTMLTMPL.1)
-LINE 53 "HTMLTMPL.lss" 
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
+&ucase '0123456789' "_")) . n tmpl_ws
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
interpret_tmpl p
HTMLTMPL.4 DIFFER(p,"") :F(HTMLTMPL.5)
-LINE 124
 v = value(value(p))
-LINE 125
 IDENT(token_type(v),"text") :F(HTMLTMPL.6)
-LINE 127
 tmpl_interpret = tmpl_interpret token_args(v) :(HTMLTMPL.7)
-LINE 129
HTMLTMPL.6 t = token_args(v)
-LINE 130
 n = a<t<"name">>
-LINE 131
 IDENT(token_type(v),"var") :F(HTMLTMPL.8)
-LINE 133
 IDENT(n,"") :F(HTMLTMPL.9)
-LINE 134
 n = t<"default">
-LINE 135
HTMLTMPL.9 e = t<"escape">
-LINE 137
 e = e "_escape"
-LINE 138
 v = &errlimit
 &errlimit = 1
 n = apply(e,n)
 &errlimit = v
-LINE 139
 tmpl_interpret = tmpl_interpret n :(HTMLTMPL.10)
-LINE 140
HTMLTMPL.8 "if unless" ? token_type(v) :F(HTMLTMPL.11)
-LINE 142
 p1 = value(next(value(p)))
-LINE 143
 p2 = next(next(value(p)))
-LINE 144
 IDENT(token_type(v),"unless") :F(HTMLTMPL.12)
-LINE 145
 swap(.p1,.p2)
-LINE 146
HTMLTMPL.12 (DIFFER(n,""),ne(+n,0)) :F(HTMLTMPL.13)
-LINE 147
 interpret_tmpl(p1,a) :(HTMLTMPL.14)
-LINE 149
HTMLTMPL.13 interpret_tmpl(p2,a)
-LINE 150
HTMLTMPL.14  :(HTMLTMPL.15)
HTMLTMPL.11 IDENT(token_type(v),"loop") :F(HTMLTMPL.16)
-LINE 152
 IDENT(datatype(n),"ARRAY") :F(HTMLTMPL.17)
-LINE 153
 p1 = value(next(value(p)))
-LINE 154
 i = 1
HTMLTMPL.18 n<i> :F(HTMLTMPL.19)
-LINE 155
 interpret_tmpl(p1,n<i>)
 i = i + 1 :(HTMLTMPL.18)
HTMLTMPL.19 
HTMLTMPL.17 
HTMLTMPL.16 
HTMLTMPL.15 
HTMLTMPL.10 
-LINE 159
HTMLTMPL.7 p = next(p) :(HTMLTMPL.4)
-LINE 160
HTMLTMPL.5  :(RETURN)
-LINE 165
interpret_tmpl.END  :(tmpl_parse.END)
-LINE 166
tmpl_parse IDENT(l,"") :S(RETURN)F(HTMLTMPL.20)
-LINE 168
HTMLTMPL.20 r = tmpl_seq() :S(HTMLTMPL.21)F(FRETURN)
-LINE 170
HTMLTMPL.21 DIFFER(l,"") :S(FRETURN)F(HTMLTMPL.22)
-LINE 172
HTMLTMPL.22 tmpl_parse = r :(RETURN)
-LINE 178
tmpl_parse.END  :(tmpl_seq.END)
-LINE 179
tmpl_seq DIFFER(l,"") :F(HTMLTMPL.23)
-LINE 180
 v = value(l)
-LINE 181
 "text var" ? token_type(v) :F(HTMLTMPL.24)
-LINE 182
 r = link(link(v),r)
-LINE 183
 l = next(l) :(HTMLTMPL.25)
-LINE 184
HTMLTMPL.24 "if unless loop" ? token_type(v) :F(HTMLTMPL.26)
-LINE 185
 DIFFER(token_end(v),"") :F(HTMLTMPL.27)
-LINE 186
 tmpl_seq = revl(r) :(RETURN)
-LINE 187
HTMLTMPL.27 l = next(l)
-LINE 188
 p1 = tmpl_seq() :S(HTMLTMPL.28)F(FRETURN)
-LINE 190
HTMLTMPL.28 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.29)
-LINE 192
HTMLTMPL.29 p2 = ""
-LINE 193
 v2 = value(l)
-LINE 194
 "if unless loop" ? token_type(v2) :F(HTMLTMPL.30)
-LINE 195
 l = next(l) :(HTMLTMPL.31)
-LINE 196
HTMLTMPL.30 IDENT(token_type(v2),"else") :F(HTMLTMPL.32)
-LINE 197
 l = next(l)
-LINE 198
 p2 = tmpl_seq() :S(HTMLTMPL.33)F(FRETURN)
-LINE 200
HTMLTMPL.33 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.34)
-LINE 202
HTMLTMPL.34 l = next(l) :(HTMLTMPL.35)
-LINE 204
HTMLTMPL.32  :(FRETURN)
HTMLTMPL.35 
-LINE 205
HTMLTMPL.31 r = link(link(v,link(p1,p2)),r) :(HTMLTMPL.36)
-LINE 206
HTMLTMPL.26 IDENT(token_type(v),"else") :F(HTMLTMPL.37)
-LINE 207
 tmpl_seq = revl(r) :(RETURN)
-LINE 209
HTMLTMPL.37  :(FRETURN)
HTMLTMPL.38 
HTMLTMPL.36 
-LINE 210
HTMLTMPL.25  :(tmpl_seq)
-LINE 211
HTMLTMPL.23 tmpl_seq = revl(r) :(RETURN)
-LINE 216
tmpl_seq.END  :(tmpl_tokenize.END)
-LINE 217
tmpl_tokenize n = .tmpl_tokenize
-LINE 218
HTMLTMPL.39 DIFFER(s,"") :F(HTMLTMPL.40)
-LINE 219
 s ? tmpl_piece :F(HTMLTMPL.41)
-LINE 220
 tag = replace(tag,&ucase,&lcase)
-LINE 221
 tmpl_keys ? tag " " :F(HTMLTMPL.42)
-LINE 222
 DIFFER(l,"") :F(HTMLTMPL.43)
-LINE 223
 $n = link(tmpl_token("text","",l))
 n = .next($n)
-LINE 225
HTMLTMPL.43 IDENT(tag,"include") :F(HTMLTMPL.44)
-LINE 230
 t = tmpl_parse_args(arg) :S(HTMLTMPL.45)F(FRETURN)
-LINE 232
HTMLTMPL.45 s = readfile(tmpl_dir t<'name'>) :F(HTMLTMPL.46)
-LINE 233
 $n = tmpl_tokenize(s) :S(HTMLTMPL.47)F(FRETURN)
-LINE 235
HTMLTMPL.47 n = .last(tmpl_tokenize)
-LINE 237
HTMLTMPL.46  :(HTMLTMPL.48)
-LINE 238
HTMLTMPL.44 t = tmpl_token(tag,h,tmpl_parse_args(arg))
-LINE 239
 $n = link(t)
 n = .next($n)
-LINE 241
HTMLTMPL.48  :(HTMLTMPL.49)
-LINE 242
HTMLTMPL.42 $n = link(tmpl_token("text","",l p))
 n = .next($n)
-LINE 244
HTMLTMPL.49 s = r :(HTMLTMPL.50)
-LINE 246
HTMLTMPL.41 $n = link(tmpl_token("text","",s))
 n = .next($n)
-LINE 247
 s = ""
-LINE 249
HTMLTMPL.50  :(HTMLTMPL.39)
-LINE 250
HTMLTMPL.40  :(RETURN)
-LINE 255
tmpl_tokenize.END  :(tmpl_parse_args.END)
-LINE 256
tmpl_parse_args tmpl_parse_args = table()
-LINE 257
HTMLTMPL.51 DIFFER(s,"") :F(HTMLTMPL.52)
-LINE 258
 n = ""
-LINE 259
 v = ""
-LINE 260
 s ? tmpl_arg_p = "" :F(HTMLTMPL.53)
-LINE 261
 n = replace(n,&ucase,&lcase)
-LINE 262
 n = ident(n) "name"
-LINE 263
 tmpl_parse_args<n> = v :(HTMLTMPL.54)
-LINE 265
HTMLTMPL.53  :(FRETURN)
-LINE 266
HTMLTMPL.54  :(HTMLTMPL.51)
-LINE 267
HTMLTMPL.52  :(RETURN)
tmpl_parse_args.END 
-LINE 276 "HTMLTMPL.lss" 
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
