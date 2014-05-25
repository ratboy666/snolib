-LINE 24 "UNIQUE.lss"
-INCLUDE 'REPL.INC'
-STITL UNIQUE
-EJECT
-LINE 70 "UNIQUE.lss"
*
************************************************************************
*                                                                      *
*           #     #  #     #  ###   #####   #     #  #######           *
*           #     #  ##    #   #   #     #  #     #  #                 *
*           #     #  # #   #   #   #     #  #     #  #                 *
*           #     #  #  #  #   #   #     #  #     #  #####             *
*           #     #  #   # #   #   #   # #  #     #  #                 *
*           #     #  #    ##   #   #    #   #     #  #                 *
*            #####   #     #  ###   #### #   #####   #######           *
*                                                                      *
* UNIQUE                 GENERATE UNIQUE NAME                          *
*                                                                      *
************************************************************************
*
* UNIQUE.lss
*
-LINE 28 "UNIQUE.lss"
         DEFINE('MAKE_UNIQUE(SUF)S')
         MAKE_UNIQUE()                                     :(UNIQUE_END)
*
MAKE_UNIQUE
         S =
+ 'UNIQUESUF  UNIQUESUF_ = IDENT(I) UNIQUESUF_ + 1 :F(UNIQUECSUF);'
+ '           UNIQUESUF = "USUF" UNIQUESUF_ "_"         :(RETURN);'
+ 'UNIQUECSUF $("USUF" UNIQUESUF_ "_") = '
+ '           ?(UNIQUESUF_ = GT(UNIQUESUF_,0) UNIQUESUF_ - 1)'
+ '                                       :S(UNIQUECSUF)F(RETURN);'
         CODE(REPL(S, 'SUF', SUF))
         DEFINE('UNIQUE' SUF '(I)')                            :(RETURN)
*
UNIQUE_END
*
* CE: .MSNOBOL4;
