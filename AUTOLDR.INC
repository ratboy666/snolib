-MODULE AUTOLDR
-INCLUDE 'SLOAD.INC'
-INCLUDE 'JSON.INC'
-INCLUDE 'READFILE.INC'
-INCLUDE 'KEYST.INC'
-IN72
-STITL AUTOLDR
-EJECT
*
************************************************************************
*                                                                      *
*       #     #     #  #######  #######  #        ######   ######      *
*      # #    #     #     #     #     #  #        #     #  #     #     *
*     #   #   #     #     #     #     #  #        #     #  #     #     *
*    #     #  #     #     #     #     #  #        #     #  ######      *
*    #######  #     #     #     #     #  #        #     #  #   #       *
*    #     #  #     #     #     #     #  #        #     #  #    #      *
*    #     #   #####      #     #######  #######  ######   #     #     *
*                                                                      *
* AUTOLDR                FUNCTION AUTO-LOADER                          *
*                                                                      *
************************************************************************
*
* AUTOLDR USES THE INFORMATON GATHERED BY BLDIDX IN FILE 'IDX' TO CREATE
* STUBS AND TRACE() CALLS FOR FUNCTIONS IN SNOLIB. WHEN ONE OF THE
* FUNCTIONS IS CALLED, THE SOURCE CODE IS BROUGHT IN. NOTE THAT THIS
* IN TURN MAY BRING IN OTHER SOURCE FILES. THESE ARE RECORDED IN
* SLOAD(). IF THE SOURCE FILE IS ALREADY RESIDENT, SLOAD() WILL NOT
* RELOAD IT, AND THE CALL WILL BE ISSUED NORMALLY AND THE TRACE REMOVED.
* THIS IS DONE WHETHER OR NOT THE COMPONENT NEEDS LOADING. NOTE THAT
* THE TRACE IS ESTABLISHED TO CAPTURE THE NAME OF THE FUNCTION. EACH
* FUNCTION IS INITIALLY DEFINED WITH THE SAME ENTRY POINT (AUTOFUNC).
* A SINGLE TRACE ON AUTOFUNC IS NOT SUFFICIENT -- EACH FUNCTION MUST
* BE INDIVIDUALLY TRACED.
*
* VARIABLES ARE NOT TRACED -- WE CAN PRE-DECLARE THESE.
*-INCLUDE 'ARRAY0.INC'
*-INCLUDE 'CHARS.INC'
*-INCLUDE 'DISPLAY.INC'
*-INCLUDE 'GETKEY.INC'
*-INCLUDE 'HOST.INC'
*-INCLUDE 'UNIX.INC'
*
         DEFINE('AUTOLDR()F,T,K,I,S')
         DEFINE('AUTOTRC(NAME,TAG)')
         DEFINE('AUTOFUNC(P1_,P2_,P3_,P4_,P5_,P6_,P7_,P8_)'
+               'FNAME__,RET__')                          :(END_AUTOLDR)
*
* THIS IS THE TRACE() HANDLER FOR THE AUTOLOADER. ALL PARAMETERS OF
* THE FUNCTION HAVE BEEN EVALUATED. LOCALS HAVE BEEN ESTABLISHED, AND
* FUNCTION RETURN NAME IS AVAILABLE. CAPTURE THE NAME OF THE FUNCTION
* FROM 'NAME' INTO AUTOFUNC LOCAL FNAME__. REMOVE TRACING FROM THE
* FUNCTION.
*
AUTOTRC  FNAME__ = NAME
         STOPTR(FNAME__, 'CALL')                               :(RETURN)
*
* AUTOFUNC, THE AUTOLOADER FUNCTION LOADER. AUTOTRC (THE TRACE FUNCTION)
* HAS EXECUTED AND SET THE FUNCTION NAME INTO FNAME__ FIND AND LOAD THE
* SOURCE FOR THE FUNCTION, APPLY THE FUNCTION. CAPTURE THE RETURN TYPE
* AND REPLICATE IT BACK TO THE CALLER, ALONG WITH THE FUNCTION RESULTS.
*
AUTOFUNC SLOAD(FUNCS__<FNAME__ '()'>)
         $FNAME__ =
+           APPLY(FNAME__, P1_, P2_, P3_, P4_, P5_, P6_, P7_, P8_)
         RET__ = &RTNTYPE                                      :($RET__)
*
* READ IDX. ITERATE ALL FUNCTIONS, DEFINING THOSE THAT ARE NOT ALREADY
* FUNCTIONS AND ESTABLISH TRACE ON THOSE.
*
AUTOLDR  F = READFILE('IDX')                                 :F(FRETURN)
AUTOLDR2 T = JSON_DECODE(F)
         F = JSON_REST
         FUNCS__ = IDENT(T<'#'>, 'FUNCTIONS') T
         IDENT(FUNCS__)                                     :S(AUTOLDR2)
         FUNCS__<'#'> =
         K = KEYST(FUNCS__)                                  :F(FRETURN)
         I = 1
AUTOLDR3 F = K<I>                                             :F(RETURN)
         F '()' =                                           :F(AUTOLDR4)
         IDENT(F)                                           :S(AUTOLDR4)
         FUNCTION(F)                                        :S(AUTOLDR4)
         DEFINE(F '(P1_,P2_,P3_,P4_,P5_,P6_,P7_,P8_)', 'AUTOFUNC')
         TRACE(F, 'CALL',, 'AUTOTRC')
         AUTOLDR = AUTOLDR + 1
AUTOLDR4 I = I + 1                                          :S(AUTOLDR3)
*
END_AUTOLDR
*
* RETURN IS NUMBER OF FUNCTIONS TRACED
*
*        N = AUTOLDR()
*        &TRACE = 999999999999
*
* CE: .MSNOBOL4;
*
