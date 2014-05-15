000010 IDENTIFICATION DIVISION.       
000020*
000030******************************************************************       
000040*                                                                *       
000050* COO.CBL                                                        *       
000060*                                                                *       
000070******************************************************************       
000080*
000090* PROGRAM-ID MUST BE LOWER CASE. WRAPPERS ARE AUTOMATICALLY       
000100* GENERATED FOR SNOBOL4.       
000110*
000120 PROGRAM-ID.      say.       
000130 AUTHOR.          FRED WEIGEL.       
000140 INSTALLATION.    TORONTO CANADA.       
000150 DATE-WRITTEN.    JANUARY 2013.       
000160 DATE-COMPILED.   JANUARY 2013.       
000170 SECURITY.        NONE.       
000180 REMARKS.         HELLO WORLD PROGRAM.       
000190*
000200 ENVIRONMENT DIVISION.       
000210*
000220 CONFIGURATION SECTION.       
000230 SOURCE-COMPUTER. DEJAH       
000240                  WITH DEBUGGING MODE.       
000250 OBJECT-COMPUTER. DEJAH       
000260                  MEMORY SIZE 65536 CHARACTERS       
000270                  PROGRAM COLLATING SEQUENCE IS ALPHABET-1.       
000280 SPECIAL-NAMES.   ALPHABET ALPHABET-1 IS NATIVE.       
000290* 
000300 DATA DIVISION.       
000310*
000320 LINKAGE SECTION.       
000330 01 HELLO PIC X(6).       
000340 01 WORLD PIC X(6).       
000350*
000360 PROCEDURE DIVISION USING HELLO WORLD.       
000370     DISPLAY HELLO WORLD.       
000380     CALL 'COBDUMP' USING HELLO.       
000390     EXIT PROGRAM.       
