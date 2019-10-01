/*
   Name: Alfredo Sepulveda

   Project 4

	Description:
	Implementation of a deque by keeping a counter of the
	numbermof items and a pointer to a dummy node.
	The deque consists of the counter and a doubly-linked
	circular linked-list with a dummy node that only inserts
	or deletes nodes that are either at the start or the end
	of the linked list, giving the linked list the properties
	of a deque.
*/

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define NODE struct node
#include "deque.h"



struct node
{
	struct node *next;
	struct node *prev;
	int data;
};

struct deque{
	int count;
	struct node *dummy;
};


/*
	O(1)
	Creates a deque, sets its count to 0, creates
	the dummy node, and sets both its pointers to itself
*/

DEQUE *createDeque(void)
{
	DEQUE *dp;

	dp= malloc(sizeof(DEQUE));
	assert(dp!=NULL);

	dp->count=0;
	dp->dummy= malloc(sizeof(NODE));
	assert(dp->dummy!=NULL);
	dp->dummy->prev=dp->dummy;
	dp->dummy->next=dp->dummy;
	
	return dp;
}


/*
	O(n)
	Destroys a set using a temporary node to free each node
	before freeing the dummy and then the deque
*/

void destroyDeque(DEQUE *dp)
{
	assert(dp!=NULL);
	NODE *temp=dp->dummy->next;

	while(temp!=dp->dummy){		/*frees every node in the deque that is not the dummy node by going forward and deleting the previous node*/
		temp=temp->next;
		free(temp->prev);
	}

	free(dp->dummy);
	free(dp);

	return;
}


/*
	O(1)
	Returns the counter that keeps
	the number of items in the deque
*/

int numItems(DEQUE *dp)
{
	assert(dp!=NULL);
	return dp->count;
}


/*
	O(1)
	Adds a new node with the value given in the place next to the dummy node
	(first node), and increases the counter of elements in the deque by 1
*/

void addFirst(DEQUE *dp, int x)
{
	assert(dp!=NULL);
	NODE *new;

	new=malloc(sizeof(NODE));
	assert(new!=NULL);

	new->data=x;

	dp->dummy->next->prev=new;
	new->next=dp->dummy->next;
	dp->dummy->next=new;
	new->prev=dp->dummy;
	
	dp->count++;
	return;
}


/*
	O(1)
	Adds a new node with the value given in the place previous to the dummy node
	(last node), and increases the counter of elements in the deque by 1
*/

void addLast(DEQUE *dp, int x)
{
	assert(dp!=NULL);
	NODE *new;

	new=malloc(sizeof(NODE));
	assert(new!=NULL);

	new->data=x;

	dp->dummy->prev->next=new;
	new->prev=dp->dummy->prev;
	dp->dummy->prev=new;
	new->next=dp->dummy;

	dp->count++;
	return;
}


/*
	O(1)
	Removes the node in the place next to the dummy node (first node),
	decreases the counter of elements in the deque by 1,
	and returns the number stored in the deleted node
*/

int removeFirst(DEQUE *dp)
{
	assert(dp!=NULL && dp->count!=0);
	NODE *deleted;
	int x;

	deleted=dp->dummy->next;
	assert(deleted!=NULL);

	x=deleted->data;

	dp->dummy->next=deleted->next;
	deleted->next->prev=dp->dummy;

	free(deleted);
	dp->count--;
	return x;
}


 /*
	O(1)
	Removes the node in the place previous to the dummy node (last node),
	decreases the counter of elements in the deque by 1
	and returns the number stored in the deleted node
*/

int removeLast(DEQUE *dp)
{
   assert(dp!=NULL && dp->count!=0);
   NODE *deleted;
   int x;
   
   deleted=dp->dummy->prev;
   assert(deleted!=NULL);

   x=deleted->data;

	dp->dummy->prev=deleted->prev;
	deleted->prev->next=dp->dummy;

   free(deleted);
   dp->count--;
   return x;

}


/*
	O(1)
	Returns the number stored in the node next to the dummmy node (first node)
*/

int getFirst(DEQUE *dp)
{
   assert(dp!=NULL && dp->count!=0);
   NODE *first;
   int x;
   
   first=dp->dummy->next;
   assert(first!=NULL);

   x=first->data;

	return x;
}


/*
	O(1)
	Returns the number stored in the node previous to the dummy node (last node)
*/

int getLast(DEQUE *dp)
{
   assert(dp!=NULL && dp->count!=0);
   NODE *last;
   int x;

   last=dp->dummy->prev;
   assert(last!=NULL);

   x=last->data;

   return x;

}
