# In this Makefile we'll introduce the concepts of Makefile automatic variables
# Make will simply substitute these variables with the corresponding string
# $< - first dependency
# $^ - all dependencies
# $@ - target name (whatever's before colon)

# Let's declare some variables
CXX = g++ -g
CPPFLAGS = -Wall -g
BIN_EXE = exe
BIN_DIR = bin

all: $(BIN_EXE)/.dirstamp ./reader
	-@echo "--- All Built!---"

# compiles the hashtable object into an object file
$(BIN_EXE)/hashtable.o: $(BIN_DIR)/hashtable.cpp $(BIN_DIR)/hashtable.h $(BIN_DIR)/Map.h $(BIN_EXE)/.dirstamp
	$(CXX) -c $(CPPFLAGS) $< -o $@

# compiles the splaytree object into an object file
$(BIN_EXE)/splaybst.o: $(BIN_DIR)/splaybst.cpp $(BIN_DIR)/splaybst.h $(BIN_DIR)/Map.h $(BIN_DIR)/bst.h $(BIN_EXE)/.dirstamp
	$(CXX) -c $(CPPFLAGS) $< -o $@

# $^ is an auto variable that means "all dependencies"
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
./reader: main.cpp $(BIN_EXE)/hashtable.o $(BIN_EXE)/splaybst.o
	$(CXX) $(CPPFLAGS) $^ -o $@

# Rule to ensure the $(BIN_EXE) directory exist or it'll create it.
# $@ is an auto variable that means "target name", which is $(BIN_EXE)/.dirstamp in this case
$(BIN_EXE)/.dirstamp:
	-@mkdir -p $(BIN_EXE)
	-@touch $@

.PHONY: clean tests

tests: clean
	-@$ ./reader
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_EXE)
	-@echo "--- All Clean!---"