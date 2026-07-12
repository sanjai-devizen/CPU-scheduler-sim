# --- Compiler Settings ---
CC = gcc
# -Wall and -Wextra turn on all warnings. -g compiles with debug symbols for GDB.
CFLAGS = -Wall -Wextra -g -I$(INC_DIR)

# --- Directory Paths ---
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# --- Files ---
# Find all .c files in the src/ directory
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Convert the list of .c files into a list of .o files that will live in build/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# --- Target Executable ---
EXEC = $(BUILD_DIR)/sim.bin

# --- Build Rules ---

# The default rule when you just type 'make'
all: $(BUILD_DIR) $(EXEC)

# Rule to link the object files into the final binary executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successful! Run with: ./$(EXEC)"

# Rule to compile .c source files into .o object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# --- Utility Rules ---

# Clean up compiled files to force a fresh build
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)
	@echo "Cleaned build directory."

# Automatically build and run the simulator
run: all
	./$(EXEC)

# Phony targets aren't actual files, just commands
.PHONY: all clean run