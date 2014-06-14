-MODULE BALX
-LINE 19 "BALX.lss"
-INCLUDE 'UNIQUE.INC'
-IN72
-LINE 53 "BALX.lss"
-STITL BALX
-EJECT
*
************************************************************************
*                                                                      *
*                  ######      #     #        #     #                  *
*                  #     #    # #    #         #   #                   *
*                  #     #   #   #   #          # #                    *
*                  ######   #     #  #           #                     *
*                  #     #  #######  #          # #                    *
*                  #     #  #     #  #         #   #                   *
*                  ######   #     #  #######  #     #                  *
*                                                                      *
* BALX                      BAL EXTENDED                               *
*                                                                      *
************************************************************************
*
* BALX.lss
*
-LINE 23 "BALX.lss"
-PUBLIC BALX()
*
         DEFINE('BALX(PARENS,QTS)Q,GBAL,NAME,STAR,LP,RP')    :(BALX_END)
*
BALX     NAME = UNIQUE()
         STAR = CONVERT(NAME, 'EXPRESSION')
         GBAL = NOTANY(PARENS QTS)
BALX_1   QTS LEN(1) . Q =                                     :F(BALX_2)
         GBAL = Q BREAK(Q) Q | GBAL                            :(BALX_1)
BALX_2   PARENS LEN(1) . LP  RTAB(1) . PARENS  LEN(1) . RP    :F(BALX_3)
         GBAL = LP  (STAR | NULL) RP  |  GBAL                  :(BALX_2)
BALX_3   BALX = GBAL ARBNO(GBAL)
         $NAME = BALX                                          :(RETURN)
*
BALX_END
*
* CE: .MSNOBOL4;
