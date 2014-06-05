-LINE 25 "READFILE.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'SYSTEM.INC'
-STITL READLINE
-EJECT
-LINE 86 "READFILE.lss"
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
-LINE 31 "READFILE.lss"
-MODULE READFILE
-PUBLIC WRITEFILE(), READFILE()
         DEFINE('WRITEFILE(FILE,S)F,U,E,T')
         DEFINE('READFILE(FILE)F,U,E')                   :(READFILE_END)
*
WRITEFILE
         SYSTEM() 'CSNOBOL4'                              :S(WRITEFILE3)
         U = 20
         OUTPUT(.F, U, FILE)                                 :F(FRETURN)
WRITEFILE2
         S BRKREM(CHARS_NL) . T (CHARS_NL | NULL) =
         F = T
         IDENT(S)                             :S(READFILE4)F(WRITEFILE2)
WRITEFILE3
         U = IO_FINDUNIT()
         OUTPUT(.F, U, 'B,65536', FILE)
WRITEFILE4
         T = LT(SIZE(S), 65536) S                         :F(WRITEFILE6)
         S =
WRITEFILE5
         F = T
         IDENT(S)                             :S(READFILE4)F(WRITEFILE4)
WRITEFILE6
         S LEN(65536) . T REM . S                          :(WRITEFILE5)
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
