CXX = g++
CXXFLAGS = -std=c++11

SRC = main.cpp
TARGET = main.out

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
