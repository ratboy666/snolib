       IDENTIFICATION DIVISION.
       PROGRAM-ID.   COBDUMPTEST.
      *****************************************************************
      ** THIS IS A PROGRAM THAT DEMONSTRATES (AND TESTS) THE USE OF  **
      ** THE "COBDUMP" SUBROUTINE.                                   **
      **                                                             **
      ** AUTHOR: GARY L. CUTLER                                      **
      **         CUTLERGL@GMAIL.COM                                  **
      **                                                             **
      ** DATE-WRITTEN: JUNE 10, 2009                                 **
      **                                                             **
      *****************************************************************
      **  DATE  CHANGE DESCRIPTION                                   **
      ** ====== ==================================================== **
      ** GC0609 INITIAL CODING.                                      **
      *****************************************************************
       DATA DIVISION.
       WORKING-STORAGE SECTION.

       01  TEST-DATA.
           05 PIC X(16) VALUE X'000102030405060708090A0B0C0D0E0F'.
           05 PIC X(16) VALUE X'101112131415161718191A1B1C1D1E1F'.
           05 PIC X(16) VALUE X'202122232425262728292A2B2C2D2E2F'.
           05 PIC X(16) VALUE X'303132333435363738393A3B3C3D3E3F'.
           05 PIC X(16) VALUE X'404142434445464748494A4B4C4D4E4F'.
           05 PIC X(16) VALUE X'505152535455565758595A5B5C5D5E5F'.
           05 PIC X(16) VALUE X'606162636465666768696A6B6C6D6E6F'.
           05 PIC X(16) VALUE X'707172737475767778797A7B7C7D7E7F'.
           05 PIC X(16) VALUE X'808182838485868788898A8B8C8D8E8F'.
           05 PIC X(16) VALUE X'909192939495969798999A9B9C9D9E9F'.
           05 PIC X(16) VALUE X'A0A1A2A3A4A5A6A7A8A9AAABACADAEAF'.
           05 PIC X(16) VALUE X'B0B1B2B3B4B5B6B7B8B9BABBBCBDBEBF'.
           05 PIC X(16) VALUE X'C0C1C2C3C4C5C6C7C8C9CACBCCCDCECF'.
           05 PIC X(16) VALUE X'D0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF'.
           05 PIC X(16) VALUE X'E0E1E2E3E4E5E6E7E8E9EAEBECEDEEEF'.
           05 PIC X(16) VALUE X'F0F1F2F3F4F5F6F7F8F9FAFBFCFDFEFF'.

       01  TEST-DATA-2.
           05 PIC X(16) VALUE X'0F0E0D0C0B0A09080706050403020100'.
       
       PROCEDURE DIVISION.

       010-CALL-COBDUMP.
           CALL 'COBDUMP'
               USING TEST-DATA
           END-CALL

           CALL 'COBDUMP'
               USING TEST-DATA, 64
           END-CALL

           CALL 'COBDUMP'
               USING TEST-DATA-2
           END-CALL

           STOP RUN
           .
