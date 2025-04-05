# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall
BISON = bison
FLEX = flex

# Files
TARGET = compiler
SRCS = main.cpp ast.cpp
GEN = parser.tab.cpp lexer.yy.cpp
OBJS = $(SRCS:.cpp=.o) $(GEN:.cpp=.o)

# Build rules
all: $(TARGET)

parser.tab.cpp parser.tab.hpp: parser.y
	$(BISON) -d parser.y

lexer.yy.cpp: lexer.l
	$(FLEX) -o lexer.yy.cpp lexer.l

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o parser.tab.* lexer.yy.cpp






# This Makefile will:

# Compile parser.y → parser.tab.cpp and parser.tab.hpp using Bison

# Compile lexer.l → lexer.yy.cpp using Flex

# Compile .cpp files into .o

# Link everything into a binary called compiler

# Clean build files when you run make clean

