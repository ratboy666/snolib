-STITL FOR
-EJECT
*
-LINE 256 "FOR.lss"
************************************************************************
*                                                                      *
*                      #######  #######  ######                        *
*                      #        #     #  #     #                       *
*                      #        #     #  #     #                       *
*                      #####    #     #  ######                        *
*                      #        #     #  #   #                         *
*                      #        #     #  #    #                        *
*                      #        #######  #     #                       *
*                                                                      *
* FOR                         FOR LOOP                                 *
*                                                                      *
************************************************************************
*
* FOR.lss
*
-LINE 62 "FOR.lss"
-MODULE FOR
-PUBLIC CODE_(), WHILE_COMPILE(), IF_COMPILE(), FOR_COMPILE()
-PUBLIC STMT_COMPILE(), PROG2_COMPILE(), SET_RVAL(), EVAL_CODE_()
-PUBLIC FOR(), WHILE()
         DATA('CODE_(TYPE,INIT,TEST,INCR,STMT,ELSE,'
+                        'INIT_,TEST_,INCR_,STMT_,ELSE_)')
         DEFINE('WHILE_COMPILE(TEST_,STMT_)')
         DEFINE('IF_COMPILE(TEST_,STMT_,ELSE_)')
         DEFINE('FOR_COMPILE(INIT_,TEST_,INCR_,STMT_)')
         DEFINE('STMT_COMPILE(STMT_)')
         DEFINE('PROG2_COMPILE(INIT_,STMT_)')
         DEFINE('SET_RVAL(R)')
         DEFINE('EVAL_CODE_(F_)')
*
         OPSYN('FOR', 'EVAL_CODE_')
         OPSYN('WHILE', 'EVAL_CODE_')                         :(FOR_END)
*
SET_RVAL EVAL_CODE_ = R
         SET_RVAL = R                                          :(RETURN)
*
PROG2_COMPILE
         PROG2_COMPILE = CODE_('PROG2')
         INIT_(PROG2_COMPILE) = INIT_
         STMT_(PROG2_COMPILE) = STMT_
         INIT_ = IDENT(DATATYPE(INIT_), 'CODE_')
+           ' EVAL_CODE_(INIT_(F_))'
         INIT(PROG2_COMPILE) =
+           CODE(INIT_ ' :<STMT(F_)>')                         :F(ERROR)
         STMT_ = IDENT(DATATYPE(STMT_), 'CODE_')
+           ' EVAL_CODE_ = EVAL_CODE_(STMT_(F_))'
         STMT(PROG2_COMPILE) =
+           CODE(STMT_ ' :S(RETURN)F(FRETURN)')       :S(RETURN)F(ERROR)
*
STMT_COMPILE
         STMT_COMPILE = CODE_('STMT')
         STMT_(STMT_COMPILE) = STMT_
         INIT(STMT_COMPILE) = CODE(' :<STMT(F_)>')
         STMT_ = IDENT(DATATYPE(STMT_), 'CODE_')
+           ' EVAL_CODE_ = EVAL_CODE_(STMT_(F_))'
         STMT(STMT_COMPILE) =
+           CODE(STMT_ ' :S(RETURN)F(FRETURN)')       :S(RETURN)F(ERROR)
*
IF_COMPILE
         IF_COMPILE = CODE_('IF')
         TEST_(IF_COMPILE) = TEST_
         STMT_(IF_COMPILE) = STMT_
         ELSE_(IF_COMPILE) = ELSE_
         INIT(IF_COMPILE) = CODE(' :<TEST(F_)>')
         TEST_ = IDENT(DATATYPE(TEST_), 'CODE_')
+           ' EVAL_CODE_(TEST_(F_))'
         TEST(IF_COMPILE) =
+           CODE(TEST_ ' :S<STMT(F_)>F<ELSE(F_)>')             :F(ERROR)
         STMT_ = IDENT(DATATYPE(STMT_), 'CODE_')
+           ' EVAL_CODE_ = EVAL_CODE_(STMT_(F_))'
         STMT(IF_COMPILE) =
+           CODE(STMT_ ' :S(RETURN)F(FRETURN)')                :F(ERROR)
         ELSE_ = IDENT(DATATYPE(STMT_), 'CODE_')
+           ' EVAL_CODE_ = EVAL_CODE_(ELSE_(F_))'
         ELSE(IF_COMPILE) =
+           CODE(ELSE_ ' :S(RETURN)F(FRETURN)')       :S(RETURN)F(ERROR)
*
WHILE_COMPILE
         WHILE_COMPILE = FOR_COMPILE(, TEST_,, STMT_)
         TYPE(WHILE_COMPILE) = 'WHILE'                         :(RETURN)
*
FOR_COMPILE
         FOR_COMPILE = CODE_('FOR')
         TEST_(FOR_COMPILE) = TEST_
         STMT_(FOR_COMPILE) = STMT_
         INCR_(FOR_COMPILE) = INCR_
         INIT_(FOR_COMPILE) = INIT_
         TEST_ = IDENT(DATATYPE(TEST_), 'CODE_')
+           ' EVAL_CODE_(TEST_(F_))'
         TEST(FOR_COMPILE) =
+           CODE(TEST_ ' :S<STMT(F_)>F(RETURN)')               :F(ERROR)
         STMT_ = IDENT(DATATYPE(STMT_), 'CODE_')
+           ' EVAL_CODE_ = EVAL_CODE_(STMT_(F_))'
         STMT(FOR_COMPILE) =
+           CODE(STMT_ ' :S<INCR(F_)>F(FRETURN)')              :F(ERROR)
         INCR_ = IDENT(DATATYPE(INCR_), 'CODE_')
+           ' EVAL_CODE_(INCR_(F_))'
         INCR(FOR_COMPILE) =
+           CODE(INCR_ ' :S<TEST(F_)>F(ERROR)')                :F(ERROR)
         INIT_ = IDENT(DATATYPE(INIT_), 'CODE_')
+           ' EVAL_CODE_(INIT_(F_))'
         INIT(FOR_COMPILE) =
+           CODE(INIT_ ' :S<TEST(F_)>F(ERROR)')       :S(RETURN)F(ERROR)
*
EVAL_CODE_                                                   :<INIT(F_)>
*
FOR_END
*
* CE: .MSNOBOL4;
