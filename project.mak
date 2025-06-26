CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC = src/main.cpp src/memory_manager.cpp
INC = -Iinclude

all: simulator

simulator: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) -o simulator

clean:
	rm -f simulator
