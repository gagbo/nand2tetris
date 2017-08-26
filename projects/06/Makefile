ALL: HackAssembler

HackAssembler: hackAssembler/HackAssembler.c hackAssembler/HackAssembler.h hackAssembler/HackTools.c hackAssembler/HackTools.h hackAssembler/HackInstruction.c hackAssembler/HackInstructionList.c hackAssembler/HackInstruction.h hackAssembler/HackInstructionList.h hackAssembler/HackParser.h hackAssembler/HackParser.c
	gcc -std=c11 hackAssembler/HackAssembler.c hackAssembler/HackTools.c hackAssembler/HackInstruction.c hackAssembler/HackInstructionList.c hackAssembler/HackParser.c -IhackAssembler -o HackAssembler -Wall -pedantic -Wextra -g

clean:
	rm -vf HackAssembler
