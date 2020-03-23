#pragma once

using namespace std;

class RBT {

public:

	void Insert(char key[]);

private:
	struct node
	{
		char key[50];
		int height = 0;
		bool color;			// false is black and true is red 
		node* parent = nullptr;
		node* LCH = nullptr;
		node* RCH = nullptr;
	};

	node* nil = nullptr;
	node* root = nullptr;
	unsigned int comparisons = 0;
	unsigned int numOfNodes = 0;
	unsigned int numOfKeys = 0;

	void Case1(node* p);
	void Case2(node* p);
	void Case3(node* p);
};
