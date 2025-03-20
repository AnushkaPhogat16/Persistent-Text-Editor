CXX = g++
CXXFLAGS = -std=c++11 -02 -Wall

all: editor

editor: main.o Rope.o
	$(CXX) $(CXXFLAGS) -o editor main.o Rope.o

main.o: main.cpp Rope.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Rope.o: Rope.cpp Rope.h
	$(CXX) $(CXXFLAGS) -c Rope.cpp

clean:
	rm -f *.o editor
