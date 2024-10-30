CXX = g++

#CXXFLAGS = -Wall -Wextra -std=c++17
CXXFLAGS = -std=c++17

SOURCES = Main.cpp lexer.cpp parser.cpp
TARGET = ../bin/tec

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
