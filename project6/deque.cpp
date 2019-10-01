/*
   Name: Alfredo Sepulveda

   Project 6 - deque.cpp

	Description:
	Implementation of a deque by keeping a counter of the
	number of items and a pointer to a dummy node.
	The deque consists of the counter and a doubly-linked
	circular linked-list with a dummy node that only inserts
	or deletes nodes that are either at the start or the end
	of the linked list, giving the linked list the properties
	of a deque.
*/

#include <cassert>
#include "deque.h"


/*
	O(1)
	The constructor creates a deque, sets its count to 0, creates
	the dummy node, and sets both its pointers to itself
*/

Deque::Deque()
{
	count=0;
	dummy= new Node;
	assert(dummy!=NULL);
	dummy->prev=dummy;
	dummy->next=dummy;
}


/*
	O(n)
	The destructor destroys an entire deque using a temporary node to delete each node
	before deleting the dummy
*/

Deque::~Deque()
{
	Node *temp=dummy->next;

	while(temp!=dummy){		/*deletes every node in the deque that is not the dummy node by going forward and deleting the previous node*/
		temp=temp->next;
		delete(temp->prev);
	}

	delete(dummy);
}


/*
	O(1)
	Returns the counter that keeps
	the number of items in the deque
*/

int Deque::size()
{
	return count;
}


/*
	O(1)
	Adds a new node with the value given in the place next to the dummy node
	(first node), and increases the counter of elements in the deque by 1
*/

void Deque::addFirst(int x)
{
	Node *first;

	first=new Node;
	assert(first!=NULL);

	first->data=x;

	dummy->next->prev=first;
	first->next=dummy->next;
	dummy->next=first;
	first->prev=dummy;
	
	count++;
	return;
}


/*
	O(1)
	Adds a new node with the value given in the place previous to the dummy node
	(last node), and increases the counter of elements in the deque by 1
*/

void Deque::addLast(int x)
{
	Node *last;

	last=new Node;
	assert(last!=NULL);

	last->data=x;

	dummy->prev->next=last;
	last->prev=dummy->prev;
	dummy->prev=last;
	last->next=dummy;

	count++;
	return;
}


/*
	O(1)
	Removes the node in the place next to the dummy node (first node),
	decreases the counter of elements in the deque by 1,
	and returns the number stored in the deleted node
*/

int Deque::removeFirst()
{
	assert(count!=0);
	Node *deleted;
	int x;

	deleted=dummy->next;
	assert(deleted!=NULL);

	x=deleted->data;

	dummy->next=deleted->next;
	deleted->next->prev=dummy;

	delete(deleted);
	count--;
	return x;
}


 /*
	O(1)
	Removes the node in the place previous to the dummy node (last node),
	decreases the counter of elements in the deque by 1
	and returns the number stored in the deleted node
*/

int Deque::removeLast()
{
   assert(count!=0);
   Node *deleted;
   int x;
   
   deleted=dummy->prev;
   assert(deleted!=NULL);

   x=deleted->data;

	dummy->prev=deleted->prev;
	deleted->prev->next=dummy;

   delete(deleted);
   count--;
   return x;

}


/*
	O(1)
	Returns the integer stored in the node next to the dummmy node (first node)
*/

int Deque::getFirst()
{
   assert(count!=0);
   Node *first;
   int x;
   
   first=dummy->next;
   assert(first!=NULL);

   x=first->data;

	return x;
}


/*
	O(1)
	Returns the integer stored in the node previous to the dummy node (last node)
*/

int Deque::getLast()
{
   assert(count!=0);
   Node *last;
   int x;

   last=dummy->prev;
   assert(last!=NULL);

   x=last->data;

   return x;

}
