all: HeapCalculator

HeapCalculator: main.o Node.o BinaryHeap.o
	g++ main.o Node.o BinaryHeap.o -o HeapCalculator

main.o: main.cpp
	g++ -c main.cpp

Node.o: Node.cpp
	g++ -c Node.cpp

BinaryHeap.o: BinaryHeap.cpp
	g++ -c BinaryHeap.cpp

clean: 
	rm -rf *o HeapCalculator