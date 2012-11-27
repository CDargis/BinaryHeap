#include "BinaryHeap.h"
#include <iostream>        //DEBUGGING
#include <sstream>
#include <queue>

BinaryHeap::BinaryHeap()
{
	root = NULL;
	last_inserted = NULL;
	count = 0;
}

// Iterate through the heap, in breadth-first order, populate the new heap
BinaryHeap::BinaryHeap(const BinaryHeap& h)
{
	root = NULL;
	last_inserted = NULL;
	count = 0;

	std::queue<Node*> q;
	if(h.root)
		q.push(h.root);
	while(!q.empty())
	{
		Node* n = q.front();
		this->add(n->value);
		q.pop();
		if(n->left)
			q.push(n->left);
		if(n->right)
			q.push(n->right);
	}
}

BinaryHeap::~BinaryHeap()
{
	if(root)
		delete root;    // Deleting the root will recursively delete all children nodes
}

//------- Core Functionality Functions -------------------------------------------------------------------

// First determine next available location to be inserted
// Then call percolateUp to move the node to its correct spot in the tree to maintain the heap property
void BinaryHeap::add(int val)
{
	if(root == NULL)               // Check if the tree is empty
	{
		root = new Node(val);
		last_inserted = root;
		count++;
		return;
	}

	if(!exists(val))    // If the value doesn't exist in the tree, then add it
	{
		Node* node = new Node(val);
		Node* last = last_inserted;
		if(last->parent == NULL)            // Looking at the root?
		{
			last->left = node;
			node->parent = last;
		}
		else
		{
			last = last->parent;           // Checking if left child is next to be inserted
			if(last->left == NULL)
			{
				last->left = node;
				node->parent = last;
			}
			else
			{
				if(last->right == NULL)     // Checking if right child is next to be inserted
				{
					last->right = node;
					node->parent = last;
				}
				else
				{
					last->next->left = node;
					node->parent = last->next;
				}
			}
		}
		last_inserted->next = node;   //Adjust the pointer of the previously inserted node
		node->prev = last_inserted;
		last_inserted = node;
		count++;
		percolateUp(node);
	}
}

// First locate the node to be removed. If it doesn't exist simply return. Otherwise, remove the last node from
// the tree, remove the last node in the tree, take the value from the removed node and 
// copy it into the node to be deleted. Percolate the node down the tree it its correct position.
void BinaryHeap::remove(int val)
{
	Node* node = this->find(val, root);	
	if(node == NULL)
		return;                    // Return if the number doesn't exist in the tree
	Node* last = this->removeLast();
	this->swap(node, last);
	delete last;
	count--;
	this->percolateDown(node);
	if(count == 0)
		root = NULL;
}

//---------- Helper Functions ----------------------------------------------------------------------

// Return true if a value exists in the tree, false otherwise
bool BinaryHeap::exists(int val)
{
	if(this->find(val, root) == NULL)
		return false;
	else return true;
}

// Return a Node pointer if the value exists, otherwise return null
Node* BinaryHeap::find(int val, Node* node)
{
	if(node == NULL)
		return NULL;
	if(val == node->value)
		return node;
	if(val > node->value)
		return NULL;
	Node* lResult = find(val, node->left);
	Node* rResult = find(val, node->right);
	if(lResult != NULL)
		return lResult;
	if(rResult != NULL)
		return rResult;
	else return NULL;
}

// Swap the values in two nodes
void BinaryHeap::swap(Node* n1, Node* n2)
{
	int temp = n1->value;
	n1->value = n2->value;
	n2->value = temp;
}

// Percolate a node up the tree to its correct position
void BinaryHeap::percolateUp(Node* n)
{
	if(n == root)
		return;
	if(n->value > n->parent->value)
	{
		swap(n, n->parent);
		percolateUp(n->parent);
	}
}

// Percolate a node down the tree until the heap property is satisfied
void BinaryHeap::percolateDown(Node* n)
{
	if(n->left == NULL)
		return;                 // Reached a leaf
	if(n->right == NULL)        // Is the left the only child?
	{
		if(n->value < n->left->value)
			this->swap(n, n->left);
		return;
	}
	else                       // Recursive case, the node has two children
	{
		if((n->value < n->left->value) || (n->value < n->right->value)) 
		{
			Node* temp = this->max(n->left, n->right);    // Replace with maximum of chidlren
			this->swap(n, temp);
			this->percolateDown(temp);
		}
	}
}

// Print the tree in breadth-first order using a queue
void BinaryHeap::printTree()
{
	if(root == NULL)
		return;
	std::queue<Node*> q;
	q.push(root);
	while(!q.empty())
	{
		std::stringstream left;
		std::stringstream right;
		Node* n = q.front();
		q.pop();
		if(n->left)
		{
			left << n->left->value;
			q.push(n->left);
		}
		else left << "N";
		if(n->right)
		{
			right << n->right->value;
			q.push(n->right);
		}
		else right << "N";
		std::cout << "[" << n->value << " - (" << left.str() << ", " << right.str() << ")] ";
	}
	std::cout << std::endl;
}

// Return a pointer to a node that was the last to be inserted
// Remove all ties of the node to the tree
Node* BinaryHeap::removeLast()
{
	if(last_inserted == NULL)
		return NULL;               // Return null if the tree is empty
	Node* node = last_inserted;
	last_inserted = last_inserted->prev;
	if(last_inserted)
		last_inserted->next = NULL;
	node->removeFromParent();
	return node;
}

// Return a pointer to the node than contains the maximum value
Node* BinaryHeap::max(Node* n1, Node* n2)
{
	if(n1->value > n2->value)
		return n1;
	else return n2;
}

// Returns a vector containing the tree's elements, in breadth-first order
std::vector<int> BinaryHeap::asVector()
{
	std::vector<int> result;
	if(root == NULL)
		return result;
	std::queue<Node*> q;
	q.push(root);
	while(!q.empty())
	{
		Node* n = q.front();
		result.push_back(n->value);
		q.pop();
		if(n->left)
			q.push(n->left);
		if(n->right)
			q.push(n->right);
	}
	return result;
}

// ----------- Static Functions -------------------------------------------------------------------

// Return the set union of heaps h1 and h2
BinaryHeap BinaryHeap::setUnion(BinaryHeap h1, BinaryHeap h2)
{
	BinaryHeap newHeap;
	std::vector<int> h1Vector = h1.asVector();
	std::vector<int> h2Vector = h2.asVector();
	std::vector<int>::iterator it;
	for(it = h1Vector.begin(); it != h1Vector.end(); it++)
		newHeap.add((*it));
	for(it = h2Vector.begin(); it != h2Vector.end(); it++)
		newHeap.add((*it));
	return newHeap;	
}

// Return the set intersection of heaps h1 and h2
BinaryHeap BinaryHeap::setIntersection(BinaryHeap h1, BinaryHeap h2)
{
	BinaryHeap newHeap;
	std::vector<int> v = h1.asVector();
	std::vector<int>::iterator it;
	for(it = v.begin(); it != v.end(); it++)
		if(h2.exists((*it)))
			newHeap.add((*it));
	return newHeap;
}