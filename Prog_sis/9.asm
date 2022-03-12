uno equ 4096
   org $1000
dos ldaa uno
 ldab dos,x
 subd #uno
 ldab [dos,y]
 ldaa cuatro
cuatro equ 15
 ldaa tres
 ldaa tres,x
tres bne tres
end