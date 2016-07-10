# Discreve-events simulator for Bank Makefile

CC = gcc

INCLUDES = -I.

# Compilation options:
CFLAGS = -g -O2 $(INCLUDES)

# Linking options:
LDFLAGS = -g -L.

# Libraries
LDLIBS =

# Executable
EXEC = simulator

# Dependencies
DEPS = event.h heap.h

# Objects
OBJS = $(EXEC).o event.o heap.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(EXEC)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o *.a $(EXEC)

.PHONY: clear
clear:
	rm -rf *.o *.a
