#include <iostream>
#include <string>
#include <sstream>

#include "BinaryHeap.h"

// Pointers to the two heaps used by the program
BinaryHeap* h1;
BinaryHeap* h2;

// Function signatures
void mainLoop();
void printUsage();
int getIntFromUser();
void swap();
void clear();
void add();
void remove();
void display();
void copy();
void setUnion();
void setIntersection();

// Main function
int main(int argc, char **argv)
{
	h1 = new BinaryHeap();
	h2 = new BinaryHeap();
	std::cout << "Binary Heap Calculator\n" << "Chris Dargis\n" 
		<< "CS474 - Fall 2012\n" << "-----------------------\n";
	printUsage();
	mainLoop();
	std::cout << "\nBye!\n";

	if(h1)
		delete h1;
	if(h2)
		delete h2;

	return 0;
}

// Continuously run a loop that waits for the user's input
// As soon as the user types 'q', break from the loop and return
// to main
void mainLoop()
{
	while(true)
	{
		std::string input;
		std::cout << "Command: ";
		getline(std::cin, input);
		char in = input.at(0);
		switch(in) 
		{
			case 'c': clear();	   		 break;
			case 'o': copy();	   		 break;
			case 's': swap(); 	   		 break;
			case 'd': display();   		 break;
			case 'a': add();	   		 break;
			case 'r': remove();	   		 break;
			case 'u': setUnion();  		 break;
			case 'i': setIntersection(); break;
			case 'q': 					 return;
			default: printUsage(); 		 break;
		} 
	}
}

// Output the recognized commands
void printUsage()
{
	std::cout << "\nUsage:\n" << "  c - Clear heap\n  o - Copy heap\n  s - Switch heap\n  d - Display heap contents\n"
	<< "  a - Add element\n  r - Remove element\n  u - Union\n  i - Intersection\n  q - Quit\n\n";
}

// get an integer from the user
int getIntFromUser()
{
	int i;
	std::string str;
	std::cout << "Please enter a value: ";
	getline(std::cin, str);
	std::stringstream(str) >> i;
	return i;
}

// Function to swap the heaps
void swap()
{
	BinaryHeap* temp = h1;
	h1 = h2;
	h2 = temp;
}

// Function to clear the first heap
void clear()
{
	if(h1)
		delete h1;
	h1 = new BinaryHeap();
}

// Function add a number to the first heap
void add()
{
	int val = getIntFromUser();
	h1->add(val);
}

// Function to remove a number from the first heap
void remove()
{
	int val = getIntFromUser();
	h1->remove(val);
}

// Display the contents of each heap
void display()
{
	std::cout << "Contents of h1:\n";
	h1->printTree();
	std::cout << "Contents of h2:\n";
	h2->printTree();
}

// Call functions to copy the first heap to the second heap (deep-copy)
void copy()
{
	if(h2)
		delete h2;
	h2 = new BinaryHeap(*h1);
}

// Call the static function that performs set union
void setUnion()
{
	BinaryHeap newHeap = BinaryHeap::setUnion(*h1, *h2);
	if(h1)
		delete h1;
	h1 = new BinaryHeap(newHeap);
}

// Call the static function that perfroms set intersection
void setIntersection()
{
	BinaryHeap newHeap = BinaryHeap::setIntersection(*h1, *h2);
	if(h1)
		delete h1;
	h1 = new BinaryHeap(newHeap);
}