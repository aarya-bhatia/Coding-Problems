BIN_DIR=bin
OBJ_DIR=obj

FILES=$(shell ls | grep '\.cpp')
TARGETS=$(FILES:%.cpp=$(BIN_DIR)/%)

all: DIR | $(TARGETS)

DIR:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

$(TARGETS): $(BIN_DIR)/%: $(OBJ_DIR)/%.cpp.o
	g++ -std=c++11 $^ -o $@

$(OBJ_DIR)/%.cpp.o: %.cpp
	g++ -std=c++11 -Wall -c $< -o $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
