;	Name 1: Dhruv Bansal
;   Name 2: Carolyn Hoang
;   UTEID 1: db45988
;   UTEID 2: ch52677

;take bytes from 0x3100 and 0x3101 and add them
;the two bytes are 8bit 2's compelemnt
;so adding should be easy
;then store result in 0x3102
;check overflow and if overflow, store one in 0x3103
;overflow means that if both input msb bits are the same, the output msb bit should also be that
    .ORIG x3000
    LEA R0, inputs ; load into r0 the location the inputs start
    LDW R0, R0, #0 ; 
    LDB R1, R0, #0 ; load the first operant into R1
    LDB R2, R0, #1 ; load the second operant into R2
    ADD R3, R1, R2 ; add the two operants and store into R3
    STB R3, R0, #2 ; store the output into the correct location

    LEA R4, bitmask ; load the bitmask into R4
    LDW R4, R4, #0 ;
    AND R1, R1, R4 ; mask everything but the msb for operant 1
    AND R2, R2, R4 ; mask everything but the msb for operant 2
    
    NOT R5, R2 ; need to find 8 bit complement of the bit in op 2
    ADD R5, R5, #1
    
    ADD R5, R5, R1 ; This will tell me if a overflow is possible
    BRZ run
    AND R5, R5, #0 ; clear register 5
    STB R5, R0, #3 ; store the output that a overflow is not possible
    HALT
run    AND R5, R2, R1 ; this is the bit that the output needs to be
    AND R3, R3, R4 ; bit mask the output
    XOR R6, R5, R3 ; this will tell us if there is a overflow or not
    RSHFL R6, R6, #8 ; move the overflow to the LSB
    STB R6, R0, #3 ; store the overflow
    HALT
inputs  .FILL x3100
bitmask .FILL x80

    .end