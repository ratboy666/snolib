-STITL READLINE
-EJECT
*
-LINE 39 "READFILE.lss"
************************************************************************
*                                                                      *
*  ######   #######     #     ######   #######  ###  #        #######  *
*  #     #  #          # #    #     #  #         #   #        #        *
*  #     #  #         #   #   #     #  #         #   #        #        *
*  ######   #####    #     #  #     #  #####     #   #        #####    *
*  #   #    #        #######  #     #  #         #   #        #        *
*  #    #   #        #     #  #     #  #         #   #        #        *
*  #     #  #######  #     #  ######   #        ###  #######  #######  *
*                                                                      *
* READFILE          READ COMPLETE FILE INTO STRING                     *
*                                                                      *
************************************************************************
*
* READFILE.lss
*
-LINE 13 "READFILE.lss"
         DEFINE('READFILE(FILE)F,U')                     :(READFILE_END)
*
READFILE U = IO_FINDUNIT()                                   :F(FRETURN)
         INPUT(.F, U, 'B,65536', FILE)                       :F(FRETURN)
READFILE2
         READFILE = READFILE F                             :S(READFILE2)
         ENDFILE(U)
         DETACH(.F)                                            :(RETURN)
*
READFILE_END
*
* CE: .F.MSNOBOL4;
