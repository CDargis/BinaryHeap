#include "Node.h"

Node::Node(int v)
{
	value = v;
	left = NULL;
	right = NULL;
	next = NULL;
	prev = NULL;
	parent = NULL;
}

// Recursively delete all child nodes
Node::~Node()
{
	if(left)
		delete left;
	if(right)
		delete right;
}

// This function will remove a node from its parent
void Node::removeFromParent()
{
	Node* parent = this->parent;
	if(parent == NULL)
		return;
	if(parent->left == this)
		parent->left = NULL;
	else if(parent->right == this)
		parent->right = NULL;
	this->parent = NULL;
}