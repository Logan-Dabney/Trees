#pragma once

using namespace std;

class SkipList {

public:

	SkipList();
	~SkipList();
	void Insert(char key[]);
	void Find(char key[]);

private:
	struct node 
	{
		char key[50];
		node* left = nullptr;
		node* right = nullptr;
		node* up = nullptr;
		node* down = nullptr;
	};

	node* head;
	node* tail;
	int h;
	int n;
	unsigned int comparisons = 0;
	unsigned int numOfNodes = 0;
	unsigned int numOfKeys = 0;

	const char POS_INF[7]{ "posInf" };
	const char NEG_INF[7]{ "negInf" };
	
	void NewLevel();
	node* search(char key[]);
	void InOrderTraverse(); //non-recursive 
};
