# to build, type `make`
# to clean, type `make clean`

CC = gcc
CFLAGS = -std=c99 -Wall
BIN = ksim
# replace OBJS and HDRS with a
#HDRS =
SRCS = $(wildcard $(SRCDIR)/*c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))
#OBJS = $(BUILD)/main.o $(BUILD)/ksim.o
# directories
BUILDDIR = build
SRCDIR = src

all: $(BIN)

$(BIN): $(OBJS) | $(BUILDDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c -MMD $< -o $@

$(BUILDDIR):
	mkdir $(BUILDDIR)

clean:
	rm -f $(BIN) $(BUILDDIR)/*

-include *.d
