-STITL TIME
-EJECT
*
-LINE 78 "TIME.lss"
************************************************************************
*                                                                      *
*                    #######  ###  #     #  #######                    *
*                       #      #   ##   ##  #                          *
*                       #      #   # # # #  #                          *
*                       #      #   #  #  #  #####                      *
*                       #      #   #     #  #                          *
*                       #      #   #     #  #                          *
*                       #     ###  #     #  #######                    *
*                                                                      *
* TIME                    DATE/TIME FUNCTIONS                          *
*                                                                      *
* PHILE BUDNE <PHIL@ULTIMATE.COM>                                      *
* DECEMBER 15, 2010                                                    *
*                                                                      *
************************************************************************
*
* TIME.lss
*
-LINE 11 "TIME.lss"
-MODULE TIME
-PUBLIC TIMEVAL(), TV_SEC(), TV_USEC()
         DATA('TIMEVAL(TV_SEC,TV_USEC)')
-PUBLIC TM(), TM_SEC(), TM_MIN(), TM_HOUR(), TM_MDAY(), TM_MON()
-PUBLIC TM_YEAR(), TM_WDAY(), TM_YDAY(), TM_ISDST(), TM_GMTOFF()
         DATA('TM(TM_SEC,TM_MIN,TM_HOUR,TM_MDAY,TM_MON,'
+                'TM_YEAR,TM_WDAY,TM_YDAY,TM_ISDST,TM_GMTOFF)')
*
         LOAD('GETTIMEOFDAY_(TIMEVAL)')
         LOAD('LOCALTIME_(INTEGER,TM)')
         LOAD('GMTIME_(INTEGER,TM)')
-PUBLIC STRFTIME()
         LOAD('STRFTIME(STRING,TM)STRING')
-PUBLIC MKTIME()
         LOAD('MKTIME(TM)INTEGER')
-PUBLIC SLEEP()
         LOAD('SLEEP(REAL)')
         LOAD('STRPTIME_(STRING,STRING,TM)')
*
-PUBLIC GETTIMEOFDAY()
         DEFINE('GETTIMEOFDAY()TIMEVAL')             :(GETTIMEOFDAY_END)
*
GETTIMEOFDAY
         GETTIMEOFDAY = TIMEVAL()
         GETTIMEOFDAY_(GETTIMEOFDAY)                :S(RETURN)F(FRETURN)
*
GETTIMEOFDAY_END
*
-PUBLIC LOCALTIME()
         DEFINE('LOCALTIME(T)TM')                       :(LOCALTIME_END)
*
LOCALTIME
         LOCALTIME = TM()
         LOCALTIME_(T, LOCALTIME)                   :S(RETURN)F(FRETURN)
*
LOCALTIME_END
*
-PUBLIC GMTIME()
         DEFINE('GMTIME(T)TM')                             :(GMTIME_END)
*
GMTIME   GMTIME = TM()
         GMTIME_(T, GMTIME)                         :S(RETURN)F(FRETURN)
*
GMTIME_END
*
-PUBLIC STRPTIME()
         DEFINE('STRPTIME(S,F)TM')                       :(STRPTIME_END)
*
STRPTIME STRPTIME = TM()
         STRPTIME_(S, F, STRPTIME)                  :S(RETURN)F(FRETURN)
*
STRPTIME_END
*
* CE: .MSNOBOL4;
