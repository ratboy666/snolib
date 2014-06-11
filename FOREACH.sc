-SNOCONE
-MODULE FOREACH
-LINE 10 "FOREACH.lss"
-LINE 71 "FOREACH.lss"
-STITL FOREACH
-EJECT
#
########################################################################
#                                                                      #
#                                                                      #
#    #######  #######  ######   #######     #      #####   #     #     #
#    #        #     #  #     #  #          # #    #     #  #     #     #
#    #        #     #  #     #  #         #   #   #        #     #     #
#    #####    #     #  ######   #####    #     #  #        #######     #
#    #        #     #  #   #    #        #######  #        #     #     #
#    #        #     #  #    #   #        #     #  #     #  #     #     #
#    #        #######  #     #  #######  #     #   #####   #     #     #
#                                                                      #
# FOREACH            APPLY PROC TO EACH ELEMENT                        #
#                                                                      #
########################################################################
#
# FOREACH.lss
#

-LINE 13 "FOREACH.lss"
# Apply procedure proc to each element of x, where x may be an array,
# table, or expression that produces a sequence of values.
#
-PUBLIC FOREACH()
procedure foreach(x, proc) a, i {
   i = datatype(x)
   if (i :: 'ARRAY') {
      i = 1
      prototype(x) ? fence && break(':') . i
      while (a = x[i]) {
	 if (~apply(proc, a))
	    freturn
	 i = i + 1
      }
   } else if (i :: 'TABLE') {
      if (~(x = convert(x, 'ARRAY')))
	 freturn
      x = sort(x)
      i = 1
      while (a = x[i, 2]) {
	 if (~apply(proc, a, x[i, 1]))
	    freturn
	 i = i + 1
      }
   } else if (i :: 'EXPRESSION') {
      while (a = eval(x)) {
	 if (~apply(proc, a))
	    freturn
      }
   } else {
      if (apply(proc, x))
	 return
      else
	 freturn
   }
}

# ce: .msnocone;
