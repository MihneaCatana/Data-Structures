#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Plane Plane;

struct Plane
{
	int id;
	char* producer;
};

Plane createPlane(int id, char* producer)
{
	Plane p;
	p.producer = (char*)malloc(strlen(producer) + 1);
	strcpy(p.producer, producer);
	p.id = id;
	return p;
}

void displayPlane(Plane p)
{
	printf("Plane made by %s has the id: %i \n", p.producer, p.id);
}

//Binary Tree

typedef struct Node Node;

struct Node
{
	Node* left;
	Plane p;
	Node* right;
};

void insertTree(Node** tree, Plane p)
{
	if (*tree == NULL)
	{
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->p = p;
		newNode->left = NULL;
		newNode->right = NULL;
		*tree = newNode;
	}
	else
	{	//if we have an element, we compare the ids so we will find where we will insert the new element
		//if we have equality, we don't insert the new element
		
		if (p.id > (*tree)->p.id)
			insertTree(&(*tree)->right, p);
		else
			if (p.id < (*tree)->p.id)
				insertTree(&(*tree)->left, p);
	}

}

void displayPreOrder(Node* tree) // Root Left Right
{
	if (tree)
	{
		displayPlane(tree->p);
		displayPreOrder(tree->left);
		displayPreOrder(tree->right);
	}
}

void displayInOrder(Node* tree) //Left Root Right
{
	if (tree)
	{
		displayInOrder(tree->left);
		displayPlane(tree->p);
		displayInOrder(tree->right);
		
	}
}

void displayPostOrder(Node* tree) //Left Right Root 
{
	if (tree)
	{
		displayPostOrder(tree->left);
		displayPostOrder(tree->right);
		displayPlane(tree->p);
	}
}

//free memory
void freeTree(Node** tree)
{
	if (*tree)
	{
		freeTree(&(*tree)->left);
		freeTree(&(*tree)->right);

		free((*tree)->p.producer);
		free(*tree);
	}
	*tree = NULL;
	
}

Plane searchPlaneId(Node* tree, int id)
{
	if (tree)
	{
		if (tree->p.id > id)
			searchPlaneId(tree->left, id);
		else
			if (tree->p.id < id)
				searchPlaneId(tree->right, id);
			else
			{
				Plane copy;
				copy.id = id;
				copy.producer = (char*)malloc(strlen(tree->p.producer) + 1);
				strcpy(copy.producer, tree->p.producer);
				return copy;
			}

	}
	else
		return createPlane(-1, "Invalid");
}

int calculateHeight(Node* tree)
{
	if (tree)
	{
		int st =calculateHeight(tree->left);
		int dr =calculateHeight(tree->right);
		if (st > dr)
			return st + 1;
		else
			return dr + 1;
	}
	return 0;
}

//AVL TREE

// https://www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm#

int calculateInbalance(Node* tree)
{
	if (tree)
	{
		return calculateHeight(tree->left) - calculateHeight(tree->right);
	}
	else
		return 0;
}

void rotateLeft(Node** root)
{
	// for rotate left we need to position on the right Node (temp)
	Node* temp = (*root)->right;
	
	//we save the left Nodes of temp in the right of the original Node
	(*root)->right = temp->left;

	//in the left of Temp, we save the original Node and the Temp becomes the new root
	temp->left = *root;
	*root = temp;

}

void rotateRight(Node** root)
{
	// like the rotation on left side, but left becomes right and right becomes left

	Node* temp = (*root)->left;

	(*root)->left = temp->right;

	temp->right = *root;

	*root = temp;

}

void insertAVLTree(Node** tree, Plane p )
{
	if (*tree)
	{
		if (p.id > (*tree)->p.id)
			insertAVLTree(&(*tree)->right, p);
		else
			if (p.id < (*tree)->p.id)
				insertAVLTree(&(*tree)->left, p);
		
		int echilibru = calculateInbalance(*tree); // if our AVL tree is not balanced we need to do rotates

		if (echilibru == 2) // if we have inbalance in the left
		{
			int echilibruLEFT = calculateInbalance((*tree)->left);

			if (echilibruLEFT == -1)
				rotateLeft(&(*tree)->left);

				rotateRight(tree);
		}

		if (echilibru == -2) //if we have inbalance in the right
		{
			int echilibruRIGHT = calculateInbalance((*tree)->right);

			if (echilibruRIGHT == 1)
				rotateRight(&(*tree)->right);
			
			rotateLeft(tree);
		}

	}
	else
	{
		//if it is empty, we insert a new Node
		Node* nou = (Node*)malloc(sizeof(Node));
		nou->left = NULL;
		nou->right = NULL;
		nou->p = p;
		*tree = nou;
	}



}


int main()
{
	Node* tree =NULL;
	insertTree(&tree, createPlane(7, "Boeing1"));
	insertTree(&tree, createPlane(4, "Boeing2"));
	insertTree(&tree, createPlane(10, "Boeing3"));
	insertTree(&tree, createPlane(2, "Boeing4"));
	insertTree(&tree, createPlane(8, "Boeing5"));
	insertTree(&tree, createPlane(6, "Boeing6"));

	displayPreOrder(tree);
	printf("\n");
	displayInOrder(tree);
	printf("\n");
	displayPostOrder(tree);
	printf("\n");

	displayPlane(searchPlaneId(tree, 7));
	printf("\n");

	freeTree(&tree);

	Node* AVLtree = NULL;
	insertAVLTree(&AVLtree, createPlane(1, "Test1"));
	insertAVLTree(&AVLtree, createPlane(2, "Test2"));
	insertAVLTree(&AVLtree, createPlane(3, "Test3"));
	insertAVLTree(&AVLtree, createPlane(4, "Test4"));
	insertAVLTree(&AVLtree, createPlane(5, "Test5"));
	insertAVLTree(&AVLtree, createPlane(6, "Test6"));
	insertAVLTree(&AVLtree, createPlane(7, "Test7"));

	displayPreOrder(AVLtree);
	freeTree(&AVLtree);

}
