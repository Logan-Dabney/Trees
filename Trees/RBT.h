#pragma once

using namespace std;

class RBT {

public:
	RBT();							// creates the nil and root nodes
	~RBT();							// destroys the RB tree
	void Insert(char key[]);		// inserts into the RBT Tree
	void GetData();					// Gets all the data computed during tree creation process

private:
	struct node						// struture that makes up the tree
	{
		char key[50];				// key value 
		int count = 1;				// amount of time entered
		bool color;					// false is black and true is red 
		node* parent = nullptr;		// the parent pointer of this node
		node* LCH = nullptr;		// the left child pointer
		node* RCH = nullptr;		// the right child pointer
	};

	node* nil;						// root node and nil node  
	node* root;						// the rest are class variables that maintain
	unsigned int comparisons = 0;	// different values needed to comapare different trees
	unsigned int numOfNodes = 0;
	unsigned int numOfKeys = 0;
	unsigned int leftChange = 0;
	unsigned int rightChange = 0;
	unsigned int parentChange = 0;
	unsigned int colorChange = 0;
	unsigned int treeHeight = 0;
	unsigned int noFix = 0;
	unsigned int case1 = 0;
	unsigned int case2 = 0;
	unsigned int case3 = 0;

	void Fixup(node* z);			// Fixs any errors produced from adding a value
	void LeftRotation(node* z);		// Used to correct either a Case 2 or Case 3 error by rotating nodes
	void RightRotation(node* z);	// Used to correct either a Case 2 or Case 3 error by rotating nodes
	void GetTreeHeightKeysNodes(node* p, unsigned int currentHeight = 1);	// gets the tree height, number of node and number of keys
	void DeleteTree(node* z);		// called by ~RBT() to delete all nodes of a tree
};
