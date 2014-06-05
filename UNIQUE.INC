-LINE 25 "UNIQUE.lss"
-INCLUDE 'REPL.INC'
-STITL UNIQUE
-EJECT
-LINE 74 "UNIQUE.lss"
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
-LINE 29 "UNIQUE.lss"
-MODULE UNIQUE
-PUBLIC MAKE_UNIQUE(), UNIQUE()
         DEFINE('MAKE_UNIQUE(SUF)S')
         MAKE_UNIQUE()
         OPSYN('UNIQUE', 'UNIQUE_')                        :(UNIQUE_END)
*
MAKE_UNIQUE
         S =
+ 'UNIQUE_SUF  UNIQUE_SUF_ = IDENT(I) UNIQUE_SUF_ + 1  :F(UNIQUECSUF);'
+ '            UNIQUE_SUF = "USUF" UNIQUE_SUF_ "_"          :(RETURN);'
+ 'UNIQUECSUF $("USUF" UNIQUE_SUF_ "_") = '
+ '           ?(UNIQUE_SUF_ = GT(UNIQUE_SUF_,0) UNIQUE_SUF_ - 1)'
+ '                                           :S(UNIQUECSUF)F(RETURN);'
         CODE(REPL(S, 'SUF', SUF))
         DEFINE('UNIQUE_' SUF '(I)')                           :(RETURN)
*
UNIQUE_END
*
* CE: .MSNOBOL4;
