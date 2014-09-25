-MODULE READFILE
-LINE 15 "READFILE.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'SYSTEM.INC'
-IN72
-LINE 52 "READFILE.lss"
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
READFILE SYSTEM() 'CSNOBOL4'                                 :S(RDFILE3)
         U = 20
         E = CHARS_NL
         INPUT(.F, U, FILE)                        :S(RDFILE2)F(FRETURN)
RDFILE3  U = IO_FINDUNIT()                                   :F(FRETURN)
         INPUT(.F, U, 'B,65536', FILE)                       :F(FRETURN)
RDFILE2  READFILE = READFILE F E                             :S(RDFILE2)
RDFILE4  ENDFILE(U)
         DETACH(.F)                                            :(RETURN)
*
READFILE_END
*
* CE: .F.MSNOBOL4;
