// not
@SP
M=M-1
A=M
D=M
@GOTOFALSE.J
D;JEQ
D=0
@END_NOT.J
0;JMP
(GOTOFALSE.J)
D=-1
(END_NOT.J)
@SP
A=M
M=D
@SP
M=M+1
