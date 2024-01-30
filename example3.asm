.ORIG x1000
a add R1, R1, R1
add R1, R1, #1
and r2, r3, r4
and r2, r3, #7
jmp r2
ret
jsr a
jsrr r3
ldb r4, r2, #10
lshf r2, r3, #3
rshfl r2, r3, #7
;rshfa r2, r3, #7
rti
HALT
.fill x3000
.end
