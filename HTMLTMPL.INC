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
-LINE 101
tmpl_init.END  :(tmpl_compile.END)
-LINE 102
tmpl_compile l = tmpl_tokenize(s) :S(HTMLTMPL.2)F(FRETURN)
-LINE 104
HTMLTMPL.2 l = tmpl_parse(l) :S(HTMLTMPL.3)F(FRETURN)
-LINE 106
HTMLTMPL.3 tmpl_compile = l :(RETURN)
-LINE 113
tmpl_compile.END  :(tmpl_interpret.END)
-LINE 114
tmpl_interpret interpret_tmpl(p,a) :(RETURN)
-LINE 119
tmpl_interpret.END  :(none_escape.END)
-LINE 120
none_escape none_escape = s :(RETURN)
-LINE 125
none_escape.END  :(interpret_tmpl.END)
-LINE 126
interpret_tmpl p
HTMLTMPL.4 DIFFER(p,"") :F(HTMLTMPL.5)
-LINE 127
 v = value(value(p))
-LINE 128
 IDENT(token_type(v),"text") :F(HTMLTMPL.6)
-LINE 130
 tmpl_interpret = tmpl_interpret token_args(v) :(HTMLTMPL.7)
-LINE 132
HTMLTMPL.6 t = token_args(v)
-LINE 133
 n = a<t<"name">>
-LINE 134
 IDENT(token_type(v),"var") :F(HTMLTMPL.8)
-LINE 136
 IDENT(n,"") :F(HTMLTMPL.9)
-LINE 137
 n = t<"default">
-LINE 138
HTMLTMPL.9 e = t<"escape">
-LINE 140
 e = e "_escape"
-LINE 141
 v = &errlimit
 &errlimit = 1
 n = apply(e,n)
 &errlimit = v
-LINE 142
 tmpl_interpret = tmpl_interpret n :(HTMLTMPL.10)
-LINE 143
HTMLTMPL.8 "if unless" ? token_type(v) :F(HTMLTMPL.11)
-LINE 145
 p1 = value(next(value(p)))
-LINE 146
 p2 = next(next(value(p)))
-LINE 147
 IDENT(token_type(v),"unless") :F(HTMLTMPL.12)
-LINE 148
 swap(.p1,.p2)
-LINE 149
HTMLTMPL.12 (DIFFER(n,""),ne(+n,0)) :F(HTMLTMPL.13)
-LINE 150
 interpret_tmpl(p1,a) :(HTMLTMPL.14)
-LINE 152
HTMLTMPL.13 interpret_tmpl(p2,a)
-LINE 153
HTMLTMPL.14  :(HTMLTMPL.15)
HTMLTMPL.11 IDENT(token_type(v),"loop") :F(HTMLTMPL.16)
-LINE 155
 IDENT(datatype(n),"ARRAY") :F(HTMLTMPL.17)
-LINE 156
 p1 = value(next(value(p)))
-LINE 157
 i = 1
HTMLTMPL.18 n<i> :F(HTMLTMPL.19)
-LINE 158
 interpret_tmpl(p1,n<i>)
 i = i + 1 :(HTMLTMPL.18)
HTMLTMPL.19 
HTMLTMPL.17 
HTMLTMPL.16 
HTMLTMPL.15 
HTMLTMPL.10 
-LINE 162
HTMLTMPL.7 p = next(p) :(HTMLTMPL.4)
-LINE 163
HTMLTMPL.5  :(RETURN)
-LINE 168
interpret_tmpl.END  :(tmpl_parse.END)
-LINE 169
tmpl_parse IDENT(l,"") :S(RETURN)F(HTMLTMPL.20)
-LINE 171
HTMLTMPL.20 r = tmpl_seq() :S(HTMLTMPL.21)F(FRETURN)
-LINE 173
HTMLTMPL.21 DIFFER(l,"") :S(FRETURN)F(HTMLTMPL.22)
-LINE 175
HTMLTMPL.22 tmpl_parse = r :(RETURN)
-LINE 181
tmpl_parse.END  :(tmpl_seq.END)
-LINE 182
tmpl_seq DIFFER(l,"") :F(HTMLTMPL.23)
-LINE 183
 v = value(l)
-LINE 184
 "text var" ? token_type(v) :F(HTMLTMPL.24)
-LINE 185
 r = link(link(v),r)
-LINE 186
 l = next(l) :(HTMLTMPL.25)
-LINE 187
HTMLTMPL.24 "if unless loop" ? token_type(v) :F(HTMLTMPL.26)
-LINE 188
 DIFFER(token_end(v),"") :F(HTMLTMPL.27)
-LINE 189
 tmpl_seq = revl(r) :(RETURN)
-LINE 190
HTMLTMPL.27 l = next(l)
-LINE 191
 p1 = tmpl_seq() :S(HTMLTMPL.28)F(FRETURN)
-LINE 193
HTMLTMPL.28 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.29)
-LINE 195
HTMLTMPL.29 p2 = ""
-LINE 196
 v2 = value(l)
-LINE 197
 "if unless loop" ? token_type(v2) :F(HTMLTMPL.30)
-LINE 198
 l = next(l) :(HTMLTMPL.31)
-LINE 199
HTMLTMPL.30 IDENT(token_type(v2),"else") :F(HTMLTMPL.32)
-LINE 200
 l = next(l)
-LINE 201
 p2 = tmpl_seq() :S(HTMLTMPL.33)F(FRETURN)
-LINE 203
HTMLTMPL.33 IDENT(l,"") :S(FRETURN)F(HTMLTMPL.34)
-LINE 205
HTMLTMPL.34 l = next(l) :(HTMLTMPL.35)
-LINE 207
HTMLTMPL.32  :(FRETURN)
HTMLTMPL.35 
-LINE 208
HTMLTMPL.31 r = link(link(v,link(p1,p2)),r) :(HTMLTMPL.36)
-LINE 209
HTMLTMPL.26 IDENT(token_type(v),"else") :F(HTMLTMPL.37)
-LINE 210
 tmpl_seq = revl(r) :(RETURN)
-LINE 212
HTMLTMPL.37  :(FRETURN)
HTMLTMPL.38 
HTMLTMPL.36 
-LINE 213
HTMLTMPL.25  :(tmpl_seq)
-LINE 214
HTMLTMPL.23 tmpl_seq = revl(r) :(RETURN)
-LINE 219
tmpl_seq.END  :(tmpl_tokenize.END)
-LINE 220
tmpl_tokenize n = .tmpl_tokenize
-LINE 221
HTMLTMPL.39 DIFFER(s,"") :F(HTMLTMPL.40)
-LINE 222
 s ? tmpl_piece :F(HTMLTMPL.41)
-LINE 223
 tag = replace(tag,&ucase,&lcase)
-LINE 224
 tmpl_keys ? tag " " :F(HTMLTMPL.42)
-LINE 225
 DIFFER(l,"") :F(HTMLTMPL.43)
-LINE 226
 $n = link(tmpl_token("text","",l))
 n = .next($n)
-LINE 228
HTMLTMPL.43 IDENT(tag,"include") :F(HTMLTMPL.44)
-LINE 233
 t = tmpl_parse_args(arg) :S(HTMLTMPL.45)F(FRETURN)
-LINE 235
HTMLTMPL.45 s = readfile(tmpl_dir t<'name'>) :F(HTMLTMPL.46)
-LINE 236
 $n = tmpl_tokenize(s) :S(HTMLTMPL.47)F(FRETURN)
-LINE 238
HTMLTMPL.47 n = .last(tmpl_tokenize)
-LINE 240
HTMLTMPL.46  :(HTMLTMPL.48)
-LINE 241
HTMLTMPL.44 t = tmpl_token(tag,h,tmpl_parse_args(arg))
-LINE 242
 $n = link(t)
 n = .next($n)
-LINE 244
HTMLTMPL.48  :(HTMLTMPL.49)
-LINE 245
HTMLTMPL.42 $n = link(tmpl_token("text","",l p))
 n = .next($n)
-LINE 247
HTMLTMPL.49 s = r :(HTMLTMPL.50)
-LINE 249
HTMLTMPL.41 $n = link(tmpl_token("text","",s))
 n = .next($n)
-LINE 250
 s = ""
-LINE 252
HTMLTMPL.50  :(HTMLTMPL.39)
-LINE 253
HTMLTMPL.40  :(RETURN)
-LINE 258
tmpl_tokenize.END  :(tmpl_parse_args.END)
-LINE 259
tmpl_parse_args tmpl_parse_args = table()
-LINE 260
HTMLTMPL.51 DIFFER(s,"") :F(HTMLTMPL.52)
-LINE 261
 n = ""
-LINE 262
 v = ""
-LINE 263
 s ? tmpl_arg_p = "" :F(HTMLTMPL.53)
-LINE 264
 n = replace(n,&ucase,&lcase)
-LINE 265
 n = ident(n) "name"
-LINE 266
 tmpl_parse_args<n> = v :(HTMLTMPL.54)
-LINE 268
HTMLTMPL.53  :(FRETURN)
-LINE 269
HTMLTMPL.54  :(HTMLTMPL.51)
-LINE 270
HTMLTMPL.52  :(RETURN)
tmpl_parse_args.END 
-LINE 279 "HTMLTMPL.lss" 
HTMLTMPL.1 
 DATA('tmpl_token(token_type,token_end,token_args)')
-include 'LINK.INC' 
-include 'CHARS.INC' 
-include 'LAST.INC' 
-include 'REVL.INC' 
-include 'SWAP.INC' 
-include 'READFILE.INC' 
-include 'HTMLESC.INC' 
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
