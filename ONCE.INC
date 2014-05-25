-LINE 13 "ONCE.lss"
-INCLUDE 'UNIQUE.INC'
-STITL ONCE
-EJECT
-LINE 40 "ONCE.lss"
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
         DEFINE('ONCE(ID)NAME')                              :(ONCE_END)
ONCE     ONCE = IDENT(ID, NULL)
+               CONVERT('ONCE(' 1 ')', 'EXPRESSION')          :S(RETURN)
         NAME = UNIQUE()
         ONCE = $NAME
         $NAME = FAIL                                          :(RETURN)
ONCE_END
*
*
* CE: .MSNOBOL4;
