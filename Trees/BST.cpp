#define _CRT_SECURE_NO_WARNINGS
#include "BST.h"
#include <string.h>
#include <iostream>

BST::BST()
{
	root = nullptr;
}

BST::~BST()
{
	if (root != nullptr) DeleteTree(root);
}

// This method is called to delete the created tree
// It is done by a post traversal.
void BST::DeleteTree(node* p)
{

	if (p->LCH != nullptr) DeleteTree(p->LCH);	// if the p's left child isn't nullpter send it to DeleteTree()
	if (p->RCH != nullptr) DeleteTree(p->RCH);	// if the p's left child isn't nullpter send it to DeleteTree()
	delete p;									// delete the node
}

// This function inserts nodes on a Binary search tree. It runs through
// all the possiblities (no root, left branch of parent node, right branch of parent node)
// It also maintains the amount of comparisons made when inserting into the tree.
void BST::Insert(const char key[])
{
	node* p = root;
	node* lag = nullptr;
	int cmpChk;

	// If the pointer is not null, it checks to see if the pointers key is equal to the entered key
	// if it is increment the count that node and return the name and count. If it is not it will
	// check to see if the pointer is greater than the key. If so, it sets p equal to the left node otherwise
	// it sets p to the rightnode. This continues untill p is a nullptr and the lag pointer will contain p's 
	// prevous reference.
	while (p != nullptr)
	{
		cmpChk = strcmp(key, p->key);
		comparisons++;

		if (cmpChk == 0)
		{
			p->count++;
			return;
		}

		lag = p;
		p = (cmpChk < 0) ? p->LCH : p->RCH;
	}

	// Creates a newNode with entered key
	node* newNode = new node();
	strcpy(newNode->key, key);

	if (lag == nullptr)		// if the lag point is equal to null that means the
	{						// root started of null so set the root as the new node.
		root = newNode;
		//return root->key + " " + to_string(root->count) + "\n";
	}
	else if (cmpChk > 0)		// if the newNode's key is larger than the lag's key set 
	{													// lag's rightNode to newNode and set newNode's parentNode to lag
		lag->RCH = newNode;
		newNode->parent = lag;

		rightChange++;
		parentChange++;
		//return newNode->key + " " + to_string(newNode->count) + "\n";
	}
	else							// the only remaining option is if newNode's key is smaller than the
	{								// lag's key. Set lag's leftNode to newNode and newNode's parentNode to lag
		lag->LCH = newNode;
		newNode->parent = lag;

		leftChange++;
		parentChange++;
		//return newNode->key + " " + to_string(newNode->count) + "\n";
	}
}

// This is the pubkic method to get the tree height. It calls the GetTreeHeight() (private method)
// to get the height.
//void BST::TreeHeight()
//{
//	if (root != nullptr) GetTreeHeight(root);
//	cout << "The BST height is" << treeHeight;
//}

// This method traverses the bst tree that was created and returns the tree height 
// this corresponds to the largest path and this is an inorder traversal that counts 
// all the nodes and keys that each node has.
void BST::GetTreeHeightKeysNodes(node* p, unsigned int currentHeight)
{
	if (p->LCH != nullptr) GetTreeHeightKeysNodes(p->LCH, currentHeight + 1);	// if the left child is not null recursively called GetTreeHeight with the left child and one added to the height

	numOfNodes++;				// increments the numer of nodes
	numOfKeys += p->count;		// adds the count from the node the numOfKeys

	if (p->RCH != nullptr) GetTreeHeightKeysNodes(p->RCH, currentHeight + 1);  // if the right child is not null recursively called GetTreeHeight with the right child and one added to the height

	if (currentHeight > treeHeight) treeHeight = currentHeight;		// if the currentHeight is bigger than the treeHeight set the new tree height to currentHeight
}

// this is an inorder traversal that counts all the nodes and keys that each node has.
//void BST::InOrderTransversal(node* p)
//{
//	if (p->LCH != nullptr) InOrderTransversal(p->LCH);	// if the left child is not null recursively call InOrderTraversal with the left child
//	numOfNodes++;				// increments the numer of nodes
//	numOfKeys += p->count;		// adds the count from the node the numOfKeys
//	if (p->RCH != nullptr) InOrderTransversal(p->RCH);	// if the RIGHT child is not null recursively call InOrderTraversal with the right child
//
//}

void BST::GetData()
{
	if(root != nullptr) GetTreeHeightKeysNodes(root);
	//InOrderTransversal(root);
	cout << "BST" << endl;
	cout << "Comparisons: " << comparisons << endl;
	cout << "Tree Height: " << treeHeight << endl;
	cout << "Number of nodes: " << numOfNodes << endl;
	cout << "Number of entries: " << numOfKeys << endl;
	cout << "Left Changes: " << leftChange << endl;
	cout << "Right Changes: " << rightChange << endl;
	cout << "Parent Changes: " << parentChange << endl;
	cout << endl;
	//cout << "Total: " << comparisons +  leftChange + rightChange + parentChange + numOfNodes + numOfKeys << endl;
}
