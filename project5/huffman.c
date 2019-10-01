/*
 * Name: Alfredo Sepulveda
 *
 * Project 5 - huffman.c
 *
 * Description:
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"
#define p(x) (((x)-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)


/*Function protoypes*/

void insert(struct tree *t);
struct tree* delete(void);
void print (struct tree *t);


/*global variables*/

struct tree* heap[257];
struct tree* leaves[257];
int n=0;


int main(int argc, char *argv[])
{
	//make sure an input file and output file are included
	assert(argc==3 && argv[1]!=NULL);

	FILE *fp=fopen(argv[1], "r");
	int c, i;
	int counts[257];
	struct tree *templeft, *tempright;


	//initializing the arrays
	for(i=0;i<257;i++){
		counts[i]=0;
		leaves[i]=NULL;

	}


	//filling the counts array with the amount of times each character appears
	//in the input file
	while((c=fgetc(fp))!=EOF){
		counts[c]++;
	}

	//we're done reading the input file, so we close it
	fclose(fp);

	//for every character in the input file, a tree is created and added to the
	//leaves array, including EOF
	for (i=0;i<256;i++){
		if(counts[i]!=0)
			leaves[i]=createTree(counts[i], NULL, NULL);
	}

	leaves[256]=createTree(0, NULL, NULL);


	//for every tree in the leaves array, insert into heap
	for (i=0;i<257;i++){
		if(leaves[i]!=NULL){
			insert(leaves[i]);
		}
	}

	//creates a single tree from the leaves. Stored in heap[0]
	while (n>1){
		templeft=delete();
		tempright=delete();
		insert(createTree(getData(templeft)+getData(tempright),templeft, tempright));
	}


	//prints every character used in the input file
	//with its occurrence, and its assigned binary code
	for (i=0;i<257;i++){
		if (leaves[i]!=NULL){
			if(isprint(i))
				printf("%c", i);
			else
				printf("%03o", i);
			printf(":\t%d\t", counts[i]);
			print(leaves[i]);
			printf("\n");
		}
	}

	//compress input file into output file
	pack(argv[1], argv[2], leaves);

	//deletes tree before ending program
	destroyTree(heap[0]);

	return 0;
}

void insert(struct tree *tp){
	struct tree *temp;

	//get current position. Insert tree at the end of the heap
	int curPos=n;

	heap[n++]=tp;

	//rearrange heap so that the node falls into the right place
	//(our min value should be at heap[0])
	while(curPos > 0 && getData(heap[curPos]) < getData(heap[p(curPos)])){
		//switch parent and current in the heap
		temp = heap[curPos];
		heap[curPos] = heap[p(curPos)];
		heap[p(curPos)] = temp;

		//we update the current position
		curPos = p(curPos);
	}

	return;
}

struct tree* delete(){
	int curPos=0, minPos;
	struct tree *minTree = heap[0];
	struct tree *temp;

	if(n>1){
		//switch first and last tree in heap
		heap[0] = heap[n-1];
		heap[n-1] = minTree;

		while(1){
			//if there are only two subtrees in the heap,
			//the minPosition will simply be set at the left
			//child of the current position's subtree.
			if(n==2)
				minPos = l(curPos);

			//otherwise, we set the minPos to be the child of the current tree
			//with the lower number
			else if(getData(heap[l(curPos)]) <= getData(heap[r(curPos)])){
				minPos = l(curPos);
			}
			else{
				minPos = r(curPos);
			}

			//if the position of the smaller child is the last place in the heap
			//and the left child of the current position's subtree is smaller than
			//the current subtree, then we set the minPos to this left child
			if(minPos == (n-1) && getData(heap[l(curPos)]) < getData(heap[curPos])){
				minPos = l(curPos);
			}

			//if the current position's subtree is bigger than the 
			//subtree of the minPosition
			if(getData(heap[curPos]) > getData(heap[minPos])){
				//if min is not last in heap,
				//switch trees at current and min
				if(minPos != (n-1)){
					temp = heap[curPos];
					heap[curPos] = heap[minPos];
					heap[minPos] = temp;
				}

				//curPosition is now the minPosition
				curPos= minPos;

				//if either child of the new curPosition's subtree is
				//in the last of the heap, we're done
				if(l(curPos) > (n-1) || r(curPos) > (n-1))
					break;
			}
			else
				//if the current position's subtree is equal or smaller than
				//the subtree at minPosition, we're done
				break;
		}

	}

	n--;

	return minTree;
}


//Recursive function: goes to root, and then back down to leaf,
//printing 1 if it travels to the right child or 0
//if it travels to its left child
void print (struct tree *tp){
	if(getParent(tp) !=NULL){
		print(getParent(tp));
		if(tp == getRight(getParent(tp)))
			printf("1");
		else
			printf("0");
	}
}
