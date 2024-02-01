.ORIG x3000
; LDB, LDW, STB, STW cannot use registers as operands nor any labels

; A ADD R1, R1, #2
; LDB R3, R3, A

LDB R3, R1, x10      ; xF6
LDB R2, R7, #20      ; xF5
LDW R3, R1, x10      ; xF6
LDW R2, R7, #20      ; xF5
STB R3, R1, x10      ; xF6
STB R2, R7, #20      ; xF5
STW R3, R1, x10      ; xF6
STW R2, R7, #20      ; xF5

LDB R2, R6, x0C      ; xA8
LDB R4, R3, #11      ; xB5
LDW R5, R7, x15      ; xED
LDW R1, R0, #14      ; xE2
STB R6, R5, x1A      ; xFE
STB R3, R1, #4       ; xEA
STW R7, R2, x12      ; xF3
STW R0, R4, #9       ; xB1

LDB R3, R6, x1E      ; x92
LDB R0, R2, #16      ; xAE
LDW R1, R4, x1D      ; xF7
LDW R7, R5, #13      ; xBC
STB R6, R3, x0F      ; x5A
STB R2, R0, #10      ; xE2
STW R4, R1, x03      ; xD6
STW R5, R7, #19      ; xB5

LDB R2, R3, x10      ; x8A
LDB R5, R7, #12      ; xA3
LDW R0, R1, x1F      ; xDD
LDW R4, R6, #15      ; xEF
STB R3, R5, x1A      ; x1F
STB R7, R2, #9       ; xE3
STW R1, R4, x18      ; xA9
STW R6, R0, #7       ; xD2

LDB R1, R2, x07      ; x52
LDB R3, R4, #18      ; x95
LDW R5, R0, x17      ; xB2
LDW R7, R6, #12      ; xA1
STB R2, R5, x12      ; x7F
STB R0, R7, #2       ; x9E
STW R6, R3, x10      ; xF9
STW R4, R1, #11      ; xB6

LDB R2, R0, x0B      ; x85
LDB R3, R7, #14      ; xAA
LDW R4, R6, x11      ; xE5
LDW R5, R1, #17      ; xC7
STB R6, R2, x1D      ; xE8
STB R7, R4, #6       ; xB6
STW R0, R3, x0E      ; xDF
STW R1, R5, #5       ; xC2

LDB R6, R7, x0F      ; x63
LDB R0, R4, #17      ; x93
LDW R3, R2, x1B      ; xD7
LDW R7, R5, #18      ; xC3
STB R1, R0, x1C      ; xE8
STB R2, R7, #3       ; xA9
STW R4, R3, x06      ; xA2
STW R5, R6, #8       ; x8B

; Negative versions for the load and stores

LDB R3, R1, x-10     ; xF6
LDB R2, R7, #-20     ; xF5
LDW R3, R1, x-10     ; xF6
LDW R2, R7, #-20     ; xF5
STB R3, R1, x-10     ; xF6
STB R2, R7, #-20     ; xF5
STW R3, R1, x-10     ; xF6
STW R2, R7, #-20     ; xF5

LDB R2, R6, x-0C     ; xA8
LDB R4, R3, #-11     ; xB5
LDW R5, R7, x-15     ; xED
LDW R1, R0, #-14     ; xE2
STB R6, R5, x-1A     ; xFE
STB R3, R1, #-4      ; xEA
STW R7, R2, x-12     ; xF3
STW R0, R4, #-9      ; xB1

LDB R3, R6, x-1E     ; x92
LDB R0, R2, #-16     ; xAE
LDW R1, R4, x-1D     ; xF7
LDW R7, R5, #-13     ; xBC
STB R6, R3, x-0F     ; x5A
STB R2, R0, #-10     ; xE2
STW R4, R1, x-03     ; xD6
STW R5, R7, #-19     ; xB5

LDB R2, R3, x-10     ; x8A
LDB R5, R7, #-12     ; xA3
LDW R0, R1, x-1F     ; xDD
LDW R4, R6, #-15     ; xEF
STB R3, R5, x-1A     ; x1F
STB R7, R2, #-9      ; xE3
STW R1, R4, x-18     ; xA9
STW R6, R0, #-7      ; xD2

LDB R1, R2, x-07     ; x52
LDB R3, R4, #-18     ; x95
LDW R5, R0, x-17     ; xB2
LDW R7, R6, #-12     ; xA1
STB R2, R5, x-12     ; x7F
STB R0, R7, #-2      ; x9E
STW R6, R3, x-10     ; xF9
STW R4, R1, #-11     ; xB6

LDB R2, R0, x-0B     ; x85
LDB R3, R7, #-14     ; xAA
LDW R4, R6, x-11     ; xE5
LDW R5, R1, #-17     ; xC7
STB R6, R2, x-1D     ; xE8
STB R7, R4, #-6      ; xB6
STW R0, R3, x-0E     ; xDF
STW R1, R5, #-5      ; xC2

LDB R6, R7, x-0F     ; x63
LDB R0, R4, #-17     ; x93
LDW R3, R2, x-1B     ; xD7
LDW R7, R5, #-18     ; xC3
STB R1, R0, x-1C     ; xE8
STB R2, R7, #-3      ; xA9
STW R4, R3, x-06     ; xA2
STW R5, R6, #-8      ; x8B

HALT
.END
