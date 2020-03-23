#pragma once

using namespace std;

class BST {
public:

	BST();
	~BST();
	void Insert(const char key[]);
	void GetTreeHeight();



private:
	struct node 
	{
		char key[50];
		unsigned int count = 1;
		node* parent = nullptr;
		node* LCH = nullptr;
		node* RCH = nullptr;
	};
	node* root = nullptr;

	unsigned int comparisons = 0;
	unsigned int numOfNodes = 0;
	unsigned int numOfKeys = 0;
	int treeHeight = 0;

	void TreeHeightComp(node* p, int currentHeight = 0);
	void InOrderTransversal(node* p);
};