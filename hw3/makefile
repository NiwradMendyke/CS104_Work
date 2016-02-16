BIN_DIR = exe
CXX = g++ -g
EXECUTABLE1 = exe/test
EXECUTABLE2 = exe/main
EXECUTABLE3 = exe/parser
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

# main target that creates the bin and compiles each object file
all: $(BIN_DIR)/.dirstamp g_test parser $(BIN_DIR)/llistint.o

# compiles the gtest class for the actual assignment
g_test: test_hw3.cpp 
	$(CXX) $^ $(GTEST_LL) -o $(BIN_DIR)/test

# compiles the main.cpp llistint test class
main:  test/main.cpp $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o
	$(CXX) $^ -o $(BIN_DIR)/main

# compiles the parser program
parser:	parser.cpp $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o
	$(CXX) $^ -o $(BIN_DIR)/parser

# compiles the llist object file
$(BIN_DIR)/llistint.o: llistint.h llistint.cpp
	$(CXX) -c llistint.cpp -o $(BIN_DIR)/llistint.o

# compiles the stackint object file
$(BIN_DIR)/stackint.o: stackint.h stackint.cpp
	$(CXX) -c stackint.cpp -o $(BIN_DIR)/stackint.o

# creates the bin/ folder
$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

# not called by all:, executes the gtest exe file placed in exe
gtest: $(EXECUTABLE1)
	$(EXECUTABLE1)

# not called by all:, executes the main exe file placed in exe
test: $(EXECUTABLE2)
	$(EXECUTABLE2)

# not called by all:, executes the parser exe file placed in exe
parse: $(EXECUTABLE3)
	$(EXECUTABLE3) input.txt

# calls clean and empties the bin
.PHONY: clean

clean:
	rm -rf $(BIN_DIR)