/*
	Name: Alfredo Sepulveda

	Project 4

	Description:
	The program implements deques to store
	a set of numbers entered by the user
	and rearranges them until they are ordered,
	then it prints them out
*/

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define NODE struct node
#include "deque.h"


/*
	Main starts by creating a deque and an array of 10 deques
	Then, saves the biggest number out of all the numbers the user inputs,
	which are stored in the deque in the order they are entered.
	The program then uses the array of deques to rearrange the order
	of the numbers, eventually printing out all of them from smallest to biggest.
*/

int main ()
{

	int i, j, temp, num, size, iterations, index;
	int max=0;
	int power=1;

	DEQUE *list =createDeque();
	DEQUE *bins[10];
	
	/*creates 10 deques for the array of deques*/
	for (i=0;i<10;i++)
		bins[i]=createDeque();
	
	printf("Input as many integers as you want. Input a nonnummeric character to end the input\n");

	/*asks user for integers, storing them into the list deque and remembering the biggest number, until the user inputs a nonnummeric character*/
	while (scanf("%d", &num)==1){
		assert(num>=0);
		if(num>max)
			max=num;
		addLast(list , num);
	}

	iterations=ceil(log(max+1)/log(10));
	size=numItems(list);

	/*
		for every iteration (the amount of iterations will be the number of digits of biggest number),
		the numbers will be rearranged from the list deque to the array of deques and back to the
		list deque. The numbers will be ordered by up the corresponding most significant digit of
		the iteration, which will be updated each time
	*/
	for(i=0;i<iterations; i++){

		/*for each number entered, the loop moves the number from the list deque into the deque of the corresponding index of the array*/
		for(j=0;j<size;j++){
			num=removeFirst(list);
			temp=num/power;	/*temp will be the number we want to mod to get the index*/
			index=temp%10;
			addLast(bins[index], num);
		}

		/*All the numbers in each of the 10 deques are moved to the list deque without altering order*/
		for(j=0;j<10;j++){
			while(numItems(bins[j])>0){
				num=removeFirst(bins[j]);
				addLast(list, num);
			}
		}
		power=power*10;
	}
	
	printf("\nRadix order:\n");

	/*prints the numbers in the list deque, which are now in order from smallest to biggest*/
	for (i=0;i<size;i++)
		printf("%d\n", removeFirst(list));

	destroyDeque(list);

	/*destroys the deques in the array*/
	for(i=0;i<10;i++)
		destroyDeque(bins[i]);

	return 0;
}
