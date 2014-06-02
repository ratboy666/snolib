-STITL LIKE
-EJECT
*
-LINE 44 "LIKE.lss"
************************************************************************
*                                                                      *
*                     #        ###  #    #  #######                    *
*                     #         #   #   #   #                          *
*                     #         #   #  #    #                          *
*                     #         #   ###     #####                      *
*                     #         #   #  #    #                          *
*                     #         #   #   #   #                          *
*                     #######  ###  #    #  #######                    *
*                                                                      *
* LIKE                PATTERN TO MATCH LIKE STRING                     *
*                                                                      *
************************************************************************
*
* LIKE.lss
*
-LINE 14 "LIKE.lss"
         DEFINE('LIKE(S)C,T1,T2,N')                          :(LIKE_END)
*
LIKE     LIKE = S
LIKE_1   S TAB(N) . T1 REM . T2                               :F(RETURN)
         N = N + 1
* INSERTION OF CHARACTER AT POSITION N
         LIKE = LIKE | (T1 LEN(1) T2)
* DELETION OF CHARACTER AT POSITION N
         T2 LEN(1) . C  =                                     :F(RETURN)
         LIKE = LIKE | (T1 T2)
* TRANSPOSITION OF TWO CHARACTERS
         T2 POS(1) = C                                        :F(LIKE_1)
         LIKE = LIKE | (T1 T2)                                 :(LIKE_1)
*
LIKE_END
*
* CE: .MSNOBOL4;
