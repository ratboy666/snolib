-STITL LPROG
-EJECT
*
-LINE 42 "LPROG.lss"
************************************************************************
*                                                                      *
*               #        ######   ######   #######   #####             *
*               #        #     #  #     #  #     #  #     #            *
*               #        #     #  #     #  #     #  #                  *
*               #        ######   ######   #     #  #  ####            *
*               #        #        #   #    #     #  #     #            *
*               #        #        #    #   #     #  #     #            *
*               #######  #        #     #  #######   #####             *
*                                                                      *
* LPROG                    LENGTH OF PROGRAM                           *
*                                                                      *
************************************************************************
*
* LPROG.lss
*
-LINE 19 "LPROG.lss"
-MODULE LPROG
-PUBLIC LPROG()
         DEFINE('LPROG()')                                  :(LPROG_END)
*
LPROG                                :<CODE(' LPROG = &STNO :(RETURN)')>
*
LPROG_END
*
* CE: .MSNOBOL4;
