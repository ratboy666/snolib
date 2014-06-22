-MODULE REAL
-STITL REAL
*
************************************************************************
*                                                                      *
*                  ######   #######     #     #                        *
*                  #     #  #          # #    #                        *
*                  #     #  #         #   #   #                        *
*                  ######   #####    #     #  #                        *
*                  #   #    #        #######  #                        *
*                  #    #   #        #     #  #                        *
*                  #     #  #######  #     #  #######                  *
*                                                                      *
* REAL                 FASBOL II REAL PREDICATE                        *
*                                                                      *
************************************************************************
*
* REAL.INC
*
         DEFINE('REAL(X)')                                   :(END_REAL)
*
REAL     IDENT(DATATYPE(X), 'REAL')                            :(RETURN)
         INTEGER(X)                                          :S(FRETURN)
         (IDENT(DATATYPE(X), 'STRING') CONVERT(X, 'REAL'))
+                                                   :S(RETURN)F(FRETURN)        
*
END_REAL
*
* CE: .MSNOBOL4;
*
