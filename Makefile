CXX = g++
CXXFLAGS = -Wall -Wextra -g
SRC = $(wildcard *.cpp)
SRC += $(wildcard include/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = tony

all: $(TARGET)
	rm -f $(OBJ)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
