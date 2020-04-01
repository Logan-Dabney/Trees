#define _CRT_SECURE_NO_WARNINGS
#include "RBT.h"
#include <string.h>
#include <iostream>

RBT::RBT()
{
	nil = new node();

	nil->count = 0;
	nil->color = false;
	root = nil;
}

RBT::~RBT()
{
	if (root != nil) DeleteTree(root);
	delete nil;
}

// This method is called to delete the created tree
// It is done by a post traversal.
void RBT::DeleteTree(node* p)
{

	if (p->LCH != nil) DeleteTree(p->LCH);	// if the p's left child isn't nil send it to DeleteTree()
	if (p->RCH != nil) DeleteTree(p->RCH);	// if the p's left child isn't nil send it to DeleteTree()
	delete p;								// delete the node
}


// This function inserts nodes on a Red Black tree. It runs through
// all the possiblities (no root, left branch of parent node, right branch of parent node)
// It also maintains the amount of comparisons made when inserting into the tree.
void RBT::Insert(char key[])
{
	node* lag = nil;
	node* p = root;
	int cmpChk;

	while (p != nil)							// while pointer isn't nil (after a child)
	{
		cmpChk = strcmp(key, p->key);			// perform a compare check
		comparisons++;							// add a comparison

		if (cmpChk == 0)						// if the compare check was 0 
		{										// increment p's count and return
			p->count++;
			return;
		}

		lag = p;								// set lag to p (to stay one step behind)
		p = (cmpChk < 0) ? p->LCH : p->RCH;		// if the copmparte check is less than 0 set p to p's left child
	}											// otherwise set it to it;s right child

	node* z = new node();						// create a new node put the key into it
	strcpy(z->key, key);
	z->parent = lag;							// set it's parent to lag

	parentChange++;								// add 1 to parentChanges

	if (lag == nil)								// if lag was nil
		root = z;								// set z equal to the root
	else if (cmpChk > 0)						// if the cmpChk is greater than 0
	{
		lag->RCH = z;							// set lags right child to z

		rightChange++;
	}
	else
	{
		lag->LCH = z;							// OTHERWISE set lags right child to z

		leftChange++;
	}

	z->LCH = nil;								// set both of z's children to nil
	z->RCH = nil;
	z->color = true;							// set it's color to red			

	colorChange++;
	rightChange++;
	leftChange++;

	Fixup(z);									// call Fixup()
}

// This method is used to fix any error's that may have been caused by the inserting of a new node
// There are three cases for both the left and right child of z's parent parent.
// Case 1: z, z's parents nad z's uncle are all red
// Case 2: z and z's parent are both red while z's uncle is black. z is also a right child
// Case 3: z and z's parent are both red while z's uncle is black. z is also a left child
void RBT::Fixup(node* z)
{
	if (!z->parent->color) noFix++;

	while (z->parent->color)						// while z's parent's color is Red (true)
	{
		if (z->parent == z->parent->parent->LCH)	// if z's parent is the left child of it's parent
		{
			node* y = z->parent->parent->RCH;		// set y to z's uncle

			if (y->color)							// if the uncle is red		(CASE 1)
			{
				z->parent->color = false;			// set the parent and uncle to black 
				y->color = false;
				z->parent->parent->color = true;	// but set z's grandparent to red
				z = z->parent->parent;				// set z to it's grandparent
				
				colorChange += 3;		
				case1++;
			}
			else {									// if it's uncle is blacl

				if (z == z->parent->RCH)			// and z is a right child (CASE 2)
				{
					z = z->parent;					// set z to i's parent and do a left rotation
					LeftRotation(z);
					case2++;
				}
													// OTHERWISE CASE 3
				z->parent->color = false;			// set z's parent to black is it's grandparentto red 
				z->parent->parent->color = true;	// then right rotate it's grandparent
				RightRotation(z->parent->parent);

				colorChange += 2;
				case3++;
			}
		}
		else										// if z's parent is the right child of it's parent
		{											// the rest is the same just left is swapped for right
			node* y = z->parent->parent->LCH;		

			if (y->color)
			{
				z->parent->color = false;
				y->color = false;
				z->parent->parent->color = true;
				z = z->parent->parent;

				colorChange += 3;
				case1++;
			}
			else {

				if (z == z->parent->LCH)
				{
					z = z->parent;
					RightRotation(z);
					case2++;
				}

				z->parent->color = false;
				z->parent->parent->color = true;
				LeftRotation(z->parent->parent);

				colorChange += 2;
				case3++;
			}
		}
	}
	root->color = false;	// stops a rule 2 violation 
	colorChange++;
}

// This method is called by the Fixup method to either fix a second or third case
// It's moves z to the being the left child of it's right child and put's it right 
// child in it's original spot
void RBT::LeftRotation(node* z)
{
	node* y = z->RCH;			//place holder for z's right child

	if (z->parent == nil)			// if z's parent is nil set the root to y
		root = y;
	else if (z == z->parent->LCH)	// if z is a left child
	{								// y takes z spot
		z->parent->LCH = y;
		leftChange++;
	}
	else							// OTHERWISE it's a right child
	{								// set z's parent's right child to y
		z->parent->RCH = y;			
		rightChange++;
	}

	y->parent = z->parent;						// set y's parent to z's parent
	z->parent = y;								// then z's parent to y (y has fully taken z's spot)
	z->RCH = y->LCH;							// z's right child is now y's left child
	if (y->LCH != nil) 
	{
		y->LCH->parent = z;		// if y's left child isn't nil set it's parent to z 
		parentChange++;
	}
	y->LCH = z;									// then set y's left child to z


	parentChange += 2;
	rightChange++;
	leftChange++;
}

// This method is called by Fixup() to either fix a second or third case
// It moves z to being the right child of its left child (y). Then y takes z's old place
void RBT::RightRotation(node* z)
{
	node* y = z->LCH;			// place holder for z's left child

	if (z->parent == nil)			// if z's parent is nil set the root to y
		root = y;
	else if (z == z->parent->LCH)	// if z is a left child
	{								// y takes z spot
		z->parent->LCH = y;
		leftChange++;
	}
	else							// OTHERWISE it's a right child
	{								// set z's parent's right child to y
		z->parent->RCH = y;
		rightChange++;
	}

	y->parent = z->parent;						// set y's parent to z's parent
	z->parent = y;								// then z's parent to y (y has fully taken z's spot)
	z->LCH = y->RCH;							// z's left child is now y's right child
	if (y->RCH != nil) 
	{
		y->RCH->parent = z;		// if y's right child isn't nil set it's parent to z
		parentChange++;
	}
	y->RCH = z;									// then set y's right child to z

	parentChange += 2;
	rightChange++;
	leftChange++;
}

// This method is used to recursivly obtain the, number of nodes, number of keys and the tree height.
void RBT::GetTreeHeightKeysNodes(node* z, unsigned int currentHeight)
{
	if (z->LCH != nil) GetTreeHeightKeysNodes(z->LCH, currentHeight + 1);	// if the left child is not null recursively called GetTreeHeight with the left child and one added to the height

	numOfNodes++;				// increments the numer of nodes
	numOfKeys += z->count;		// adds the count from the node the numOfKeys

	if (z->RCH != nil) GetTreeHeightKeysNodes(z->RCH, currentHeight + 1);  // if the right child is not null recursively called GetTreeHeight with the right child and one added to the height
	
	if (currentHeight > treeHeight) treeHeight = currentHeight;	// if the currentHeight is bigger than the treeHeight set the new tree height to currentHeight
}

// This gets all the data needed to be collected.
void RBT::GetData()
{
	if(root != nil) GetTreeHeightKeysNodes(root);

	cout << "RBT" << endl;
	cout << "Comparisons: " << comparisons << endl;
	cout << "Tree Height: " << treeHeight << endl;
	cout << "Number of nodes: " << numOfNodes << endl;
	cout << "Number of entries: " << numOfKeys << endl;
	cout << "Left Changes: " << leftChange << endl;
	cout << "Right Changes: " << rightChange << endl;
	cout << "Parent Changes: " << parentChange << endl;
	cout << "No Fixes: " << noFix << endl;
	cout << "Case 1: " << case1 << endl;
	cout << "Case 2: " << case2 << endl;
	cout << "Case 3: " << case3 << endl;
	cout << "Color Changes: " << colorChange << endl;
	cout << endl;

}
