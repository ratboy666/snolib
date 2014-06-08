# Makefile
#
# SNOLIB

# Binary (executables), library (includes) and CGI directories

BINDIR=/usr/local/bin
LIBDIR=/usr/local/snolib
CGIDIR=/var/www/cgi-bin
HTMLDIR=/var/www/html
#SODIR=/usr/local/lib

# Unit tests
#
# Note unit_tests script -- should be driven from $(T) instead,
# with results gathered (performance, and module failure).

T = AGT.tst      AI.tst       AOPA.tst     BALREV.tst   BALX.tst     \
    BLEND.tst    BQ.tst       CATA.tst     CHARS.tst    CH.tst       \
    COMB.tst     COPYL.tst    COUNT.tst    CRACK.tst    CSNOBOL4.tst \
    CVAR.tst     DAY.tst      DDT.tst      DDTCARD.tst  DEXP.tst     \
    DISPLAY.tst  DYNAMIC.tst  ENDCARD.tst  FASTBAL.tst  FENCE.tst    \
    FFI.tst      FIND.tst     FLOOR.tst    GETKEY.tst   GOTOS.tst    \
    HEX.tst      HOST.tst     INFINIP.tst  JIT.tst      LAST.tst     \
    LIKE.tst     LOG.tst      LOGIC.tst    LPROG.tst    MDY.tst      \
    NDBM.tst     NOTP.tst     ONCE.tst     ORDER.tst    P64.tst      \
    QUOTE.tst    RANDOM.tst   READLINE.tst REDEFINE.tst SIZEA.tst    \
    REPL.tst     RESOL.tst    REVL.tst     ROMAN.tst    ROTATER.tst  \
    SDIFF.tst    SEQ.tst      SKIM.tst     SLOAD.tst    SOUNDEX.tst  \
    SPELL.tst    STACK.tst    STCL.tst     STROUT.tst   SWAP.tst     \
    SYSLOG.tst   SYSTEM.tst   TEST.tst     TIME.tst     TIMEGC.tst   \
    TIMER.tst    TPROFILE.tst TRUNC.tst    UNIQUE.tst   UTF8.tst     \
    WRAPPER.tst  LINK.tst     HTMLESC.tst  TRIMB.tst    PSQL.tst     \
    BRKREM.tst   HASH.tst     READL.tst    FOREACH.tst  SCOOP.tst    \
    CGI.tst      READFILE.tst SESSION.tst  GCD.tst      COMPLEX.tst  \
    COOKIE.tst   HTMLTMPL.tst JSON.tst     FCGI.tst     MAX.tst      \
    DSERVE.tst   VDIFFER.tst  FOR.tst      FREEZE.tst   ROUTING.tst  \
    GDDT.tst     DEDUPA.tst   ATOL.tst     ITERDIR.tst  SIZEL.tst    \
    SIZET.tst

# Library files FIXME: TRIAL should be removed.

L = $(addsuffix .INC, $(basename $(T)))

# Utilities

P = bundle       code         compile      deretn       deseq        \
    deseql       embed        ifs          illum        list         \
    lseq         lsinc        rseq         snofmt       stangle      \
    sweave       uban         upcase       g360         scan         \
    snocone      cpmed        ED4          bldidx       uses         \
    upinc

all: $(L) $(T) ALL.INC $(P) docs

# Library dependencies

ALL.INC:      $(L)

AI.INC:       SEQ.INC
AOPA.INC:     SEQ.INC
BALX.INC:     UNIQUE.INC
CATA.INC:     SEQ.INC
CH.INC:       HEX.INC
COPYL.INC:    LINK.INC
CRACK.INC:    COUNT.INC
CSNOBOL4.INC: FFI.INC
CVAR.INC:     P64.INC      CHARS.INC    HASH.INC
DDT.INC:      CHARS.INC    HOST.INC     READLINE.INC TRIMB.INC    \
              QUOTE.INC    VDIFFER.INC
DISPLAY.INC:  BQ.INC       CHARS.INC
DYNAMIC.INC:  BQ.INC       HOST.INC
FASTBAL.INC:  UNIQUE.INC
FENCE.INC:    UNIQUE.INC
FFI.INC:      P64.INC
FLOOR.INC:    DEXP.INC
GETKEY.INC:   BQ.INC       CHARS.INC
HEX.INC:      BLEND.INC
INFINIP.INC:  REDEFINE.INC SWAP.INC
JIT.INC:      BQ.INC       CRACK.INC    DYNAMIC.INC  P64.INC      \
              SEQ.INC      WRAPPER.INC
LAST.INC:     LINK.INC
LOG.INC:      DEXP.INC
NOTP.INC:     STACK.INC
ONCE.INC:     UNIQUE.INC
P64.INC:      CRACK.INC    DYNAMIC.INC  SEQ.INC      WRAPPER.INC
QUOTE.INC:    REPL.INC
REVL.INC:     LINK.INC
SKIM.INC:     SDIFF.INC
SLOAD.INC:    CRACK.INC    HOST.INC     TRIMB.INC
STACK.INC:    REPL.INC     LINK.INC
SYSLOG.INC:   FFI.INC      P64.INC
TEST.INC:     UNIQUE.INC
TIMEGC.INC:   RESOL.INC    SYSTEM.INC   LINK.INC
TIMER.INC:    RESOL.INC    SYSTEM.INC
TPROFILE.INC: LPROG.INC    SEQ.INC
TRUNC.INC:    SEQ.INC
HTMLESC.INC:  REPL.INC     SDIFF.INC    HEX.INC      CHARS.INC
BRKREM.INC:   SDIFF.INC
PSQL.INC:     REPL.INC     COUNT.INC    CHARS.INC    SEQ.INC      \
              BRKREM.INC   SCOOP.INC
HASH.INC:     BRKREM.INC
READL.INC:    LINK.INC
SCOOP.INC:    VDIFFER.INC  FREEZE.INC
CGI.INC:      SCOOP.INC    COOKIE.INC   HOST.INC     CRACK.INC    \
              SEQ.INC      HTMLESC.INC  TRIMB.INC    CHARS.INC    \
              HASH.INC     UNIQUE.INC   JSON.INC
SESSION.INC:  BQ.INC       NDBM.INC     SEQ.INC      CRACK.INC    \
              HASH.INC     TIME.INC
COOKIE.INC:   HASH.INC     TIME.INC     DEXP.INC     CHARS.INC
HTMLTMPL.INC: LINK.INC     CHARS.INC    LAST.INC     REVL.INC     \
              SWAP.INC     READFILE.INC HTMLESC.INC
JSON.INC:     CHARS.INC    HASH.INC     SIZEA.INC    HEX.INC      \
              CH.INC       SEQ.INC
SIZEA.INC:    BRKREM.INC   SWAP.INC
UNIQUE.INC:   REPL.INC
FCGI.INC:     FFI.INC      P64.INC      BQ.INC       CSNOBOL4.INC \
              LOGIC.INC    HASH.INC     SEQ.INC      TIME.INC     \
              JSON.INC
DSERVE.INC:   CHARS.INC    REPL.INC     CSNOBOL4.INC HOST.INC     \
              MAX.INC      DDT.INC
VDIFFER.INC:  SYSTEM.INC
FREEZE.INC:   SYSTEM.INC
READFILE.INC: SYSTEM.INC   CHARS.INC    BRKREM.INC
ROUTING.INC:  SDIFF.INC    UNIQUE.INC   BRKREM.INC
GDDT.INC:     STCL.INC     REPL.INC     CHARS.INC    DDT.INC
DEDUPA.INC:   HASH.INC     SIZEA.INC    SEQ.INC
ATOL.INC:     LINK.INC     SEQ.INC      REVL.INC
ITERDIR.INC:  BQ.INC       CRACK.INC    ATOL.INC     CHARS.INC
SIZEL.INC:    LINK.INC
SIZET.INC:    HASH.INC     SIZEA.INC

# Bootstrapping. We need embed, ifs, sweave, stangle, snocone and ED4
# to build the code. We keep embed0, ifs0, sweave0 and stangle0 for
# bootstrapping.  After the library is built, the bootstrap utilities
# can be generated from the most recent using the bundle utility.
#
# make clean
# make realclean
# make bootstrap
# make deliver
# make embed0
# make ifs0
# make sweave0

embed0: bundle embed
	./bundle <embed >embed0
	chmod +x embed0

ifs0: bundle ifs
	./bundle <ifs >ifs0
	chmod +x ifs0

sweave0: bundle sweave
	./bundle <sweave >sweave0
	chmod +x sweave0

stangle0: bundle stangle
	./bundle <stangle >stangle0
	chmod +x stangle0

snocone0: bundle snocone
	./bundle <snocone >snocone0
	chmod +x snocone0

bootstrap:
	sudo cp embed0 $(BINDIR)/embed
	sudo cp ifs0 $(BINDIR)/ifs
	sudo cp stangle0 $(BINDIR)/stangle
	sudo cp sweave0 $(BINDIR)/sweave
	sudo cp snocone0 $(BINDIR)/snocone
	sudo cp ED4 $(BINDIR)/ED4
	sudo cp g360 $(BINDIR)/g360

# Utilities

code:         code.SNO     BQ.INC       CHARS.INC    HOST.INC     \
                           READLINE.INC SEQ.INC      SLOAD.INC
deretn:       deretn.SNO
deseq:        deseq.SNO
deseql:       deseql.SNO
embed:        embed.SNO    CHARS.INC    SLOAD.INC
ifs:          ifs.SNO      CHARS.INC    CRACK.INC    HOST.INC     \
                           FASTBAL.INC  SYSTEM.INC   VDIFFER.INC
illum:        illum.SNO    BQ.INC       CRACK.INC    SEQ.INC      \
                           TRIMB.INC
lseq:         lseq.SNO
lsinc:        lsinc.SNO    SEQ.INC      SLOAD.INC    TRIMB.INC
rseq:         rseq.SNO
snofmt:       snofmt.SNO   CHARS.INC
uban:         uban.SNO     CRACK.INC    SEQ.INC      STROUT.INC   \
                           TRIMB.INC
upcase:       upcase.SNO
compile:      compile.SNO  CRACK.INC    TRIMB.INC
bundle:       bundle.SNO   CRACK.INC    TRIMB.INC
list:         list.SNO     CHARS.INC    DISPLAY.INC  GETKEY.INC   \
                           HOST.INC     LOGIC.INC    BQ.INC       \
                           READLINE.INC
cgi:          cgi.SNO      BQ.INC       CHARS.INC    CRACK.INC    \
                           SEQ.INC
scan:         scan.SNO     HOST.INC
bldidx:       CHARS.INC    BQ.INC       CRACK.INC    JSON.INC     \
              SEQ.INC      VDIFFER.INC
uses:         HASH.INC     JSON.INC     READFILE.INC SDIFF.INC
upinc:        HOST.INC     READFILE.INC BQ.INC       JSON.INC     \
              CHARS.INC    SEQ.INC      REPL.INC


# Doesn't clean *.so for now

clean:
	-rm  p64.h *.o *.bak *.lst *.SNO *.html *.INC *.tst
	-rm -fr null/ images
	-rm COBDUMPTEST COBDUMP.so

deliver: $(P)
	sudo cp $(P) $(BINDIR)/
	#sudo cp *.so $(SODIR)/
	sudo cp *.so $(LIBDIR)/
	sudo rm -f $(BINDIR)/ED $(BINDIR)/EDIT
	sudo rm -f $(BINDIR)/LIST
	sudo rm -f $(LIBDIR)/ENDCARD
	sudo rm -f $(LIBDIR)/DDTCARD
	sudo ln $(BINDIR)/cpmed $(BINDIR)/ED
	sudo ln $(BINDIR)/cpmed $(BINDIR)/EDIT
	sudo ln $(BINDIR)/list $(BINDIR)/LIST
	sudo cp $(L) $(LIBDIR)/
	sudo chmod +r $(LIBDIR)/*.INC $(LIBDIR)/*.so
	sudo chmod +x $(LIBDIR)/*.so
	sudo ln -s $(LIBDIR)/ENDCARD.INC $(LIBDIR)/ENDCARD
	sudo ln -s $(LIBDIR)/DDTCARD.INC $(LIBDIR)/DDTCARD
	sudo cp CGI.tst $(CGIDIR)/cgi.cgi
	sudo cp CGI.tst $(CGIDIR)/cgi.fcgi
	sudo cp CGI.tmpl $(CGIDIR)
	sudo cp jquery-1.11.1.js $(HTMLDIR)
	sudo chown apache:apache $(CGIDIR)/cgi.cgi \
				 $(CGIDIR)/cgi.fcgi \
	                         $(CGIDIR)/CGI.tmpl \
	                         $(HTMLDIR)/jquery-1.11.1.js

# Testing

COBDUMPTEST: COBDUMPTEST.CBL COBDUMP.so

COBDUMP.so: COBDUMP.CBL

test_all.lst: test_all ALL.INC $(L) COBDUMP.so COO.CBL SNOO.FTN \
                                    test_gambit.scm

jit_test.lst: P64.INC FFI.INC JIT.INC LOGIC.INC DDT.INC

test: test_all.lst jit_test.lst

# Snocone needs The pattern stack size specified. Use ED4 to edit
# snocone.

snocone: sc ED4
	cp sc snocone
	echo  >E '$$F' "'\"-b\"'"
	echo >>E '$$R' "'\"-b\"' = '\"-b\" \"-P100k\"'"
	echo >>E '$$X'
	ED4 snocone <E
	rm E

cpmed: cpmed.c
	cc -Os -DLINUX -o cpmed cpmed.c
	strip cpmed

docs:         AGT.html      AI.html       ALL.html      AOPA.html     \
              BALREV.html   BALX.html     BLEND.html    BQ.html       \
              bundle.html   CATA.html     CHARS.html    CH.html       \
              code.html     COMB.html     compile.html  COPYL.html    \
              COUNT.html    CRACK.html    CSNOBOL4.html CVAR.html     \
              DAY.html      DDTCARD.html  DDT.html      deretn.html   \
              deseql.html   deseq.html    DEXP.html     DISPLAY.html  \
              DYNAMIC.html  embed.html    ENDCARD.html  FASTBAL.html  \
              FENCE.html    FFI.html      FIND.html     FLOOR.html    \
              GETKEY.html   GOTOS.html    HEX.html      HOST.html     \
              ifs.html      illum.html    INFINIP.html  JIT.html      \
              LAST.html     LIKE.html     LOGIC.html    LOG.html      \
              LPROG.html    lseq.html     list.html     lsinc.html    \
              MDY.html      NDBM.html     NOTP.html     ONCE.html     \
              ORDER.html    P64.html      SIZEA.html    QUOTE.html    \
              RANDOM.html   READLINE.html REDEFINE.html REPL.html     \
              RESOL.html    REVL.html     ROMAN.html    ROTATER.html  \
              rseq.html     SDIFF.html    SEQ.html      SKIM.html     \
              SLOAD.html    snofmt.html   SOUNDEX.html  SPELL.html    \
              STACK.html    STCL.html     STROUT.html   SWAP.html     \
              SYSLOG.html   SYSTEM.html   TEST.html     TIMEGC.html   \
              TIME.html     TIMER.html    TPROFILE.html TRUNC.html    \
              uban.html     UNIQUE.html   upcase.html   UTF8.html     \
              WRAPPER.html  LINK.html     HTMLESC.html  TRIMB.html    \
              PSQL.html     BRKREM.html   HASH.html     MAX.html      \
              READL.html    scan.html     FOREACH.html  SCOOP.html    \
              CGI.html      READFILE.html SESSION.html  GCD.html      \
              COMPLEX.html  COOKIE.html   HTMLTMPL.html JSON.html     \
              stangle       sweave        greenbar.gif  index.html    \
              utility.html  snocone.html  cpmed.html    ED4           \
              FCGI.html     DSERVE.html   VDIFFER.html  FOR.html      \
              FREEZE.html   ROUTING.html
	touch docs

snocone.html: snocone.htm
	cp snocone.htm snocone.html

cpmed.html: cpmed.htm
	cp cpmed.htm cpmed.html

index.html: index workflow library favicon.jpg
	IFSLC=@ ifs index >index.ditaa
	cp index.ditaa index.html
	ditaa index.ditaa index.html --html --overwrite >/dev/null

utility.html: utility
	IFSLC=@ ifs utility >utility.ditaa
	cp utility.ditaa utility.html
	ditaa utility.ditaa utility.html --html --overwrite >/dev/null

# Help make find the right way to construct files

ALL.INC: ALL.SNO
AGT.INC: AGT.SNO
AI.INC: AI.SNO
AOPA.INC: AOPA.SNO
BALREV.INC: BALREV.SNO
BALX.INC: BALX.SNO
BLEND.INC: BLEND.SNO
BQ.INC: BQ.SNO
CATA.INC: CATA.SNO
CHARS.INC: CHARS.SNO
CH.INC: CH.SNO
COMB.INC: COMB.SNO
COPYL.INC: COPYL.SNO
COUNT.INC: COUNT.SNO
CRACK.INC: CRACK.SNO
CSNOBOL4.INC: CSNOBOL4.SNO
CVAR.INC: CVAR.SNO
DAY.INC: DAY.SNO
DDT.INC: DDT.SNO
DDTCARD.INC: DDTCARD.SNO
DEXP.INC: DEXP.SNO
DISPLAY.INC: DISPLAY.SNO
DYNAMIC.INC: DYNAMIC.SNO
ENDCARD.INC: ENDCARD.SNO
FASTBAL.INC: FASTBAL.SNO
FENCE.INC: FENCE.SNO
FFI.INC: FFI.SNO
FIND.INC: FIND.SNO
FLOOR.INC: FLOOR.SNO
GETKEY.INC: GETKEY.SNO
GOTOS.INC: GOTOS.SNO
HEX.INC: HEX.SNO
HOST.INC: HOST.SNO
INFINIP.INC: INFINIP.SNO
JIT.INC: JIT.SNO
LAST.INC: LAST.SNO
LIKE.INC: LIKE.SNO
LOG.INC: LOG.SNO
LOGIC.INC: LOGIC.SNO
LPROG.INC: LPROG.SNO
MDY.INC: MDY.SNO
NDBM.INC: NDBM.SNO
NOTP.INC: NOTP.SNO
ONCE.INC: ONCE.SNO
ORDER.INC: ORDER.SNO
P64.INC: P64.SNO
QUOTE.INC: QUOTE.SNO
RANDOM.INC: RANDOM.SNO
READLINE.INC: READLINE.SNO
REDEFINE.INC: REDEFINE.SNO
REPL.INC: REPL.SNO
RESOL.INC: RESOL.SNO
REVL.INC: REVL.SNO
ROMAN.INC: ROMAN.SNO
ROTATER.INC: ROTATER.SNO
SDIFF.INC: SDIFF.SNO
SEQ.INC: SEQ.SNO
SKIM.INC: SKIM.SNO
SLOAD.INC: SLOAD.SNO
SOUNDEX.INC: SOUNDEX.SNO
SPELL.INC: SPELL.SNO
STACK.INC: STACK.SNO
STCL.INC: STCL.SNO
STROUT.INC: STROUT.SNO
SWAP.INC: SWAP.SNO
SYSLOG.INC: SYSLOG.SNO
SYSTEM.INC: SYSTEM.SNO
TEST.INC: TEST.SNO
TIME.INC: TIME.SNO
TIMEGC.INC: TIMEGC.SNO
TIMER.INC: TIMER.SNO
TPROFILE.INC: TPROFILE.SNO
TRUNC.INC: TRUNC.SNO
UNIQUE.INC: UNIQUE.SNO
UTF8.INC: UTF8.SNO
WRAPPER.INC: WRAPPER.SNO
LINK.INC: LINK.SNO
HTMLESC.INC: HTMLESC.SNO
TRIMB.INC: TRIMB.SNO
PSQL.INC: PSQL.SNO
BRKREM.INC: BRKREM.SNO
HASH.INC: HASH.SNO
READL.INC: READL.SNO
FOREACH.INC: FOREACH.sc
SCOOP.INC: SCOOP.SNO
CGI.INC: CGI.SNO
READFILE.INC: READFILE.SNO
SESSION.INC: SESSION.SNO
GCD.INC: GCD.SNO
COMPLEX.INC: COMPLEX.SNO
COOKIE.INC: COOKIE.SNO
HTMLTMPL.INC: HTMLTMPL.sc
JSON.INC: JSON.SNO
SIZEA.INC: SIZEA.SNO
FCGI.INC: FCGI.SNO
MAX.INC: MAX.SNO
DSERVE.INC: DSERVE.SNO
VDIFFER.INC: VDIFFER.SNO
FOR.INC: FOR.SNO
FREEZE.INC: FREEZE.SNO
ROUTING.INC: ROUTING.SNO
DEDUPA.INC: DEDUPA.SNO
ATOL.INC: ATOL.SNO
ITERDIR.INC: ITERDIR.SNO
SIZEL.INC: SIZEL.SNO
SIZET.INC: SIZET.SNO
