#pragma once
#include <random>

using namespace std;

class SkipList {

public:

	SkipList();					// constructor
	~SkipList();				// destructor
	void Insert(char key[]);	// inserts into a skiplist
	void GetData();				// gets data collect over  list creation

private:
	struct node					// node structure for list
	{
		char key[50];			// key in each node
		unsigned int count = 1;	// number of entires
		node* left = nullptr;	// left pointer
		node* right = nullptr;	// right pointer
		node* up = nullptr;		// up pointer
		node* down = nullptr;	// down pointer
	};

	node* head;					// head of list
	node* tail;					// tail of list
	mt19937 coin;
	int h = 1;					// height of list
	int n = 0;					// number of nodes
	int numOfKeys = 0;			// number of entries
	unsigned int comparisons = 0;
	unsigned int headsTossed = 0;
	unsigned int leftChange = 1;
	unsigned int rightChange = 1;
	unsigned int upChange = 0;
	unsigned int downChange = 0;

	const char POS_INF[50]{ "posInf" };	// constant value for tail
	const char NEG_INF[50]{ "negInf" };	// constant value for head

	void NewLevel();						// createa new level to the list
	node* search(char key[], bool& found);	// searches the list
	void InOrderTraversal();				// traverse the list (collects data)
};
