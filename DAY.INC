-MODULE DAY
-LINE 10 "DAY.lss"
-IN72
-LINE 59 "DAY.lss"
-STITL DAY
-EJECT
*
************************************************************************
*                                                                      *
*                      ######      #     #     #                       *
*                      #     #    # #     #   #                        *
*                      #     #   #   #     # #                         *
*                      #     #  #     #     #                          *
*                      #     #  #######     #                          *
*                      #     #  #     #     #                          *
*                      ######   #     #     #                          *
*                                                                      *
* DAY                         DAY OF WEEK                              *
*                                                                      *
************************************************************************
*
* DAY.lss
*
-LINE 13 "DAY.lss"
-PUBLIC DAY()
*
         DEFINE('DAY(DATE)M,Y,CD')
         YEAR_ = 365
         YEAR_4 = 4 * YEAR_ + 1
         CENT_ = (25 * YEAR_4) - 1
         CENT_4 = 4 * CENT_ + 1
         DAY_ZERO = 2                                         :(DAY_END)
*
DAY      CD = DATE()
         DIFFER(DATE)                                          :S(DAY_3)
* IF NO DATE GIVEN, USE TODAY
         CD ARB . DATE ' '
DAY_3    DATE BREAK('/') . M LEN(1)
+           (BREAK('/') . D LEN(1) REM . Y | REM . D)
* IF NO YEAR GIVEN, USE THIS YEAR
         (IDENT(Y) CD) '/' ARB '/' LEN(4) . Y
* TWO DIGIT YEAR IS 20XX
         Y = EQ(SIZE(Y), 2) '20' Y
         M = LE(M, 2) M + 12                                   :F(DAY_1)
         Y = Y - 1
DAY_1    M = M - 3
DAY_2    DAY = (Y / 400) * CENT_4 + (REMDR(Y, 400) / 100) * CENT_
+           +  (REMDR(Y, 100) / 4) * YEAR_4 +  REMDR(Y, 4) * YEAR_
         DAY = DAY + ((153 * M) + 2) / 5 + D + DAY_ZERO
         D = REMDR(DAY, 7)
         '0SUN1MON2TUES3WEDNES4THURS5FRI6SATUR7'
+           D BREAK('01234567') . DAY
         DAY = DAY 'DAY'                                       :(RETURN)
*
DAY_END
*
* CE: .MSNOBOL4;
