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
@LT_TRUE.J
D;JLT
D=-1
@END_LT.J
0;JMP
(LT_TRUE.J)
D=0
(END_LT.J)
@SP
A=M
M=D
@SP
M=M+1
