#pragma once

using namespace std;

class AVL {

public:

	void Insert(char key[]);

private:
	struct node
	{
		char key[50];
		int balFact = 0;
		node* parent = nullptr;
		node* LCH = nullptr;
		node* RCH = nullptr;
	};

	node* root = nullptr;
	unsigned int comparisons = 0;
	unsigned int numOfNodes = 0;
	unsigned int numOfKeys = 0;

	void LeftLeft(node* p);
	void LeftRight(node* p);
	void RightRight(node* p);
	void RightLeft(node* p);
	void InOrderTraversal(node* p);
};