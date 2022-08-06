CPP_SRC=$(wildcard src/*.cpp)
C_SRC=$(wildcard src/*.c)

INC_FILES=$(shell find include -type f -name "*.cpp")
INC_FILES+=$(shell find include -type f -name "*.hpp")

CPP_TARGETS=$(CPP_SRC:src/%.cpp=bin/%)
C_TARGETS=$(C_SRC:src/%.c=bin/%)

DIRS=$(shell find include src -type d)
INCLUDES=$(addprefix -I, $(DIRS))

all: $(CPP_TARGETS) $(C_TARGETS)

$(CPP_TARGETS): bin/%: obj/%.cpp.o
	mkdir -p $(dir $@);
	g++ -std=c++11 $^ -o $@

$(C_TARGETS): bin/%: obj/%.c.o
	mkdir -p $(dir $@);
	gcc -std=c11 $^ -o $@

obj/%.cpp.o: src/%.cpp
	mkdir -p $(dir $@);
	g++ -std=c++11 -Wall $(INCLUDES) -c $< -o $@

obj/%.c.o: src/%.c
	mkdir -p $(dir $@);
	gcc -std=c11 -Wall -c $< -o $@

debug:
	@echo $(CPP_TARGETS)
	@echo $(C_TARGETS)

clean:
	rm -rf bin/ obj/
