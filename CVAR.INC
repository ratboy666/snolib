-MODULE CVAR
-USES HASH()
-LINE 73 "CVAR.lss"
-INCLUDE 'CHARS.INC'
-INCLUDE 'HASH.INC'
-INCLUDE 'HOST.INC'
-INCLUDE 'P64.INC'
-LINE 264 "CVAR.lss"
-IN72
-STITL CVAR
-EJECT
*
************************************************************************
*                                                                      *
*                                                                      *
*                   #####   #     #     #     ######                   *
*                  #     #  #     #    # #    #     #                  *
*                  #        #     #   #   #   #     #                  *
*                  #        #     #  #     #  ######                   *
*                  #         #   #   #######  #   #                    *
*                  #     #    # #    #     #  #    #                   *
*                   #####      #     #     #  #     #                  *
*                                                                      *
* CVAR           C VARIABLE DECLARATIONS, AND LOAD/STORE               *
*                                                                      *
************************************************************************
*
* CVAR.lss
*
-LINE 80 "CVAR.lss"
*
* FIXME - ISOLATE BY PASSING CVARSYMS
*
* THIS WILL ALLOW SUPPORT OF MULTIPLE ROUTINES. BUT... PARAMETER
* PASSING WILL BE... DIFFICULT. RECURSION IS TOUGH. WE CAN SIMPLY
* SET PARAMETER VARIABLES IF NEEDED. PARAMETERS ARE TOUGHER. WE
* CAN RETRIEVE POINTER. BUT THAT DOESN'T DEFINE STORAGE! ON RECURSIVE
* CALL WE WOULD NEED TO SAVE ALL PARAMETERS TO A STACK. WHICH WOULD
* WORK FOR DIRECT RECURSIVE CALL. ALTERNATIVE IS PUSH AND RETRIEVE,
* AND COPY BACK ON RETURN.
*
* PUSH/POP OF PARAMETERS TO ALTERNATE STACK... CRIB STACK CODE.
* TO PUSH DOUBLE, PUSH TWO WORDS, OR ONE QWORD. REGISTER IS QWORD.
* PUSH MEMORY_WORD, PUSH MEMORY_QWORD WOULD BE USEFUL... (AND POP
* VARIANTS): PUSHMW PUSHMQ POPMW POPMQ, AND PUSH POP.
*
* THEN,
*
* FUNCTION NAME(P1,P2...PN)
* INTEGER V(D1,D2,D3),V...
* REAL V
* DOUBLE PRECISION V
* LOGICAL V
* DIMENSION V(D1,D2,D3)
* COMMON /NAME/ V,V,V...
*
* BY DEFAULT, FUNCTION CREATE COMMON BLOCK NAME_
*
* LABEL EXPR
*       IF (EXPR) EXPR
*       GOTO LABEL
*
* CALL THIS LANGUAGE "F00" - MINI-FORTRAN. WE CAN INTRODUCE DO,
* RETURN, ETC.
*
-PUBLIC CVARSYMS(), CV_BASE(), CV_SYMTAB(), CV_END()
*
         DATA('CVARSYMS(CV_BASE,CV_SYMTAB,CV_END)')
*
-PUBLIC CVART(), CV_OFFSET(), CV_SIZE(), CV_DIM(), CV_SIGN(), CV_ISINT()
*
         DATA('CVART(CV_OFFSET,CV_SIZE,CV_DIM,CV_SIGN,CV_ISINT)')
*
-PUBLIC PTRV(), LOADV(), STOREV(), NEWDECLV(), DECLAREV()
*
         DEFINE('PTRV(B,V,I)')
         DEFINE('LOADV(B,V,I)')
         DEFINE('STOREV(B,V,I,X)')
         DEFINE('NEWDECLV()')
         DEFINE('DECLAREV(L)SIGN,INT,FLOAT,AL,NU,SP,BS,BN,IDENT,DIM,'
+                          'INTDECL,FLOATDECL,DECL,SIZE,ALIGN,ISINT,'
+                          'S,T,I,N,SIGNED')
                                                         :(DECLAREV_END)
*
PTRV     V = VTAB<V>
         IDENT(V)                                            :S(FRETURN)
         I = IDENT(I) 0
         PTRV = B + CV_OFFSET(V) + I * CV_SIZE(V)              :(RETURN)
*
STOREV   B = PTRV(B, V, I)                                   :F(FRETURN)
         V = VTAB<V>                          :($('STOREV_' CV_SIZE(V)))
STOREV_1 POKE_C(B, X)                                          :(RETURN)
STOREV_2 POKE_S(B, X)                                          :(RETURN)
STOREV_4 (EQ(CV_ISINT(V)) POKE_F(B, X))                       :S(RETURN)
         POKE_I(B, X)                                          :(RETURN)
STOREV_8 (EQ(CV_ISINT(V)) POKE_D(B, X))                       :S(RETURN)
         POKE_P(B, X)                                          :(RETURN)
*
LOADV    B = PTRV(B, V, I)                                   :F(FRETURN)
         V = VTAB<V>                           :($('LOADV_' CV_SIZE(V)))
LOADV_1  LOADV = PEEK_C(B)
         NE(CV_SIGN(V))                                       :S(RETURN)
         LOADV = LT(LOADV) (2 ** 8) + LOADV                    :(RETURN)
LOADV_2  LOADV = PEEK_S(B)
                                                               :(RETURN)
         NE(CV_SIGN(V))                                       :S(RETURN)
         LOADV = LT(LOADV) (2 ** 16) + LOADV                   :(RETURN)
LOADV_4  LOADV = EQ(CV_ISINT(V)) PEEK_F(B)                    :S(RETURN)
         LOADV = PEEK_I(B)
-LINE 168 "CVAR.lss"
         NE(CV_SIGN(V))                                       :S(RETURN)
         LOADV = LT(LOADV) (2 ** 32) + LOADV                   :(RETURN)
LOADV_8  LOADV = EQ(CV_ISINT(V)) PEEK_D(B)                    :S(RETURN)
         LOADV = PEEK_P(B)                                     :(RETURN)
*
NEWDECLV VTAB = TABLE()
         VOFFSET = 0                                           :(RETURN)
*
DECLAREV SIGN = ('signed' | 'SIGNED' | 'unsigned' | 'UNSIGNED') . S
         INT =  ('char' | 'CHAR' | 'short' | 'SHORT' | 'int' |
+                'INT' | 'long' | 'LONG' | 'pointer' | 'POINTER') . T
         FLOAT = ('float' | 'FLOAT' | 'double' | 'DOUBLE') . T
         AL = &UCASE &LCASE
         NU = &DIGITS
         SP = '_'
         BS = SPAN(' ' CHARS_TAB)
         BN = BS | NULL
         IDENT = (ANY(AL SP) (SPAN(AL NU SP) | NULL)) . I
         DIM = '[' BN SPAN(&DIGITS) . N BN ']'
         INTDECL = (SIGN BS INT) | SIGN | INT
         FLOATDECL = FLOAT
         DECL = BN (INTDECL | FLOATDECL) BN IDENT BN (DIM | NULL)
*
         SIZE =
+           #'CHAR=1,SHORT=2,INT=4,LONG=8,POINTER=8,FLOAT=4,DOUBLE=8'
         ALIGN =
+           #'CHAR=1,SHORT=2,INT=4,LONG=8,POINTER=8,FLOAT=4,DOUBLE=8'
         ISINT =
+           #'CHAR=1,SHORT=1,INT=1,LONG=1,POINTER=1,FLOAT=,DOUBLE='
*
* ASSIGN PATTERN VARIABLE TO DEFAULTS - SIGNED INT [1]
*
         S = 'SIGNED'
         T = 'INT'
         I =
         N = 1
*
* SCAN THE DECLARATION, SETTING PATTERN VARIABLES S, T, I, N
*
         L DECL                                              :F(FRETURN)
*
* CONVERT T AND S TO UPPERCASE
*
         T = REPLACE(T, &LCASE, &UCASE)
         S = REPLACE(S, &LCASE, &UCASE)
*
* SIGNED = 1 IF SIGNED, 0 IF UNSIGNED
*
         SIGNED = 0
         S 'UNSIGNED'                                         :S(DECLV2)
         SIGNED = 1
*
* ADJUST OFFSET FOR ALIGNMENT
*
DECLV2   R = REMDR(VOFFSET, ALIGN<T>)
         VOFFSET = NE(R) VOFFSET + (ALIGN<T> - R)
*
* ALREADY DECLARED?
*
         V = VTAB<I>
         IDENT(V)                                            :F(FRETURN)
*
* CREATE CVART() RECORD FOR NEW VARIABLE
*
         V = CVART(VOFFSET, SIZE<T>, N, SIGNED, ISINT<T>)
*
* PUT VARIABLE INTO SYMBOL TABLE
*
         VTAB<I> = V
*
* ADJUST OFFSET BY SIZE OF NEW VARIABLE (INCLUDING DIMENSION)
*
         VOFFSET = VOFFSET + SIZE<T> * N
*
         DECLAREV = VOFFSET                                    :(RETURN)
*
DECLAREV_END
*
* CE: .MSNOBOL4;
