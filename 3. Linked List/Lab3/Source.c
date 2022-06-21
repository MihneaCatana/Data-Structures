#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Human Human;

// we will use a struct with a dynamically allocated attribute 
struct Human
{
	char* name;
	int age;
};

Human createHuman(char* name, int age)
{
	Human h;

	//we don't need to multiply with sizeof(char), because size of char is 1 byte 
	h.name = (char*)malloc(strlen(name) + 1);
	strcpy(h.name, name);

	h.age = age;
	return h;
}

void displayHuman(Human h)
{
	printf("This human is named %s and is %i years old \n \n", h.name, h.age);
}

//Linked List

typedef struct LinkedList LinkedList;

struct LinkedList
{
	Human h;
	LinkedList* next;
};

LinkedList* insertList(LinkedList* l, Human h1)
{
	// we will insert new nodes in our list at the start of our list 

	/*
		---------   +  OLD list
			^
			|
			|
		New Node
	*/
	
	LinkedList* newNode = (LinkedList*)malloc(sizeof(LinkedList));
	newNode->h = h1;
	newNode->next = l;
	return newNode;

}

void showList(LinkedList* l)
{
	// we create a new Node to browse the list ( it s a good practice for the integrity of the list 
   //  in case we modify it )
	LinkedList* iterator = l;

	while (iterator)
	{
		displayHuman(iterator->h);
		//we go to the next element
		iterator = iterator->next;
	}
}

LinkedList* insertListEnd(LinkedList* list, Human h)
{

	/*
			OLD list	+	---------   
								^
								|
								|
							New Node
	*/

	//We create the new Node 
	LinkedList* nou = (LinkedList*)malloc(sizeof(LinkedList));
	nou->h = h;
	nou->next = NULL;

	if (list)
	{
		//we find the last element of the list and we link it with the new Node
		LinkedList* iterator = list;
		while (iterator->next)
		{
			iterator = iterator->next;
		}
		iterator->next = nou;
	}
	else
	{
		//if the list is empty, the new node is the start of the list
		list = nou;
	}

	return list;
}

//free the memory
void freeList(LinkedList** l)
{
	LinkedList* iterator = *l;

	while (iterator)
	{
		//first we need to free the dynamically allocated attribute from structure
		free(iterator->h.name);

		//then we need to save the current Node in AUX, go to the next one and then delete AUX
		LinkedList* aux = iterator;
		iterator = iterator->next;
		free(aux);
	}
	*l = NULL;
}

int main()
{
	LinkedList* listaSimpla = NULL;
	listaSimpla = insertList(listaSimpla, createHuman("Andrew", 20));
	listaSimpla = insertList(listaSimpla, createHuman("Michael", 27));
	listaSimpla = insertList(listaSimpla, createHuman("John", 29));
	listaSimpla = insertListEnd(listaSimpla, createHuman("Andreea", 25));
	showList(listaSimpla);
	freeList(&listaSimpla);
}