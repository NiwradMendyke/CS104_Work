# In this Makefile we'll introduce the concepts of Makefile automatic variables
# Make will simply substitute these variables with the corresponding string
# $< - first dependency
# $^ - all dependencies
# $@ - target name (whatever's before colon)

# Let's declare some variables
CC = g++
CPPFLAGS = -Wall -g
BIN_DIR = bin
BIN_EXE = exe
STACKS = $(BIN_DIR)/StackInt.o $(BIN_DIR)/LlistInt.o
TARGETS = $(BIN_DIR)/LetStatement.o $(BIN_DIR)/PrintStatement.o $(BIN_DIR)/PrintallStatement.o $(BIN_DIR)/AddStatement.o $(BIN_DIR)/SubStatement.o $(BIN_DIR)/MultStatement.o $(BIN_DIR)/DivStatement.o $(BIN_DIR)/IfStatement.o $(BIN_DIR)/GotoStatement.o $(BIN_DIR)/GosubStatement.o $(BIN_DIR)/ReturnStatement.o $(BIN_DIR)/EndStatement.o

all: $(BIN_DIR)/ProgramState.o $(TARGETS) $(BIN_EXE)/.dirstamp $(BIN_EXE)/facile
	-@echo "--- All Built!---"

$(BIN_DIR)/ProgramState.o: Statements/ProgramState.cpp Statement_headers/ProgramState.h $(STACKS) $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/StackInt.o: StackInt/stackint.cpp StackInt/stackint.h $(BIN_DIR)/LlistInt.o $(BIN_DIR)/.dirstamp 
	$(CC) -c StackInt/stackint.cpp -o $@

$(BIN_DIR)/LlistInt.o: StackInt/llistint.cpp StackInt/llistint.h $(BIN_DIR)/.dirstamp 
	$(CC) -c StackInt/llistint.cpp -o $@

# Compiles any .o file by using the .cpp and .h file of the same name. 
$(BIN_DIR)/%.o: Statements/%.cpp Statement_headers/%.h $(BIN_DIR)/ProgramState.o $(STACKS)
	$(CC) $(CPPFLAGS) -c $< -o $@

# $^ is an auto variable that means "all dependencies"
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
$(BIN_EXE)/facile: Facile.cpp $(TARGETS) $(BIN_DIR)/ProgramState.o $(STACKS)
	$(CC) $(CPPFLAGS) $^ -o $@

# Rule to ensure the $(BIN_DIR) directory exist or it'll create it.
# $@ is an auto variable that means "target name", which is $(BIN_DIR)/.dirstamp in this case
$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $@

# Rule to ensure the $(BIN_EXE) directory exist or it'll create it.
# $@ is an auto variable that means "target name", which is $(BIN_EXE)/.dirstamp in this case
$(BIN_EXE)/.dirstamp:
	-@mkdir -p $(BIN_EXE)
	-@touch $@

.PHONY: clean tests

tests: clean
	-@$(BIN_EXE)/facile
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
