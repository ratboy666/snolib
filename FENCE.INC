-LINE 34 "FENCE.lss"
-INCLUDE 'UNIQUE.INC'
-STITL FENCE
-EJECT
-LINE 62 "FENCE.lss"
*
************************************************************************
*                                                                      *
*             #######  #######  #     #   #####   #######              *
*             #        #        ##    #  #     #  #                    *
*             #        #        # #   #  #        #                    *
*             #####    #####    #  #  #  #        #####                *
*             #        #        #   # #  #        #                    *
*             #        #        #    ##  #     #  #                    *
*             #        #######  #     #   #####   #######              *
*                                                                      *
************************************************************************
*
* FENCE.lss
*
-LINE 38 "FENCE.lss"
        DEFINE('FENCE(P)N')                                 :(FENCE_END)
*
FENCE   N = UNIQUE()
        FENCE = EVAL('@' N
+                    ' P '
+                    ' "" $ *$(.' N ' DIFFER(' N '))'
+                   )                                          :(RETURN)
*
FENCE_END
*
* CE: .MSNOBOL4;
