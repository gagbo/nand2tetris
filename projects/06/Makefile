CC=gcc -std=c11
CFLAGS=-Wall -pedantic -Wextra

SRCDIR=hackAssembler

_DEPS=HackAssembler.h HackTools.h HackInstruction.h HackInstructionList.h HackParser.h HackSymbolTable.h
DEPS=$(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJS=HackAssembler.o HackTools.o HackInstruction.o HackInstructionList.o HackParser.o HackSymbolTable.o
OBJS=$(patsubst %,$(SRCDIR)/%,$(_OBJS))

all: HackAssembler

$(SRCDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

HackAssembler: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f HackAssembler $(SRCDIR)/*.o $(SRCDIR)/*~
