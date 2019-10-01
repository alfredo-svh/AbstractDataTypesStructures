/*
	Name: Alfredo Sepulveda

	Project 5 - tree.c

	Description:
	Implementation of a binary tree ADT by keeping pointers to
	the parent, and the left and right children of each node.
	This code includes functions to create a new tree, destroy
	an entire tree, get information about a root, such as
	its data, its parent, or any of its children, as well as
	two functions that set a new left or right subtree respectively
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tree.h"

struct tree{
	int data;
	struct tree *left,
					*right,
					*parent;
};


/*
 * O(1)
 * createTree creates a new tree given the data the root will hold and the pointers
 * to their left and right children by allocating memory for a new tree, then
 * setting its parent pointer to NULL and the integer passed as its data.
 * Then, for each of the tree pointers passed, it disconnects them from their
 * parent, if they have one, and sets them as the new tree's children.
 * The function, then returns the pointer to the root of the new tree.
 */

struct tree *createTree(int data, struct tree *left, struct tree *right)
{
	struct tree *tp;
	tp=malloc(sizeof(struct tree));
	assert(tp!=NULL);

	tp->data=data;
	tp->parent=NULL;

	if(left!=NULL){
		if(left->parent!=NULL){					/*if new left child is not NULL and already has a parent, */
			if (left->parent->left==left)		/*checks if it is the left or right child, and sets its respective parent's child pointer to NULL*/
				left->parent->left=NULL;
			else
				left->parent->right=NULL;

		}
		left->parent=tp;						/*sets the new root as its new parent*/
	}

	if(right!=NULL){
		if(right->parent!=NULL){				/*follows the same steps as for the left child*/
			if(right->parent->left==right)
				right->parent->left=NULL;
			else
				right->parent->right=NULL;

		}
		right->parent=tp;
	}

	tp->left=left;
	tp->right=right;

	return tp;
}


/*
 * O(n)
 * destroyTree recursively destroys the tree which root is the pointer passed
 * to the function as the argument by traversing the tree post-orde.
 */

void destroyTree(struct tree *root)
{
	if(root==NULL)
		return;
	destroyTree(root->left);
	destroyTree(root->right);
	free(root);
}


/*
 * O(1)
 * getData returns the integer stored in the data of the node pointed to
 * by the argument
 */

int getData(struct tree *root)
{
	assert(root!=NULL);

	return root->data;
}


/*
 * O(1)
 * getLeft returns the pointer to the left child of the root pointed to by the argument
 */

struct tree *getLeft(struct tree *root)
{
	assert(root!=NULL);


	return root->left;
}


/*
 * O(1)
 * getRight returns a pointer to the right child of the root pointed to by the argument
 */

struct tree *getRight(struct tree *root)
{
	assert(root!=NULL);

	return root->right;
}


/*
 * O(1)
 * getParent returns a pointer to the parent of the root pointed to by the argument
 */

struct tree *getParent(struct tree *root)
{
	assert(root!=NULL);

	return root->parent;
}


/*
 * O(1)
 * setLeft sets a subtree as the left child of a root, both pointed to by pointers passed
 * in the argument. The function first checks if the root already has a left child and if
 * it does, then it cuts the link between them. Then, it checks if the subtree has a parent.
 * If it does, then it cuts the link between them. And, finally, it creates the link between
 * the root and its new left child.
 */

void setLeft(struct tree *root, struct tree *left)
{
	assert(root!=NULL && left!=NULL);

	if(root->left!=NULL)
		root->left->parent=NULL;

	if(left->parent!=NULL){
		if (left->parent->left==left)
			left->parent->left=NULL;
		else
			left->parent->right=NULL;
	}

	left->parent=root;
	root->left=left;

	return;
}


/*
 * O(1)
 * setRight sets a subtree as the right child of a root, both pointed to by pointers passed
 * in the argument. The function first checks if the root already has a right child and if
 * it does, then it cuts the link between them. Then, it checks if the subtree has a parent.
 * If it does, then it cuts the link between them. And, finally, it creates the link between
 * the root and its new right child.
 */


void setRight(struct tree *root, struct tree *right)
{
	assert(root!=NULL && right!=NULL);

	if(root->right!=NULL)
		root->right->parent=NULL;

	if(right->parent!=NULL){
		if (right->parent->left==right)
			right->parent->left=NULL;
		else
			right->parent->right=NULL;
	}

	right->parent=root;
	root->right=right;

	return;
}
