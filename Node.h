#ifndef NODE_H
#define NODE_H

#include <cstddef>

class Node {

public:
	Node(int v);
	~Node();

	void removeFromParent();

	int value;
	Node* left;
	Node* right;
	Node* next;
	Node* prev;
	Node* parent;
};

#endif