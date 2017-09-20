# Nand to Tetris
This course is done with the OSSU curriculum in mind.
[![Open Source Society University - Computer Science](https://img.shields.io/badge/OSSU-computer--science-blue.svg)](https://github.com/ossu/computer-science)

The goal of this course is to design a computer from the bottom up.
First 6 weeks projects are about the hardware layers (from NAND gate
to Assembly), the other are about software layers (from Compiler
to tetris).

The so-called HACK computer that is being built works on a 16-bit
architecture.

The tests can be ran following the tutorials found on [The course website](http://nand2tetris.org/software.php)

## Week 1-3 : Combinatorial and Sequential Logic
All basic chips have been implemented using the given hdl. Starting from NAND gate up to
an ALU and Memory chips

## Week 4 : Assembly Language
Basic programs are done directly in assembly to get a hang on the very low level instructions.
The programs done include an infinite loop listening to the keyboard memory map, and changing the
screen accordingly.
### HACK Computer Assembly specification
The CPU takes 2 different types of instructions :
- *A instructions*, which change the value of the A register to a given 15-bit value.
- *C instructions*, which can manipulate A, D and M registers to do simple operations (addition,
substraction, incrementation and decrementation), order jumps in Assembly code, and write the
output of the operation in zero, one or any combination of A, D and M registers

## Week 5 : HACK CPU hardware description
Given the assembly language specification, the CPU chip, and then the whole Computer hdl are
implemented in this week's project. Now, we can feed binary instructions in the ROM to our
hdl script and let our 'chip' handle all the bits to manipulate correctly the RAM.

## Week 6 : HACK Assembler
Now that we have a Computer chip to handle the bits in ROM and RAM, and a properly specified
Assembly language for the HACK Computer, we're adding the missing link to finish the "hardware
layers" : an assembler. The [assembler](projects/06/HackAssembler) needs 1 argument, and 1 argument only, the assembly
source file. It then writes the number of instructions parsed to stderr, and then the binary
code to stdout.

I chose to write the assembler in C because I also wanted to try and implement linked lists
and hash tables in this language, think that doing almost everything would widen my
understanding of "bigger" code projects issues, and hope to continue doing work in
C-family languages.

There are actually 2 linked lists in the Assembler sources, one to implement the queue for
the instructions, and one for the hash table implementation. I didn't try to do inheritance to
make a more compact code, it may happen after I'm done with the course.

The hash table is implemented as an array (size HASHSIZE) of linked lists to handle
collisions. I took the hash function from the internet, and I feel like this implementation
of hash tables is very efficient.

As suggested by the course, the assembly translation is done in 2 passes : one to obtain
the values of the goto-labels, and one to translate everything. This is probably the best
solution, since encountering a new "@foo" instruction for the first time can't tell us if
foo is a goto-label (get value from the code) or a new variable (which have to get the
first free space in memory starting from 16). 
A solution to do the assembly in one pass would need the hash table to implement an iterator
that goes through the table in the order of creation of the key-value pairs in it. This does
not seem worth it here.

## Transistor count to this point
### Week 1 projects : Base chips
- Nand = 2 transistors
- Not = 2 transistors
- And = 4 transistors
- Or = 10 transistors
- Xor = 22 transistors

- Mux = 20 transistors
- DMux = 10 transistors

- And16 = 64 transistors
- Not16 = 32 transistors
- Or16 = 160 transistors
- Mux16 = 320 transistors

- Or8Way = 70 transistors
- Mux4Way16 = 960 transistors
- DMux4Way = 30 transistors
- Mux8Way16 = 2240 transistors
- DMux8Way = 70 transistors

### Week 2 projects : Additions
- Inc16 = 64 transistors
- HalfAdder = 26 transistors
- FullAdder = 62 transistors

- Add16 = 956 transistors

- Or16Way = 150 transistors
- ALU = 4252 transistors

### Week 3 projects : Memory
- Bit = 20 transistors + DFF
- Register = 320 transistors + 16\*DFF
- PC = 1414 transistors + 16\*DFF
- RAM8 = 4870 transistors + 128\*DFF
- RAM64 = 41270 transistors + 1024\*DFF
- RAM512 = 332470 transistors + 8192\*DFF
- RAM4K = 2662070 transistors + 65536\*DFF
- RAM16K = 10649270 transistors + 262144\*DFF
