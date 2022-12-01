# to build, type `make`
# to clean, type `make clean`

CXX = g++
CXXFLAGS = -Wall -std=c++11
BIN = ksim
# replace OBJS and HDRS with a
#HDRS =
SRCS = $(wildcard $(SRCDIR)/*cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))
#OBJS = $(BUILD)/main.o $(BUILD)/ksim.o
# directories
BUILDDIR = build
SRCDIR = src

all: $(BIN)

$(BIN): $(OBJS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

$(BUILDDIR):
	mkdir $(BUILDDIR)

clean:
	rm -f $(BIN) $(BUILDDIR)/*

-include $(BUILDDIR)/*.d
