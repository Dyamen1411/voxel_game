# ---
# General infos
# ---

APP_NAME=app

# ---
# Build tools and flags
# ---

CC=g++

LFLAGS:=-lm
FLAGS=`sdl2-config --cflags --libs` -lGLESv2

# ---
# Directories and sources
# ---

SRC_DIR=src
INC_DIR=inc
BIN_DIR=bin

SRCS:=$(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
BINS:=$(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# ---
# General targets
# ---

# Default target
all: build

# Build target
build: $(APP_NAME)

# Clean target
clean:
	@rm -rf $(BINS)

# Rebuild everything
re: clean build

# Run the app
run: $(APP_NAME)
	@./$(APP_NAME)


.PHONY: all build clean re run 

# ---
# Build targets and rules
# ---

# Linking the app
$(APP_NAME): $(BINS)
	@echo "Linking..."
	$(CC) $(BINS) -o $(APP_NAME) $(LFLAGS) $(FLAGS)

# Rule for make each objects files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "$(CC) $<..."
	@$(CC) -c $< -I$(INC_DIR) -o $@
