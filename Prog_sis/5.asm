uno	equ $1
	org $1000
	swi
	wav
	ldaa $fb
	ldaa @20
	ldab $1234
	ldab 4096
	dec $ab
	ldaa 8,y
	ldaa -3,sp
	ldaa #$10
	ldaa #%101
	addd #$1234
	addd #4096
	addd #$FF
	end