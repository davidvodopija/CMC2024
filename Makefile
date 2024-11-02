# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude -Iutil

# Folders
SRC_DIR = src
INC_DIR = include
UTIL_DIR = util
OBJ_DIR = obj
BIN_DIR = bin

# Source and Object Files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(UTIL_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(patsubst $(UTIL_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)))

# Target Executable
TARGET = $(BIN_DIR)/main

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source and util files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTIL_DIR)/%.cpp $(UTIL_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
