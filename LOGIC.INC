-STITL LOGIC
-EJECT
*
-LINE 78 "LOGIC.lss"
************************************************************************
*                                                                      *
*             #        #######   #####   ###   #####                   *
*             #        #     #  #     #   #   #     #                  *
*             #        #     #  #         #   #                        *
*             #        #     #  #  ####   #   #                        *
*             #        #     #  #     #   #   #                        *
*             #        #     #  #     #   #   #     #                  *
*             #######  #######   #####   ###   #####                   *
*                                                                      *
* LOGIC       CATSPAW SPITBOL COMPATIBLE LOGIC() FUNCTIONS             *
*                                                                      *
* PHIL BUDNE <PHIL@ULTIMATE.COM>                                       *
* JANUARY 21, 2002                                                     *
*                                                                      *
************************************************************************
*
* LOGIC.lss
*
-LINE 6 "LOGIC.lss"
*
* NOTE! BASE ARGUMENT MUST BE PASSED A EXPLICIT NULL STRING FOR DEFAULT
*
* INTEGER/INTEGER, STRING/INTEGER, STRING/STRING
*
-PUBLIC LOGIC()
         LOAD('LOGIC(INTEGER,,)')
*
-PUBLIC NOT(), AND(), OR(), XOR(), NAND(), NOR(), UPLUS(), UMINUS()
-PUBLIC  UMUL(), UDIV(), SHL(), SHR(), SAR(), ROL(), ROR()
-PUBLIC HI(), IH(), DIB(), IDB()
         DEFINE('NOT(ARG)')
         DEFINE('AND(ARG1,ARG2)')
         DEFINE('OR(ARG1,ARG2)')
         DEFINE('XOR(ARG1,ARG2)')
         DEFINE('NAND(ARG1,ARG2)')
         DEFINE('NOR(ARG1,ARG2)')
         DEFINE('UPLUS(ARG1,ARG2)')
         DEFINE('UMINUS(ARG1,ARG2)')
         DEFINE('UMUL(ARG1,ARG2)')
         DEFINE('UDIV(ARG1,ARG2)')
         DEFINE('SHL(ARG1,ARG2)')
         DEFINE('SHR(ARG1,ARG2)')
         DEFINE('SAR(ARG1,ARG2)')
         DEFINE('ROL(ARG1,ARG2)')
         DEFINE('ROR(ARG1,ARG2)')
         DEFINE('HI(ARG)')
         DEFINE('IH(ARG)')
         DEFINE('DIB(ARG,BASE)')
         DEFINE('IDB(ARG,BASE)')                            :(LOGIC_END)
*
NOT      NOT    = LOGIC( 1, ARG)                    :S(RETURN)F(FRETURN)
AND      AND    = LOGIC( 2, ARG1, ARG2)             :S(RETURN)F(FRETURN)
OR       OR     = LOGIC( 3, ARG1, ARG2)             :S(RETURN)F(FRETURN)
XOR      XOR    = LOGIC( 4, ARG1, ARG2)             :S(RETURN)F(FRETURN)
NAND     NAND   = LOGIC( 5, ARG1, ARG2)             :S(RETURN)F(FRETURN)
NOR      NOR    = LOGIC( 6, ARG1, ARG2)             :S(RETURN)F(FRETURN)
UPLUS    UPLUS  = LOGIC( 7, ARG1, ARG2)             :S(RETURN)F(FRETURN)
UMINUS   UMINUS = LOGIC( 8, ARG1, ARG2)             :S(RETURN)F(FRETURN)
UMUL     UMUL   = LOGIC( 9, ARG1, ARG2)             :S(RETURN)F(FRETURN)
UDIV     UDIV   = LOGIC(10, ARG1, ARG2)             :S(RETURN)F(FRETURN)
SHL      SHL    = LOGIC(11, ARG1, ARG2)             :S(RETURN)F(FRETURN)
SHR      SHR    = LOGIC(12, ARG1, ARG2)             :S(RETURN)F(FRETURN)
SAR      SAR    = LOGIC(13, ARG1, ARG2)             :S(RETURN)F(FRETURN)
ROL      ROL    = LOGIC(14, ARG1, ARG2)             :S(RETURN)F(FRETURN)
ROR      ROR    = LOGIC(15, ARG1, ARG2)             :S(RETURN)F(FRETURN)
HI       HI     = LOGIC(16, CONVERT(ARG, 'STRING'), '')
+                                                   :S(RETURN)F(FRETURN)
IH       IH     = LOGIC(17, CONVERT(ARG, 'INTEGER'), '')
+                                                   :S(RETURN)F(FRETURN)
DIB      DIB    = LOGIC(16, CONVERT(ARG, 'STRING'), BASE)
+                                                   :S(RETURN)F(FRETURN)
IDB      IDB    = LOGIC(17, CONVERT(ARG, 'INTEGER'), BASE)
+                                                   :S(RETURN)F(FRETURN)
*
LOGIC_END
         CODE('LOGIC')
*
* CE: .MSNOBOL4;
