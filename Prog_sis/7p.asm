org $1000

ldaa 0,x
ldaa 8,y
ldaa -3,sp
ldaa ,pc
ldab 18,x
ldab -20,y

adda 3,+x
adda 5,y+
adda 8,+sp
adda 1,sp+
addb 2,-x
addb 4,y-
addb 5,-sp
addb 7,sp-

end