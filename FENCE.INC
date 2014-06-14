-MODULE FENCE
-LINE 34 "FENCE.lss"
-INCLUDE 'UNIQUE.INC'
-IN72
-LINE 64 "FENCE.lss"
-STITL FENCE
-EJECT
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
-PUBLIC FENCE()
*
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
