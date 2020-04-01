#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "SkipList.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>


// This contructs the first lane in skiplist
SkipList::SkipList()
{
	head = new node();
	tail = new node();

	strcpy(head->key, NEG_INF);
	strcpy(tail->key, POS_INF);

	head->right = tail;
	tail->left = head;

	coin = mt19937(time(NULL));
}

SkipList::~SkipList()
{
	node* p = head;

	while (p != nullptr) 
	{
		node* q = p->right;

		while(q != nullptr)
		{
			node* toDelete = q;
			q = q->right;
			delete toDelete;
		}
		node* toDelete = p;
		p = p->down;
		delete toDelete;
	}
}

// This method is used to insert into the skip list. It starts off by finding where to insert the new key
// it does this by calling the search function. It checks to see if the key's are the same if so it just
// increments the count. If not it will insert a new node with the key next to the found node. Then it will
// randomly generate a "coin toss" if heads it will create a node in a new level with the same key if not the
// insert is done. 
void SkipList::Insert(char key[])
{
	bool found = false;
	node* foundNode = search(key, found);	// finds the node that contians the key or the node to left of where
									// a new node will be inserted on the bottom level

	if (found) foundNode->count++; // if the foundNode contains the same key as to be inserted increment the count (technally a comparison
	else {
		node* q = new node();
		// THE NEXT LINES COMPLETELY INSERTS q INTO LIST
		strcpy(q->key, key);			// copies the key into the new node (q)
		q->left = foundNode;			// sets q's left equal to the foundNode
		q->right = foundNode->right;	// sets q's right to foundNodes right

		foundNode->right->left = q;		// sets the left node. of the node that is to the right of foundNode tp q
		foundNode->right = q;			// set's foundNode's right node to q

		leftChange += 2;
		rightChange += 2;

		while (coin() & 1)				// this is the "coin toss" with bit wise operations. This ands the first bit with 1 if 
		{								// it is 1 then enter the loop

			node* searchLeft = q->left;

			while (searchLeft->up == nullptr)					// while searchLeft's up node is null continue loop
			{
				if (searchLeft->left == nullptr) NewLevel();	// if the left node of serachLeft is ever nullptr create a newLevel to list
				else searchLeft = searchLeft->left;				// otherwise set it to it's left node
			}
			// THE NEXT LINES CREATES THE NODE TO GO ABOVE THE ALREADY INSERTED Q AND INSERTS IT
			node* newLevelNode = new node();					// 

			strcpy(newLevelNode->key, key);						// cpys the key into the newLevelNode						searchleft up --- newLevelNode --- searchLeft up right
			newLevelNode->down = q;								// sets the down node as q										  |                |   
			newLevelNode->left = searchLeft->up;				// sets the left node as the searchLefts up node			 serachLeft   ---      q       --- 
			newLevelNode->right = searchLeft->up->right;		// sets the right node as serachLefs up nodes right node 

			q->up = newLevelNode;								// set q's up node to newLevelNode

			searchLeft->up->right->left = newLevelNode;			// set's searchLefts up nodes right nodes left node to newLevelNode
			searchLeft->up->right = newLevelNode;				// set's searchlefts up nodes riight node to newLevelnode

			leftChange += 2;
			rightChange += 2;
			upChange++;
			downChange++;

			q = newLevelNode;									// set's q to newLevelNode just in case the coin toss is heads again
		}
	}
}

// This mthod is used to createa new level to the SkipList by taking the current head and tail
// and creating new ones that will be placed on top of the old ones.  
void SkipList::NewLevel()
{
	node* p = new node();		// careates the new nodes
	node* q = new node();

	strcpy(p->key, NEG_INF);	// sets the key to negInf
	strcpy(q->key, POS_INF);	// sets the key to posInf

	p->down = head;				// makes p's down node the current head
	p->right = q;				// makes p's right node the new tail node (q)

	q->down = tail;				// makes q's down node the current tail
	q->left = p;				// makes q's right node the new head node (p)

	head->up = p;				// old head's up is new head
	head = p;					// set head node as p

	tail->up = q;				// old tail's up is new tail
	tail = q;					// set tail node as q

	leftChange++;
	rightChange++;
	upChange += 2;
	downChange += 2;
	h++;						// increment the height
}

// This method is used to search through the skiplist and return the node containing the
// key being searched at the bottom level. If the key is not there it will return the node 
// that is has a key that is less than the key being searched
SkipList::node* SkipList::search(char key[], bool& found)
{
	node* p = head;
	int cmpChk = -1;

	while (true)
	{
		while (p->right->right != nullptr && (cmpChk = strcmp(p->right->key, key)) <= 0)	// while the p's right right node is not null and p's right node's key is less than or 
		{ // one or two comparisions. strcmp(p->right->key, POS_INF) != 0		// equal to the key being search continue to loop 
			p = p->right;	// set p to it's right node

			comparisons++;

			if (cmpChk == 0)								// if cmp chk is 0 that means a node with the key was found
			{
				found = true;								// set found to true
				while (p->down != nullptr) p = p->down;		// go down to the bottom level
				return p;									// and return p
			}
		}

		if (p->right->right != nullptr) comparisons++;

		if (p->down == nullptr) return p;	// if there is no bottom level return p

		p = p->down;	// otherwise set p to it's lower level version

	}
}

void SkipList::InOrderTraversal()
{
	node* p = head;

	while (p->down != nullptr) p = p->down;

	p = p->right;

	while (strcmp(p->key, POS_INF))
	{
		node* q = p;
		n++;						// increments the number of nodes
		numOfKeys += q->count;
		do
		{
			//cout << q->key << " ";
			headsTossed++;
			q = q->up;
		} while (q != nullptr);

		//cout << endl;
		p = p->right;
	}
	//cout << h << endl;
	headsTossed = headsTossed - n;
}

void SkipList::GetData()
{
	InOrderTraversal();

	cout << "SkipList" << endl;
	cout << "Comparisons: " << comparisons << endl;
	cout << "Tree Height: " << h << endl;
	cout << "Number of nodes (Bottom): " << n << endl;
	cout << "Number of entries: " << numOfKeys << endl;
	cout << "Heads Tossed: " << headsTossed << endl;
	cout << "Left Changes: " << leftChange << endl;
	cout << "Right Changes: " << rightChange << endl;
	cout << "Up Changes: " << upChange << endl;
	cout << "Down Changes: " << downChange << endl;
	cout << endl;
	//cout << "Total: " << comparisons + n + countTotal + headsTossed + leftChange + rightChange + upChange + downChange << endl;
}

//SkipList::node* SkipList::search(char key[])
//{
//	node* p = head;		
//
//	while(true)
//	{
//		while (p->right->right != nullptr && strcmp(p->right->key, key) <= 0)	// while the p's right right node is not null and p's right node's key is less than or 
//		{ // one or two comparisions. strcmp(p->right->key, POS_INF) != 0		// equal to the key being search continue to loop
//			comparisons++;	// add a comparison 
//			p = p->right;	// set p to it's right node
//		}
//
//		if (p->right->right != nullptr) comparisons++;
//
//		//comparisons += 2;
//
//		if (p->down == nullptr) return p;	// if there is no bottom level return p
//
//		p = p->down;	// otherwise set p to it's lower level version
//	}
//}