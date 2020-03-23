#include "BST.h"
#include <string.h>
#include <iostream>

BST::BST()
{
}

BST::~BST()
{
}

void BST::Insert(const char key[])
{
	node* p = root;
	node* lag = nullptr;

	// If the pointer is not null, it checks to see if the pointers key is equal to the entered key
	// if it is increment the count that node and return the name and count. If it is not it will
	// check to see if the pointer is greater than the key. If so, it sets p equal to the left node otherwise
	// it sets p to the rightnode. This continues untill p is a nullptr and the lag pointer will contain p's 
	// prevous reference.
	while (p != nullptr)
	{
		if (strcmp(p->key, key) == 0)
		{
			p->count++;
			return;
		}
		comparisons++;

		lag = p;
		p = (strcmp(p->key, key) > 0) ? p->LCH : p->RCH;
		comparisons++;

	}

	// Creates a newNode with entered key
	node* newNode = new node();
	strcpy(newNode->key, key);

	if (lag == nullptr)		// if the lag point is equal to null that means the
	{						// root started of null so set the root as the new node.
		comparisons++;
		root = newNode;
		//return root->key + " " + to_string(root->count) + "\n";
	}
	else if (strcmp(newNode->key, lag->key) > 0)		// if the newNode's key is larger than the lag's key set 
	{													// lag's rightNode to newNode and set newNode's parentNode to lag
		comparisons++;
		lag->RCH = newNode;
		newNode->parent = lag;
		//return newNode->key + " " + to_string(newNode->count) + "\n";
	}
	else							// the only remaining option is if newNode's key is smaller than the
	{								// lag's key. Set lag's leftNode to newNode and newNode's parentNode to lag
		comparisons++;
		lag->LCH = newNode;
		newNode->parent = lag;
		//return newNode->key + " " + to_string(newNode->count) + "\n";
	}
}

void BST::GetTreeHeight()
{
	if (root != nullptr) TreeHeightComp(root);
	cout << "The BST height is" << treeHeight;
}

void BST::TreeHeightComp(node* p, int currentHeight)
{
	if (p->LCH != nullptr) 
	{
		//comparisons++;
		TreeHeightComp(p->LCH, currentHeight++);
	}	
	if (p->RCH != nullptr)
	{
		//comparisons++;
		TreeHeightComp(p->RCH, currentHeight++);
	}
	
	if (currentHeight > treeHeight) treeHeight = currentHeight;
}

void BST::InOrderTransversal(node* p)
{
	if (p->LCH != nullptr) InOrderTransversal(p->LCH);
	numOfNodes++;
	numOfKeys += p->count;
	if (p->RCH != nullptr) InOrderTransversal(p->RCH);
}
