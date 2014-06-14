-MODULE LPROG
-LINE 15 "LPROG.lss"
-IN72
-LINE 41 "LPROG.lss"
-STITL LPROG
-EJECT
*
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
-LINE 18 "LPROG.lss"
-PUBLIC LPROG()
*
         DEFINE('LPROG()')                                  :(LPROG_END)
*
LPROG                                :<CODE(' LPROG = &STNO :(RETURN)')>
*
LPROG_END
*
* CE: .MSNOBOL4;
