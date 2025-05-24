CXX = g++
CXXFLAGS = -Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self

# los folders
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj

MAIN = main.cpp

CPPFILES = $(wildcard ./lib/*.cpp)
HFILES = $(wildcard ./lib/*.h)
SRCS = $(MAIN) $(CPPFILES)

OBJS = $(SRCS:.cpp=.o)

TARGET = juego

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -c $< -o $@

run: all
	./$(TARGET)


clean:
	rm -f $(OBJS) $(TARGET)

temp: clean
	$(MAKE) all
	./$(TARGET)
	rm -f $(OBJS) $(TARGET)

