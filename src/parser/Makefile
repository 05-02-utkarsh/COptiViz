# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall
BISON = bison
FLEX = flex

# Paths
LEXER_DIR = ../lexer

# Files
TARGET = compiler
SRCS = main.cpp ast.cpp $(LEXER_DIR)/lexer.yy.cpp
GEN = parser.tab.cpp
OBJS = $(SRCS:.cpp=.o) $(GEN:.cpp=.o)

# Build rules
all: $(TARGET)

parser.tab.cpp parser.tab.hpp: parser.y
	$(BISON) -d parser.y

$(LEXER_DIR)/lexer.yy.cpp: $(LEXER_DIR)/lexer.l
	cd $(LEXER_DIR) && $(FLEX) -o lexer.yy.cpp lexer.l

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(LEXER_DIR) -c $<

clean:
	rm -f $(TARGET) *.o parser.tab.* 
	cd $(LEXER_DIR) && rm -f lexer.yy.cpp *.o




# This Makefile will:

# Compile parser.y → parser.tab.cpp and parser.tab.hpp using Bison

# Compile lexer.l → lexer.yy.cpp using Flex

# Compile .cpp files into .o

# Link everything into a binary called compiler

# Clean build files when you run make clean

