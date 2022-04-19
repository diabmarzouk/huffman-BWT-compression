HEADERS = huffTree.h huffObj.h freqCount.h huffNode.h bwt.h codec.h

default: main

main.o: main.cpp $(HEADERS)
	g++ -c main.cpp -o main.o

debug: main.cpp $(HEADERS)
	g++ -c -g main.cpp -o main.o

main: main.o
	g++ main.o -o bwtHuff
clean:
	-rm -f main.o
	-rm -f bwtHuff
