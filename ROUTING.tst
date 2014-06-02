#!/usr/bin/bash
         exec "/usr/local/bin/snobol4" "-b" "$0" "$@"
-INCLUDE 'ROUTING.INC'
-LINE 71 "ROUTING.lss"
-INCLUDE 'DDT.INC'
*
         &CODE = 1
         ROUTING = ROUTING_INIT()
         ROUTING = ROUTING_ADD(ROUTING, 'A', 'ACTION 1')
         ROUTING = ROUTING_ADD(ROUTING, 'B', 'ACTION 2')
         &FULLSCAN = 1
         ACTION =
         'A' ROUTING
         OUTPUT = ACTION
         ACTION =
         'B' ROUTING
         OUTPUT = ACTION
*
* TEST COMPILING ROUTES
*
* V IS A TABLE THAT WILL STORE THE VARIABLES. METHOD WILL BE SEPARATED
* FROM PATH_INFO WITH A '\'.
*
***         DDT()
         V = TABLE()
         P = ROUTING('', '/A/B', .V)
         V = TABLE()
         '\/A/B' P :F(NOTOK)
         'POST\/A/B' P :F(NOTOK)
*
         P = ROUTING('', ':VAR', .V)
         '\/A/B' P :F(NOTOK)
         OUTPUT = V<'VAR'>
*
         P = ROUTING('', '/:VAR', .V)
         'POST\/A/B' P :F(NOTOK)
         OUTPUT = V<'VAR'>
*
         P = ROUTING('', '/:VARA/B', .V)
         '\/A/B' P :F(NOTOK)
         OUTPUT = V<'VARA'>
*
         P = ROUTING(('GET' | 'POST'), '/:VARA/:VARB', .V)
         'GET\/A/B' P :F(NOTOK)
         OUTPUT = V<'VARA'> ' ' V<'VARB'>
*
         &CODE = 0 :(END)
NOTOK    OUTPUT = 'NOT OK'
*
END
