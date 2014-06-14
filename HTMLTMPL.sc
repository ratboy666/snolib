-MODULE HTMLTMPL
-SNOCONE
-LINE 28 "HTMLTMPL.lss"
//-INCLUDE 'CHARS.INC'
//-INCLUDE 'LAST.INC'
//-INCLUDE 'LINK.INC'
//-INCLUDE 'READFILE.INC'
//-INCLUDE 'REVL.INC'
//-INCLUDE 'SWAP.INC'
//-INCLUDE 'TIMER.INC'
-LINE 293 "HTMLTMPL.lss"
-IN1024
-LINE 72 "HTMLTMPL.lss"

# A compiled template is a list of template tokens

struct tmpl_token { token_type, token_end, token_args }


//-USES HTML_ESCAPE(), JS_ESCAPE(), URL_ESCAPE()

# Initialize patterns for HTML template module

//-PUBLIC TMPL_INIT()
procedure tmpl_init() {

   # Directory for template includes

   tmpl_dir = "./"

   # Patterns to break template into tokens

   tmpl_ws = span(" " && chars_tab) | ""
   tmpl = ("/" | "") . h &&
          any("Tt") && any("Mm") && any("Pp") && any("Ll") && "_"
   tmpl_tag = tmpl && span(&ucase && &lcase) . tag
   tmpl_c = "<!-- " && tmpl_ws && tmpl_tag && arb . arg && " -->"
   tmpl_t = "<" && tmpl_tag && break(">") . arg && ">"
   tmpl_piece = pos(0) && breakx("<") . l && (tmpl_t | tmpl_c) . p &&
                rem . r
   tmpl_keys = "var if unless else loop include "

   # Patterns to parse arguments for template token

   tmpl_arg_var = tmpl_ws && (any(&lcase && &ucase) && span(
      &lcase && &ucase && '0123456789' && "_")) . n && tmpl_ws
   tmpl_qval = '"' && break('"') . v && '"'
   tmpl_sval = break(" " && chars_tab) . v
   tmpl_arg_p = ((tmpl_arg_var && "=") | "") && tmpl_ws &&
      (tmpl_qval | tmpl_sval | (rem . v))
}

# Compile template

//-PUBLIC TMPL_COMPILE()
procedure tmpl_compile(s) l {
   if (~(l = tmpl_tokenize(s)))
      freturn
   if (~(l = tmpl_parse(l)))
      freturn
   return l
}

# Interpret template p with arguments a. interpret_tmpl() is
# recursive, so the results are collected into tmpl_interpret.

//-PUBLIC TMPL_INTERPRET()
procedure tmpl_interpret(p, a) {
   interpret_tmpl(p, a)
}

# Default var value escape procedure

procedure none_escape(s) {
   none_escape = s
}

# Recursive interpret template

procedure interpret_tmpl(p, a) p1 p2 v n t e i {
   for (p, p :!: "", p = next(p)) {
      v = value(value(p))
      if (token_type(v) :: "text") {
# text - text from template
	 tmpl_interpret = tmpl_interpret && token_args(v)
      } else {
	 t = token_args(v)
	 n = a[t["name"]]
	 if (token_type(v) :: "var") {
# var - (name, default, escape)
	    if (n :: "")
	       n = t["default"]
	    e = t["escape"]
	    e = ident(e) "none"
	    e = e && "_escape"
	    v = &errlimit; &errlimit = 1; n = apply(e, n); &errlimit = v
	    tmpl_interpret = tmpl_interpret && n
	 } else if ("if unless" ? token_type(v)) {
# if/unless - (name) else
	    p1 = value(next(value(p)))
	    p2 = next(next(value(p)))
	    if (token_type(v) :: "unless")
	       swap(.p1, .p2)
	    if ((n :!: "") || ne(+n, 0))
	       interpret_tmpl(p1, a)
	    else
	       interpret_tmpl(p2, a)
	 } else if (token_type(v) :: "loop") {
# loop - (name)
	    if (datatype(n) :: "ARRAY") {
	       p1 = value(next(value(p)))
	       for (i = 1, n[i], i = i + 1)
		  interpret_tmpl(p1, n[i]);
	    }
	 }
      }
   }
}

# Parse the template, given token list. Separate from tmpl_seq() because
# we want to ensure that all tokens are consumed.

procedure tmpl_parse(l) r {
   if (l :: "")
      return
   if (~(r = tmpl_seq()))
      freturn
   if (l :!: "")
      freturn
   return r
}

# Parse a sequence of tokens from tmpl_tokenize(), into a list
# structure that can be passed to tmpl_interpret()

procedure tmpl_seq() r v v2 p1 p2 {
   while (l :!: "") {
      v = value(l)
      if ("text var" ? token_type(v)) {
	 r = link(link(v), r)
	 l = next(l)
      } else if ("if unless loop" ? token_type(v)) {
	 if (token_end(v) :!: "")
	    return revl(r)
	 l = next(l)
	 if (~(p1 = tmpl_seq()))
	    freturn
	 if (l :: "")
	    freturn
	 p2 = ""
	 v2 = value(l)
	 if ("if unless loop" ? token_type(v2)) {
	    l = next(l)
	 } else if (token_type(v2) :: "else") {
	    l = next(l)
	    if (~(p2 = tmpl_seq()))
	       freturn
	    if (l :: "")
	       freturn
	    l = next(l)
	 } else
	    freturn
	 r = link(link(v, link(p1, p2)), r)
      } else if (token_type(v) :: "else") {
	 return revl(r)
      } else
	 freturn
   }
   return revl(r)
}

# Tokenize the string into a list of tokens

procedure tmpl_tokenize(s) l r p tag r h n t {
   n = .tmpl_tokenize
   while (s :!: "") {
      if (s ? tmpl_piece) {
	 tag = replace(tag, &ucase, &lcase)
	 if (tmpl_keys ? (tag && " ")) {
	    if (l :!: "") {
	       $n = link(tmpl_token("text", "", l)); n = .next($n)
	    }
	    if (tag :: "include") {
               # include tags - read the named file from the tmpl_dir
               # directory, tokenize it and graft the new token list to
               # the list we are building. Walk to the end of the new
               # list with last()
	       if (~(t = tmpl_parse_args(arg)))
		  freturn
	       if (s = readfile(tmpl_dir && t['name'])) {
		  if (~($n = tmpl_tokenize(s)))
		     freturn
		  n = .last(tmpl_tokenize)
	       }
	    } else {
	       t = tmpl_token(tag, h, tmpl_parse_args(arg))
	       $n = link(t); n = .next($n)
	    }
	 } else {
	    $n = link(tmpl_token("text", "", l && p)); n = .next($n)
	 }
	 s = r
      } else {
	 $n = link(tmpl_token("text", "", s)); n = .next($n)
	 s = ""
      }
   }
}

# Parse the arguments for the token. Any arguments are possible,
# only name= default= and escape= will matter.

procedure tmpl_parse_args(s) n v {
   tmpl_parse_args = table()
   while (s :!: "") {
      n = ""
      v = ""
      if ((s ? tmpl_arg_p) = "") {
	 n = replace(n, &ucase, &lcase)
	 n = ident(n) && "name"
	 tmpl_parse_args[n] = v
      } else
	 freturn
   }
   return
}

// tmpl_init()

# ce: .f.msnocone;
