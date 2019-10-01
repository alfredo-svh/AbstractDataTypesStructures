/*
	Alfredo Sepulveda
	Project 2
	Sets and elements functions using an unosrted array as ADT
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "set.h"

struct set //declare struct
{
	int count;
	int length;
	char **elts;
};

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

void destroySet (SET *sp) //deletes entire struct
{
	assert(sp!=NULL);
	free(sp);
	return;
}

int numElements (SET *sp) //returns count, which is number of elements in the array of strings
{
	assert(sp!=NULL);
	return sp->count;
}

int findElement(SET *sp, char *elt)
{
   assert(sp!=NULL && elt!=NULL);

   int i;

   for (i=0;i<sp->count; i++) //starting on the first location, loop will find a match for elt in the array of strings
      if(strcmp(sp->elts[i], elt)==0)
         return i; //returns location of match
   return -1; //if elt is not in the struct, it returns -1
}


bool hasElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);

	if ((findElement(sp, elt))==-1) //if the element is not in the array of strings, return false
		return false;
	return true; //otherwise, return true
}

bool addElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	
	if(sp->count==sp->length || findElement(sp, elt)!=-1)
		return false; //return false if array is full or the element is already in the array

	elt=strdup(elt); //duplicates string elt
	assert(elt!=NULL);
	sp->elts[sp->count++] = elt; //add string to the end and increase count
	return true;
}

bool removeElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);

	int i;
	i=(findElement(sp, elt));

	if (i==-1 || sp->count==0) //if the element is not in the array or the array is empty, returns false
		return false;

	free(sp->elts[i]); //removes element found
	sp->count--; //decreases count
	return true;
}
