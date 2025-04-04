
# === Makefile for lexer ===

# Compiler and tools
LEX     = flex
CC      = gcc

# Files
LEX_SRC = lexer.l
LEX_OUT = lexer.c
HDR     = tokens.h
TARGET  = lexer

# Flags
CFLAGS  = -Wall -Wextra -O2
LDFLAGS = -lfl

# Default rule
all: $(TARGET)

# Rule to build the lexer executable
$(TARGET): $(LEX_OUT) $(HDR)
	$(CC) $(CFLAGS) -o $@ $(LEX_OUT) $(LDFLAGS)

# Rule to generate lexer.c from lexer.l
$(LEX_OUT): $(LEX_SRC)
	$(LEX) -o $@ $<

# Optional: Run on a sample input
run: $(TARGET)
	./$(TARGET) < input.c

# Clean up
clean:
	rm -f $(TARGET) $(LEX_OUT)

.PHONY: all clean run




#  Why This Is Better:
# Feature	      Your Version	     Improved Version
# Variable Usage	❌ None	  		✅ Makes code reusable and readable
# Flags Separation	❌ Hardcoded		✅ Use CFLAGS and LDFLAGS
# Portability	    ❌				✅ Safer with .PHONY targets
# Optimization	    ❌				✅ Includes -Wall -Wextra -O2
# Extendability	    ❌				✅ Easy to plug in parser.y, headers, etc.




# Future Extension Example:
# If you also add a parser.y file:


# YACC     = bison
# YACC_SRC = parser.y
# YACC_OUT = parser.c
# YACC_HDR = parser.h

# $(YACC_OUT) $(YACC_HDR): $(YACC_SRC)
# 	$(YACC) -d -o $(YACC_OUT) $(YACC_SRC)




# Let me know if you want a full lexer + parser Makefile too.


