/*
	Alfredo Sepulveda
	Project 2
	Sets and elements functions for a sorted array by ADT
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "set.h"

struct set
{
	int count;
	int length;
	char **elts;
};

/*
	Creates a new struct
*/

SET *createSet(int maxElts)
{
	SET *sp;

	sp=malloc(sizeof(SET)); //allocates memory for a new struct
	assert(sp!=NULL);

	sp->count=0;
	sp->length=maxElts;
	sp->elts=malloc(sizeof(char*)*maxElts); //allocates memory for max number of strings
	assert(sp->elts!=NULL);

	return sp;
}

/*
	Deletes entire struct
*/

void destroySet (SET *sp)
{
	assert(sp!=NULL);

	free(sp);

	return;
}

/*
	Returns count, which is the number of elements in the array
*/


int numElements (SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

/*
	O(log n)
	Searches for an element in the array by comparing the strings and dividing search area by half each time.
	It returns the place where it is or where it should be if not found.
	It also sets a value for a bool variable if it was found or not
*/


int findElement(SET *sp, char *elt, bool *found)
{
   int lo, hi, mid, diff;
	lo=0;
	hi=sp->count-1;

	while (lo<=hi){ //loop will continue to go as long as a place is found or every place was searched for
		mid=(lo+hi)/2;
		diff=strcmp(elt, sp->elts[mid]);
		if(diff<0)
			hi=mid-1;
		else if (diff>0)
			lo=mid+1;
		else {
			*found=true;
			return mid;
		}
	}

	*found=false;
	return lo;
}

/*
	O(log n)
	Checks if element is already in the array
	If it is, it returns true.
	Otherwise, it returns false.
*/


bool hasElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	bool f;

	findElement(sp, elt, &f); //calls findElement to determine true or false
	if (f==true)
		return true;
	return false;
}

/*
	O(n)
	Adds an element to the sorted array
*/


bool addElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	bool f;
	int s, i;
	s=findElement(sp, elt, &f);

	if(sp->count==sp->length || f==true)
		return false; //return false if array is full or the element is already in the array

	sp->elts[sp->count]=malloc(sizeof(char*)); //allocates memory for a string
	elt=strdup(elt); //duplicates string
	assert(elt!=NULL);

	for (i=sp->count; i>s;i--)
		sp->elts[i]=sp->elts[i-1]; //shifting
	sp->elts[s] = elt;
	sp->count++; //counter increases
	return true;
}

/*
	O(n)
	Removes an element from the sorted array
*/


bool removeElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	int s, i;
	bool f;

	s=(findElement(sp, elt, &f));

	if (f==false || sp->count==0) //if the element is not in the array or the array is empty, returns false
		return false;

	for (i=s+1;i<sp->count; i++)
		sp->elts[i-1]=sp->elts[i]; //shifting
	sp->elts[sp->count-1]=NULL; //removes element found
	sp->count--; //decreases count
	return true;
}
