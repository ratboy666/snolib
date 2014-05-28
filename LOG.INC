-LINE 12 "LOG.lss"
-INCLUDE 'DEXP.INC'
-STITL LOG
-EJECT
-LINE 32 "LOG.lss"
*
************************************************************************
*                                                                      *
*                      #        #######   #####                        *
*                      #        #     #  #     #                       *
*                      #        #     #  #                             *
*                      #        #     #  #  ####                       *
*                      #        #     #  #     #                       *
*                      #        #     #  #     #                       *
*                      #######  #######   #####                        *
*                                                                      *
* LOG                       LOG FUNCTIONS                              *
*                                                                      *
************************************************************************
*
* LOG.lss
*
* CONSTANTS TO 50 PLACES
*
* SEE
* http://numbers.computation.free.fr/Constants/Miscellaneous/digits.html
*
         LN_10    =
+                   2.30258509299404568401799145468436420760110148862877
         EULERS_NUMBER =
+                   2.71828182845904523536028747135266249775724709369995
         PI =
+                   3.14159265358979323846264338327950288419716939937510
*
         DEXP('CLOG(X) = LN(X) / LN_10')
         DEXP('LOGB(X,B) = NE(B, 0) LN(X) / LN(B) ;'
+             'LOGB      = EQ(B, 0) LN(X)         ;')
*
LOG_END
*
* CE: .MSNOBOL4;
