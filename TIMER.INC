-LINE 12 "TIMER.lss"
-INCLUDE 'SYSTEM.INC'
-INCLUDE 'RESOL.INC'
-STITL TIMER
-EJECT
-LINE 67 "TIMER.lss"
*
************************************************************************
*                                                                      *
*                 #######  ###  #     #  #######  ######               *
*                    #      #   ##   ##  #        #     #              *
*                    #      #   # # # #  #        #     #              *
*                    #      #   #  #  #  #####    ######               *
*                    #      #   #     #  #        #   #                *
*                    #      #   #     #  #        #    #               *
*                    #     ###  #     #  #######  #     #              *
*                                                                      *
* TIMER                       TIME STATEMENTS                          *
*                                                                      *
************************************************************************
*
* TIMER.lss
*
-LINE 17 "TIMER.lss"
         DEFINE('TIMER(S_,N_)C_,T_,I_')                     :(TIMER_END)
*
TIMER    EQ(N_, 0)                                           :F(TIMER_N)
         N_ = 10
TIMER_1  T_ = TIMER(' ;' S_, N_) - TIMER(, N_)               :F(FRETURN)
* WAS 20 * RESOLUTION. NOW THAT RESOLUTION IS ON THE ORDER OF 4
* MICROSECONDS, WE LOOK FOR 2000 * RESOLUTION (8 MILLISECONDS).
         N_ = LT(T_, 2000 * RESOLUTION()) N_ * 2             :S(TIMER_1)
         T_ = CONVERT(T_, 'REAL')
         OUTPUT =
         OUTPUT = 'THE STATEMENT'
         OUTPUT = S_
* CALCULATE THE TIME, AND SCALE TO MICROSECONDS, MILLISECONDS OR
* SECONDS.
         T_ = T_ / N_
         C_ = ' MILLISECONDS'
         (GE(T_, 1.0) LT(T_, 1000.0))                        :S(TIMER_2)
         C_ = GE(T_, 1000.0) ' SECONDS'
         T_ = GE(T_, 1000.0) T_ / 1000.0                     :S(TIMER_2)
         T_ = T_ * 1000.0
         C_ = ' MICROSECONDS'
TIMER_2  OUTPUT = 'REQUIRED ' T_ C_ ' +/- 10%'
+           ' TO EXECUTE IN '  SYSTEM()                        :(RETURN)
*
TIMER_N  I_ = 1
         C_ = '          COLLECT()                             ;'
+             '          TIMER = TIME()                        ;'
+             'TIMER_4   EQ(TIMER, TIME())          :S(TIMER_4);'
+             '          TIMER = TIME()                        ;'
+             'TIMER_3 ' S_                                   ';'
+             '          I_ = I_ + 1 LT(I_, ' N_ ') :S(TIMER_3);'
+             '          TIMER = TIME() - TIMER       :(RETURN)'
         C_ = CODE(C_)                                  :S<C_>F(FRETURN)
*
TIMER_END
*
* CE: .MSNOBOL4;
