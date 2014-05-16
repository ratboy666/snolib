snolib
======

SNOBOL4 Library

This is Fred Weigel's SNOBOL4 library. The SNOBOL4 community is very
small these days, but, heck, I still like the language, and I am sure
that others will too.

You will require Phil's CSNOBOL4 1.5. Preferably build from source!
(with NDBM)

I configure it as:
./configure --with-tcl=/usr/lib64/tclConfig.sh

You will require a C compiler -- I use GCC

Makefile:

Edit the Makefile and modify the DIR directories. CGI uses apache

BINDIR=/usr/local/bin                                                           
LIBDIR=/usr/local/snolib                                                        CGIDIR=/var/www/cgi-bin                                                |

CGI.lss should be edited to reference the correct LIBDIR as well.

Extra libraries needed:

I use Fedora 20 linux. Known to work on previous versions (17, 18, 19)
as well. On versions 17 and earlier, you will have to build GNU
Lightning version 2 yourself.

libffi-devel - foreign function interface
gdbm-devel
ditaa - ascii diagrams
lightning - GNU Lightning version 2

To get ditaa to work, I had to edit /usr/bin/ditaa and add
jericho-html to the BASE_JARS

Minor updates to CSNOBOL4 1.5: Needed for PSQL and "compile"
	fork.c
	init.c
	io.c
	main.c

Carefully review Makefile -- especially sudo lines (in deliver).

File .boxes is for the boxes utility to produce comment boxes
for SNOBOL4.

File std.mak is the default Makefile rules I use:

export MAKEFILES=std.mak

Where you use the path to std.mak

Building:

First step, create BINDIR, LIBDIR, and CGIDIR (if needed). Add
LIBDIR to your SNOPATH. BINDIR should be on your PATH. ditaa
should be on your PATH, and runnable (see comment about ditaa
above). C compiler and "make" should be on your PATH and functional.

Second step, bootstrap needed utilities:

	cd snolib
	make bootstrap

This will put embed, ifs, stangle, sweave, snocone, ED4 and g360
utilities into the BINDIR directory.

Third step, build INC files and documentation

Fourth step. Now the long part. This is where the action is!

	cd snolib
	make

The lss files are tangled and woven, ditaa called on for graphics,
embed to tease out internal files, the C compiler will be called, etc.

This should run to completion in 1 to 3 minutes. Review the output
for any errors.

Step five. Deliver the results

	cd snolib
	make deliver

This will deliver the INC files to LIBDIR, executables to BINDIR
CGI to CGIDIR

There are some .so (shared object) files that may need to be placed
in your shared objects location:

	editline.so
	ffi.so
	format.so
	jit.so
	p64.so

Step six. Add fonts to your system

The .ttf and .otf files should be added as fonts to your system, so
your Web browser will have access to them.

And, the build is complete

Call up your Web browser (I use Firefox). and open "index.html".

Warning! --
test_all tests combining COBOL, FORTRAN and SCHEME into a single
load module driven by CSNOBOL4. One word -- don't! This was an early
use-case for me. I am working with a client with millions of lines
of FORTRAN 77, that is being re-platformed. This allowed me to write
test drivers in SNOBOL4.

Fred Weigel
fred_weigel@hotmail.com
