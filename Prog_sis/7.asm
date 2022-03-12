org $1000
ldaa [$ABCD,x]
ldaa [@20,y]
ldaa [%101,sp]
ldab a,pc
ldab b,x
ldab d,y
ldab [d,sp]
ldab [d,pc]
adda 3,+x
adda 5,y+
adda 8,+sp
adda 1,sp+
addb 2,-x
addb 4,y-
addb 5,-sp
addb 7,sp-
end