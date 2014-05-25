#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'TIMER.INC'
-LINE 251 "PSQL.lss"
-INCLUDE 'PSQL.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'BQ.INC'
-INCLUDE 'DDT.INC'
*        DDT()
         &CODE = 1
*
* CREATE THE PSQL OBJECT
*
         PSQL = SEND(PSQL_CLASS, 'NEW')
*
* OPEN THE PSQL CONNECTION. NOTE THE &ERRLIMIT SETTING TO PREVENT
* PROBLEMS IF THE POSTGRESQL SERVER CANNOT BE REACHED.
*
         &ERRLIMIT = 1
         SEND(PSQL, 'OPEN')
*
* GET THE PIPE NAME CONNECTING TO PSQL
*
         P = SEND(PSQL, 'GET_PIPE')
*
* A SIMPLE PSQL COMMAND
*
         $P = "SELECT version();"                                :F(END)
         OUTPUT = SEND(PSQL, 'OUTPUT')                           :F(END)
*
* ANOTHER COMMAND
*
         $P = "SELECT 1 + 1;"                                    :F(END)
         OUTPUT = SEND(PSQL, 'OUTPUT')                           :F(END)
*
* CREATE THE WEATHER TABLE. DROP IT FIRST IN CASE IT EXISTS
*
         $P = "DROP TABLE weather;"                              :F(END)
         SEND(PSQL, 'DISCARD')                                   :F(END)
         $P = "CREATE TABLE weather ("
         $P = "  city    VARCHAR(80),"
         $P = "  temp_lo INT,         -- low temperature"
         $P = "  temp_hi INT,         -- high temperature"
         $P = "  prcp    REAL,        -- precipitation"
         $P = "  date    DATE"
         $P = ");"
         SEND(PSQL, 'DISCARD')                                   :F(END)
*
* INSERT TWO ROWS INTO THE WEATHER TABLE
*
         $P = "INSERT INTO weather"                              :F(END)
         $P = PSQL_INSERT(
+           #("city=San Francisco,temp_lo=46,temp_hi=50,prcp=0.25,"
+           "date=1994-11-27")) ";"                              :F(END)
         SEND(PSQL, 'DISCARD')                                   :F(END)
         $P = "INSERT INTO weather"                              :F(END)
         $P = PSQL_INSERT(
+           #"city=Hayward,temp_lo=37,temp_hi=55,date=1994-11-29")
+           ";"                                                  :F(END)
         SEND(PSQL, 'DISCARD')                                   :F(END)
*
* SELECT FROM WEATHER TABLE, FOR A CITY THAT DOESN'T EXIST. WE EXPECT
* NO RESULTS FROM THIS
*
         $P = "SELECT * FROM weather"                            :F(END)
         $P = "WHERE city = 'xx';"                               :F(END)
         S = SEND(PSQL, 'OUTPUT')                                :F(END)
         IDENT(S)                                                :F(END)
*
* SELECT EVERYTHING FROM TABLE WEATHER. WE EXPECT TWO ROWS. NOTE THE
* USE OF PSQL_INSERT() TO FORMAT A ROW FOR DEBUG DISPLAY
*
         $P = "SELECT * FROM weather;"                           :F(END)
         R = PSQL_RESULT(SEND(PSQL, 'OUTPUT'))                   :F(END)
         EQ(PROTOTYPE(R), 2)                                     :F(END)
         OUTPUT = PSQL_INSERT(R<1>)                              :F(END)
         OUTPUT = PSQL_INSERT(R<2>)                              :F(END)
*
* USE 'AS' TO NAME A RESULT COLUMNS. RETRIEVE THE RESULT AND DISPLAY
*
         $P = 'SELECT 1 + 1 AS result;'                          :F(END)
         T = PSQL_RESULT(SEND(PSQL, 'OUTPUT'))                   :F(END)
         EQ(T<1><'result'>, 2)                                   :F(END)
         OUTPUT = T<1><'result'>
*
* SOME TIMING
*
* TIME SIMPLE SELECT AND RESULT ANALYSIS
*
         TIMER(" $P = 'SELECT 1 + 1 AS result;'; "
+              " T = PSQL_RESULT(SEND(PSQL, 'OUTPUT')) ")
*
* A SIMPLE SELECT, DISCARDING RESULTS
*
         TIMER(" $P = 'SELECT 1 + 1 AS result;'; "
+              " SEND(PSQL, 'DISCARD') ")
*
* A TABLE SELECT, AND RESULT ANALYSIS
*
         TIMER(" $P = 'SELECT * FROM weather;'; "
+              " R = PSQL_RESULT(SEND(PSQL, 'OUTPUT')) ")
*
* A TABLE SELECT, DISCARDING RESULTS
*
         TIMER(" $P = 'SELECT * FROM weather;'; "
+              " SEND(PSQL, 'DISCARD') ")
*
* DROP THE WEATHER TABLE
*
         $P = "DROP TABLE weather;"                              :F(END)
         SEND(PSQL, 'DISCARD')                                   :F(END)
*
* CLOSE PSQL, FREEING THE PIPE AND UNIT
*
         SEND(PSQL, 'CLOSE')                                     :F(END)
*
* SEE IF WE HAVE ANY ZOMBIES
*
         OUTPUT = BQ('ps ax | grep " Z "')
         &CODE = 0
END
