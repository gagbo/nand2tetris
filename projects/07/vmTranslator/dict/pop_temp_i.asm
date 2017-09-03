// pop TEMP I
@I
D=A
@CLASSIC
D=A+D
@R13
M=D
// D = RAM[--SP]
@SP
M=M-1
A=M
D=M
// RAM[TEMP+I] = D
@R13
A=M
M=D
