/*
	Alfredo Sepulveda
	Project 3
	Sets and elements functions for an ADT hash table
	createSet function that creates a new node
	destroySet function that deletes a node
	numElement function that returns the number of elements in the array of a given node
	hasElement function that returns whether a string is in the array of a given node or not
	addElement function that adds a new string into the array of a given node
	removeElement that deletes a string from the array of a given node
	findElement that looks for a string in the array using a hashing function and flags,
	and returns the slot that the string is in if found or where it should go if it isn't already there
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "set.h"

/*create flags for use in the array*/

typedef enum Flags
{
	empty,
	filled,
	deleted
}Flags;

/*define each node*/

struct set
{
	int count;
	int length;
	char **elts;
	Flags *flag;
};

/*hashing function*/

unsigned hashString(char *s)
{
	unsigned hash = 0;

	while (*s != '\0')
		hash = 31 * hash + *s ++;
	return hash;
}

/*
	Creates a new struct
*/

SET *createSet(int maxElts)
{
	SET *sp;
	int i;

	sp=malloc(sizeof(SET)); /*allocates memory for a new node*/
	assert(sp!=NULL);			/*Make sure malloc worked*/

	sp->count=0;									/*set initial count to 0*/
	sp->length=maxElts;
	sp->elts=malloc(sizeof(char*)*maxElts); 	/*allocates memory for max number of strings*/
	assert(sp->elts!=NULL);							/*make sure malloc worked*/
	sp->flag=malloc(sizeof(Flags)*maxElts);	/*allocates memory for max number of flags*/
	assert(sp->flag!=NULL);							/*make sure malloc worked*/
	for(i=0;i<maxElts;i++)							/*set all flags to empty*/
		sp->flag[i]=empty;

	return sp;
}

/*
	Deletes entire node  making sure the given node is not NULL
	and freeing the entire node
*/

void destroySet (SET *sp)
{
	assert(sp!=NULL);

	free(sp);

	return;
}

/*
	Make sure the given node is not NULL
	Returns count, which is the number of elements in the array
*/


int numElements (SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

/*
	Best case: O(1)
	Worst case: O(n)
	Searches for an element in the array by using the hashing function with the string
	given while updating it if a collison occurs.
	It returns the place where the string is if found, or the first available spot if not found.
	It also sets a value for a bool variable if it was found or not.
*/


int findElement(SET *sp, char *elt, bool *found)
{
	int i, s;
	int j=0;
	bool del=false;
	int first_del=0;

	assert(sp!=NULL && elt!=NULL);						/*Make sure string and given node are not NULL*/

	i=((hashString(elt)+j)%sp->length);					/*i becomes our hashing location using hashing function*/
	s=i;															/*s will remember this original location*/

	while(i>=s){												/*loop will continue as long as the new i is bigger than the original i*/

		if (del==false && sp->flag[i]==deleted){		/*first_del remembers location of first deleted element*/
			first_del=i;
			del = true;
		}

		if (sp->flag[i]==empty){							/*if it hashes to an empty slot, then the string wasn't found*/ 
			*found=false;
			if (del==false)									/*if it found a deleted slot before, it returns its location*/
				return i;										/*otherwise, it returns the location of the empty slot*/
			else
				return first_del;
		}

		if (strcmp(sp->elts[i], elt)==0 && sp->flag[i]==filled){		/*if the string is found in a filled spot*/
			*found=true;															/*then it found it and returns the slot*/
			return i;
		}

		j++;												/*updates probe number*/
		i=((hashString(elt)+j)%sp->length);		/*updates hashing location*/
	}

	*found=false;					/*if loop goes all the way around, then it didn't find the string*/
	return first_del;				/*and returns the location of the first deleted slot*/
}

/*
	Best case: O(1)
	Worst case: O(n)
	Checks if element is already in the array by calling findElement
	If it is, it returns true.
	Otherwise, it returns false.
*/


bool hasElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);		/*make sure given node and string are not NULL*/
	bool f;

	findElement(sp, elt, &f); 				/*calls findElement to determine if the string is found in the array*/
	if (f==true)								/*if it is in the array, it returns true. Otherwise, it returns false*/
		return true;
	return false;
}

/*
	Best case: O(1)
	Worst case: O(n)
	Adds an element to the sorted array by using findElement to find an available slot
	if the array is not full and the string is not already in the array
	Changes flag of the slot to filled, copies the string into the slot, count increases
	Returns true if successful, returns false if string was not added
*/


bool addElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);		/*Make sure given node and string are not NULL*/
	bool f;
	int i;
	i=findElement(sp, elt, &f);			/*calls findElement to look for string in the array*/

	if(sp->count==sp->length || f==true)	/*if the array is full or the element is already in the array, it returns false*/
		return false;
	sp->flag[i]=filled;		/*update flag of slot to filled*/
	elt=strdup(elt); 			/*duplicates string*/
	assert(elt!=NULL);		/*make sure it worked*/
	sp->elts[i] = elt;
	sp->count++; 				/*counter increases*/
	return true;
}

/*
	O(n)
	Removes an element from the sorted array by using findElement to look for the array.
	If it is not found or if the array is empty, then it returns false.
	Otherwise, the flag for the slot gets updated to deleted and count decreases. Returns true
*/


bool removeElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	int s, i;
	bool f;

	s=(findElement(sp, elt, &f));		/*findElement to look for string in the array*/

	if (f==false || sp->count==0) 	/*if the element is not in the array or the array is empty, returns false*/
		return false;

	sp->flag[s]=deleted;					/*updates flag of slot to deleted*/
	sp->count--; 							/*decreases count*/
	return true;
}
