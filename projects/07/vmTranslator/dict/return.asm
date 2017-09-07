// return
// Register returnAddress and endFrame
@LCL
D=M
@R13 // endFrame
M=D
@5
D=D-A
A=D
D=M
@R14 // retAddr
M=D
// pop arg 0
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
// SP = *ARG+1
@ARG
D=M+1
@SP
M=D
// Restore caller frame
@R13
M=M-1
A=M
D=M
@THAT
M=D
@R13
M=M-1
A=M
D=M
@THIS
M=D
@R13
M=M-1
A=M
D=M
@ARG
M=D
@R13
M=M-1
A=M
D=M
@LCL
M=D
// Jump to the saved return address
@R14
A=M
0;JMP
