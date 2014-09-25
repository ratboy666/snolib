-MODULE WRTFILE
-LINE 13 "WRTFILE.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'CHARS.INC'
-INCLUDE 'SYSTEM.INC'
-INCLUDE 'READFILE.INC'
-IN72
-LINE 56 "WRTFILE.lss"
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
-LINE 20 "WRTFILE.lss"
*
-USES READFILE()
*
         DEFINE('WRITEFILE(FILE,S)F,U,E,T')               :(WRTFILE_END)
*
WRITEFILE
         SYSTEM() 'CSNOBOL4'                                 :S(WRFILE3)
         U = 20
         OUTPUT(.F, U, FILE)                                 :F(FRETURN)
WRFILE2  S BRKREM(CHARS_NL) . T (CHARS_NL | NULL) =
         F = T
         IDENT(S)                                  :S(RDFILE4)F(WRFILE2)
WRFILE3  U = IO_FINDUNIT()
         OUTPUT(.F, U, 'B,65536', FILE)
WRFILE4  T = LT(SIZE(S), 65536) S                            :F(WRFILE6)
         S =
WRFILE5  F = T
         IDENT(S)                                  :S(RDFILE4)F(WRFILE4)
WRFILE6  S LEN(65536) . T REM . S                             :(WRFILE5)
*
WRTFILE_END
*
* CE: .F.MSNOBOL4;
