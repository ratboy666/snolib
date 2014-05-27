-STITL FOR
-EJECT
*
-LINE 66 "FOR.lss"
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
-LINE 27 "FOR.lss"
         DEFINE('FOR(INIT_,TEST_,UPDT_,STMT_)')               :(FOR_END)
*
FOR      TEST_ = CODE(TEST_ ' :S<STMT_>F(RETURN)')             :F(ERROR)
         STMT_ = CODE(STMT_ ' :S<UPDT_>F(FRETURN)')            :F(ERROR)
         UPDT_ = CODE(UPDT_ ' :S<TEST_>F(FRETURN)')            :F(ERROR)
         INIT_ = CODE(INIT_ ' :S<TEST_>F(FRETURN)')    :S<INIT_>F(ERROR)
*
FOR_END
*
* CE: .MSNOBOL4;
