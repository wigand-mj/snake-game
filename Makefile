CXX := g++
CXXFLAGS := -Wall
LIBS := -std=c++14
LFLAGS := -lwinmm
TARGET := game
OBJECTS := main.o board.o snake.o Io.o
H_PATH := ./include
LIB_PATH := ./lib
TARGET_PATH := ./build
SRC_PATH := ./src
OBJECT_PATH := ./src/obj
SRC = $(wildcard $(SRC_PATH)/*.cpp)

.PHONY: build all clean
all: build $(TARGET_PATH)/$(TARGET) clean

$(TARGET_PATH)/$(TARGET): $(SRC:$(SRC_PATH)/%.cpp=$(OBJECT_PATH)/%.o)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LFLAGS) $(LIBS)

$(OBJECT_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LIBS)

clean:
	-@rm -rvf $(OBJECT_PATH)

build:
	mkdir -p $(TARGET_PATH)
	mkdir -p $(OBJECT_PATH)