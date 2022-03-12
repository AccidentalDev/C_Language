et1 equ 15
 org $1220
ldaa	%10111000101
 fcc "hola"
rmb 116
et2 adda m,y
yupi 32
adda @241
et3 adda $100
adda 110 ;CHECAR
adda 32000
adda -25000
aba
ldaa 12
ldab $10
adca #121
adcb #160
addd #$a
bita $F
bitb $10E
et1 adda [320,sp]
adda [D,pc]
adda [@467,y
kjj end