CXX = g++
CXXFLAGS = -g -std=c++11
RM = rm -f

all: decoder encoder

clean: 
	$(RM) *.o encoder decoder

encoder: encoder.o pheap.o bheap.o fheap.o
	$(CXX) $(CXXFLAGS) -o encoder encoder.o pheap.o bheap.o fheap.o


encoder.o: encoder.cpp pheap.h bheap.h fheap.h
	$(CXX) $(CXXFLAGS) -c encoder.cpp


pheap.o: pheap.h	

bheap.o: bheap.h

fheap.o: fheap.h

decoder: decoder.o decodertree.o
	$(CXX) $(CXXFLAGS) -o decoder decoder.o decodertree.o 

decoder.o: decoder.cpp decodertree.h 
	$(CXX) $(CXXFLAGS) -c decoder.cpp

decodertree.o: decodertree.h
