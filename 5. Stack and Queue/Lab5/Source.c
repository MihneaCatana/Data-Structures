#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Phone Phone;

struct Phone
{
	char* name;
	int price;
};

Phone createPhone(char* name, int price)
{
	Phone p;
	p.name = (char*)malloc(strlen(name) + 1);
	strcpy(p.name, name);
	p.price = price;
	return p;
}

void displayPhone(Phone p)
{
	printf("The model %s costs %i euros \n \n", p.name, p.price);
}

//STACK AND QUEUE 

//STACK - LIFO - LAST IN, FIRST OUT    

/*
	   |  ^	
	   |  |
	| _____ |
	| _____ |
	| _____ |
	| _____ |
	|_______|
*/

//QUEUE - FIFO - FIRST IN, FIRST OUT      

//-> [ | | | ] ->

typedef struct Node Node;

struct Node
{
	Phone p;
	Node* next;
};

Node* pushBeginning(Node* list, Phone p)
{
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->p = p;
	nou->next = list;
	return nou;
}

Phone popQueue(Node** list)
{
	if (list)
	{
		Node* iterator = *list;
		while (iterator->next->next)
		{
			iterator = iterator->next;
		}
		//we create a new object that has the same attributes as the last element in list
		// we need to use the function createPhone, because it creates a deep copy that 
		// doesn't get deleted 
		Node* prev = iterator;
		iterator = iterator->next;
		Phone p = createPhone(iterator->p.name, iterator->p.price);
		free(iterator->p.name);
		free(iterator);
		prev->next = NULL;
		return p;
		
	}
	else
	{
		return(createPhone("Invalid", -1));
	}
}

Phone popStack(Node** list)
{
	if (*list)
	{
		Phone p = createPhone((*list)->p.name, (*list)->p.price);
		Node* aux = *list;
		*list = (*list)->next; // we go to the second element

		//free the first element
		free(aux->p.name);
		free(aux);
		return p;
	}
	else
	{
		return(createPhone("Invalid", -1));
	}
}

void displayList(Node* list)
{
	Node* iterator = list;
	while (iterator)
	{
		displayPhone(iterator->p);
		iterator = iterator->next;
	}
}

void freeList(Node** list)
{
	Node* iterator = *list;
	while (iterator)
	{
		free(iterator->p.name);
		Node* aux = iterator;
		iterator = iterator->next;
		free(aux);
	}
}

int main()
{
	Node* list = NULL;
	list = pushBeginning(list, createPhone("S1", 1000));
	list = pushBeginning(list, createPhone("S3", 1500));
	list = pushBeginning(list, createPhone("S5", 1700));
	displayList(list);
	displayPhone(popQueue(&list));
	displayList(list);
	displayPhone(popStack(&list));
	displayList(list);
}