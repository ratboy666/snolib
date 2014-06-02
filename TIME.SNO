-STITL TIME
-EJECT
*
-LINE 62 "TIME.lss"
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
-LINE 6 "TIME.lss"
         DATA('TIMEVAL(TV_SEC,TV_USEC)')
         DATA('TM(TM_SEC,TM_MIN,TM_HOUR,TM_MDAY,TM_MON,'
+                'TM_YEAR,TM_WDAY,TM_YDAY,TM_ISDST,TM_GMTOFF)')
*
         LOAD('GETTIMEOFDAY_(TIMEVAL)')
         LOAD('LOCALTIME_(INTEGER,TM)')
         LOAD('GMTIME_(INTEGER,TM)')
         LOAD('STRFTIME(STRING,TM)STRING')
         LOAD('MKTIME(TM)INTEGER')
         LOAD('SLEEP(REAL)')
         LOAD('STRPTIME_(STRING,STRING,TM)')
*
         DEFINE('GETTIMEOFDAY()TIMEVAL')             :(GETTIMEOFDAY_END)
*
GETTIMEOFDAY
         GETTIMEOFDAY = TIMEVAL()
         GETTIMEOFDAY_(GETTIMEOFDAY)                :S(RETURN)F(FRETURN)
*
GETTIMEOFDAY_END
*
         DEFINE('LOCALTIME(T)TM')                       :(LOCALTIME_END)
*
LOCALTIME
         LOCALTIME = TM()
         LOCALTIME_(T, LOCALTIME)                   :S(RETURN)F(FRETURN)
*
LOCALTIME_END
*
         DEFINE('GMTIME(T)TM')                             :(GMTIME_END)
*
GMTIME   GMTIME = TM()
         GMTIME_(T, GMTIME)                         :S(RETURN)F(FRETURN)
*
GMTIME_END
*
         DEFINE('STRPTIME(S,F)TM')                       :(STRPTIME_END)
*
STRPTIME STRPTIME = TM()
         STRPTIME_(S, F, STRPTIME)                  :S(RETURN)F(FRETURN)
*
STRPTIME_END
*
* CE: .MSNOBOL4;
