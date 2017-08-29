CC=gcc -std=c11
CFLAGS=-Wall -pedantic -Wextra

SRCDIR=vmTranslator
DICTDIR=vmTranslator/dict

_DEPS=vmTMain.h vmTParser.h vmTWriter.h dict/vmTDictFiles.h
DEPS=$(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJS=vmTMain.o vmTParser.o vmTWriter.o
OBJS=$(patsubst %,$(SRCDIR)/%,$(_OBJS))

_DICT=add.asm and.asm eq.asm gt.asm lt.asm neg.asm not.asm \
      or.asm pop_classic_i.asm pop_pointer_b.asm \
      pop_static_i.asm push_classic_i.asm push_constant_i.asm \
      push_pointer_b.asm push_static_i.asm sub.asm
DICT=$(patsubst %,$(DICTDIR)/%,$(_DICT))

# DEPS += $(patsubst %.asm,%.h,$(DICT))

all: VMTranslator

$(SRCDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# First method implied perl manip, I prefer xxd method
# TODO: Use Makefile to create properly vmTDictFiles from .asm folder
# $(DICTDIR)/vmTDictFiles.h: $(DICT)
# 	 cat $< | perl -pe 's/^/"/mg; s/$/\n"/mg' > $@
# ###xxd -i %.asm


VMTranslator: $(OBJS)
	$(CC) -o $@ $^ -I$(SRCDIR) $(CFLAGS)

.PHONY: clean

clean:
	rm -f VMTranslator $(SRCDIR)/*.o $(SRCDIR)/*~
