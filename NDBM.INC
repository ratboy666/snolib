-STITL NDBM
-EJECT
*
-LINE 60 "NDBM.lss"
************************************************************************
*                                                                      *
*                 #     #  ######   ######   #     #                   *
*                 ##    #  #     #  #     #  ##   ##                   *
*                 # #   #  #     #  #     #  # # # #                   *
*                 #  #  #  #     #  ######   #  #  #                   *
*                 #   # #  #     #  #     #  #     #                   *
*                 #    ##  #     #  #     #  #     #                   *
*                 #     #  ######   ######   #     #                   *
*                                                                      *
* NDBM               NDBM INTERFACE FOR CSNOBOL4                       *
*                                                                      *
* PHIL BUDNE <PHIL@ULTIMATE.COM>                                       *
* DECEMBER 3, 2005                                                     *
*                                                                      *
************************************************************************
*
* NDBM.lss
*
-LINE 8 "NDBM.lss"
NDBM_LOAD
*
-PUBLIC DBM_INSERT, DBM_REPLACE
         DBM_INSERT = 0
         DBM_REPLACE = 1
*
-PUBLIC DBM_OPEN(), DBM_CLOSE()
         LOAD('DBM_OPEN(STRING,STRING,STRING)INTEGER')
         LOAD('DBM_CLOSE(INTEGER)STRING')
*
-PUBLIC DBM_STORE(), DBM_FETCH(), DBM_DELETE()
         LOAD('DBM_STORE(INTEGER,STRING,STRING,INTEGER)INTEGER')
         LOAD('DBM_FETCH(INTEGER,STRING)STRING')
         LOAD('DBM_DELETE(INTEGER,STRING)INTEGER')
*
-PUBLIC DBM_FIRSTKEY(), DBM_NEXTKEY()
         LOAD('DBM_FIRSTKEY(INTEGER)STRING')
         LOAD('DBM_NEXTKEY(INTEGER)STRING')
*
-PUBLIC DBM_ERROR(), DBM_CLEARERR()
         LOAD('DBM_ERROR(INTEGER)STRING')
         LOAD('DBM_CLEARERR(INTEGER)STRING')
*
         CODE('NDBM_LOAD')
*
* CE: .MSNOBOL4;
