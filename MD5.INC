-MODULE MD5
-LINE 11 "MD5.lss"
-INCLUDE 'BQ.INC'
-INCLUDE 'MKTEMP.INC'
-INCLUDE 'READFILE.INC'
-INCLUDE 'WRTFILE.INC'
-IN72
-LINE 46 "MD5.lss"
-STITL MD5
-EJECT
*
************************************************************************
*                                                                      *
*                       #     #  ######   #####                        *
*                       ##   ##  #     #  #                            *
*                       # # # #  #     #  #                            *
*                       #  #  #  #     #  #####                        *
*                       #     #  #     #      #                        *
*                       #     #  #     #      #                        *
*                       #     #  ######   #####                        *
*                                                                      *
* MD5                           MD5 HASH                               *
*                                                                      *
************************************************************************
*
* MD5.lss
*
-LINE 18 "MD5.lss"
-PUBLIC MD5()
*
         DEFINE('MD5(S)T')                                    :(MD5_END)
*
MD5      T = MKTEMP()
         WRITEFILE(T, S)
         MD5 = BQ('md5sum ' T)
         MD5 BREAK(' ') . MD5
         DELETE(T)                                             :(RETURN)
*
MD5_END
*
* CE: .MSNOBOL4;
