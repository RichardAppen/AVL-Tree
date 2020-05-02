# use g++ with C++11 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++11
OUTFILES=MarketObserver

all: $(OUTFILES)

MarketObserver: MarketObserver.cpp BinaryTree.cpp BinaryTree.h
	$(CXX) $(CXXFLAGS) -o MarketObserver MarketObserver.cpp BinaryTree.cpp

clean:
	$(RM) $(OUTFILES) *.o
