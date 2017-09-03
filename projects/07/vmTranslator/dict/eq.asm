// eq
// Label issue with the goto
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=D-M
D=M
@END_EQ.J
D;JEQ
D=-1
(END_EQ.J)
@SP
A=M
M=D
@SP
M=M+1
