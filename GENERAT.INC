-MODULE GENERAT
-INCLUDE 'UNIX.INC'
-INCLUDE 'UNIQUE.INC'
-IN72
-STITL GENERAT
-EJECT
*
************************************************************************
*                                                                      *
*                                                                      *
*     #####   #######  #     #  #######  ######      #     #######     *
*    #     #  #        ##    #  #        #     #    # #       #        *
*    #        #        # #   #  #        #     #   #   #      #        *
*    #  ####  #####    #  #  #  #####    ######   #     #     #        *
*    #     #  #        #   # #  #        #   #    #######     #        *
*    #     #  #        #    ##  #        #    #   #     #     #        *
*     #####   #######  #     #  #######  #     #  #     #     #        *
*                                                                      *
* GENERAT                      GENERATOR                               *
*                                                                      *
************************************************************************
*
* USE FORK() AND PIPE() TO ESTABLISH A CLOSURE THAT IS USED AS A
* GENERATOR. EACH CALL TO GETNEXT() RETURNS THE NEXT RESULT OF THE
* GENERATOR. INJECT() CAN BE USED TO MANIPULATE THE GENERATOR. THE
* GENERATOR CAN USE YIELD() TO RETURN A RESULT. THROW() WILL CAUSE AN
* EXCEPTION TO BE THROWN, AND THE SUBPROCESS WILL BE EXITED. IF THE
* GENERATOR RETURNS, IT WILL BE TERMINATED.
*
         DATA('SBLOCK(PIPE1,PIPE2,UNITS,IOVS,PID)')
*
-PUBLIC GENERATOR(), YIELD(), GETNEXT(), INJECT(), END_GENERATOR()
-PUBLIC THROW()
*
         DEFINE('GENERATOR(E)S')
         DEFINE('YIELD(RESULT)')
         DEFINE('GETNEXT(G)S')
         DEFINE('INJECT(G,E)')
         DEFINE('THROW(EXCEPTION)')
         DEFINE('END_GENERATOR(G)')                     :(EXCEPTION_END)
*
THROW    IOVS(GENERATOR)<4> = 'EXCEPTION'
         IOVS(GENERATOR)<4> = EXCEPTION
         IOVS(GENERATOR)<4> = 'COMPLETE'
         EXIT(0)                                               :(RETURN)
*
INJECT   IOVS(G)<2> = 'EVAL'
         IOVS(G)<2> = E                                        :(RETURN)
*
END_GENERATOR
         KILL(PID(G), 1)
         WAITPID(PID(G))
         ENDFILE(UNITS(G)<1>)
         ENDFILE(UNITS(G)<2>)
         ENDFILE(UNITS(G)<3>)
         ENDFILE(UNITS(G)<4>)
         DETACH(.(IOVS(G)<1>))
         DETACH(.(IOVS(G)<2>))
         DETACH(.(IOVS(G)<3>))
         DETACH(.(IOVS(G)<4>))
         UNITS(G) =
         IOVS(G) =
         PIPE1(G) =
         PIPE2(G) =                                            :(RETURN)
*
GENERATOR
         GENERATOR = SBLOCK(PIPE(), PIPE(), ARRAY(4), ARRAY(4))
*
* FOUR UNITS - TWO FOR EACH PIPE (READ/WRITE)
*
         UNITS(GENERATOR)<1> = IO_FINDUNIT() ;* SLAVE
         UNITS(GENERATOR)<2> = IO_FINDUNIT() ;* MASTER
         UNITS(GENERATOR)<3> = IO_FINDUNIT() ;* MASTER
         UNITS(GENERATOR)<4> = IO_FINDUNIT() ;* SLAVE
*
* FOUR NAMES - ONE FOR EACH PIPE END. FIXME: NOT ALL FOUR UNITS ARE
* NEEDED IN THE MASTER.
*
         IOVS(GENERATOR)<1> = UNIT_NAME(UNITS(GENERATOR)<1>)
         IOVS(GENERATOR)<2> = UNIT_NAME(UNITS(GENERATOR)<2>)
         IOVS(GENERATOR)<3> = UNIT_NAME(UNITS(GENERATOR)<3>)
         IOVS(GENERATOR)<4> = UNIT_NAME(UNITS(GENERATOR)<4>)
*
* I/O ASSOCIATE EACH PIPE END
*
         OUTPUT(.(IOVS(GENERATOR)<2>), UNITS(GENERATOR)<2>, 'W',
+           '/dev/fd/' PIPE1(GENERATOR)<2>)
         INPUT(.(IOVS(GENERATOR)<1>), UNITS(GENERATOR)<1>,,
+           '/dev/fd/' PIPE1(GENERATOR)<1>)
         OUTPUT(.(IOVS(GENERATOR)<4>), UNITS(GENERATOR)<4>, 'W',
+           '/dev/fd/' PIPE2(GENERATOR)<2>)
         INPUT(.(IOVS(GENERATOR)<3>), UNITS(GENERATOR)<3>,,
+           '/dev/fd/' PIPE2(GENERATOR)<1>)
*
* FORK() THE PROCESS TO CREATE THE GENERATOR
*
         PID(GENERATOR) = FORK()
*
* THE MAIN PROCESS RETURNS
*
         NE(PID(GENERATOR))                                   :S(RETURN)
*
* IN THE SLAVE. WE WAIT FOR THE 'GO' FROM THE MAIN PROCESS. WE CAN THEN
* EXECUTE THE GENERATOR. ON RETURN FROM THE GENERATOR, WE INDICATE
* COMPLETION. ON YIELD() WE WRITE THE NEXT RESULT WHICH IS READ IN
* GETNEXT(). YIELD() COMPLETES BY WAITING FOR THE NEXT 'GO'.
*
GENERATOR_2
         IOVS(GENERATOR)<1> 'EVAL'                       :F(GENERATOR_3)
         EVAL(IOVS(GENERATOR)<1>)                         :(GENERATOR_2)
GENERATOR_3
*
* WHEN WE GET 'GO', EXECUTE THE GENERATOR. THIS WILL CALL YIELD(), OR
* RETURN. ON RETURN, THE GENERATOR IS COMPLETE, SO WRITE 'COMPLETE' TO
* THE MASTER.
*
         EVAL(E)
         IOVS(GENERATOR)<4> = 'COMPLETE'
         EXIT(0)
*
* GENERATOR IS STILL IN SCOPE: WE DON'T NEED TO PASS IN THE GENERATOR.
* WRITE 'RESULT' AND THE RESULT TO THE MASTER.
*
YIELD    IOVS(GENERATOR)<4> = 'RESULT'
         IOVS(GENERATOR)<4> = RESULT
*
* WAIT FOR NEXT 'GO'.
*
YIELD_2  IOVS(GENERATOR)<1> 'EVAL'                            :F(RETURN)
         EVAL(IOVS(GENERATOR)<1>)                             :(YIELD_2)
*
* SUBPROCESS IS ALLOWED TO EXECUTE, UNTIL YIELD() OR TERMINATION
*
GETNEXT  IOVS(G)<2> = 'GO'
*
* READ RESULT. IF THE SUBPROCESS IS COMPLETE WE REAP. GETNEXT() FAILS ON
* COMPLETION OF THE GENERATOR -- END_GENERATOR() IS WHERE THE REAPING
* HAPPENS.
*
         S = IOVS(G)<3>
         S 'RESULT'                                        :F(GETNEXT_2)
         GETNEXT = IOVS(G)<3>                                  :(RETURN)
GETNEXT_2
         EXCEPTION =
         S 'EXCEPTION'                                       :F(FRETURN)
         EXCEPTION = IOVS(G)<3>                               :(FRETURN)

*
EXCEPTION_END
*
* CE: .MSNOBOL4;
