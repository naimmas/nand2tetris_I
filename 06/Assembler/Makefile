# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g -I./libs/C_Parser -I./libs/A_Parser

# Source files
SRCS = assembler.c ./libs/C_Parser/cParser.c ./libs/A_Parser/aParser.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = assembler
# ARGS = ../pong/PongL.asm 
# ARGS = ../add/Add.asm 
# ARGS = ../max/Max.asm 
ARGS = ../max/MaxL.asm 

all: $(TARGET)
	
run:  $(TARGET)
	 ./$(TARGET) $(ARGS)
# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object files and executable
clean:
	$(RM) $(OBJS) $(TARGET)