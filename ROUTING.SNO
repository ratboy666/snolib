-LINE 16 "ROUTING.lss"
-INCLUDE 'BRKREM.INC'
-INCLUDE 'SDIFF.INC'
-INCLUDE 'UNIQUE.INC'
-STITL ROUTING
-EJECT
-LINE 124 "ROUTING.lss"
*
************************************************************************
*                                                                      *
*      ######   #######  #     #  #######  ###  #     #   #####        *
*      #     #  #     #  #     #     #      #   ##    #  #     #       *
*      #     #  #     #  #     #     #      #   # #   #  #             *
*      ######   #     #  #     #     #      #   #  #  #  #  ####       *
*      #   #    #     #  #     #     #      #   #   # #  #     #       *
*      #    #   #     #  #     #     #      #   #    ##  #     #       *
*      #     #  #######   #####      #     ###  #     #   #####        *
*                                                                      *
* ROUTING                   ROUTING FOR CGI                            *
*                                                                      *
************************************************************************
*
* ROUTING.lss
*
-LINE 22 "ROUTING.lss"
-MODULE ROUTING
-PUBLIC ROUTING_INIT(), ROUTING_ADD(), ROUTING()
         DEFINE('ROUTING_INIT()')
         DEFINE('ROUTING_ADD(ROUTE,PATTERN,ACTION_)NAME,P')
         DEFINE('ROUTING(METHOD,ROUTE,VARS_)P,S')
*
         ROUTING_VAR = ':'
         ROUTING_NAME_C = &UCASE &LCASE '0123456789' '._'
         ROUTING_NAME = SDIFF(&ALPHABET, &UCASE &LCASE '0123456789._')
         MAKE_UNIQUE('ROUTING')
*
                                                          :(ROUTING_END)
*
* INITIALIZE ROUTE. THE INITIAL ROUTE ALWAYS FAILS.
*
ROUTING_INIT
         UNIQUE_ROUTING('CLEAR')
         ROUTING_INIT = ABORT                                  :(RETURN)
*
* ADD PATTERN TO ROUTE, WITH ACTION. ON MATCH, YIELDS ACTION, AND
* SUCCESS.
*
ROUTING_ADD
         NAME = UNIQUE_ROUTING()
         $NAME = ACTION_
         P = EVAL('PATTERN *?(ACTION = ' NAME ')')
         ROUTING_ADD = P | ROUTE                               :(RETURN)
*
* MAKE A ROUTING PATTERN. METHOD WILL BE SOMETHING LIKE 'GET', 'POST',
* '', ('GET' | 'POST'). ROUTE WILL BE '/A/B/C', '/A/:VAR/C'
*
ROUTING  METHOD = IDENT(METHOD) BREAK('\')
ROUTE_3  ROUTE POS(0) BRKREM(ROUTING_VAR) . S =
         P = DIFFER(S) P S
         IDENT(ROUTE)                                        :S(ROUTE_9)
         ROUTE POS(0) LEN(1) BRKREM(ROUTING_NAME) . S =
         IDENT(S)                                            :S(ROUTE_3)
         ROUTE LEN(1) . B =                                  :F(ROUTE_4)
         P = P BREAK(B) . ($VARS_)<S> B                       :(ROUTE_3)
ROUTE_4  P = P REM . ($VARS_)<S>
ROUTE_9  ROUTING = METHOD '\' P                                :(RETURN)
*
ROUTING_END
*
*
* CE: .F.MSNOBOL4;
