.ORIG x1000
a add R1, R1, R1
;add R1, R1, #1
ldw r1, r1, #2
lea r1, a
nop
not r1,r1
xor r1, r1, r1
xor r1, r1,#-1
trap x23
trap x21
trap x4
stb r1, r1, #12
stw r1, r1, #2
HALT
.fill x3000
.end