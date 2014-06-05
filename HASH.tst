#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'HASH.INC'
-LINE 112 "HASH.lss"
         &CODE = 1
         H = #'FIRST=BOB,LAST=LOBLAW'
         IDENT(H<'FIRST'>, 'BOB')                                :F(END)
         IDENT(H<'LAST'>, 'LOBLAW')                              :F(END)
         T = COPY_TABLE(H)
         IDENT(T<'FIRST'>, 'BOB')                                :F(END)
         T<'FIRST'> = 'FRED'
         IDENT(H<'FIRST'>, 'BOB')                                :F(END)
         T2 = #'ADDRESS=SOMEWHERE'
         T3 = MERGE_TABLE(T, T2)
         IDENT(T3<'FIRST'>, 'FRED')                              :F(END)
         IDENT(T3<'LAST'>, 'LOBLAW')                             :F(END)
         IDENT(T3<'ADDRESS'>, 'SOMEWHERE')                       :F(END)
         H = #'XXX,NAME=VALUE'
         IDENT(H<NULL>, 'XXX')                                   :F(END)
         IDENT(H<'NAME'>, 'VALUE')                               :F(END)
         A = KEYS_IN_TABLE(T3)                                   :F(END)
         A = SORT(A)                                             :F(END)
         IDENT(A<1>, 'ADDRESS')                                  :F(END)
         IDENT(A<2>, 'FIRST')                                    :F(END)
         IDENT(A<3>, 'LAST')                                     :F(END)
         &CODE = 0
END
