-MODULE READFILE
-LINE 15 "READFILE.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'SYSTEM.INC'
-IN72
-LINE 55 "READFILE.lss"
-STITL READLINE
-EJECT
*
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
-LINE 21 "READFILE.lss"
-PUBLIC READFILE()
*
         DEFINE('READFILE(FILE)F,U,E')                   :(READFILE_END)
*
READFILE SYSTEM() 'CSNOBOL4'                               :S(READFILE3)
         U = 20
         E = CHARS_NL
         INPUT(.F, U, FILE)                      :S(READFILE2)F(FRETURN)
READFILE3
         U = IO_FINDUNIT()                                   :F(FRETURN)
         INPUT(.F, U, 'B,65536', FILE)                       :F(FRETURN)
READFILE2
         READFILE = READFILE F E                           :S(READFILE2)
READFILE4
         ENDFILE(U)
         DETACH(.F)                                            :(RETURN)
*
READFILE_END
*
* CE: .F.MSNOBOL4;
