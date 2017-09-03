CC=gcc -std=c11
CFLAGS=-Wall -pedantic -Wextra -g

SRCDIR=vmTranslator
DICTDIR=vmTranslator/dict

_DEPS=vmTMain.h vmTParser.h vmTWriter.h
DEPS=$(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJS=vmTMain.o vmTParser.o vmTWriter.o dict/vmTDictFiles.o
OBJS=$(patsubst %,$(SRCDIR)/%,$(_OBJS))

_DICT=add.asm and.asm eq.asm gt.asm lt.asm neg.asm not.asm \
      or.asm pop_classic_i.asm pop_pointer_b.asm \
      pop_static_i.asm pop_temp_i.asm push_classic_i.asm push_constant_i.asm \
      push_pointer_b.asm push_static_i.asm push_temp_i.asm sub.asm
DICT=$(patsubst %,$(DICTDIR)/%,$(_DICT))

# DEPS += $(patsubst %.asm,%.h,$(DICT))

all: VMTranslator

$(SRCDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# First method implied perl manip, I prefer xxd method
# TODO: Use Makefile to create properly vmTDictFiles from .asm folder
$(DICTDIR)/vmTDictFiles.c: $(DICT)
	echo "#include \"vmTDictFiles.h\"" > $@
	for file in $(DICT); do \
	    xxd -i $$file >> $@; \
	done
	sed -i 's/unsigned char/const char/' $@
	sed -i 's/};/, 0x00};/' $@
	sed -i 's/vmTranslator_dict_//' $@


VMTranslator: $(OBJS)
	$(CC) -o $@ $^ -I$(SRCDIR) $(CFLAGS)

.PHONY: clean valgrind

clean:
	rm -f VMTranslator $(SRCDIR)/*.o $(SRCDIR)/*~

valgrind: VMTranslator
	valgrind --leak-check=full --show-leak-kinds=all  ./VMTranslator StackArithmetic/StackTest/StackTest.vm
