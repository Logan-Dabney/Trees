#pragma once

using namespace std;

class BST {
public:

	BST();							// constructor
	~BST();							// destructor
	void Insert(const char key[]);	// inserts into the bst tree
	//void TreeHeight();
	void GetData();					// Get the necessary data collected


private:
	struct node						// node structure for the tree 
	{
		char key[50];				// the identifier for the node 
		unsigned int count = 1;		// number of entries
		node* parent = nullptr;		// parent pointer
		node* LCH = nullptr;		// left child
		node* RCH = nullptr;		// right child
	};
	node* root;						// root for the tree (beginning)

	// data to be collected
	unsigned int comparisons = 0;
	unsigned int numOfNodes = 0;
	unsigned int numOfKeys = 0;
	unsigned int treeHeight = 0;
	unsigned int leftChange = 0;
	unsigned int rightChange = 0;
	unsigned int parentChange = 0;

	void GetTreeHeightKeysNodes(node* p, unsigned int currentHeight = 1);	// gets the tree height, keys and nodes
	void DeleteTree(node* p);	// deletes the bst tree
};