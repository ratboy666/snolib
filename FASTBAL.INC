-LINE 20 "FASTBAL.lss"
-INCLUDE 'UNIQUE.INC'
-STITL FASTBAL
-EJECT
-LINE 98 "FASTBAL.lss"
*
************************************************************************
*                                                                      *
*    #######     #      #####   #######  ######      #     #           *
*    #          # #    #     #     #     #     #    # #    #           *
*    #         #   #   #           #     #     #   #   #   #           *
*    #####    #     #   #####      #     ######   #     #  #           *
*    #        #######        #     #     #     #  #######  #           *
*    #        #     #  #     #     #     #     #  #     #  #           *
*    #        #     #   #####      #     ######   #     #  #######     *
*                                                                      *
* FASTBAL                                                              *
*                                                                      *
************************************************************************
*
* FASTBAL.lss
*
-LINE 24 "FASTBAL.lss"
-PUBLIC FASTBAL()
         DEFINE('FASTBAL(PARENS,QTS,S)NAME,IBAL,SPCHARS,ELEM'
+               ',LPS,Q,LP,RP')                           :(FASTBAL_END)
*
FASTBAL  NAME = UNIQUE()
         IBAL = CONVERT(NAME, 'EXPRESSION')
         IBAL = DIFFER(S, NULL) FASTBAL(PARENS, QTS)
         SPCHARS = PARENS QTS S
-LINE 39 "FASTBAL.lss"
         ELEM = NOTANY(PARENS QTS) BREAK(SPCHARS)
-LINE 47 "FASTBAL.lss"
FASTBAL_1
         QTS LEN(1) . Q  =                                 :F(FASTBAL_2)
         ELEM = Q BREAK(Q) Q | ELEM                         :(FASTBAL_1)
-LINE 58 "FASTBAL.lss"
FASTBAL_2
         PARENS LEN(1) . LP RTAB(1) . PARENS LEN(1) . RP   :F(FASTBAL_3)
         ELEM = LP IBAL RP | ELEM                           :(FASTBAL_2)
-LINE 78 "FASTBAL.lss"
FASTBAL_3
         FASTBAL = BREAK(SPCHARS) ARBNO(ELEM)
         $NAME = FASTBAL                                       :(RETURN)
*
FASTBAL_END
*
* CE: .MSNOBOL4;
