CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
SRCS = node.cpp fingertable.cpp test_chord.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = chord_test

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) 