.ORIG #4096
A   ADD R1, R1, R1
    ADD R2, R2, R7
    ADD R3, R4, #0
    ADD R3, R4, x0
    ADD R3, R4, #-1
    ADD R3, R4, #1
    ADD R3, R4, x-1
    ADD R3, R4, x1
B   AND R1, R1, R1
    AND R2, R2, R7
    AND R3, R4, #-1
    AND R3, R4, #0
    AND R3, R4, x0
    AND R3, R4, #-1
    AND R3, R4, #1
    AND R3, R4, x-1
    AND R3, R4, x1
C   BR B
    BRN A
    BRZ C
    BRP D
    BRNZ E
    BRZP F
    BRNP G
    BRNZP I
    NOP
D   JMP R7
    JSR D 
    JSR A
    JSRR R6
E   LDB R3, R3, #-7
    LDW R5, R5, #-4
    LDB R3, R3, #7
    LDW R5, R5, #4
    LDW R0, R0, #0
    LDB R0, R0, #0
    LDW R0, R0, x0
    LDB R0, R0, x0
    LDW R0, R0, x3
    LDB R0, R0, x2
    LDW R0, R0, x-10
    LDB R0, R0, x-11
    LEA R6, GOT
F   NOT R2, R2
    RET
    RTI
    LSHF R1, R4, #8
    RSHFL R1, R4, #8
    RSHFA R1, R4, #8
    LSHF R1, R4, #7
    RSHFL R1, R4, #7
    RSHFA R1, R4, #7
    LSHF R1, R4, #0
    RSHFL R1, R4, #0
    RSHFA R1, R4, #0
    LSHF R1, R4, x0
    RSHFL R1, R4, x0
    RSHFA R1, R4, x0
    LSHF R1, R4, xF
    RSHFL R1, R4, xF
    RSHFA R1, R4, xF
G   STB R3, R3, #-7
    STW R5, R5, #-4
    STB R3, R3, #7
    STW R5, R5, #4
    STW R0, R0, #0
    STB R0, R0, #0
    STW R0, R0, x0
    STB R0, R0, x0
    STW R0, R0, x3
    STB R0, R0, x2
    STW R0, R0, x-10
    STB R0, R0, x-11
    STW R1, R1, x-20
    STB R1, R1, x-20
    TRAP x1
    TRAP x6
    TRAP x12
    TRAP x25
    TRAP #255
I   XOR R4, R5, R6
    XOR R3, R2, xF
    XOR R3, R2, x0
    XOR R3, R2, x-3
    XOR R3, R2, x-10
    XOR R3, R2, #-16
    XOR R3, R2, #15
    XOR R3, R2, #4
    XOR R3, R2, #0
    XOR R3, R2, #-4
HALT
GOT .fill x3000
.end