-MODULE ONCE
-LINE 13 "ONCE.lss"
-INCLUDE 'UNIQUE.INC'
-IN72
-LINE 43 "ONCE.lss"
-STITL ONCE
-EJECT
*
************************************************************************
*                                                                      *
*                  #######  #     #   #####   #######                  *
*                  #     #  ##    #  #     #  #                        *
*                  #     #  # #   #  #        #                        *
*                  #     #  #  #  #  #        #####                    *
*                  #     #  #   # #  #        #                        *
*                  #     #  #    ##  #     #  #                        *
*                  #######  #     #   #####   #######                  *
*                                                                      *
* ONCE                                                                 *
*                                                                      *
************************************************************************
*
* ONCE.lss
*
-LINE 17 "ONCE.lss"
-PUBLIC ONCE()
*
         DEFINE('ONCE(ID)NAME')                              :(ONCE_END)
ONCE     ONCE = IDENT(ID, NULL)
+               CONVERT('ONCE(' 1 ')', 'EXPRESSION')          :S(RETURN)
         NAME = UNIQUE()
         ONCE = $NAME
         $NAME = FAIL                                          :(RETURN)
*
ONCE_END
*
*
* CE: .MSNOBOL4;
