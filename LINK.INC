-STITL LINK
-EJECT
*
-LINE 56 "LINK.lss"
************************************************************************
*                                                                      *
*                    #        ###  #     #  #    #                     *
*                    #         #   ##    #  #   #                      *
*                    #         #   # #   #  #  #                       *
*                    #         #   #  #  #  ###                        *
*                    #         #   #   # #  #  #                       *
*                    #         #   #    ##  #   #                      *
*                    #######  ###  #     #  #    #                     *
*                                                                      *
* LINK                        LINK TYPE                                *
*                                                                      *
************************************************************************
*
* LINK.lss
*
-LINE 8 "LINK.lss"
         DATA('LINK(VALUE,NEXT)')
         OPSYN('CONS', 'LINK')
         OPSYN('CAR', 'VALUE')
         OPSYN('CDR', 'NEXT')
         DEFINE('CAAR(L)')
         DEFINE('CDAR(l)')
         DEFINE('CADR(L)')
         DEFINE('CDDR(L)')
         DEFINE('CAAAR(L)')
         DEFINE('CAADR(L)')
         DEFINE('CADAR(L)')
         DEFINE('CADDR(L)')
         DEFINE('CDAAR(L)')
         DEFINE('CDADR(L)')
         DEFINE('CDDAR(L)')
         DEFINE('CDDDR(L)')
                                                             :(LINK_END)
*
CAAAR    CAAAR = CAR(CAAR(L))                                  :(RETURN)
CAADR    CAADR = CAR(CADR(L))                                  :(RETURN)
CADAR    CADAR = CAR(CDAR(L))                                  :(RETURN)
CADDR    CADDR = CAR(CDDR(L))                                  :(RETURN)
CDAAR    CDAAR = CDR(CAAR(L))                                  :(RETURN)
CDADR    CDADR = CDR(CADR(L))                                  :(RETURN)
CDDAR    CDDAR = CDR(CDAR(L))                                  :(RETURN)
CDDDR    CDDDR = CDR(CDDR(L))                                  :(RETURN)
*
CAAR     CAAR = CAR(CAR(L))                                    :(RETURN)
CDAR     CDAR = CDR(CAR(L))                                    :(RETURN)
CADR     CADR = CAR(CDR(L))                                    :(RETURN)
CDDR     CDDR = CDR(CDR(L))                                    :(RETURN)
*
LINK_END
*
* CE: .MSNOBOL4;