-MODULE ITERDIR
-LINE 48 "ITERDIR.lss"
-INCLUDE 'BQ.INC'
-INCLUDE 'CRACK.INC'
-INCLUDE 'ATOL.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'LOGIC.INC'
-INCLUDE 'REPL.INC'
-INCLUDE 'VDIFFER.INC'
-INCLUDE 'LINK.INC'
-IN72
-LINE 140 "ITERDIR.lss"
-STITL ITERDIR
-EJECT
*
************************************************************************
*                                                                      *
*        ###  #######  #######  ######   ######   ###  ######          *
*         #      #     #        #     #  #     #   #   #     #         *
*         #      #     #        #     #  #     #   #   #     #         *
*         #      #     #####    ######   #     #   #   ######          *
*         #      #     #        #   #    #     #   #   #   #           *
*         #      #     #        #    #   #     #   #   #    #          *
*        ###     #     #######  #     #  ######   ###  #     #         *
*                                                                      *
* ITERDIR                   DIRECTORY ITERATOR                         *
*                                                                      *
************************************************************************
*
* ITERDIR.lss
*
-LINE 59 "ITERDIR.lss"
-PUBLIC VALUE_DIR(), ITER_DIR(), NEXT_DIR(), READ_DIR()
*
         DEFINE('READ_DIR(W)P,O,V')
         DEFINE('ITER_DIR(W)P,L')
         DEFINE('VALUE_DIR(D)')
         DEFINE('NEXT_DIR(D)')                           :(END_ITER_DIR)
*
* READ DIRECTORY, RETURNING LIST OF FILES. WE USE -b TO HAVE ls ENCODE
* FILENAMES WITH C ESCAPES, AND THEN REPLACE THE ESCAPES IN EACH NAME.
* READ_DIR() CAN BE USED DIRECTLY, OR IS CALLED BY ITER_DIR(). THE
* ARGUMENT PASSED IS A FILENAME PATTERN THAT CAN BE APPLIED TO ls, (NOT
* A PATTERN).
*
* BE CAREFUL WITH THE WILDCARD PASSED - QUOTES (' AND ") WILL NOT WORK
* SO IT IS BETTER TO GATHER THE ENTIRE DIRECTORY CONTENTS AND FILTER.
* EVEN AN EMPTY DIRECTORY WILL HAVE . AND .. ENTRIES.
*
READ_DIR READ_DIR = ATOL(CRACK(BQ('/usr/bin/ls -a -1 -b 2>/dev/null ' W,
+                                 CHARS_NL),
+                              CHARS_NL))                    :F(FRETURN)
         P = READ_DIR
         O = ANY('01234567')
RD_DIR2  IDENT(P)                                             :S(RETURN)
RD_DIR3  VALUE(P) '\' (O O O) . V = CHAR(DIB(V, 8))          :S(RD_DIR3)
         VALUE(P) = REPL(VALUE(P), '\a', CHARS_BEL)
         VALUE(P) = REPL(VALUE(P), '\"', '"')
         VALUE(P) = REPL(VALUE(P), "\'", "'")
         VALUE(P) = REPL(VALUE(P), '\b' CHARS_BS)
         VALUE(P) = REPL(VALUE(P), '\e' CHARS_ESC)
         VALUE(P) = REPL(VALUE(P), '\f' CHARS_FF)
         VALUE(P) = REPL(VALUE(P), '\n' CHARS_NL)
         VALUE(P) = REPL(VALUE(P), '\r' CHARS_CR)
         VALUE(P) = REPL(VALUE(P), '\t' CHARS_HT)
         VALUE(P) = REPL(VALUE(P), '\v' CHARS_VT)
         VALUE(P) = REPL(VALUE(P), '\\', '\')
         P = NEXT(P)                                          :(RD_DIR2)
*
VALUE_DIR
         VALUE_DIR = VALUE(VDIFFER(D))              :S(RETURN)F(FRETURN)
*
ITER_DIR IDENT(DATATYPE(W), 'PATTERN')                      :S(ITERDIR2)
*
         ITER_DIR = READ_DIR(W)                     :S(RETURN)F(FRETURN)
*
ITERDIR2 ITER_DIR = READ_DIR()                               :F(FRETURN)
         P = ITER_DIR
ITERDIR3 IDENT(P)                                             :S(RETURN)
         VALUE(P) W                                         :S(ITERDIR4)
         NEXT(VDIFFER(L)) = NEXT(P)
         ITER_DIR = IDENT(L) NEXT(ITER_DIR)
         P = IDENT(L) ITER_DIR                              :S(ITERDIR3)
         P = NEXT(P)                                         :(ITERDIR3)
ITERDIR4 L = P; P = NEXT(P)                                  :(ITERDIR3)
*
NEXT_DIR NEXT_DIR = NEXT(VDIFFER(D))                :S(RETURN)F(FRETURN)
*
END_ITER_DIR
*
* CE: .MSNOBOL4;
