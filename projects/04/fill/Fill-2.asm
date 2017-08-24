// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.


@storedState // Last key stored by the listener
M=0
@storedLast // Difference between last scan code and current touch
M=0

// Listener. If KBD = 0, we check difference and set color to 0;
//          Else we check difference and set color to -1
(LISTEN)
@storedState
D=M
@storedLast
M=D
@KBD
D=M
@NOKEY
D;JEQ

// In D there's KBD
@storedState
M=D
@storedLast
D=D-M
@LISTEN
D;JEQ
@color
M=-1
@WRITESCREEN
0;JMP

// In D there's KBD
(NOKEY)
@storedState
M=D
@storedLast
D=D-M
@LISTEN
D;JEQ
@color
M=0
@WRITESCREEN
0;JMP


// Write color in every cell of the screen
(WRITESCREEN)
@jscreen
M=0
    (LOOPWRITESCREEN)
    @8192
    D=A
    @jscreen
    D=D-M
    @LISTEN
    // Jump if 8192 - j <= 0
    D;JLE

    @SCREEN
    D=A
    @currRegister
    M=D // Now we have the base address of SCREEN

    @jscreen
    D=M
    @currRegister
    M=M+D

    // Do the painting
    @color
    D=M
    @currRegister
    A=M
    M=D

    // Advance one word on screen memory map
    @jscreen
    M=M+1

    @LOOPWRITESCREEN
    0;JMP

(END)
@END
0;JMP
