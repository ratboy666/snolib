-MODULE WRTFILE
-LINE 13 "WRTFILE.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'SYSTEM.INC'
-IN72
-LINE 57 "WRTFILE.lss"
-STITL WRTFILE
-EJECT
*
************************************************************************
*                                                                      *
*      #     #  ######   #######  #######  ###  #        #######       *
*      #  #  #  #     #     #     #         #   #        #             *
*      #  #  #  #     #     #     #         #   #        #             *
*      #  #  #  ######      #     #####     #   #        #####         *
*      #  #  #  #   #       #     #         #   #        #             *
*      #  #  #  #    #      #     #         #   #        #             *
*       ## ##   #     #     #     #        ###  #######  #######       *
*                                                                      *
* WRTFILE          WRITE COMPLETE FILE FROM STRING                     *
*                                                                      *
************************************************************************
*
* WRTFILE.lss
*
-LINE 19 "WRTFILE.lss"
         DEFINE('WRITEFILE(FILE,S)F,U,E,T')               :(WRTFILE_END)
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
WRTFILE_END
*
* CE: .F.MSNOBOL4;
