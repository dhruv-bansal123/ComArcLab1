.ORIG #4096
A   ADD R1, R1, R1
    ADD R2, R2, R7
    ADD R3, R4, #-1
B   AND R1, R1, R1
    AND R2, R2, R7
    AND R3, R4, #-1
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
    LEA R6, GOT
F   NOT R2, R2
    RET
    RTI
    LSHF R1, R4, #8
    RSHFL R1, R4, #8
    RSHFA R1, R4, #8
G   STB R4, R4,  #-3
    STW R2, R2, #-8
    TRAP x1
    TRAP x6
    TRAP x12
    TRAP x25
    TRAP #255
I   XOR R4, R5, R6
    XOR R3, R2, xF
HALT
GOT .fill x3000
.end
