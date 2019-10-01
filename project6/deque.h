/*
 * Name: Alfredo Sepulveda
 *
 * Project 6 - deque.h
 *
 * Description:
 * This file contains the declaration of private class Deque and its public functions,
 * as well as the public class Node.  class Deque includes a counter, a dummy, its
 * constructor, destructor, and its functions for an ADT implementation of a deque
 * (a doubly-ended queue, in which items can only be added to or removed from the front or rear of the list).
 */

struct Node{
	   Node *next;
		Node *prev;
		int data;
};

class Deque{
   int count;
   Node *dummy;
public:
	Deque();
	~Deque();
	int size();
	void addFirst(int x);
	void addLast(int x);
	int removeFirst();
	int removeLast();
	int getFirst();
	int getLast();
};
