#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <cstddef>
#include <vector>
#include "Node.h"

class BinaryHeap {

public:
	BinaryHeap();
	BinaryHeap(const BinaryHeap& h);
	~BinaryHeap();

	static BinaryHeap setUnion(BinaryHeap h1, BinaryHeap h2);
	static BinaryHeap setIntersection(BinaryHeap h1, BinaryHeap h2);

	void add(int val);
	void remove(int val);

	bool exists(int val);
	void printTree();
	std::vector<int> asVector();

	Node* root;
	Node* last_inserted;
	int count;

private:
	Node* find(int val, Node* node);
	void swap(Node* n1, Node* n2);
	void percolateUp(Node* n);
	void percolateDown(Node* n);
	Node* removeLast();
	Node* max(Node* n1, Node* n2);
};

#endif