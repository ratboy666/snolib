#!/usr/bin/bash
         exec "snobol4" "-b" "$0" "$@"
-INCLUDE 'SCOOP.INC'
-LINE 255 "SCOOP.lss"
-INCLUDE 'TIMER.INC'
         &CODE = 1
         SHAPE_CLASS = SEND(CLASS, 'NEW_CLASS', 'SHAPE')
         SQUARE_CLASS = SEND(SHAPE_CLASS, 'NEW_CLASS', 'SQUARE')
         CIRCLE_CLASS = SEND(SHAPE_CLASS, 'NEW_CLASS', 'CIRCLE')
*
         M = CODE(' EQ(A1, 5) :F(END)S(RETURN)')
         SEND(SHAPE_CLASS, 'ADD_METHOD', 'AMETHOD', M)
*
         SQUARE = SEND(SQUARE_CLASS, 'NEW')
         SEND(SQUARE, 'AMETHOD', 5)
*
         IDENT(CLASS_OF(SQUARE), 'SQUARE')                       :F(END)
         IDENT(CLASS_OF(CLASS(SQUARE)), 'SHAPE')                 :F(END)
         IDENT(CLASS_OF(CLASS(CLASS(SQUARE))), 'CLASS')          :F(END)
*
         SEND(SQUARE, 'IS_A', SQUARE_CLASS)                      :F(END)
         SEND(SQUARE_CLASS, 'IS_A', 'SHAPE')                     :F(END)
         SEND(SQUARE, 'IS_A', 'CIRCLE')                          :S(END)
*
* TIME METHOD DISPATCH WHERE THE METHOD IS IN A SUPERCLASS
*
         TIMER(" SEND(SQUARE, 'AMETHOD', 5) ")
*
* TIME METHOD DISPATCH WHERE THE METHOD IS IN THE CLASS
*
         SEND(SQUARE_CLASS, 'ADD_METHOD', 'AMETHOD', M)
         TIMER(" SEND(SQUARE, 'AMETHOD', 5) ")
*
* TIME METHOD DISPATCH WHERE THE METHOD IS IN THE OBJECT
*
         SEND(SQUARE, 'ADD_METHOD', 'AMETHOD', M)
         TIMER(" SEND(SQUARE, 'AMETHOD', 5) ")
*
         &CODE = 0
END
