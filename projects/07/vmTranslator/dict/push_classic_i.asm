// Push CLASSIC I : CLASSIC = LCL or ARG or THIS or THAT or TEMP
// Go to RAM[CLASSIC+I]
// TODO : Penser a mettre des bons separateurs pour strtok
@I
D=A
@CLASSIC
D=M+D
A=D
// Store it
D=M
// RAM[SP] = D
@SP
A=M
M=D
// SP++
@SP
M=M+1
