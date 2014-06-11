-MODULE ITERDIR
-LINE 32 "ITERDIR.lss"
-INCLUDE 'BQ.INC'
-INCLUDE 'CRACK.INC'
-INCLUDE 'ATOL.INC'
-INCLUDE 'CHARS.INC'
-STITL ITERDIR
-LINE 69 "ITERDIR.lss"
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
-LINE 39 "ITERDIR.lss"
-PUBLIC `VALUE_DIR(), ITER_DIR(), NEXT_DIR()
*
         DEFINE('ITER_DIR(W)')
         DEFINE('VALUE_DIR(D)')
         DEFINE('NEXT_DIR(D)')                           :(END_ITER_DIR)
*
VALUE_DIR
         VALUE_DIR = DIFFER(D) VALUE(D)             :S(RETURN)F(FRETURN)
*
ITER_DIR ITER_DIR = ATOL(CRACK(BQ('ls 2>/dev/null ' W, CHARS_NL),
+           CHARS_NL))                              :S(RETURN)F(FRETURN)
*
NEXT_DIR NEXT_DIR = DIFFER(D) NEXT(D)               :S(RETURN)F(FRETURN)
*
END_ITER_DIR
*
* CE: .MSNOBOL4;
