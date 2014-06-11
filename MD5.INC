-include 'BQ.INC'
-include 'READFILE.INC'
-include 'HOST.INC'

* ce: .msnobol4;

         define('md5(s)b,t,u,f')                              :(md5_end)

md5      t = bq('mktemp')
         writefile(t, s)
         md5 = bq('md5sum ' t)
         md5 break(' ') . md5
         delete(t)                                             :(return)
md5_end

*         output = md5('hello, world')
*end

