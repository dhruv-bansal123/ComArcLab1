.ORIG #4096
; LEA cannot take in any other arguments than a label

LEA R0, A
LEA R3, B
LEA R5, C
LEA R6, D
LEA R2, E
LEA R7, F
LEA R4, G
LEA R1, H
LEA R6, I
LEA R3, J
LEA R7, K
LEA R0, L
LEA R2, M
LEA R5, N
LEA R4, O
LEA R1, P
LEA R5, Q
LEA R0, R
LEA R3, S
LEA R2, T

HALT
A   .FILL x3000
B   .FILL x1AB2
C   .FILL x71E8
D   .FILL x40F5
E   .FILL x6D3A
F   .FILL xA529
G   .FILL x87C1
H   .FILL x943F
I   .FILL x5EAD
J   .FILL x2F98
K   .FILL xB6E7
L   .FILL x8D45
M   .FILL xE971
N   .FILL x17B3
O   .FILL x3C86
P   .FILL xAF12
Q   .FILL x68D7
R   .FILL x509B
S   .FILL x14CE
T   .FILL x92BF

.END
