CXX = g++

#CXXFLAGS = -Wall -Wextra -std=c++17
CXXFLAGS = -std=c++17

SOURCES = src/main/Main.cpp src/DFA/DFA.cpp src/lexer/lexer.cpp
TARGET = bin/tec

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
