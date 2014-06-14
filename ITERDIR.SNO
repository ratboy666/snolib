-MODULE ITERDIR
-LINE 45 "ITERDIR.lss"
-INCLUDE 'BQ.INC'
-INCLUDE 'CRACK.INC'
-INCLUDE 'ATOL.INC'
-INCLUDE 'CHARS.INC'
-IN72
-LINE 105 "ITERDIR.lss"
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
-LINE 52 "ITERDIR.lss"
-PUBLIC VALUE_DIR(), ITER_DIR(), NEXT_DIR()
*
         DEFINE('ITER_DIR(W)P,L')
         DEFINE('VALUE_DIR(D)')
         DEFINE('NEXT_DIR(D)')                           :(END_ITER_DIR)
*
VALUE_DIR
         VALUE_DIR = DIFFER(D) VALUE(D)             :S(RETURN)F(FRETURN)
*
ITER_DIR DIFFER(FORCEPATTERN)                               :S(ITERDIR2)
         DATATYPE(W) 'PATTERN'                              :S(ITERDIR2)
*
         ITER_DIR = ATOL(CRACK(BQ('ls 2>/dev/null ' W, CHARS_NL),
+           CHARS_NL))                              :S(RETURN)F(FRETURN)
*
ITERDIR2 ITER_DIR =
+           ATOL(CRACK(BQ('ls 2>/dev/null', CHARS_NL), CHARS_NL))
         P = ITER_DIR
ITERDIR3 IDENT(P)                                             :S(RETURN)
         VALUE(P) W                                         :S(ITERDIR4)
         NEXT(VDIFFER(L)) = NEXT(P)
         ITER_DIR = IDENT(L) NEXT(ITER_DIR)
         P = IDENT(L) ITER_DIR                              :S(ITERDIR3)
         P = NEXT(P)                                         :(ITERDIR3)
ITERDIR4 L = P; P = NEXT(P)                                  :(ITERDIR3)
*
NEXT_DIR NEXT_DIR = DIFFER(D) NEXT(D)               :S(RETURN)F(FRETURN)
*
END_ITER_DIR
*
* CE: .MSNOBOL4;
