BIN_DIR = exe
BIN_SRC = src
CXX = g++
EXECUTABLE = exe/main

# main target that creates the bin and compiles each object file
all: $(BIN_DIR)/.dirstamp main

# compiles the main class
main: test/main.cpp $(BIN_DIR)/llistint.o
	$(CXX) $^ -o $(BIN_DIR)/main

# compiles the llist object file
$(BIN_DIR)/llistint.o: llistint.h llistint.cpp
	$(CXX) -c llistint.cpp -o $(BIN_DIR)/llistint.o

# creates the bin/ folder
$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

# not called by all:, executes the exe file placed in exe
test: $(EXECUTABLE)
	$(EXECUTABLE)

# calls clean and empties the bin
.PHONY: clean

clean:
	rm -rf $(BIN_DIR)