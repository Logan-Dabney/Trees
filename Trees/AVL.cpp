#define _CRT_SECURE_NO_WARNINGS
#include "AVL.h"
#include <string.h>
#include <iostream>

AVL::AVL()
{
	root = nullptr;
}

AVL::~AVL()
{
	if (root != nullptr) DeleteTree(root);
}

// This method is called to delete the created tree
// It is done by a post traversal.
void AVL::DeleteTree(node* p)
{
	if (p->LCH != nullptr) DeleteTree(p->LCH);	// if the p's left child isn't nullpter send it to DeleteTree()
	if (p->RCH != nullptr) DeleteTree(p->RCH);	// if the p's left child isn't nullpter send it to DeleteTree()
	delete p;									// delete the node
}

// This method is used to insert a value in to the AVL tree. It does a normal BST search
// to find where the value should be entered. If the balnace of the tree is disruptied
// due tothe insert then it will be tested to see if it is a LEFTLEFT, LEFTRIGHT,
// RIGHTRIGHT or a RIGHTLEFT case. The tree is then rebalanced. 
void AVL::Insert(char key[])
{
	node *y;			// for the newNode
	node *a, *b, *f;	// a is the last place a non-zero BF was, b will be a's child and f is a's parent
	node *p, *q;		// p is the test node for the search, q isthe lagging node
	int d, cmpChk;		// displacement, compare check

	if (root == nullptr)		// if the root is null create a new node and set it to the root
	{
		y = new node();
		strcpy(y->key, key);
		root = y;
		return;
	}

	f = q = nullptr;			// f and q will lag behind a and p
	a = p = root;				// both will start at the root for the search

	while (p != nullptr)				// while p isn't null
	{
		cmpChk = strcmp(key, p->key);	// compare the key to p's key
		comparisons++;

		if (cmpChk == 0)				// key has been found in the tree increment count 
		{
			p->count++;
			return;
		}
		if (p->BF != 0)					// finds the last place that had a non-zero BF
		{ 
			a = p;						// a becomes that place
			f = q;						// f becomes a's barent
		}
		q = p;									// q lags behidn q; 
		p = (cmpChk < 0) ? p->LCH : p->RCH;		// if key is less that p's key go left otherwise go right
	}

	// Creates a newNode with entered key
	y = new node();
	strcpy(y->key, key);

	if (cmpChk > 0)		// if the newNode's key is larger than the lag's key set 
	{													// lag's rightNode to newNode and set newNode's parentNode to lag
		q->RCH = y;
		rightChange++;
	}
	else							// the only remaining option is if newNode's key is smaller than the
	{								// lag's key. Set lag's leftNode to newNode and newNode's parentNode to lag
		q->LCH = y;
		leftChange++;
	}

	if (strcmp(key, a->key) > 0) // if the key is greater that a's key it went right d will be -1
	{ 
		b = p = a->RCH; 
		d = -1;
	} 
	else						// otherwise d = +1
	{
		b = p = a->LCH; 
		d = +1;
	} 

	comparisons++;

	while (p != y)  // Change the BF from p to the
	{               // insertion point.  Don’t do anything to new node y
		if (strcmp(key, p->key) > 0) // Same way to find BF as above with d
		{ 
			p->BF = -1; 
			p = p->RCH; 
			bfChange++;
		}
		else 
		{ 
			p->BF = +1;
			p = p->LCH; 
			bfChange++;
		}
		comparisons++;
	}

	if (a->BF == 0)  // if a's bf is 0 it will now become what d was
	{
		a->BF = d;
		bfChange++;
		noFix++;
		return;
	}

	if (a->BF == -d) // if a's bf was opposite of d then it will be 0
	{
		a->BF = 0;
		bfChange++;
		noFix++;
		return;
	}

	if (d == 1)						// if d is 1
	{
		if (b->BF == 1)				// and b's bf is also one 
		{
			LeftLeft(a, b);			// do a lefleft rotation
			LL++;
		}
		else						// OTHERWISE do a leftright
		{
			b = LeftRight(a, b);
			LR++;
		}
	}
	else							// d == -1			
	{
		if (b->BF == -1)			// and b's bf is -1 do a rightright rotation
		{
			RightRight(a, b);
			RR++;
		}
		else						// otherwise do a rightleft rotation
		{
			b = RightLeft(a, b);
			RL++;
		}
	}

	if (f == nullptr)	// if f is null set b to the new root
	{
		root = b;
		return;
	}

	if (a == f->LCH)	// if a was f's left child b is now f's left child
	{
		f->LCH = b;
		leftChange++;
		return;
	}
	if (a == f->RCH)	// if a was f's right child now b is f's right child			
	{
		f->RCH = b;
		rightChange++;
		return;
	}
}

// This is a left left rotation
// This is rotates b from a's left child to it's parent and a to b's right child
void AVL::LeftLeft(node* a, node* b)
{
	a->LCH = b->RCH;	// a's left child is no b's right child
	b->RCH = a;			// b's right child is now a

	a->BF = 0;			// BOTH BF are now 1
	b->BF = 0;

	bfChange += 2;
	leftChange++;
	rightChange++;
}

//																								a		c
// This is a left right roation. c is b's right child and it becomes		Starts of like	  /		   / \
// b's new parent as well as a's new parent. A is becomse c's left child					 b    ->  b   a
// and b is c's right child																	  \
//																								c
AVL::node* AVL::LeftRight(node* a, node* b)
{
	node* c = b->RCH;	// Sets c and it's two children
	node* cl = c->LCH;
	node* cr = c->RCH;

	c->LCH = b;			// b is c's left child
	c->RCH = a;			// a is c's righ child
	b->RCH = cl;		// c's left is now b's right
	a->LCH = cr;		// c's right is now a's left

	// There are 3 cases that hte balance factors can end up as
	// if c starts off as 0 all will be zero
	// if c starts off as 1 all are zero but a is -1
	// if c starts off as -1 all are zero by b is 1
	switch (c->BF) {
	case 0:
		c->BF = 0;
		b->BF = 0;
		a->BF = 0;
		break;
	case 1:
		c->BF = 0;
		b->BF = 0;
		a->BF = -1;
		break;
	case -1:
		c->BF = 0;
		b->BF = 1;
		a->BF = 0;
		break;
	}

	bfChange += 3;
	leftChange += 2;
	rightChange += 2;

	return c;			// return c because it needs to becomes f child now 
}

// This is a right right rotation
// This is rotates b from a's right child to it's parent and a to b's left child
void AVL::RightRight(node* a, node* b)
{
	a->RCH = b->LCH;	// a's right child is now b's left
	b->LCH = a;			// b's left child is now a

	a->BF = 0;			// BF's are now 0
	b->BF = 0;

	bfChange += 2;
	leftChange++;
	rightChange++;
}

//																							   a			c
// This is a left right roation. c is b's right child and it becomes		Starts of like	    \		   / \
// b's new parent as well as a's new parent. A is becomse c's left child						 b ->     a   b
// and b is c's right child																		/
//																							   c
AVL::node* AVL::RightLeft(node* a, node* b)
{
	node* c = b->LCH;
	node* cl = c->LCH;
	node* cr = c->RCH;

	c->RCH = b;		// b is now c's right child
	c->LCH = a;		// a is now c's left child
	b->LCH = cr;	// c's right is now b's left
	a->RCH = cl;	// c's left is now a's right

	// There are 3 cases that hte balance factors can end up as
	// if c starts off as 0 all will be zero
	// if c starts off as 1 all are zero but b is -1
	// if c starts off as -1 all are zero by a is 1
	switch (c->BF) {
	case 0:
		c->BF = 0;
		b->BF = 0;
		a->BF = 0;
		break;
	case 1:
		c->BF = 0;
		b->BF = -1;
		a->BF = 0;
		break;
	case -1:
		c->BF = 0;
		b->BF = 0;
		a->BF = 1;
		break;
	}

	bfChange += 3;
	leftChange += 2;
	rightChange += 2;

	return c;			// return c because it needs to becomes f child now 
}

// This method traverses the bst tree that was created and returns the tree height 
// this corresponds to the largest path and this is an inorder traversal that counts 
// all the nodes and keys that each node has.
void AVL::GetTreeHeightKeysNodes(node* p, unsigned int currentHeight)
{
	if (p->LCH != nullptr) GetTreeHeightKeysNodes(p->LCH, currentHeight + 1);	// if the left child is not null recursively called GetTreeHeight with the left child and one added to the height

	numOfNodes++;				// increments the numer of nodes
	numOfKeys += p->count;		// adds the count from the node the numOfKeys

	if (p->RCH != nullptr) GetTreeHeightKeysNodes(p->RCH, currentHeight + 1);  // if the right child is not null recursively called GetTreeHeight with the right child and one added to the height

	if (currentHeight > treeHeight) treeHeight = currentHeight;		// if the currentHeight is bigger than the treeHeight set the new tree height to currentHeight
}

// Prints out the data 
void AVL::GetData()
{
	if (root != nullptr) GetTreeHeightKeysNodes(root);

	cout << "AVL" << endl;
	cout << "Comparisons: " << comparisons << endl;
	cout << "Tree Height: " << treeHeight << endl;
	cout << "Number of nodes: " << numOfNodes << endl;
	cout << "Number of entries: " << numOfKeys << endl;
	cout << "Left Changes: " << leftChange << endl;
	cout << "Right Changes: " << rightChange << endl;
	cout << "No Fixes: " << noFix << endl;
	cout << "BF Changes: " << bfChange << endl;
	cout << "LL Changes: " << LL << endl;
	cout << "LR Changes: " << LR << endl;
	cout << "RR Changes: " << RR << endl;
	cout << "RL Changes: " << RL << endl;
	cout << endl;
}