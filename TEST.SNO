-LINE 18 "TEST.lss"
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
-LINE 22 "TEST.lss"
         DEFINE('TEST(ARG)NAME')                             :(TEST_END)
*
TEST     IDENT(DATATYPE(ARG), 'EXPRESSION')                   :F(TEST_1)
         NAME = UNIQUE()
         $NAME = ARG
         TEST = EVAL("NULL $ *TEST('" NAME "')")               :(RETURN)
TEST_1   TEST = ?EVAL($ARG) .TEST_                 :S(NRETURN)F(FRETURN)
*
TEST_END
*
* CE: .MSNOBOL4;
