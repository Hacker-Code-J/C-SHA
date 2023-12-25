# Compiler settings - Can be customized.
CC = gcc
CFLAGS = -I./include -O2 -Wall -Wextra
LDFLAGS = -lcrypto

# Source files
SRC = ./src/sha2.c
OBJ = $(SRC:./src/%.c=./obj/%.o)

# Test program
TEST_SRC = ./tests/sha_test.c
TEST_OUT = a.out

# Compile and build
all: $(TEST_OUT)

$(TEST_OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(TEST_OUT) $(TEST_SRC) $(OBJ) $(LDFLAGS)

# Compile source files into object files
./obj/%.o: ./src/%.c
	mkdir -p ./obj
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build
clean:
	rm -rf ./obj $(TEST_OUT)

rebuild: clean all

# Check Memory Leak
leak:
	valgrind --leak-check=full --show-leak-kinds=all ./a.out

# Phony targets
.PHONY: all clean