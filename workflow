<!-- workflow -->
<h2>Literate Programming Workflow</h2>
<h3>Introduction</h3>
<p align="justify">
  CSNOBOL4 is an implementation of SNOBOL4 based on the original
  SIL implementation. As such, it is very mature and stable, but,
  since the SIL reference implementation dates from 1969, doesn't
  offer any particular amenities for program development. Most
  programs were entered on punched cards, and programming was mostly
  a “pen and paper” activity. Computer time was very expensive,
  so the computer itself was not used to ease the programming process
  (except, perhaps, to generate cross-references).

</p>
<p align="justify">
  This project is an attempt to address some of these shortcomings. In
  1969, SNOBOL4 was run on an IBM 360 computer, which was considered
  a “Mainframe”. I started this development on an Intel ATOM
  based netbook, which is actually the slowest system I have access
  to. Still, this system is over one thousand times faster (1.6Ghz
  single core with hyper-threading) than the IBM 360 based on execution
  times published in SNOBOL4 reference “Green Book” using the
  IBM 360 SIL implementation and the CSNOBOL4 SIL implementation on
  my netbook. As well, my netbook has 1GB of memory, as compared to
  (typically) under 1MB for the IBM 360 (again, 1000 times more),
  and many times the mass storage capacity (160GB internal, and
  multiple terrabytes external - easily many thousand times the
  capacity). The other system I use for development is an Intel i3
  system with 4GB of RAM. This system is over 2000 times faster than
  the IBM 360 at single thread execution, and over 4000 times faster
  because it is dual core. it has 4000 times the RAM of the IBM 360.

</p>
<p align="justify">
  This 3 or more orders of magnitude increase in capacity should be
  used to make the programming task easier. SNOBOL4 was originally,
  and still is, generally an interpretive system. But, we have access
  to additional utility software, and ideas which were not available
  back in 1969. Automatic dependency checking with <code>MAKE</code>,
  revision control with <code>RCS</code> (and, further systems like
  <code>GIT</code>), full screen interactive editors, diagramming
  tools, formatting, spell check, test driven development and Donald
  Knuth's marvelous idea of “Literate Programming”.

</p>
<h3>Literate Programming</h3>
<p align="justify">
  Literate programming is the art of writing computer programs in such
  a way that the source code is presented clearly and engagingly for
  a human reader while still making it available to the compiler.
  Literate programming embeds source code within its technical
  documentation; it permits the code to be presented in an order that
  suits the human reader, then re-orders the code for compilation.
  It does require good tracking of line references back to the original
  literate source so that compile errors can be easily fixed.

</p>
<p align="justify">
  Donald Knuth invented literate programming during the development
  of his TeX typesetting program in 1981 in response to a challenge
  from Tony Hoare to publish the source code to TeX.  Knuth admits
  to being terrified at the prospect of publishing his code, but,
  drawing on the ideas of <i>holon</i> programming developed by Pierre
  Arnoul de Marneffe, Knuth developed the original WEB system that
  combined program code and technical documentation into a single
  document that provided a clear, engaging description to a human
  reader and simultaneously provided source code to the compiler.

</p>
<p align="justify">
  This is an implementation of the <code>tangle</code> and
  <code>weave</code> programs (here known as <code>stangle</code>
  and <code>sweave</code>).  This implementation is not tied to a
  particular language, and will work with C, Pascal, Assembler,
  SNOBOL4 and more, and “mixed language” files utilizing my
  <code>embed</code> processor.

</p>
<h3>Structured Programming</h3>
<p align="justify">
  I have started to look at <i>snocone</i> to make SNOBOL4
  more palatable to other developers. However <i>snocone</i>
  originally had no provision to generate library components; does
  not respect incoming -LINE directives; always enforced a MAIN
  routine; and guarantees label collision (L.1 etc.) if modules are
  attempted. <i>rebus</i> was another possibility, but <i>snocone</i>
  was chosen because it is easier to modify for my needs. See <a
  href="snocone.html"> snocone</a> for details of this language
  processor.

</p>
<p align="justify">
  <i>snocone</i> has been modified to support the following features.
  Each of these features is included to help with developing modules
  (separate translation units).

</p>
<table border="1">
<tr><td>-m flag</td>
<td><p align="justify">
    The -m flag has been added to suppress the generation of a MAIN
    program in the translation output. This allows modules to be coded
    with <i>snocone</i>.

</p></td></tr>
<tr><td>-CONTROL CARD passthrough</td>
<td><p align="justify">
  Control card (specifically -INCLUDE) are passed through to the
  output on translation. This allows <i>snocone</i> programs to use
  SNOBOL4 library routines.

</p></td></tr>
<tr><td>// passthrough</td>
<td><p align="justify">
  Lines beginning with // are passed through to the output on
  translation. The leading // is stripped. Note that the line must
  begin with // without leading whitespace. These lines are retained
  and emitted when the procedure definitions are output. //-include
  allows files to be included and be available. // lines are deferred
  and output when function definitions are generated.

</p><p align="justify">
  //// passes through lines immediately. This is used to introduce
  SNOBOL4 directly into code. Again the line must begin with ////
  without leading whitespace. The //// is stripped and the resulting
  line is immediately generated.

</p></td></tr>
<tr><td>LABEL=</td>
<td><p align="justify">
  Normally, <i>snocone</i> generates labels of the for L.n where n is
  a number beginning with 1. These labels will conflict if multiple
  translation units are combined. LABEL=string sets the leadin to be
  string instead of L. and can eliminate this problem.  For example
  LABEL=INC. will generate labels INC.1, INC.2 etc.

<p align="justify">
  If -m is used to generate a module, and LABEL= is not used, the
  default label prefix will be the filename (with .sc removed).
  This gives good results for my code.

</p>    
</td></tr>
<tr><td>-LINE parsing</td>
<td><p align="justify">
  <code>-LINE</code> control cards are parsed to allow compile errors
  to track back through the tool chain (back to the <code>.lss</code>
  file).

</p>
<tr><td>Prologue</td>
<td><p align="justify">
  If generating a MAIN., prologue now generates a call to CSNOBOL4.
  Extra options are not yet supported, and need to be manually
  inserted. The standard prologue is:

</p>
<pre>
#!/usr/bin/bash
 exec "snobol4" "-b" "$0" "$@"
-PLUSOPS 1
MAIN. CODE('MAIN')
</pre>
</table>
<p align="justify">
  The <i>snocone</i> translater is run after the code has been
  tangled. This is done because the code generation done by
  <i>snocone</i> is not oriented toward lines, but tokens, and
  conditionals would be difficult to do after tangling.

</p>
<p align="justify">
  The //// feature is dangerous. If used in the middle of a sequence
  of <i>snocone</i> statements, the passthrough output may not appear
  at the correct point. However, it is useful outside of procedures,
  and can be used to completely implement a procedure in SNOBOL4.
  For example:

</p>
<pre>
	-INCLUDE 'CHARS.INC'

	procedure incr(n) {
	   return n + 1;
	}

	procedure proc2(x) {
	//// OUTPUT = 'test: x = ' x
	}
</pre>
<p align="justify">
  This implements an incr procedure written in <i>snocone</i>,
  and a proc2 procedure, declared in <i>snocone</i> but the body is
  completely written in native SNOBOL4. The <code>-INCLUDE</code>
  is actually a part of MAIN.  Since <code>CHARS.INC</code>
  simply assigns character values, that is then done after the
  <code>START.</code> routine branches to <code>MAIN.</code> This
  sequence is a bit different, but should work fine in practice. Note
  that <code>-INCLUDE</code> is the same as <code>////-INCLUDE
  'CHARS.INC'</code> but is a bit more readable.

</p>
<p align="justify">
  If generating a module (to be included in another program), the
  include should be <code>//-INCLUDE 'file'</code> instead. This
  forces the include (or other startup statement) to be generated
  when the function definitions are output. This is needed because
  modules do not begin execution at the top because they have no
  main function.

</p>
<h3>Unit Tests</h3>
<p align="justify">
  Unit tests should be incorporated with the code; this means
  that these tests are to be directly included into the literate
  source. The <code>STANGLE_ROOT=unit_test</code> environment variable
  to <code>stangle</code> is used to select an alternate root chunk
  to generate unit tests.

</p>
<p align="justify">
  These components were not developed using TDD (test driven
  development).  However, a test section has been added as a
  <code>&lt;&lt;unit_test&gt;&gt;</code> root code chunk to each of the
  library components. Most of these are empty, and simply succeed. Some
  do have action. The test component of FILE.lss is FILE.tst. This
  is an executable and should return &amp;CODE=0 on test success
  and &amp;CODE=1 on failure. If the test requires interactivity,
  automatic verification may not be possible (see STCL.lss).

</p>
<h3>Editing</h3>
<p align="justify">
  The workflow begins with preparing ideas. This is done as a mental
  process, and is recorded on computer with an editor, or transcribed
  from paper.

</p>
<p align="justify">
  I generally use my own interactive editor <a
  href="cpmed.html"><code>cpmed</code></a> to prepare documentation
  and programs.  I would not recommend that anyone else use it, but
  the important characteristic is that it allows filtering of text
  through external tools, like <code>spell</code> and <code>fmt</code>.

</p>
<p align="justify">
  The purpose of a text editor (especially a programming editor) is to
  enter and revise ASCII (and, these days, UTF-8) text, conveniently
  and precisely. Text must be entered quickly in the format required by
  the language processor, and revisions should be fast and accurate.
  Any on-screen representation must facilitate these goals, without
  interfering with the creative process.

</p>
<p align="justify">
  The text editor will be used in three “modes”. First is entering
  text, where the text is known, or being composed. This requires
  positioning to the entry location (via a <i>find</i> function,
  or by line number), a ruler to assist in horizontal formatting
  (possibly a margin bell or vertical rules, and tabulation controls).

</p>
<p align="justify">
  The second mode is text revision. Again, rapid location to the
  position, from information given by the language processor (error
  message), or to other desired locations, followed by entry, deletion
  or replacement.

</p>
<p align="justify">
  The third mode is simply reading. A clean and uncluttered display
  is best, perhaps assisted by line numbering or change notification
  devices.

</p>
<p align="justify">
  Editing automation is important for routine use. Being able to
  integrate editing into other parts of the workflow is vital, and
  being able to bend the editor to the authors will is very useful,
  and makes for a satisfying experience.

</p>
<p align="justify">
  The two editors in common use (<code>vi</code> and
  <code>emacs</code>) have many of the desired traits. I use my
  own editor, but the actual editor used is a personal decision of
  the author.

</p>
<h3>Browsing (and Reading)</h3>
<p align="justify">
  Completed projects are to be browsed and read. Other peoples
  idea recorded in computer form are also to be read. I found it
  difficult to stretch the editor completely to browsing or reading
  and not compromise the editing function (and have both work to my
  satisfaction). So I introduce a tool called <code>list</code> for
  this purpose. It provides <i>nothing</i> but a full-screen view of
  the document with no other distractions to the reading process.
  But, my preferred reading software is a web browser. I use the
  <i>Firefox</i> Web Browser that provides a rich reading experience. A
  document can be displayed with nice type fonts, and illustrations
  are displayed.

</p>
<p align="justify">
  For this reason, the target of the documention production
  process will be <i>html</i> format, suitable for rendering by
  <i>Firefox</i>. Other browsers may function as well.

<h3>Diagrams</h3>
<p align="justify">
  Diagrams provide important insight into problems. I find that
  drawing a picture can help me reason about an issue, and that
  providing such illustration can help explain to others.

</p>
<p align="justify">
  Entry of such diagrams may be difficult. We want the resultant
  diagram to render with <i>Firefox</i>. External drawing tools abound
  (for example, <i>dia</i>). But, our primary tool is the editor,
  and we want to capture diagrams without excessively interrupting
  the edit process.

</p>
<p align="justify">
  To this end, I have been using a tool called <i>ditaa</i>. This
  takes a diagram in the document, represented as simple “ASCII
  art”, and converts it to a “.png” format suitable for rendering
  by <i>Firefox</i>.

</p>
<p align="justify">
  <i>ditaa</i> is not included in this archive.  <i>ditaa</i> is a
  J<small>AVA</small> application, and will require the installation of
  a J<small>AVA</small> run-time (JRE). <code>ditaa</code> is available
  (free software) from <a href="http://ditaa.sourceforge.net/">
  ditaa.sourceforge.net</a>.  <i>ditaa</i> may be available in your
  package repositories (if you are using Linux). It comes in the
  repositories for Fedora (yum install ditaa).

</p>
<p align="justify">
  A C compiler will also be needed for some of the components
  (P64, FFI, JIT and the <code>compile</code> utility). The
  <code>compile</code> utility will also require a source distribution
  of CSNOBOL4.

</p>
<p align="justify">
  If these components are not desired, the Makefile can be edited to
  remove them.

</p>
<p align="justify">
  <i>ditaa</i> is run as a filter for <i>html</i> files, where it
  locates diagrams, converts them, and inserts the correct reference
  into the resultant (new) <i>html</i> code. An example (from the
  <i>ditaa</i> documentation) follows:

</p>
<pre class="textdiagram" id="ditaa_sample">
                  +--------+   +-------+    +-------+
                  |        | --+ ditaa +--> |       |
                  |  Text  |   +-------+    |diagram|
                  |Document|   |!magic!|    |       |
                  |     {d}|   |       |    |       |
                  +---+----+   +-------+    +-------+
                      :                         ^
                      |       Lots of work      |
                      +-------------------------+
</pre>
<p align="justify">
  A benefit to using <i>ditaa</i> as compared to an external drawing
  tool is that the image is available (albeit in a cruder form)
  when viewing the ASCII source in the editor, or list tool.

</p>
<h3>Revision Control</h3>
<p align="justify">
  Being able to capture editing changes and revert changes made in
  error is a useful feature of modern programming environments. I
  use <i>RCS</i> for this purpose. There are distributed system (such
  as <i>GIT</i>) in use today. <i>RCS</i> is nice in that it is very
  simple, and easy to use.  Since I generally work on projects alone,
  I find <i>RCS</i> entirely suitable.

</p>
<h3>Source File Processing</h3>
<p align="justify">
  The literate source itself may be broken into multiple source files
  for convenience of editing. There should be a single “main”
  literate source file, that includes other files as needed for
  the project. Thus, processing begins with the <code>ifs</code>
  utility. The environment variable <code>IFSLC=@</code> is set
  to define the lead-in character to the @ sign. Includes are then
  specified by <code>@INCLUDE(FILE)</code>. <code>LSS=SNOBOL4</code>
  (or C, or ASM) to allow <code>ifs</code> to generate line references
  to the literate source.

</p>
<p align="justify">
  The combined literate source is then sent through
  <code>stangle</code>.  Again, <code>LSS=SNOBOL4</code> is used to
  generate appropriate line references for error tracking.

</p>
<p align="justify">
  After tangling, the source code is processed by <code>ifs</code>
  again, to do conditional processing. This time, the “normal”
  lead-in character % is used. This may also include needed files
  to determine conditional processing. After this, the code is
  processed with <code>embed</code>. This allows creation of needed
  support files, and compilation using the C compiler and other needed
  building tasks. The output of <code>embed</code> is the final INCLUDE
  file or executable, if the source language was SNOBOL4. However,
  it is possible that the source language may be something else
  (for example, SNOCONE). If SNOCONE, the file must be processed by
  <code>snocone</code> as either a module or main program.

</p>
<pre>
  IFSLC=@ LSS=SNOBOL4 ifs     <i>infile</i> |
          LSS=SNOBOL4 stangle        |
          LSS=SNOBOL4 ifs            |
                      embed &gt;<i>outfile</i>
</pre>
<p align="justify">
  The same commands are used to produce unit tests.
  <code>STANGLE_ROOT=unit_test</code> is added to provide a different
  root for the tangle operation. This should produce a runnable file
  that implements unit tests for this component.

</p>
<pre>
  IFSLC=@                LSS=SNOBOL4 ifs     <i>infile</i> |
  STANGLE_ROOT=unit_test LSS=SNOBOL4 stangle        |
                         LSS=SNOBOL4 ifs            |
                                     embed &gt;<i>outfile</i>
</pre>
<p align="justify">
  The documentation is produced from the same literate source
  file. Again, pieces may need to be gathered using <code>ifs</code>.
  The literate source is then processed by <code>sweave</code> to
  produce <i>html</i> output. A footer is added automatically referring
  to <code>index.html</code> which should be the “head” of the
  documentation for the project. The <i>html</i> is processed by the
  <code>ditaa</code> utility to convert ASCII diagrams to <i>png</i>
  diagrams in the <i>html</i> file.

</p>
<p align="justify">
  Line number tracking is not important when generating the
  documentation output so <code>LSS</code> is not used while weaving.

</p>
<pre>
  IFSLC=@ ifs <i>infile</i> | sweave &gt; <i>html_file</i>
  ditaa <i>html_file</i> --html --overwrite
</pre>
<p align="justify">
  A single <code>.lss</code> input file will produce a library file or
  an executable, an <i>html</i> documentation file with illustrations;
  possibly C header files and loadable <code>.so</code> objects, and
  unit tests. Since <code>embed</code> is used, other artifacts are
  also easily generated (for example, data files for the unit tests).

</p>
<h3>The Build Process</h3>
<p align="justify">
  From the diagram, twelve or so programs are typically executed to
  convert the literate source into the library or program, produce
  the documentation, and the unit test. Actually, if an external
  compiler is needed, possibly 16 or more programs may be invoked
  (C preprocessor, C compiler, linker) although these are not shown
  on the diagram.

</p>
<p align="justify">
  Compile activities are coordinated using <i>make</i>.

</p>
<pre class="textdiagram" id="workflow">
+----------+
| {d}      |
| file.lss +--\
|          |  |  /------Other Included Source
+----------+  |  :
              v  v
        +----------+  +---------+  +------+  +----------+  +-------+
        | ifs      |  |         |  |      |  | ifs      |  |       |
        | @ prefix +->| stangle +->| g360 |->| % prefix +->| embed |
        |       S1 |  |      S2 |  |   S3 |  |       S4 |  |    S5 |
        ++------+--+  +---------+  +------+  +----------+  ++--+---+
         |      |                                           :  |
         |      v                  /------------------------/  |
         |  +--------+             |                           v
         |  |        |             v                     +---------+
   /-----/  | sweave |     +----------------+            |         |
   |        |     S13|     |                |            | snocone |
   |        +---+----+     | Other outputs  |            |      S6 |
   |            |          | and processing |            +----+----+
   |            |          |                |                 |
   |            |          +----------------+                 |
   |            v                                             |
   |      +-----------+   +-----------+                       v
   |      |           |   |{d}     S15|                   +----------+
   |      | ditaa     +-->| html file |                   |{d}       |
   |      |        S14|   | png files |                   | INC file |
   |      +-----------+   +-----------+                   |       S7 |
   |                                                      +----------+
   |
   |    +-----------+  +------+  +----------+  +-------+   +-----------+
   |    | stangle   |  |      |  | ifs      |  |       |   |{d}        |
   \--->| unit_test +->| g360 |->| % prefix +->| embed +-->| UNIT TEST |
        |        S8 |  |   S9 |  |       S10|  |    S11|   |        S12|
        +-----------+  +------+  +----------+  +-------+   +-----------+
</pre>
<pre>
S1   IFS @ PREFIX
	Collect all source together to process with stangle/sweave.
	The source may be in separate file to ease editing.
S2   STANGLE <<>>
	Tangle together the chunks from the input producing a file
	in correct sequence for the language processor. Begin tangle
	with the <<>> chunk.
S3   G360
	Simple pre-processing of source code. Currently, replaces
	← with =, but can do other macro expansion tasks. This will
	be important later, to add syntax sugar.
S4   IFS % PREFIX
	Does file level includes and conditionals for the code. Sort
	out 32/64 bit issues, platform issues etc. at this phase.
	This is for software configuration.
S5   EMBED
	Extracts in-line files (C, FORTRAN, data, etc.). Runs additional
	commands to process them (eg. C compiler to produce loadable
	objects).
S6   SNOCONE
	If the source is SNOCONE rather than SNOBOL4, translate the
	SNOCONE to SNOBOL4.
S7   INCLUDE FILE OR PROGRAM
	We now have the target include file or program.
S8   STANGLE <<unit_test>>
	Tangle the source using <<unit_test>> as the root chunk. This
	extracts the unit test source.
S9   SEE S3
S10  SEE S4
S11  SEE S5
S12  UNIT TEST
	We now have the unit test built and ready to be run.
S13  SWEAVE
	Process the literate source, formatting documentation and
	code for publication.
S14  DITAA
	Convert ASCII diagrams in documentations to real drawings
S15  DOCUMENTATION
	HTML documentation prepared, with diagrams.
</pre>

<!-- ce: .f.mhtml; -->
