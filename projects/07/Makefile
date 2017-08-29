CC=gcc -std=c11
CFLAGS=-Wall -pedantic -Wextra

SRCDIR=vmTranslator

_DEPS=vmTParser.h vmTWriter.h
DEPS=$(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJS=vmTParser.o vmTWriter.o
OBJS=$(patsubst %,$(SRCDIR)/%,$(_OBJS))

_DICT=add.asm and.asm eq.asm gt.asm lt.asm neg.asm not.asm or.asm pop_classic_i.asm pop_pointer_b.asm pop_static_i.asm push_classic_i.asm push_constant_i.asm push_pointer_b.asm push_static_i.asm sub.asm
DICT=$(patsubst %,$(SRCDIR)/dict/%,$(_DICT))

DEPS += $(patsubst %.asm,%.h,$(DICT))

all: VMTranslator

$(SRCDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(SRCDIR)/dict/%.h: %.asm
	 cat $< | perl -pe 's/^/"/mg; s/$/\n"/mg' > $@

# How we should then use dict stubs converted to headers :
#const char *text = \n #include "a.h"


VMTranslator: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f VMTranslator $(SRCDIR)/*.o $(SRCDIR)/*~
