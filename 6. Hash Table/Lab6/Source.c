#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Product Product;

struct Product
{
	int id;
	char* name;
};

Product createProduct(int id, char*name)
{
	Product p;

	p.name = (char*)malloc(strlen(name) + 1);
	strcpy(p.name, name);

	p.id = id;

	return p;
}

void displayProduct(Product p)
{
	printf("The product with the id: %i is named %s \n\n", p.id, p.name);
}

typedef struct Node Node;

struct Node
{
	Node* next;
	Product p;
};

//HashTable with chaining

typedef struct HashTable HashTable;

//HashTable can be a viewed as an array of lists 
struct HashTable
{
	int dimension;
	Node** vector; // an array of Nodes
};

/*
			| * |   |   |   |	|	| *	|  - HashTable
			  |						  |
			  |						  |
			  |-> | * | * |	Node	  | -> | * | * | * | Node

			  * - object 
			|   | - empty cell
			| * | - 			

*/


//we allocate memory for our HashTable
HashTable createHashTable(int dimension)
{
	HashTable ht;

	ht.dimension = dimension;

	ht.vector = (Node**)malloc(sizeof(HashTable)*dimension);
	for (int i = 0; i < dimension; i++)
		ht.vector[i] = NULL;

	return ht;
}

//we need a hash function so we know where we will put our element 
int HashFunction(HashTable ht, Product p)
{
	return p.id % ht.dimension;
}

//insert into list
void insertIntoList(Node** list, Product p)
{
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->p = p;
	nou->next = NULL;

	if (*list)
	{
		Node* iterator = *list;
		while (iterator->next)
		{
			iterator = iterator->next;
		}
		iterator->next = nou;
	}
	else
	{
		*list = nou;
	}


}

//insert into HashTable
HashTable insertIntoHashTable(HashTable ht, Product p)
{
	if (HashFunction(ht, p) < ht.dimension)
	{
		
		int pozition = HashFunction(ht, p); // we save the pozition 
		insertIntoList(&ht.vector[pozition], p);

	}
	return ht;

}

void displayList(Node* list)
{
	while (list)
	{
		displayProduct(list->p);
		list = list->next;
	}
}

void displayHashTable(HashTable ht)
{
	for (int i = 0; i < ht.dimension; i++)
	{
		if (ht.vector[i])
			displayList(ht.vector[i]);
		printf("------------------- \n\n");
	}
}

void freeHashTable(HashTable* ht)
{
	for (int i = 0; i < ht->dimension; i++)
	{
		if (ht->vector[i])
		{
			Node* iterator = ht->vector[i];
			while (iterator)
			{
				free(iterator->p.name);
				Node* aux = iterator;
				iterator = iterator->next;
				free(aux);
			}
		}
	}
	ht->dimension = 0;
	free(ht->vector);

}

int main()
{
	HashTable ht ;
	ht = createHashTable(10);
	ht = insertIntoHashTable(ht,createProduct(1,"Lapte"));
	ht = insertIntoHashTable(ht, createProduct(11, "Carne"));
	ht = insertIntoHashTable(ht, createProduct(5, "Castravete"));
	ht = insertIntoHashTable(ht, createProduct(77, "Paine"));
	displayHashTable(ht);
	freeHashTable(&ht);
	displayHashTable(ht); //it wont display anything because HashTable has been freed
}