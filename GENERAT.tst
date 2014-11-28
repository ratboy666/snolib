-INCLUDE 'GENERAT.INC'
-INCLUDE 'TIMER.INC'
*
         TERMINAL = 'GENERAT (TUE NOV 25 13:15:20 EST 2014)'
*
* G = GENERATOR('EVAL')
* V = GETNEXT(G) :F(DONE)
* YIELD(V)
* END_GENERATOR(G)
* INJECT(G, 'EVAL')
*
*        DDT()
         DEFINE('F(X)')
         DEFINE('F2(X)')
*
* TIME THE CREATION AND DESTRUCTION OF A GENERATOR. 720 MICROSECONDS
* ON THE INTEL I3.
*
         TIMER(' G = GENERATOR("F(0)"); END_GENERATOR(G); ')
*
* CREATE THE GENERATOR
*
         G = GENERATOR('F(0)')
*
* TIME A SIMPLE FUNCTION CALL. 500 NANOSECONDS ON THE INTEL I3.
*
         TIMER(' F2(0) ')
*
* TIME THE GENERATOR. 20 MICROSECONDS ON THE INTEL I3.
*
         TIMER(' GETNEXT(G) ')
*
* RESET VARIABLE X IN THE GENERATOR. THIS SETS THE LOCAL VARIABLE X
* WITHIN THE F() FUNCTION.
*
         INJECT(G, ' X = 0 ')
TOP      L = GETNEXT(G)
         OUTPUT = L
         LT(L, 10)                                               :F(BTM)
                                                                  :(TOP)
*
* END THE GENERATOR. THIS CLEANS UP THE SUBPROCESS AND THE FILE UNITS
* USED TO COMMUNICATE WITH IT
*
BTM      END_GENERATOR(G)
 :(END)
*
F        X = X + 1
         YIELD(X)                                                   :(F)
*
F2       X = X + 1
         F2 = X   :(RETURN)
*
* CE: .MSNOBOL4;
*
END
