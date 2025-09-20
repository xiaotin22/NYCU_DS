CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2
TARGET = 113511266_hw2
SOURCE = 113511266_hw2.cpp
HEADER = 113511266_hw2.h

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: all clean
