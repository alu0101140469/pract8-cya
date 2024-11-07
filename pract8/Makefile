CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: Grammar2CNF

Grammar2CNF: Grammar2CNF.o Grammar.o Production.o
	$(CXX) $(CXXFLAGS) -o Grammar2CNF Grammar2CNF.o Grammar.o Production.o

Grammar2CNF.o: Grammar2CNF.cc Grammar.h Production.h
	$(CXX) $(CXXFLAGS) -c Grammar2CNF.cc

Grammar.o: Grammar.cc Grammar.h Production.h
	$(CXX) $(CXXFLAGS) -c Grammar.cc

Production.o: Production.cc Production.h
	$(CXX) $(CXXFLAGS) -c Production.cc

clean:
	rm -f *.o Grammar2CNF
