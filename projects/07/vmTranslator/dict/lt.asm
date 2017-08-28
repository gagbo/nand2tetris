// lt
// Label issue with the goto
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=D-M
@LT_TRUE
D;JLT
D=-1
@END_LT
0;JMP
(LT_TRUE)
D=0
(END_LT)
@SP
A=M
M=D
@SP
M=M+1
