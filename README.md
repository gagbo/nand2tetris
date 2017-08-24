# Nand to Tetris
The goal of this course is to design a computer from the bottom up.
First 6 weeks projects are about the hardware layers (from NAND gate
to Assembly), the other are about software layers (from Compiler
to tetris).

The so-called HACK computer that is being built works on a 16-bit
architecture.


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
