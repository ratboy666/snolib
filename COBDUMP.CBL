       IDENTIFICATION DIVISION.
       PROGRAM-ID. COBDUMP.
      *****************************************************************
      ** GENERATE A FORMATTED HEX/CHAR DUMP OF A STORAGE AREA.       **
      ** TO USE THIS SUBROUTINE, SIMPLY CALL IT AS FOLLOWS:          **
      **                                                             **
      ** CALL "COBDUMP" USING <DATA-ITEM> [ <LENGTH> ]               **
      **                                                             **
      ** IF SPECIFIED, THE <LENGTH> ARGUMENT SPECIFIES HOW MANY      **
      ** BYTES OF <DATA-ITEM> ARE TO BE DUMPED. IF ABSENT, ALL OF    **
      ** <DATA-ITEM> WILL BE DUMPED (I.E. LENGTH(<DATA-ITEM>) WILL   **
      ** BE ASSUMED FOR <LENGTH>).                                   **
      **                                                             **
      ** >>> NOTE THAT THE SUBROUTINE NAME MUST BE SPECIFIED IN  <<< **
      ** >>> UPPERCASE                                           <<< **
      **                                                             **
      ** THE DUMP IS GENERATED TO STDERR, SO YOU MAY PIPE IT TO A    **
      ** FILE WHEN YOU EXECUTE YOUR PROGRAM USING "2> FILE".         **
      **                                                             **
      ** AUTHOR:       GARY L. CUTLER                                **
      **               CUTLERGL@GMAIL.COM                            **
      **                                                             **
      ** NOTE:         THE AUTHOR HAS A SENTIMENTAL ATTACHMENT TO    **
      **               THIS SUBROUTINE - IT'S BEEN AROUND SINCE 1971 **
      **               AND IT'S BEEN CONVERTED TO AND RUN ON 10 DIF- **
      **               FERENT OPERATING SYSTEM/COMPILER ENVIRONMENTS **
      **                                                             **
      ** DATE-WRITTEN: OCTOBER 14, 1971                              **
      **                                                             **
      *****************************************************************
      **  DATE  CHANGE DESCRIPTION                                   **
      ** ====== ==================================================== **
      ** GC1071 INITIAL CODING - UNIVAC DEPT. OF DEFENSE COBOL '68   **
      ** GC0577 CONVERTED TO UNIVAC ASCII COBOL (ACOB) - COBOL '74   **
      ** GC1182 CONVERTED TO UNIVAC UTS4000 COBOL - COBOL '74 W/     **
      **        SCREEN SECTION ENHANCEMENTS                          **
      ** GC0883 CONVERTED TO HONEYWELL/BULL COBOL - COBOL '74        **
      ** GC0983 CONVERTED TO IBM VS COBOL - COBOL '74                **
      ** GC0887 CONVERTED TO IBM VS COBOL II - COBOL '85             **
      ** GC1294 CONVERTED TO MICRO FOCUS COBOL V3.0 - COBOL '85 W/   **
      **        EXTENSIONS                                           **
      ** GC0703 CONVERTED TO UNISYS UNIVERSAL COMPILING SYSTEM (UCS) **
      **        COBOL (UCOB) - COBOL '85                             **
      ** GC1204 CONVERTED TO UNISYS OBJECT COBOL (OCOB) - COBOL 2002 **
      ** GC0609 CONVERTED TO OPENCOBOL 1.1 - COBOL '85 W/ SOME COBOL **
      **        2002 FEATURES                                        **
      ** GC0410 ENHANCED TO MAKE 2ND ARGUMENT (BUFFER LENGTH)        **
      **        OPTIONAL                                             **
      *****************************************************************
       ENVIRONMENT DIVISION.
       CONFIGURATION SECTION.
       REPOSITORY.
           FUNCTION ALL INTRINSIC.
       DATA DIVISION.
       WORKING-STORAGE SECTION.
       78  UNDISPLAYABLE-CHAR-SYMBOL   VALUE X'2E'.
       01  ADDR-POINTER                USAGE POINTER.
FMGW  *
FMGW  * ORIGINAL REDEFINE WAS TO BINARY-LONG. THIS IS WRONG ON A
FMGW  * 64 BIT BUILD (MOST OF THEM, THESE DAYS)
FMGW  *
FMGW   01  ADDR-NUMBP                  REDEFINES ADDR-POINTER
FMGW                                   USAGE BINARY-DOUBLE UNSIGNED.
FMGW  *
FMGW  * AND, WE SEPARATE ADD-NUMBER FROM ADD-POINTER, MAKING IT
FMGW  * INDEPENDENT. ADDR-NUMBP IS GOING TO BE COPIED ONCE, AND
FMGW  * MASKED TO THE LOW BITS (WRONG FOR SOME 64 BIT MACHINES)
FMGW  *
FMGW   01  ADDR-NUMBER                 USAGE BINARY-DOUBLE UNSIGNED.

       01  ADDR-SUB                    USAGE BINARY-CHAR.

       01  ADDR-VALUE                  USAGE BINARY-LONG.

       01  BUFFER-LENGTH               USAGE BINARY-LONG.

       01  BUFFER-SUB           COMP-5 PIC 9(4).

       01  HEX-DIGITS                  VALUE '0123456789ABCDEF'.
           05 HEX-DIGIT                OCCURS 16 TIMES PIC X(1).

       01  LEFT-NIBBLE          COMP-5 PIC 9(1).
       01  NIBBLE                      REDEFINES LEFT-NIBBLE
                                       BINARY-CHAR.

       01  OUTPUT-DETAIL.
           05 OD-ADDR.
              10 OD-ADDR-HEX           OCCURS 8 TIMES PIC X.
           05 FILLER                   PIC X(1).
           05 OD-BYTE                  PIC Z(3)9.
           05 FILLER                   PIC X(1).
           05 OD-HEX                   OCCURS 16 TIMES.
              10 OD-HEX-1              PIC X.
              10 OD-HEX-2              PIC X.
              10 FILLER                PIC X.
           05 OD-ASCII                 OCCURS 16 TIMES
                                       PIC X.

       01  OUTPUT-SUB           COMP-5 PIC 9(2).

       01  OUTPUT-HEADER-1.
           05 FILLER                   PIC X(80) VALUE
              '<-ADDR-> BYTE ' &
              '<---------------- HEXADECIMAL ----------------> ' &
              '<---- CHAR ---->'.

       01  OUTPUT-HEADER-2.
           05 FILLER                   PIC X(80) VALUE
              '======== ==== ' &
              '=============================================== ' &
              '================'.

       01  PIC-XX.
           05 FILLER                   PIC X VALUE LOW-VALUES.
           05 PIC-X                    PIC X.
       01  PIC-HALFWORD                REDEFINES PIC-XX
                                       PIC 9(4) COMP-X.

       01  PIC-X10.
           05 FILLER                   PIC X(2).
           05 PIC-X8                   PIC X(8).

       01  RIGHT-NIBBLE         COMP-5 PIC 9(1).

       LINKAGE SECTION.
       01  BUFFER                      PIC X ANY LENGTH.

       01  BUFFER-LEN                  USAGE BINARY-LONG.

       PROCEDURE DIVISION USING BUFFER, OPTIONAL BUFFER-LEN.
       000-COBDUMP.
           IF NUMBER-OF-CALL-PARAMETERS = 1
               MOVE LENGTH(BUFFER) TO BUFFER-LENGTH
           ELSE
               MOVE BUFFER-LEN     TO BUFFER-LENGTH
           END-IF
           MOVE SPACES TO OUTPUT-DETAIL
           SET ADDR-POINTER TO ADDRESS OF BUFFER
FMGW  *
FMGW  * WITH 64 BIT ADDRESS, PRUNE DOWN TO LOWER 31 BITS.
FMGW  *
FMGW       MOVE 2147483647 TO ADDR-NUMBER
FMGW  *
FMGW  * I WISH I COULD WRITE THIS AS X'7FFFFFFF' BUT THAT APPEARS TO
FMGW  * NOT WORK? ALSO, HAVE TO PRUNE OFF THE TOP BIT -- NOT SURE
FMGW  * WHY, BUT THEN, 2GB ADDRESS SPACE IS ACTUALLY PLENTY, AND I
FMGW  * DON'T EXPECT TO REALLY BEING GOING OVER ANYTIME SOON.
FMGW  *
FMGW       CALL 'CBL_AND' USING ADDR-NUMBP, ADDR-NUMBER, BY VALUE 8
           PERFORM 100-GENERATE-ADDRESS
           MOVE 0 TO OUTPUT-SUB
           DISPLAY
               OUTPUT-HEADER-1 UPON SYSERR
           END-DISPLAY
           DISPLAY
               OUTPUT-HEADER-2 UPON SYSERR
           END-DISPLAY
           PERFORM VARYING BUFFER-SUB FROM 1 BY 1
                     UNTIL BUFFER-SUB > BUFFER-LENGTH
               ADD 1
                   TO OUTPUT-SUB
               END-ADD
               IF OUTPUT-SUB = 1
                   MOVE BUFFER-SUB TO OD-BYTE
               END-IF
               MOVE BUFFER (BUFFER-SUB : 1) TO PIC-X
               IF (PIC-X < ' ')
               OR (PIC-X > '~')
                   MOVE UNDISPLAYABLE-CHAR-SYMBOL
                     TO OD-ASCII (OUTPUT-SUB)
               ELSE
                   MOVE PIC-X
                     TO OD-ASCII (OUTPUT-SUB)
               END-IF
               DIVIDE PIC-HALFWORD BY 16
                   GIVING LEFT-NIBBLE
                   REMAINDER RIGHT-NIBBLE
               END-DIVIDE
               ADD 1 TO LEFT-NIBBLE
                        RIGHT-NIBBLE
               END-ADD
               MOVE HEX-DIGIT (LEFT-NIBBLE)
                 TO OD-HEX-1 (OUTPUT-SUB)
               MOVE HEX-DIGIT (RIGHT-NIBBLE)
                 TO OD-HEX-2 (OUTPUT-SUB)
               IF OUTPUT-SUB = 16
                   DISPLAY
                       OUTPUT-DETAIL UPON SYSERR
                   END-DISPLAY
                   MOVE SPACES TO OUTPUT-DETAIL
                   MOVE 0 TO OUTPUT-SUB
                   SET ADDR-POINTER UP BY 16
FMGW  *
FMGW  * AFTER INCREMENTING THE POINTER BY 16, ALSO ADD 16 TO THE
FMGW  * ADDRESS NUMBER (WE ARE NOT SIMPLY REDEFINING ANYMORE)
FMGW  *
FMGW               ADD 16 TO ADDR-NUMBER
                   PERFORM 100-GENERATE-ADDRESS
               END-IF
           END-PERFORM
           IF OUTPUT-SUB > 0
               DISPLAY
                   OUTPUT-DETAIL UPON SYSERR
               END-DISPLAY
           END-IF
           EXIT PROGRAM
           .
       100-GENERATE-ADDRESS.
           MOVE 8 TO ADDR-SUB
           MOVE ADDR-NUMBER TO ADDR-VALUE
           MOVE ALL '0' TO OD-ADDR
           PERFORM WITH TEST BEFORE UNTIL ADDR-VALUE = 0
               DIVIDE ADDR-VALUE BY 16
                   GIVING ADDR-VALUE
                   REMAINDER NIBBLE
               END-DIVIDE
               ADD 1 TO NIBBLE
               MOVE HEX-DIGIT (NIBBLE)
                 TO OD-ADDR-HEX (ADDR-SUB)
               SUBTRACT 1 FROM ADDR-SUB
           END-PERFORM
           .
