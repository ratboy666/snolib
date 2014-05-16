########################################################################
#                                                                      #
# std.mak                                                              #
#                                                                      #
# Rules for FORTRAN, COBOL, SCHEME, PASCAL, RATFOR, ASSEMBLER, APL     #
# Rules to make scripts executable (SNOBOL4, BASIC, AWK, etc.)         #
#                                                                      #
# make -r to not use built-in rules, and just the rules in this file.  #
#                                                                      #
########################################################################

# $Id$

.SUFFIXES:
.SUFFIXES: .o .so
.SUFFIXES: .c .h .y .l
.SUFFIXES: .f .r .fi .FOR .FTN
.SUFFIXES: .p
.SUFFIXES: .asm .inc .ASM .INC
.SUFFIXES: .cob .cpy .cbl .COB .CPY .CBL
.SUFFIXES: .scm .six .o1 .lss
.SUFFIXES: .tst .sc .sno .SNO .bas .BAS .apl
.SUFFIXES: .awk .bc .dc .pl .rexx .sed .tcl
.SUFFIXES: .html .ditaa .sql .sable
.SUFFIXES: .txt

# NOTE: sable files are not yet done. need to build festival
# script, and interpolate shell within that

# Libraries

LEX_LIB=-ll
YACC_LIB=-ly
FORTRAN_LIB=-lgfortran
COBOL_LIB=`cob-config --libs`
PASCAL_LIB=-lp2c
SCHEME_LIB=-lgambc -ldl -lm -lutil
APL_LIB=-L/usr/local/lib -laplc -lreadline -lncurses -lm

CC=gcc
FC=gfortran
AS=nasm

PC=p2cc
COBC=cobc
SC=gsc
APLC=aplcc

YACC=bison -y
LEX=flex
RATFOR=ratfor

CO=co
TANGLE=stangle
WEAVE=sweave
IFS=ifs
EMBED=embed
DITAA=ditaa
SNOCONE=snocone
G360=g360

P2C_HOME=/usr/local/p2c
P2CC_CC=$(CC)

#FCFLAGS=-std=legacy -fdollar-ok -mfpmath=sse -msse2 -fno-align-commons
#        -fimplicit-none -fbounds-check
#
# -Wall -Warray-temporaries -Wcharacter-truncation -Wunderflow
#  -O3 -ffpe-trap=invalid,zero,overflow

# FIXME: Need rules for archive?

%:: %,v
	$(CO) $(COFLAGS) $@

%:: RCS/%,v
	$(CO) $(COFLAGS) $@

%:: RCS/%
	$(CO) $(COFLAGS) $@

.y.c:
	$(YACC) $(YFLAGS) $<
	mv -f y.tab.c $*.c

.l.c:
	$(LEX) $(LFLAGS) -o $@ $<

.r.f:
	$(RATFOR) $(RFLAGS) -o $@ $<

.o:
	$(CC) $(LDFLAGS) -o $@ $< $(LOADLIBES) $(LDLIBS)

.p.o:
	$(PC) $(PFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

.FTN:
	$(FC) $(FFLAGS) -o $@ $<

.FOR:
	$(FC) $(FFLAGS) -o $@ $<

.f:
	$(FC) $(FFLAGS) -o $@ $<

.FTN.o:
	$(FC) -c $(FFLAGS)  -o $@ $<

.FOR.o:
	$(FC) -c $(FFLAGS)  -o $@ $<

.f.o:
	$(FC) -c $(FFLAGS)  -o $@ $<

.asm.o:
	$(AS) -f elf64 -o $@ $<

.ASM.o:
	$(AS) -f elf64 -o $@ $<

# Compile SCHEME with Gambit-C
#
# gsc -c xx.scm
# gsc -link -flat -o foo.o1.c m2 m3
# gsc  -cc-options "-D___DYNAMIC" -obj xxx.c foo.o1.c
# gsc -shared xxx.o foo.o1.o -o foo.o1
# gsi foo.o1
#
# gsc -link -o mylib.c m2
# gsc -obj -cc-options "-D___SHARED" m1.c m2.c mylib.c
# gcc -shared m1.o m2.o mylib.o -o mylib.so
# ----  "-D___SINGLE_HOST" "-O"
#  "-fpic -fPIC"
#  -D___LIBRARY to supress main()

.scm.o1:
	$(SC) $(SFLAGS) -o $@ $<

.six.o1:
	$(SC) $(SFLAGS) -o $@ $<

.scm:
	$(SC) $(SFLAGS) -exe -o $@ $<

.six:
	$(SC) $(SFLAGS) -exe -o $@ $<

.scm.c:
	$(SC) $(SFLAGS) -c $<

.six.c:
	$(SC) $(SFLAGS) -c $<

.apl:
	$(APLC) $(AFLAGS) -o $@ $<
	rm -f $*.c $*.o

.apl.c:
	$(APLC) $(AFLAGS) -a -o $@ $<

.CBL.o:
	$(COBC) -C $(COBFLAGS) $<
	$(CC) `cob-config --cflags` -pipe -c -fPIC -DPIC -O \
	  -finline-functions -fno-gcse -freorder-blocks   \
	  -Wno-unused -fsigned-char -Wno-pointer-sign -o $@ $*.c
	rm -f $*.c $*.c.h $*.c.l.h

.cbl.o:
	$(COBC) -C $(COBFLAGS) $<
	$(CC) `cob-config --cflags` -pipe -c -fPIC -DPIC -O \
	  -finline-functions -fno-gcse -freorder-blocks   \
	  -Wno-unused -fsigned-char -Wno-pointer-sign -o $@ $*.c
	rm -f $*.c $*.c.h $*.c.l.h

.COB.o:
	$(COBC) -C $(COBFLAGS) $<
	$(CC) `cob-config --cflags` -pipe -c -fPIC -DPIC -O \
	  -finline-functions -fno-gcse -freorder-blocks   \
	  -Wno-unused -fsigned-char -Wno-pointer-sign -o $@ $*.c
	rm -f $*.c $*.c.h $*.c.l.h

.cob.o:
	$(COBC) -C $(COBFLAGS) $<
	$(CC) `cob-config --cflags` -pipe -c -fPIC -DPIC -O \
	  -finline-functions -fno-gcse -freorder-blocks   \
	  -Wno-unused -fsigned-char -Wno-pointer-sign -o $@ $*.c
	rm -f $*.c $*.c.h $*.c.l.h

.COB.so:
	cobc $<
.cob.so:
	cobc $<
.CBL.so:
	cobc $<
.cbl.so:
	cobc $<

.COB:
	$(COBC) -x -O $(COBFLAGS) -o $@ $<

.cob:
	$(COBC) -x -O $(COBFLAGS) -o $@ $<

.CBL:
	$(COBC) -x -O $(COBFLAGS) -o $@ $<

.cbl:
	$(COBC) -x -O $(COBFLAGS) -o $@ $<

# Listing for SNOBOL4 programs. Old style rules cannot be used
# because the source file may not have an extension.

%.lst: %
	snobol4 -n -l $@ $<
%.lst: %.sno
	snobol4 -n -l $@ $<
%.lst: %.SNO
	snobol4 -n -l $@ $<
%.lst: %.tst
	snobol4 -n -l $@ $<

# HTML DITAA image creation. ditaa has a bug in that it puts the
# images to null/images, and directory null must exist. The html
# IMG references are to images/ though. So, we create the directory
# and a link. Also ditaa does not create the _processed file if
# there are no images. This causes issue with the workflow. If the
# _processed file does not exist, we simply copy the original
# html file to it. When the last image is removed from the source,
# the copy would not take place because the target remains. So we
# erase the target before starting. ditaa just doesn't want to play
# well in a MAKE file, it seems!
%.html: %.ditaa
	@if [ ! -d null ]; then mkdir null; fi
	@if [ ! -d null/images ]; then mkdir null/images; fi
	@if [ ! -h images ]; then ln -s null/images images; fi
	@rm -f "$@"
	$(DITAA) "$<" "$@" --html --overwrite >/dev/null
	@if [ ! -f "$@" ]; then cp "$<" "$@"; fi
	
.sc.INC:
	@echo $< " -> " $@
	@t=`mktemp /tmp/fileXXXXXXXXXX`; \
	export LABEL="$*."; \
	$(G360) < "$*.sc" | LSS=SNOBOL4 $(IFS) | $(EMBED) > $$t.sc; \
	$(SNOCONE) -m "$$t.sc"; \
	cp $$t.sno $@; \
	rm $$t.sno

# "embed" and "ifs" processing for SNOBOL4 programs. Use a temp file
# in case INC file is one needed by "embed" or "ifs" itself.

.sno.inc:
	@echo $< " -> " $@
	@t=`mktemp`; \
	$(G360) < $< | LSS=SNOBOL4 $(IFS) | $(EMBED) > $$t; \
	cp $$t $@; \
	rm $$t
.SNO.INC:
	@echo $< " -> " $@
	@t=`mktemp`; \
	$(G360) < $< | LSS=SNOBOL4 $(IFS) | $(EMBED) > $$t; \
	cp $$t $@; \
	rm $$t

# Literate programming

.lss.scm:
	$(TANGLE) <"$<" >"$@"

.lss.ditaa:
	@echo $< ' -> ' $@
	@IFSLC=@ $(IFS) "$<" | $(WEAVE) >"$@"

.lss.l:
	$(TANGLE) <"$<" >"$@"

.lss.y:
	$(TANGLE) <"$<" >"$@"

.lss.apl:
	$(TANGLE) <"$<" >"$@"

.lss.six:
	$(TANGLE) <"$<" >"$@"

.lss.p:
	$(TANGLE) <"$<" >"$@"

.lss.r:
	$(TANGLE) <"$<" >"$@"

.lss.COB:
	$(TANGLE) <"$<" >"$@"

.lss.cob:
	$(TANGLE) <"$<" >"$@"

.lss.CBL:
	$(TANGLE) <"$<" >"$@"

.lss.cbl:
	$(TANGLE) <"$<" >"$@"

.lss.CPY:
	$(TANGLE) <"$<" >"$@"

.lss.cpy:
	$(TANGLE) <"$<" >"$@"

.lss.BAS:
	$(TANGLE) <"$<" >"$@"

.lss.bas:
	$(TANGLE) <"$<" >"$@"

.lss.FOR:
	$(TANGLE) <"$<" >"$@"

.lss.FTN:
	$(TANGLE) <"$<" >"$@"

.lss.f:
	$(TANGLE) <"$<" >"$@"

.lss.fi:
	$(TANGLE) <"$<" >"$@"

.lss.ASM:
	IFSLC=@ LSS=ASM $(IFS) "$<" | LSS=ASM $(TANGLE) >"$@"

.lss.asm:
	IFSLC=@ LSS=ASM $(IFS) "$<" | LSS=ASM $(TANGLE) >"$@"

.lss.inc:
	$(TANGLE) <"$<" >"$@"

.lss.awk:
	$(TANGLE) <"$<" >"$@"

.lss.bc:
	$(TANGLE) <"$<" >"$@"

.lss.dc:
	$(TANGLE) <"$<" >"$@"

.lss.pl:
	$(TANGLE) <"$<" >"$@"

.lss.rexx:
	$(TANGLE) <"$<" >"$@"

.lss.sed:
	$(TANGLE) <"$<" >"$@"

.lss.c:
	IFSLC=@ LSS=C $(IFS) "$<" | LSS=C $(TANGLE) >"$@"

# To convert lss to sc we should track line references in snocone
# As it is, we do not... Also, -INCLUDE should be passed though.

.lss.sc:
	@echo $< " -> " $@
	@IFSLC=@ LSS=SNOBOL4 $(IFS) "$<" | LSS=SNOBOL4 $(TANGLE) >"$@"

.lss.SNO:
	@echo $< " -> " $@
	@IFSLC=@ LSS=SNOBOL4 $(IFS) "$<" | LSS=SNOBOL4 $(TANGLE) >"$@"

.lss.sno:
	@echo $< " -> " $@
	@IFSLC=@ LSS=SNOBOL4 $(IFS) "$<" | LSS=SNOBOL4 $(TANGLE) >"$@"

.sc.sno:
	@echo $< " -> " $@
	$(SNOCONE) "$<"

.lss.tst:
	@echo $< " -> " $@
	@LSS=SNOBOL4 IFSLC=@               $(IFS) "$<" |    \
	LSS=SNOBOL4 STANGLE_ROOT=unit_test $(TANGLE)   |    \
	LSS=SNOBOL4                        $(IFS)      |    \
	                                   $(EMBED) > "$@"; \
	                                   chmod +x "$@"

.lss.tcl:
	$(TANGLE) <"$<" >"$@"

.lss.sql:
	$(TANGLE) <"$<" >"$@"

.lss.h:
	IFSLC=@ LSS=C $(IFS) "$<" | LSS=C $(TANGLE) >"$@"

# These rules convert script files into executables
#
# Copy to a file without an extension, adding the appropriate
# shebang line, if it isn't already present. Make sure the
# resulting file is executable

.sh:
	rm -f $@
	grep -q "^#!" $< || echo "#!/bin/bash" >$@
	cat $< >>$@ 
	chmod a+x $@

# When a text file is made executable, it pipes it's contents
# through less. Quote all $.

.txt:
	rm -f $@
	echo "#!/bin/bash" >$@
	echo "less <<_END" >>$@
	cat $< | sed -e 's/\$$/\\$$/g' >>$@
	echo "_END" >>$@
	chmod a+x $@

# Convert html to executable -- use firefox
# (could use lynx, links or w3m)

##.html:
##	rm -f $@
##	echo "#!/bin/bash" >$@
##	echo 't=`mktemp --suffix=.html`' >>$@
##	echo 'cat >$$t <<_END' >>$@
##	cat $< >>$@
##	echo '_END' >>$@
##	#echo 'lynx file:///$$t' >>$@
##	#echo 'rm $$t' >>$@
##	echo 'exo-open --launch WebBrowser file:///$$t' >>$@
##	chmod a+x $@

.bc:
	rm -f $@
	grep -q "^#!" $< || echo "#!/usr/bin/bc -ql" >$@
	cat $< >>$@ 
	chmod a+x $@

.dc:
	rm -f $@
	grep -q "^#!" $< || echo "#!/usr/bin/dc" >$@
	cat $< >>$@ 
	chmod a+x $@

.pl:
	rm -f $@
	grep -q "^#!" $< || echo "#!/usr/bin/perl" >$@
	cat $< >>$@ 
	chmod a+x $@

.sed:
	rm -f $@
	grep -q "^#!" $< || echo "#!/usr/bin/sed -f" >$@
	cat $< >>$@ 
	chmod a+x $@

.tcl:
	rm -f $@
	grep -q "^#!" $< || echo "#!/usr/bin/tclsh" >$@
	cat $< >>$@ 
	chmod a+x $@

.awk:
	rm -f $@
	grep -q "^#!" $< || echo "#!/usr/bin/awk -f" >$@
	cat $< >>$@ 
	chmod a+x $@

.rexx:
	rm -f $@
	grep -q "^#!" $< || echo "#!/usr/bin/regina" >$@
	cat $< >>$@ 
	chmod a+x $@

.SNO:
	rm -f $@
	grep -q "^#!" $< || ( \
	  echo "#!/usr/bin/bash" >$@; \
	  echo "         exec" \"snobol4\" \"-b\" \"$$\0\" \"$$\@\" >>$@; \
	  echo "" >>$@ \
	)
	$(IFS) < $< | $(EMBED) >> $@
	chmod a+x $@

.sno:
	rm -f $@
	grep -q "^#!" $< || ( \
	  echo "#!/usr/bin/bash" >$@; \
	  echo "         exec" \"snobol4\" \"-b\" \"$$\0\" \"$$\@\" >>$@; \
	  echo "" >>$@ \
	)
	ifs < $< | embed >> $@
	chmod a+x $@

.BAS:
	rm -f $@
	grep -q "^#!" $< || echo "#!/usr/bin/bas" >$@
	cat $< >>$@ 
	chmod a+x $@

.bas:
	rm -f $@
	grep -q "^#!" $< || echo "#!/usr/bin/bas" >$@
	cat $< >>$@ 
	chmod a+x $@

.sql:
	rm -f $@
	echo "#!/bin/bash" >$@
	echo "psql <<_END" >>$@
	cat $< >>$@
	echo "_END" >>$@
	chmod a+x $@

# ce: .mmake;
