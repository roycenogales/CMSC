CXX = g++
CXXFLAGS = -Wall -g

hw8.o:	hw8.cpp
	$(CXX) $(CXXFLAGS) -c hw8.cpp

hw8:	hw8.o
	$(CXX) $(CXXFLAGS) hw8.o -o hw8

run:
	./hw8

val:
	valgrind ./hw8
