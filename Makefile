CXX = g++
CXXFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

TARGET = snake
SOURCE = main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
