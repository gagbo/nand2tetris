CC=gcc -std=c11
CFLAGS=-Wall -pedantic -Wextra

SRCDIR=vmTranslator

_DEPS=vmTParser.h vmTWriter.h
DEPS=$(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJS=vmTParser.o vmTWriter.o
OBJS=$(patsubst %,$(SRCDIR)/%,$(_OBJS))

all: VMTranslator

$(SRCDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

VMTranslator: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f VMTranslator $(SRCDIR)/*.o $(SRCDIR)/*~
