// Pop CLASSIC I : CLASSIC = LCL or ARG or THIS or THAT or TEMP
// R13 = address = CLASSIC + I
@I
D=A
@CLASSIC
D=M+D
@R13
M=D
// D = RAM[--SP]
@SP
M=M-1
A=M
D=M
// RAM[CLASSIC+I] = D
@R13
A=M
M=D
