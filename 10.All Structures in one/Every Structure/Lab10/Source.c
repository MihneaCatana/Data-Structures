#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>  

typedef struct Student Student;

struct Student
{
	int varsta;
	char* nume;
};

Student createStudent(char* n, int v)
{
	Student s;
	s.nume = (char*)malloc(strlen(n) + 1);
	strcpy(s.nume, n);
	s.varsta = v;
	return s;
}

typedef struct LinkedList LinkedList;

struct LinkedList
{
	Student s;
	LinkedList* next;
};

void insertLinkedListStart(LinkedList** list, Student s) // at the start of the list
{
	LinkedList* NewNode = (LinkedList*)malloc(sizeof(LinkedList));
	NewNode->s = s;
	NewNode->next = NULL;

	if (*list)
	{
		NewNode->next = *list;
	}

	*list = NewNode;
}

void insertLinkedListEnd(LinkedList** list, Student s) // at the end of the list
{
	LinkedList* NewNode = (LinkedList*)malloc(sizeof(LinkedList));
	NewNode->s = s;
	NewNode->next = NULL;

	if (*list)
	{
		NewNode->next = *list;
	}

	*list = NewNode;
}


void displayStudent(Student s)
{
	printf("Studentul %s este in varsta de %i ani\n\n", s.nume, s.varsta);
}

void displayList(LinkedList* list)
{
	if (list)
	{
		while (list != NULL)
		{
			displayStudent(list->s);
			list = list->next;
		}
	}
}

void freeList(LinkedList** list)
{
	while (*list)
	{
		LinkedList* aux = *list;
		free(aux->s.nume);
		*list = (*list)->next;
		free(aux);
	}
}

typedef struct Node Node;
typedef struct DoubleLinkedList DoubleLinkedList;

struct Node
{
	Node* prev;
	Student s;
	Node* after;
};

struct DoubleLinkedList
{
	Node* primul;
	Node* ultimul;
};

void insertDoubleNodeBegin(DoubleLinkedList* list, Student s)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->s = s;
	newNode->prev = NULL;

	if (list->primul)
	{
		newNode->after = list->primul;
		list->primul->prev = newNode;
	}
	else
	{
		newNode->after = NULL;
		list->ultimul = newNode;
	}
	list->primul = newNode;
}

void insertDoubleNodeAfter(DoubleLinkedList* list, Student s)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->s = s;
	newNode->after = NULL;

	if (list->ultimul)
	{
		list->ultimul->after = newNode;
		newNode->prev = list->ultimul;
	}
	else
	{
		newNode->prev = NULL;
		list->primul = newNode;
	}

	list->ultimul = newNode;
}

void displayDoubleLinkedListStart(DoubleLinkedList list)
{
	if (list.primul)
	{
		while (list.primul)
		{
			displayStudent(list.primul->s);
			list.primul = list.primul->after;
		}
	}
}

void displayDoubleLinkedListEnd(DoubleLinkedList list)
{
	if (list.ultimul)
	{
		while (list.ultimul)
		{
			displayStudent(list.ultimul->s);
			list.ultimul = list.ultimul->prev;
		}
	}

}

void freeDoubleList(DoubleLinkedList* list)
{
	while (list->primul)
	{
		free(list->primul->s.nume);
		Node* aux = list->primul;
		list->primul = list->primul->after;
		free(aux);
	}
	list->primul = NULL;
	list->ultimul = NULL;
}

void insertNodeAtPozition(DoubleLinkedList* list, int position, Student s)
{
	if (position >= 0)
	{
		int contor = 0;

		Node* iter = list->primul;

		while (iter && contor != position)
		{
			contor++;
			iter = iter->after;
		}

		if (contor < position)
			printf("Position OUT OF LIMIT");
		else
		{
			if (contor == 0)
				insertDoubleNodeBegin(list, s);
			else
				if (iter == NULL)
					insertDoubleNodeAfter(list, s);
				else
				{
					Node* newNode = (Node*)malloc(sizeof(Node));
					newNode->s = s;

					Node* previousNode = iter->prev;

					previousNode->after = newNode;
					newNode->prev = previousNode;

					newNode->after = iter;
					iter->prev = newNode;
				}
		}
	}
	else
		printf("NEGATIVE POSITION!");

}

typedef struct NodeStackQueue NodeStackQueue;

struct NodeStackQueue
{
	Student s;
	NodeStackQueue* next;
};

void pushStack(NodeStackQueue** stack, Student s)
{
	NodeStackQueue* newNode = (NodeStackQueue*)malloc(sizeof(NodeStackQueue));
	newNode->s = s;
	
	if (*stack)
	{
		newNode->next = *stack;
	}
	else
	{
		newNode->next = NULL;
	}

	*stack = newNode;
}

void pushQueue(NodeStackQueue** stack, Student s)
{
	NodeStackQueue* newNode = (NodeStackQueue*)malloc(sizeof(NodeStackQueue));
	newNode->s = s;
	newNode->next = NULL;

	if (*stack)
	{
		NodeStackQueue* iter = *stack;
		while (iter->next)
			iter = iter->next;

		iter->next = newNode;
	}
	else
	{
		*stack = newNode;
	}
	

}

Student pop(NodeStackQueue** stack)
{
	
	if (*stack)
	{
		Student s;
		s.varsta = (*stack)->s.varsta;
		s.nume = (char*)malloc(strlen((*stack)->s.nume) + 1);
		strcpy(s.nume, (*stack)->s.nume);

		NodeStackQueue* aux = *stack;
		free(aux->s.nume);
		*stack = (*stack)->next;
		free(aux);

		return s;

	}
	else return createStudent("INVALID", -1);

}

void deleteStudentFromStack(NodeStackQueue** stack, char* nume)
{
	if (*stack)
	{
		NodeStackQueue* iter = *stack;

		if (strcmp(iter->s.nume, nume) == 0)
		{
			*stack = (*stack)->next;
			free(iter->s.nume);
			free(iter);
		}
		else
		{
			NodeStackQueue* previous =NULL;
			while (iter && strcmp(iter->s.nume, nume) != 0)
			{
				 previous = iter;
				iter = iter->next;
			}

			if (iter)
			{
				previous->next = iter->next;
				free(iter->s.nume);
				free(iter);
			}
		}

		
	}


}

void displayStackQueue(NodeStackQueue* list)
{
	if (list)
	{
		while (list != NULL)
		{
			displayStudent(list->s);
			list = list->next;
		}
	}
}


typedef struct NodeHash NodeHash;
typedef struct HashTable HashTable;

struct NodeHash
{
	Student s;
	NodeHash* next;
};

struct HashTable
{
	int dimension;
	NodeHash** table;
};

int HashFunction(HashTable ht, Student s)
{
	return s.varsta % ht.dimension;
}

void insertNodeHash(NodeHash** node, Student s)
{
	NodeHash* newNode = (NodeHash*)malloc(sizeof(NodeHash));
	newNode->s = s;
	newNode->next = NULL;

	if (*node != NULL)
	{
		NodeHash* iter = *node;
		while (iter->next)
			iter = iter->next;

		iter->next = newNode;
	}
	else
	{
		*node = newNode;
	}

}

void initializeHashTable(HashTable* ht, int dim)
{
	ht->dimension = dim;
	ht->table = (Node**)malloc(sizeof(HashTable));
	for (int i = 0; i < dim; i++)
		ht->table[i] = NULL;
}

void insertIntoHashTable(HashTable* ht, Student s)
{
	int id = HashFunction(*ht, s);

	if (id < ht->dimension)
	{
		insertNodeHash(&(*ht).table[id], s);
	}
}

void displayListHash(NodeHash* node)
{
	if (node)
	{
		while (node)
		{
			displayStudent(node->s);
			node = node->next;
		}
	}
}

void displayHashTable(HashTable ht)
{
	for (int i = 0; i < ht.dimension; i++)
	{
		if(ht.table[i])
		displayListHash(ht.table[i]);
		else
		printf("********************** \n\n");
	}
	
}

void freeHashTable(HashTable* ht)
{
	for (int i = 0; i < ht->dimension; i++)
	{
		if (ht->table[i] != NULL)
		{
			NodeHash* iter = ht->table[i];

			while (iter)
			{
				free(iter->s.nume);
				NodeHash* aux = iter;
				iter = iter->next;
				free(aux);
			}

			ht->table[i] = NULL;

		}

	}
	ht->dimension = 0;
}

typedef struct BinaryTree BinaryTree;

struct BinaryTree
{
	BinaryTree* left;
	Student s;
	BinaryTree* right;
};


void insertIntoBinaryTree(BinaryTree** tree, Student s)
{

	if (*tree != NULL)
	{
		if ((*tree)->s.varsta < s.varsta)
		{
			insertIntoBinaryTree(&(*tree)->right, s);
		}
		else 
			if ((*tree)->s.varsta > s.varsta)
			{
				insertIntoBinaryTree(&(*tree)->left, s);
			}
	}
	else
	{
		BinaryTree* newNode = (BinaryTree*)malloc(sizeof(BinaryTree));
		newNode->s = s;
		newNode->left = NULL;
		newNode->right = NULL;
		*tree = newNode;
	}

}

void displayPreOrder(BinaryTree* tree) // Root Left Right
{
	if (tree)
	{
		displayStudent(tree->s);
		displayPreOrder(tree->left);
		displayPreOrder(tree->right);
	}
}

void displayInOrder(BinaryTree* tree) // Left Root Right
{
	if (tree)
	{
		displayInOrder(tree->left);
		displayStudent(tree->s);
		displayInOrder(tree->right);
	}
}

void displayPostOrder(BinaryTree* tree) // Left Right Root 
{
	if (tree)
	{
		displayPostOrder(tree->left);
		displayPostOrder(tree->right);
		displayStudent(tree->s);
	}
}

int calculateHeightTree(BinaryTree* tree)
{
	if (tree)
	{
		int st = calculateHeightTree(tree->left);
		int dr = calculateHeightTree(tree->right);
		if (st > dr)
			return st + 1;
		else
			return dr + 1;
	}
	else
		return 0;
}

Student findStudentAfterAge(BinaryTree* tree, int age)
{
	if (tree !=NULL)
	{
		if (tree->s.varsta < age)
			findStudentAfterAge(tree->right, age);
		else
			if (tree->s.varsta > age)
				findStudentAfterAge(tree->left, age);
			else
			{
				Student s;
				s.varsta = tree->s.varsta;
				s.nume = (char*)malloc(strlen(tree->s.nume) + 1);
				strcpy(s.nume, tree->s.nume);

				return s;
			}

	}
	else
		return createStudent("INVALID", -1);
}

int calculateInbalance(BinaryTree* tree)
{
	return calculateHeightTree(tree->left) - calculateHeightTree(tree->right);
}

void rotateLeft(BinaryTree** tree)
{
	BinaryTree* temp = (*tree)->right;
	(*tree)->right = temp->left;
	temp->left = *tree;
	*tree = temp;
}

void rotateRight(BinaryTree** tree)
{
	BinaryTree* temp = (*tree)->left;
	(*tree)->left = temp->right;
	temp->right = *tree;
	*tree = temp;
}

void freeBinaryTree(BinaryTree** tree)
{
	if (*tree != NULL)
	{
	freeBinaryTree(&(*tree)->left);
	freeBinaryTree(&(*tree)->right);
	free((*tree)->s.nume);
	free(*tree);
	}

	*tree = NULL;
}

void insertAVLTree(BinaryTree** tree, Student s)
{
	if (*tree != NULL)
	{
		if ((*tree)->s.varsta < s.varsta)
			insertAVLTree(&(*tree)->right, s);
		else
			if ((*tree)->s.varsta > s.varsta)
				insertAVLTree(&(*tree)->left, s);

		int echilibru = calculateInbalance(*tree);

		if (echilibru == 2)
		{
			int echilibruST = calculateInbalance((*tree)->left);
			if (echilibruST == -1)
				rotateLeft(&(*tree)->left);

			rotateRight(tree);
		}

		if(echilibru == -2)
		{
			int echilibruDR = calculateInbalance((*tree)->right);
			if (echilibruDR == 1)
				rotateRight(&(*tree)->right);

			rotateLeft(tree);
		}

	}
	else
	{
		BinaryTree* newNode = (BinaryTree*)malloc(sizeof(BinaryTree));
		newNode->s = s;
		newNode->left = NULL;
		newNode->right = NULL;
		*tree = newNode;
	}
}

typedef struct Heap Heap;

struct Heap
{
	int dimensiune;
	int dimensiuneMaxima;
	Student* vector;
};

void createHeap(Heap* h, int dim)
{
	h->dimensiune = dim;
	h->dimensiuneMaxima = dim;
	h->vector = (Student*)malloc(sizeof(Student) * h->dimensiuneMaxima);
}

void filterHeap(Heap* h, int index)
{
	int IS = 2 * index + 1;
	int ID = 2 * index + 2;

	int max = index;

	if (IS < h->dimensiune && h->vector[IS].varsta > h->vector[max].varsta)
		max = IS;

	if (ID < h->dimensiune && h->vector[ID].varsta > h->vector[max].varsta)
		max = ID;

	if (max != index)
	{
		Student aux = h->vector[max];
		h->vector[max] = h->vector[index];
		h->vector[index] = aux;

		if (max < h->dimensiune / 2)
			filterHeap(h, max);
	}
}

void displayHeap(Heap p)
{
	for (int i = 0; i < p.dimensiune; i++)
		displayStudent(p.vector[i]);
}

Student extractHeap(Heap* p)
{
	if (p)
	{
		Student s;
		s.varsta = p->vector[0].varsta;
		s.nume = (char*)malloc(strlen(p->vector[0].nume) + 1);
		strcpy(s.nume, p->vector[0].nume);

		p->dimensiune--;

		Student aux = p->vector[0];
		p->vector[0] = p->vector[p->dimensiune];
		p->vector[p->dimensiune] = aux;

		for (int i = p->dimensiune / 2; i >= 0; i--)
			filterHeap(p, i);

		return s;
	}
	else
		return createStudent("NU EXISTA", -1);


};

typedef struct NodeGraph NodeGraph;

typedef struct Graph Graph;

struct NodeGraph
{
	NodeGraph* next;
	Graph* info;
};

struct Graph
{
	Graph* next;
	Student s;
	NodeGraph* muchii;
};

void insertIntoGraph(Graph** graf, Student s)
{
	Graph* newNode = (Graph*)malloc(sizeof(Graph));

	newNode->s = s;
	newNode->muchii = NULL;
	newNode->next = NULL;

	if (*graf != NULL)
	{
		Graph* iter = *graf;
		while (iter->next)
			iter = iter->next;

		iter->next = newNode;
	}
	else
	{
		*graf = newNode;
	}
}

void insertNodeGraph(Graph* graf, NodeGraph** node)
{
	NodeGraph* newNode = (NodeGraph*)malloc(sizeof(NodeGraph));
	newNode->next = NULL;
	newNode->info = graf;

	if (*node != NULL)
	{
		NodeGraph* iter = *node;
		while (iter->next)
		{
			iter = iter->next;
		}
		iter->next = newNode;
	}
	else
	{
		*node = newNode;
	}
}

Graph* findNode(int varsta, Graph* graf)
{
	Graph* temp = graf;
	if (temp)
	{
		while (temp->s.varsta != varsta && temp != NULL)
			temp = temp->next;
	}

}

void creareMuchie(int v1, int v2, Graph* graf)
{
	Graph* p1 = findNode(v1, graf);
	Graph* p2 = findNode(v2, graf);

	if (p1 && p2)
	{
		insertNodeGraph(p1, &p2->muchii);
		insertNodeGraph(p2, &p1->muchii);
	}
}


void displayMuchiiGraf(NodeGraph* nod)
{
	if (nod != NULL)
	{
		while (nod)
		{
			displayStudent(nod->info->s);
			nod = nod->next;
		}
	}
}

void displayGraph(Graph* graf)
{
	if (graf != NULL)
	{
		while (graf)
		{
			displayStudent(graf->s);
			
			displayMuchiiGraf(graf->muchii);
			printf("***************************\n\n");
			graf = graf->next;
		}
	}
}

int main()
{
	/*  
	
	//Struct, Array, Matrix

	displayStudent(createStudent("Mihai", 20));
	displayStudent(createStudent("Andrei", 28));

	//array memory allocation 

	Student* vectorStudenti = (Student*)malloc(sizeof(Student) * 3);
	vectorStudenti[0] = createStudent("Ionut", 24);
	vectorStudenti[1] = createStudent("Andrei", 28);
	vectorStudenti[2] = createStudent("Popescu", 23);

	for (int i = 0; i < 3; i++)
		displayStudent(vectorStudenti[i]);

	//matrix memory allocation
	Student** matriceStudenti = (Student**)malloc(sizeof(Student*) * 2);
	for (int i = 0; i < 2; i++)
		matriceStudenti[i] = (Student*)malloc(sizeof(Student) * 3);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			matriceStudenti[i][j] = createStudent("A", i*10 + j);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
			displayStudent(matriceStudenti[i][j]);
		printf("*************** \n\n");
	}
	*/

	/* 
	
	//LinkedList

	LinkedList* list =NULL;
	insertLinkedListStart(&list, createStudent("Mihai", 22));
	insertLinkedListEnd(&list, createStudent("Pavel", 20));
	displayList(list);
	freeList(&list);
	*/

	/*
	
	//Double LinkedList

	DoubleLinkedList listaDubla;
	listaDubla.primul = NULL;
	listaDubla.ultimul = NULL;
	insertDoubleNodeBegin(&listaDubla, createStudent("Savu", 26));
	insertDoubleNodeBegin(&listaDubla, createStudent("Catalin", 24));
	insertDoubleNodeAfter(&listaDubla, createStudent("Andrei", 23));
	displayDoubleLinkedListStart(listaDubla);
	printf("***************************\n\n");
	displayDoubleLinkedListEnd(listaDubla);
	printf("***************************\n\n");
	insertNodeAtPozition(&listaDubla,1,createStudent("Matei",25));
	displayDoubleLinkedListStart(listaDubla);
	printf("***************************\n\n");
	displayDoubleLinkedListEnd(listaDubla);
	freeDoubleList(&listaDubla);
	*/

	/*
	
	//Stack and Queue

	NodeStackQueue* stack=NULL;
	pushStack(&stack, createStudent("Matei", 25));
	pushStack(&stack, createStudent("Andrei", 21));
	pushStack(&stack, createStudent("Paul", 19));
	displayStackQueue(stack);
	printf("***************************\n\n");
	displayStudent(pop(&stack));
	printf("***************************\n\n");
	displayStackQueue(stack);
	printf("***************************\n\n");

	NodeStackQueue* queue = NULL;
	pushQueue(&queue, createStudent("Vlad", 28));
	pushQueue(&queue, createStudent("Ionut", 24));
	pushQueue(&queue, createStudent("Andreea", 20));
	pushQueue(&queue, createStudent("Stefan", 21));
	displayStackQueue(queue);
	printf("***************************\n\n");
	displayStudent(pop(&queue));
	printf("***************************\n\n");
	displayStackQueue(queue);
	deleteStudentFromStack(&queue, "Stefan");
	printf("***************************\n\n");
	displayStackQueue(queue);
	*/

	/*
	
	//HashTable 

	HashTable ht;
	initializeHashTable(&ht, 10);
	insertIntoHashTable(&ht, createStudent("Stefan", 21));
	insertIntoHashTable(&ht, createStudent("Pavel", 29));
	insertIntoHashTable(&ht, createStudent("Andrei", 25));
	displayHashTable(ht);
	freeHashTable(&ht);
	displayHashTable(ht);
	*/

	/*
	
	//Binary Tree

	BinaryTree* tree = NULL;
	insertIntoBinaryTree(&tree, createStudent("Stefan", 21));
	insertIntoBinaryTree(&tree, createStudent("Pavel", 18));
	insertIntoBinaryTree(&tree, createStudent("Andrei", 25));
	insertIntoBinaryTree(&tree, createStudent("Matei", 22));
	insertIntoBinaryTree(&tree, createStudent("Ionut", 27));
	displayPreOrder(tree);
	printf("***************************\n\n");
	displayInOrder(tree);
	printf("***************************\n\n");
	displayPostOrder(tree);
	printf("***************************\n\n");
	displayStudent(findStudentAfterAge(tree, 27));
	freeBinaryTree(&tree);
	
	//AVL Tree

	BinaryTree* AVLTree = NULL;
	insertAVLTree(&AVLTree, createStudent("Stefan", 1));
	insertAVLTree(&AVLTree, createStudent("Ionut", 2));
	insertAVLTree(&AVLTree, createStudent("Andrei", 3));
	insertAVLTree(&AVLTree, createStudent("Maria", 4));
	insertAVLTree(&AVLTree, createStudent("Razvan", 5));
	insertAVLTree(&AVLTree, createStudent("Marius", 6));
	insertAVLTree(&AVLTree, createStudent("Andreea", 7));
	displayPreOrder(AVLTree);
	freeBinaryTree(&AVLTree);
	*/


	/*
	//Heap
	Heap p;
	createHeap(&p, 6);
	p.vector[0] = createStudent("Stefan", 1);
	p.vector[1] = createStudent("Ionut", 2);
	p.vector[2] = createStudent("Andrei", 3);
	p.vector[3] = createStudent("Maria", 4);
	p.vector[4] = createStudent("Ionela", 5);
	p.vector[5] = createStudent("Marius", 6);

	for (int i = p.dimensiune / 2 - 1; i >= 0; i--)
		filterHeap(&p, i);

	displayHeap(p);
	printf("***************************\n\n");
	displayStudent(extractHeap(&p));
	printf("***************************\n\n");
	displayHeap(p);
	*/

	//Graph
	Graph* graf = NULL;
	insertIntoGraph(&graf, createStudent("Ionela", 1));
	insertIntoGraph(&graf, createStudent("Mihai", 2));
	insertIntoGraph(&graf, createStudent("Andreea", 3));
	insertIntoGraph(&graf, createStudent("Ionut", 4));
	insertIntoGraph(&graf, createStudent("Alexandru", 5));
	insertIntoGraph(&graf, createStudent("Paula", 6));
	//displayGraph(graf);

	creareMuchie(1, 2, graf);
	creareMuchie(1, 3, graf);
	creareMuchie(1, 4, graf);
	creareMuchie(4, 3, graf);
	creareMuchie(2, 3, graf);
	creareMuchie(2, 5, graf);
	creareMuchie(2, 6, graf);
	creareMuchie(5, 6, graf);

	displayGraph(graf);

}