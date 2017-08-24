// Multiplication algorithm
// we need to have RAM[2] = RAM[0] * RAM[1]

// This implementation uses a loop.
// We add RAM[0] RAM[1] times to RAM[2].
// This implementation is more efficient if RAM[0]>RAM[1]

// Initialisation : RAM[2] = 0 and i = 0
@R2
M=0

@i
M=0

(LOOP)
// If i>RAM[1] go to end
@i
D=M
@R1
D=M-D
@END
D;JLE

// Add RAM[0] to RAM[2]
@R0
D=M
@R2
M=D+M

// Increment i and loop
@i
M=M+1

@LOOP
0;JMP

(END)
@END
0;JMP
