-MODULE SEQ
-LINE 34 "SEQ.lss"
-IN72
-LINE 64 "SEQ.lss"
-STITL SEQ
-EJECT
*
************************************************************************
*                                                                      *
*                       #####   #######   #####                        *
*                      #     #  #        #     #                       *
*                      #        #        #     #                       *
*                       #####   #####    #     #                       *
*                            #  #        #   # #                       *
*                      #     #  #        #    #                        *
*                       #####   #######   #### #                       *
*                                                                      *
* SEQ                SEQUENCE STATEMENT WITH COUNTER                   *
*                                                                      *
************************************************************************
*
* SEQ.lss
*
-LINE 37 "SEQ.lss"
-PUBLIC SEQ()
*
         DEFINE('SEQ(ARG_S,ARG_NAME,START,END)')              :(SEQ_END)
*
SEQ      START = IDENT(START) 1
         $ARG_NAME = START - 1
         ARG_S = CODE(ARG_S  ' :S(SEQ_1)F(SEQ_2)')             :F(ERROR)
SEQ_1    DIFFER(END) GE($ARG_NAME, END)                       :S(RETURN)
         $ARG_NAME = $ARG_NAME + 1                              :<ARG_S>
SEQ_2    EQ($ARG_NAME, START)                       :S(FRETURN)F(RETURN)
*
SEQ_END
*
* CE: .MSNOBOL4;
