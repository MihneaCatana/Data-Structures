#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Car Car;

struct Car
{
	char* brand;
	int yearOfProduction;
};

Car createCar(char* brand, int* yearOfProduction)
{
	Car c;

	c.brand = (char*)malloc(strlen(brand) + 1);
	strcpy(c.brand, brand);

	c.yearOfProduction = yearOfProduction;
	return c;
}

void displayCar(Car c)
{
	printf("Car is made by %s in %i \n \n", c.brand, c.yearOfProduction);
}

//Double Linked List 

//A Node with its links and its content
typedef struct Node Node;

struct Node
{
	Node* previous;
	Car c;
	Node* after;


	/*
					  ____________
		 previous	 |			  |		 after
	<--------------- |     CAR    | --------------->
					 |____________|
					
	*/
};

// the beginning and the ending of the list 
typedef struct DoubleLinkedList DoubleLinkedList;

struct DoubleLinkedList
{
	Node* first;
	Node* last;
};

void insertNodeStart(DoubleLinkedList* lista, Car c)
{
	//like the insert into a linked list, only just setting previous to NULL for explicity 
	Node* nod = (Node*)malloc(sizeof(Node));
	nod->c = c;
	nod->after = lista->first;
	nod->previous = NULL;

	if (lista->last == NULL || lista->first == NULL)
	{
		//if the list is empty, the new Node becomes also the last Node
		lista->last = nod;
	}
	else
	{
		lista->first->previous = nod;
	}
	//the new Node wil ALWAYS become the first Node of the list
	lista->first = nod;
	
}

//I changed the signature of this function so you can see the difference ( void vs DoubleLinkedList )
DoubleLinkedList insertNodeEnd(DoubleLinkedList lista, Car c)
{
	Node* nod = (Node*)malloc(sizeof(Node));
	nod->c = c;
	nod->after = NULL;
	nod->previous = lista.last;
	
	if (lista.first == NULL || lista.last == NULL)
	{
		//if the list is empty, the new Node becomes also the first Node
		lista.first = nod;
	}
	else
	{
		lista.last->after = nod;
	}
	//the new Node wil ALWAYS become the last Node of the list
	lista.last = nod;
}

void displayList(DoubleLinkedList lista)
{
	Node* nod = lista.first;

	while (nod)
	{
		displayCar(nod->c);
		nod = nod->after;
	}
}

void freeList(DoubleLinkedList* lista)
{
	Node* iterator = lista->first;

	while (iterator)
	{
		free(iterator->c.brand);
		Node* aux = iterator;
		iterator = iterator->after;
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
}

void InsertPozition(int pozition, DoubleLinkedList* lista, Car c)
{
	// Check if the pozition is a pozitive number
	if (pozition < 0)
	{
		printf("Pozition must be a pozitive number");
	}
	else
	{
		//if the pozition is 0, we use the function that inserts at the beginning of the list
		if (pozition == 0)
			insertNodeStart(lista, c);
		else
		{
			//we count till we find the poziton or the list ends
			Node* iterator = lista->first;
			int contor = 0;
			while (iterator)
			{
				if (contor == pozition)
					break;
				iterator = iterator->after;
				
				contor++;
			}
			
			if (contor < pozition)
				printf("Pozition must be lower than the length of the list");
			else
			{
				//if it is the last pozition, we use the function that inserts at the end of the list 
				if (iterator == NULL)
					*lista = insertNodeEnd(*lista, c);
				else
				{
					/*
							iterPrev								 iterator
							 _ _ _ _								 _ _ _ _
							|		|	                            |		|
							|		|-----------		 -----------|		|
							 _ _ _ _			|		 |			 _ _ _ _
									^			|		 |			^
									|			|		 |			|
									|			 _ _ _ _			|
									|			|		|			|
									|-----------|		|-----------|
								   nou->previous _ _ _ _  nou->after
					
					*/


					Node* nou = (Node*)malloc(sizeof(Node));
					nou->c = c;
					nou->after = iterator;
					Node* iterPrev = iterator->previous;
					iterator->previous = nou;
					iterPrev->after = nou;
					nou->previous = iterPrev;
				}
			}

		}
	}
}

int main()
{
	DoubleLinkedList lista;
	lista.first = NULL;
	lista.last = NULL;
	insertNodeStart(&lista, createCar("Toyoya", 2000));
	insertNodeStart(&lista, createCar("BMW", 1998));
	insertNodeStart(&lista, createCar("Tesla", 2020));
	lista = insertNodeEnd(lista, createCar("Dacia", 2016));
	lista = insertNodeEnd(lista, createCar("Renault", 2018));
	//displayList(lista);
	InsertPozition(2, &lista, createCar("Rolls-Royce",1960));
	displayList(lista);
	freeList(&lista);
}