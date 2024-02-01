.ORIG #4070
; XOR and NOR has to take a constant (either a register or an immediate)

; XOR Tests

; Hexadecimal
XOR R0, R0, x0     ; 0x00
XOR R0, R0, x1     ; 0x01
XOR R0, R0, x2     ; 0x02
XOR R0, R0, x3     ; 0x03
XOR R0, R0, x4     ; 0x04
XOR R0, R0, x5     ; 0x05
XOR R0, R0, x6     ; 0x06
XOR R0, R0, x7     ; 0x07
XOR R0, R0, x8     ; 0x08
XOR R0, R0, x9     ; 0x09
XOR R0, R0, xA     ; 0x0A
XOR R0, R0, xB     ; 0x0B
XOR R0, R0, xC     ; 0x0C
XOR R0, R0, xD     ; 0x0D
XOR R0, R0, xE     ; 0x0E
XOR R0, R0, xF     ; 0x0F
XOR R0, R0, x-A    ; 0xFF
XOR R0, R0, x-F    ; 0xFE
XOR R0, R0, x-E    ; 0xFD
XOR R0, R0, x-D    ; 0xFC
XOR R0, R0, x-C    ; 0xFB
XOR R0, R0, x-B    ; 0xFA
XOR R0, R0, x-A    ; 0xF9
XOR R0, R0, x-9    ; 0xF8
XOR R0, R0, x-8    ; 0xF7
XOR R0, R0, x-7    ; 0xF6
XOR R0, R0, x-6    ; 0xF5
XOR R0, R0, x-5    ; 0xF4
XOR R0, R0, x-4    ; 0xF3
XOR R0, R0, x-3    ; 0xF2
XOR R0, R0, x-2    ; 0xF1
XOR R0, R0, x-1    ; 0xF0
; Decimal
XOR R0, R0, #0     ; 0
XOR R0, R0, #1     ; 1
XOR R0, R0, #2     ; 2
XOR R0, R0, #3     ; 3
XOR R0, R0, #4     ; 4
XOR R0, R0, #5     ; 5
XOR R0, R0, #6     ; 6
XOR R0, R0, #7     ; 7
XOR R0, R0, #8     ; 8
XOR R0, R0, #9     ; 9
XOR R0, R0, #10    ; 10
XOR R0, R0, #11    ; 11
XOR R0, R0, #12    ; 12
XOR R0, R0, #13    ; 13
XOR R0, R0, #14    ; 14
XOR R0, R0, #15    ; 15
XOR R0, R0, #-16   ; -16
XOR R0, R0, #-15   ; -15
XOR R0, R0, #-14   ; -14
XOR R0, R0, #-13   ; -13
XOR R0, R0, #-12   ; -12
XOR R0, R0, #-11   ; -11
XOR R0, R0, #-10   ; -10
XOR R0, R0, #-9    ; -9
XOR R0, R0, #-8    ; -8
XOR R0, R0, #-7    ; -7
XOR R0, R0, #-6    ; -6
XOR R0, R0, #-5    ; -5
XOR R0, R0, #-4    ; -4
XOR R0, R0, #-3    ; -3
XOR R0, R0, #-2    ; -2
XOR R0, R0, #-1    ; -1 
; Randomized Cases
XOR R1, R4, #4     ; 0
XOR R3, R6, #3     ; 1
XOR R2, R7, #5     ; 2
XOR R5, R1, #1     ; 3
XOR R6, R3, #0     ; 4
XOR R7, R0, #4     ; 5
XOR R2, R5, #2     ; 6
XOR R4, R1, #6     ; 7
XOR R3, R2, #3     ; 0
XOR R0, R6, #7     ; 1
XOR R1, R7, #1     ; 2
XOR R6, R4, #0     ; 3
XOR R7, R3, #4     ; 4
XOR R5, R0, #3     ; 5
XOR R4, R2, #6     ; 6
XOR R0, R5, #2     ; 7
XOR R1, R3, #5     ; 0
XOR R2, R6, #1     ; 1
XOR R3, R4, #7     ; 2
XOR R7, R5, #0     ; 3
; Randomized Registers with Hexadecimal Range from -16 to 15
XOR R7, R4, R1      ; x00
XOR R3, R5, R2      ; x01
XOR R6, R0, R3      ; x02
XOR R2, R1, R4      ; x03
XOR R4, R7, R5      ; x04
XOR R1, R3, R6      ; x05
XOR R0, R2, R7      ; x06
XOR R5, R6, R0      ; x07
XOR R2, R3, R1      ; x08
XOR R1, R0, R2      ; x09

; NOT Tests
NOT R3, R5
NOT R7, R4
NOT R2, R6
NOT R0, R1
NOT R5, R3
NOT R4, R7
NOT R6, R0
NOT R1, R2
NOT R5, R4
NOT R2, R0
NOT R3, R1
NOT R6, R7
NOT R0, R5
NOT R1, R6
NOT R4, R3
NOT R7, R2
NOT R6, R5
NOT R3, R0
NOT R1, R4
NOT R2, R7
NOT R5, R1
NOT R4, R2
NOT R7, R6
NOT R0, R3
NOT R2, R1
NOT R6, R4
NOT R3, R7
NOT R5, R0
NOT R1, R3
NOT R7, R5
NOT R4, R1
NOT R6, R2
NOT R0, R7
NOT R2, R3
NOT R1, R5
NOT R3, R6
NOT R7, R0
NOT R4, R6
NOT R5, R2
NOT R1, R7
NOT R3, R2
NOT R0, R4
NOT R2, R5
NOT R6, R3
NOT R1, R0
NOT R5, R7
NOT R4, R0
NOT R2, R4

HALT
.END
