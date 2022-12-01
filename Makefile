# to build, type `make`
# to clean, type `make clean`

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
BIN = ksim
SRCS = $(wildcard $(SRCDIR)/*cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# directories
BUILDDIR = build
SRCDIR = src

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

$(BUILDDIR):
	mkdir $(BUILDDIR)

clean:
	rm -f $(BIN) $(BUILDDIR)/*

-include $(BUILDDIR)/*.d
