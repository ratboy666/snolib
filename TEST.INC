-LINE 16 "TEST.lss"
-INCLUDE 'UNIQUE.INC'
-STITL TEST
-EJECT
-LINE 46 "TEST.lss"
*
************************************************************************
*                                                                      *
*                                                                      *
*                  #######  #######   #####   #######                  *
*                     #     #        #     #     #                     *
*                     #     #        #           #                     *
*                     #     #####     #####      #                     *
*                     #     #              #     #                     *
*                     #     #        #     #     #                     *
*                     #     #######   #####      #                     *
*                                                                      *
* TEST                                                                 *
*                                                                      *
************************************************************************
*
* TEST.lss
*
-LINE 20 "TEST.lss"
-MODULE TEST
-PUBLIC TESTP()
         DEFINE('TESTP(ARG)NAME')                            :(TEST_END)
*
TESTP    IDENT(DATATYPE(ARG), 'EXPRESSION')                   :F(TEST_1)
         NAME = UNIQUE()
         $NAME = ARG
         TEST = EVAL("NULL $ *TEST('" NAME "')")               :(RETURN)
TEST_1   TEST = ?EVAL($ARG) .TEST_                 :S(NRETURN)F(FRETURN)
*
TEST_END
*
* CE: .MSNOBOL4;
