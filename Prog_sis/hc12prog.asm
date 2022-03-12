	Org $4000
ET1	EQU $4006 ;cualquier cosa
	LDAA ET1
	ADDA ET2

	ADDB B,y
ET2	LDAA $5000
	;otra cosa
	LDAB -100,y
	LDAA -600,sp
	End