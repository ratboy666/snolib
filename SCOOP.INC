-LINE 104 "SCOOP.lss"
-INCLUDE 'VDIFFER.INC'
-EJECT
-STITL SCOOP
-LINE 298 "SCOOP.lss"
-EJECT
*
************************************************************************
*                                                                      *
*              #####    #####   #######  #######  ######               *
*             #     #  #     #  #     #  #     #  #     #              *
*             #        #        #     #  #     #  #     #              *
*              #####   #        #     #  #     #  ######               *
*                   #  #        #     #  #     #  #                    *
*             #     #  #     #  #     #  #     #  #                    *
*              #####    #####   #######  #######  #                    *
*                                                                      *
* SCOOP            OBJECT ORIENTED PROGRAMMING                         *
*                                                                      *
************************************************************************
*
* SCOOP.lss
*
* THE SAFETY FLAG. IF 0, SOME CHECKS ARE NOT COMPILED IN. I RECOMMEND
* THAT IT ALWAYS BE ENABLED.
*
-LINE 108 "SCOOP.lss"
-MODULE SCOOP
-PUBLIC OBJECT()
         DATA('OBJECT(CLASS,IVARS,METHODS)')
*
-PUBLIC SEND(), SUPER(), SELF(), IVAR(), CVAR(), CLASS_OF(), |1
         DEFINE('SEND(THIS,METHOD,A1,A2,A3,A4,A5,A6,A7,A8)'
+               'C,M,M_CLASS,T1,T2,T3')
         DEFINE('SUPER(METHOD,A1,A2,A3,A4,A5,A6,A7,A8)T1,T2,T3')
         DEFINE('SELF(METHOD,A1,A2,A3,A4,A5,A6,A7,A8)T1,T2,T3')
         DEFINE('FIND_METHOD(OBJ,METHOD)')
         DEFINE('IVAR(NAME)')
         DEFINE('CVAR(NAME)')
         DEFINE('CLASS_OF(OBJ)')
         OPSYN('|', 'IVAR', 1)
*
* INITIALIZE OOP SYSTEM, CREATE ROOT CLASS. MAKE SURE ROOT CLASS CAN
* ANSWER NEW_CLASS, NEW, INIT, DOES_NOT_UNDERSTAND AND ADD_METHOD
* MESSAGES. ALSO, ANSWER THE IS_A MESSAGE.
*
-PUBLIC CLASS:CLASS
         CLASS = OBJECT(, TABLE(), TABLE())
         IVARS(CLASS)<'CLASS'> = 'CLASS'
-PUBLIC CLASS:'ADD_METHOD'
         METHODS(CLASS)<'ADD_METHOD'> =
+           CODE(
+              ' METHODS(THIS) = IDENT(METHODS(THIS)) TABLE();'
+              ' THAW(METHODS(THIS));'
+              ' METHODS(THIS)<A1> = A2;'
+              ' FREEZE(METHODS(THIS)) :(RETURN)')
*
-PUBLIC CLASS:'NEW_CLASS'
         SEND(CLASS, 'ADD_METHOD', 'NEW_CLASS',
+           CODE(
+              ' THIS = OBJECT(THIS);'
+              ' IVAR("CLASS") = A1;'
+              ' SEND = THIS :(RETURN)'))
-PUBLIC CLASS:'INIT'
         SEND(CLASS, 'ADD_METHOD', 'INIT',
+           CODE(' :(RETURN)'))
-PUBLIC CLASS:'NEW'
         SEND(CLASS, 'ADD_METHOD', 'NEW',
+           CODE(
+              ' THIS = OBJECT(THIS);'
+              ' SELF("INIT", A1, A2, A3, A4, A5, A6, A7, A8);'
+              ' SEND = THIS :(RETURN)'))
-PUBLIC CLASS:'DOES_NOT_UNDERSTAND'
         SEND(CLASS, 'ADD_METHOD', 'DOES_NOT_UNDERSTAND',
+           CODE(
+            " TERMINAL = 'SCOOP: DOES NOT UNDERSTAND ' METHOD :(END)"))
         DEFINE('IS_A(ACLASS)')
-PUBLIC CLASS:'IS_A'
         SEND(CLASS, 'ADD_METHOD', 'IS_A', 'IS_A')
                                                              :(OOP_END)
*
* IS_A - IS OBJECT IN CLASS? ACLASS CAN BE A STRING WITH A CLASS NAME
*        OR A CLASS OBJECT
*
IS_A     T1 = THIS
IS_A_2   T1 = CLASS(T1)
         IDENT(T1)                                           :S(FRETURN)
         IDENT(T1, ACLASS)                                    :S(RETURN)
         IDENT(IVARS(T1)<'CLASS'>, ACLASS)           :S(RETURN)F(IS_A_2)
*
* ACCESS INSTANCE VARIABLE. CREATE THE INSTANCE VARIABLES IF THEY DO
* NOT YET EXIST.
*
IVAR     IVARS(THIS) = IDENT(IVARS(THIS)) TABLE()
         IVAR = .(IVARS(THIS)<NAME>)                          :(NRETURN)
*
* ACCESS CLASS VARIABLE
*
CVAR     IVARS(CLASS(THIS)) = IDENT(IVARS(CLASS(THIS))) TABLE()
         CVAR = .(IVARS(CLASS(THIS))<NAME>)                   :(NRETURN)
*
* CLASS_OF RETURNS THE NAME OF THE CLASS OF THE PASSED OBJECT. THE
* CLASS NAMES SHOULD BE UNIQUE WITHIN A PROGRAM. THE ROOT CLASS HAS
* NAME 'CLASS' (ROOT'S SUPERCLASS IS NULL)
*
CLASS_OF CLASS_OF = IVARS(CLASS(OBJ))<'CLASS'>                 :(RETURN)
*
* FIND METHOD BEGINNING AT OBJ SEARCHING UP TO THE ROOT CLASS
*
FIND_METHOD
         M_CLASS =
         IDENT(OBJ)                                          :S(FRETURN)
         C = OBJ
FIND_METHOD2
         FIND_METHOD = VDIFFER(METHODS(C))<METHOD>
         DIFFER(FIND_METHOD)                            :F(FIND_METHOD3)
         M_CLASS = C                                           :(RETURN)
FIND_METHOD3
         IDENT(C = CLASS(C))                  :S(FRETURN)F(FIND_METHOD2)
*
* DISPATCH TO THE PARENT CLASS. THAT, IN TURN, MAY DISPATCH TO ITS
* PARENT. THIS IS USED WITH 'INIT' (FOR EXAMPLE).
*
* TO IMPLEMENT SUPER, WE WANT TO START SEARCHING WITH THE CLASS OF THE
* CLASS WE FOUND THE METHOD IN. THIS IS IN LOCAL SEND() VARIABLE
* M_CLASS WHICH IS SET IN FIND_METHOD.
*
SUPER    SUPER = THIS
         IDENT(M_CLASS)                                       :S(RETURN)
         M = FIND_METHOD(CLASS(M_CLASS), METHOD)     :F(RETURN)S(SEND_3)
*
* DISPATCH METHOD FROM WITHIN A METHOD
*
SELF     SELF = THIS                                           :(SEND_2)
*
* DISPATCH METHOD TO OBJECT. DEFAULT ANSWER IS SIMPLY 'THIS' TO ALLOW
* CHAINED METHODS
*
SEND     SEND = THIS
*
* ENSURE THAT THIS PARAMETER IS AN OBJECT (OR CLASS).
*
         IDENT(THIS)                                         :S(FRETURN)
         IDENT(DATATYPE(THIS), 'OBJECT')                      :S(SEND_2)
         TERMINAL = 'SCOOP: SEND NEEDS OBJECT AS RECEIVER'        :(END)
*
SEND_2   M = FIND_METHOD(THIS, METHOD)                        :S(SEND_3)
         M = FIND_METHOD(THIS, 'DOES_NOT_UNDERSTAND')         :S(SEND_3)
*
* THIS ERROR SHOULD NOT HAPPEN! (THE ROOT CLASS SHOULD ALWAYS ANSWER
* DOES_NOT_UNDERSTAND).
*
         TERMINAL =
+           'SCOOP: ROOT CLASS MISSING DOES_NOT_UNDERSTAND'       :(END)
*
* WE HAVE THE METHOD, DISPATCH IT. SINCE ALL VARIABLES ARE GLOBAL,
* ACCESS TO 'THIS' WILL SIMPLY REFER TO SELF AS PASSED TO SEND()
* WHICH IS WHAT WE WANT.
*
* IF THE METHOD IS CODE, EXECUTE IT. OTHERWISE, APPLY M TO THE PASSED
* ARGUMENTS.
*
SEND_3   IDENT(DATATYPE(M), 'CODE')                                :S<M>
         SEND = APPLY(M, A1, A2, A3, A4, A5, A6, A7, A8)
+                                                   :S(RETURN)F(FRETURN)
*
OOP_END
*
* CE: .F.MSNOBOL4;
