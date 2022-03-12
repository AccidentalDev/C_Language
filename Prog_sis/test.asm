dos	equ $2
	Org $4000
adca #1201
andb @1470
andcc #12548
adda #$154
adda 12,x
adda $a10,sp
movb 3431
 stx 38000
ldaa 70500
bcs $45
	Aba
	End