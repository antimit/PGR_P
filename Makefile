CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
INCLUDE_DIR = -I$(PWD)/include -I$(PWD)/include/States -I$(PWD)/include/Jewels -I$(PWD)/include/Abilities  
SRC = $(wildcard src/*.cpp) $(wildcard Astar/*.cpp)
OBJ = $(SRC:.cpp=.o)
OUT = $(PWD)/myProgram


all: $(OUT)


$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $(OUT) $(LDFLAGS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c $< -o $@



clean:
	rm -rf $(OBJ) 

fclean:clean
	rm -rf $(OUT)


.PHONY: all clean