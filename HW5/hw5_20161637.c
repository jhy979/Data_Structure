#include<stdio.h>
#include<stdlib.h>

typedef struct threadedTree* threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
}threadedTree;

//justift bool type
typedef int bool;
#define true 1
#define false 0

void construct_tree(threadedPointer tree);
threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void insertRight(threadedPointer s, threadedPointer r);
void insert(threadedPointer s, char data);

int main()
{
	/* initialize a head node */
	// type your code 
	threadedPointer root = (threadedPointer)malloc(sizeof(threadedTree));
	root->leftChild = NULL;
	root->rightChild = root;
	root->leftThread = false;
	root->rightThread = false;

	/* construct a given tree */
	construct_tree(root);
	insert(root->leftChild->rightChild, 'E');
	insert(root->leftChild->leftChild->rightChild, 'F');
	insert(root->leftChild->leftChild, 'G');
	tinorder(root);
	//getchar();
	printf("\n");
	return 0;
}

void construct_tree(threadedPointer tree)
{
	threadedPointer temp, temp_root;

	temp_root = tree;
	/* insert node 'A' to the left of the head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = true;
	temp->rightThread = true;
	temp->leftChild = temp;
	temp->rightChild = temp;
	temp->data = 'A';

	temp_root->leftChild = temp;
	temp_root->leftThread = false;

	temp_root = tree->leftChild;
	/* insert node 'B' to the left of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->rightThread = true;
	temp->leftThread = true;
	temp->leftChild = tree;
	temp->rightChild = temp;
	temp->data = 'B';

	temp_root->leftChild = temp;
	temp_root->leftThread = false;

	/* insert node 'C' to the right of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = true;
	temp->leftChild = temp_root;
	temp->rightChild = tree;
	temp->data = 'C';

	temp_root->rightChild = temp;
	temp_root->rightThread = false;

	temp_root = temp_root->leftChild;
	/* insert node 'D' to the right of the temp_head */
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftThread = temp->rightThread = true;
	temp->leftChild = temp_root;
	temp->rightChild = tree->leftChild;
	temp->data = 'D';

	temp_root->rightChild = temp;
	temp_root->rightThread = false;
}

threadedPointer insucc(threadedPointer tree)
{
	/* find the inorder successor of tree
	in a threaded binary tree */
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread)
		while (!temp->leftThread)
			temp = temp->leftChild;
	return temp;

}

void tinorder(threadedPointer tree)
{
	//by using insucc function, just repeat printing the data of node
	threadedPointer temp = tree;
	for (; ; ) {
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%3c", temp->data);
	}
}

void insert(threadedPointer s, char data)
{
	//allocate new threadedPointer with given data and call insertRight function to insert the node into tree
	threadedPointer temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->rightChild = NULL;
	temp->rightThread = false;
	temp->leftChild = NULL;
	temp->leftThread = false;
	temp->data = data;
	insertRight(s, temp);
}

void insertRight(threadedPointer s, threadedPointer r)
{
	/* insert child as the right child of parent in a threaded binary tree */
	threadedPointer temp;
	r->rightChild = s->rightChild;
	r->rightThread = s->rightThread;
	r->leftChild = s;
	r->leftThread = true;
	s->rightChild = r;
	s->rightThread = false;
	if (!r->rightThread) {
		temp = insucc(r);
		temp->leftChild = r;
	}
}
