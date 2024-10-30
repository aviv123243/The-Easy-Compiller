CXX = g++

#CXXFLAGS = -Wall -Wextra -std=c++17
CXXFLAGS = -std=c++17

SOURCES = src/Main.cpp src/lexer.cpp src/parser.cpp
TARGET = bin/tec

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
