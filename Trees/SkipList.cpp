#include <string.h>
#include "SkipList.h"
#include <stdlib.h>
#include <time.h>

SkipList::SkipList()
{
	head = new node();
	tail = new node();

	strcpy(head->key, NEG_INF);
	strcpy(tail->key, POS_INF);

	head->right = tail;
	tail->left = head;

	srand(clock());
	n = 0;
	h = 1;
}

SkipList::~SkipList()
{
}

void SkipList::Insert(char key[])
{
	node* p = search(key);
	node* q = new node();

	strcpy(q->key, key);
	q->left = p;
	q->right = p->right;
	p->right = q;

	while (rand() & 1) 
	{
		node* searchNode = p;
		while (searchNode->up == nullptr && strcmp(searchNode->key, NEG_INF)) 
			searchNode = searchNode->left;

	}

}

void SkipList::Find(char key[])
{
	search(key);
}



void SkipList::NewLevel()
{
	node* p = new node();
	node* q = new node();

	strcpy(p->key, NEG_INF);
	strcpy(q->key, POS_INF);

	p->down = head;
	p->right = q;

	q->down = tail;
	q->left = p;

	head->up = p;
	head = p;

	tail->up = q;
	tail = q;

	h++;
}

SkipList::node* SkipList::search(char key[])
{
	node* p = head;

	while(true)
	{
		while (strcmp(p->right->key, POS_INF) != 0 && strcmp(p->right->key, key) <= 0) // one or two comparisions.
			p = p->right;

		//comparisons += 2;

		if (p->down == nullptr) return p;

		p = p->down;
	}
}

