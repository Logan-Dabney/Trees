#pragma once

using namespace std;

class AVL {

public:

	AVL();						// Contructor
	~AVL();						// Destructor
	void Insert(char key[]);	// inserts into a AVL tree
	void GetData();				// gets data collect over tree creation

private:
	struct node						// node structure for tree
	{
		char key[50];				// key in each node
		int BF = 0;					// balance facter
		int count = 1;				// the number of entries
		node* LCH = nullptr;		// left child
		node* RCH = nullptr;		// right child
	};

	node* root;						// root of the tree
	unsigned int comparisons = 0;	// all data to be collected
	unsigned int numOfNodes = 0;
	unsigned int numOfKeys = 0;
	unsigned int leftChange = 0;
	unsigned int rightChange = 0;
	unsigned int parentChange = 0;
	unsigned int treeHeight = 0;
	unsigned int noFix = 0;
	unsigned int bfChange = 0;
	unsigned int LL = 0;
	unsigned int LR = 0;
	unsigned int RR = 0;
	unsigned int RL = 0;

	void DeleteTree(node* p);			// deletes the tree
	void LeftLeft(node* a , node* b);	// does a left left rotation
	node* LeftRight(node* a, node* b);	// does a left right rotation
	void RightRight(node* a, node* b);	// does a right right rotation
	node* RightLeft(node* a, node* b);	// does a right left rotation
	void GetTreeHeightKeysNodes(node* p, unsigned int currentHeight = 1);	// gets the tree height, number of node and number of keys
};