ALL: HackAssembler

HackAssembler: hackAssembler/HackAssembler.c hackAssembler/HackAssembler.h hackAssembler/HackTools.c hackAssembler/HackTools.h hackAssembler/HackInstruction.c hackAssembler/HackInstructionList.c hackAssembler/HackInstruction.h
	gcc -std=c11 hackAssembler/HackAssembler.c hackAssembler/HackTools.c hackAssembler/HackInstruction.c hackAssembler/HackInstructionList.c -IhackAssembler -o HackAssembler -Wall -pedantic -Wextra

clean:
	rm -vf HackAssembler
