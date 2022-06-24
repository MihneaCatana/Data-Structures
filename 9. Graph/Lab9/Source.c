#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct City City;

struct City
{
	int id;
	char* name;
};

City createCity(int id, char* name)
{
	City c;
	c.id = id;
	c.name = (char*)malloc(strlen(name) + 1);
	strcpy(c.name, name);

	return c;
}

void displayCity(City c)
{
	printf("City with the id %i is named %s \n\n", c.id, c.name);
}

typedef struct Node Node;
typedef struct NodeGraph NodeGraph;

//Graph

struct Node
{
	Node* next;
	NodeGraph* address;
};

struct NodeGraph
{
	City c;
	NodeGraph* next;
	Node* lines; //links between nodes
};

//we insert in the graph the nodes
void insertGraph(NodeGraph** graph, City c)
{
	NodeGraph* newNode = (NodeGraph*)malloc(sizeof(NodeGraph));
	newNode->c = c;
	newNode->lines = NULL;
	newNode->next = NULL;

	if (*graph)
	{
		NodeGraph* iter = *graph;
		while (iter->next)
		{
			iter = iter->next;
		}
		iter->next = newNode;
	}
	else
	{
		*graph = newNode;
	}
}

void insertNodes(NodeGraph* info, Node** nod)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->address = info;
	newNode->next = NULL;

	if (*nod)
	{
		Node* iter = *nod;
		while (iter->next)
		{
			iter = iter->next;
		}
		iter->next = newNode;
	}
	else {
		*nod = newNode;
	}
	
}

void displayNode(Node* node)
{
	if (node)
	{
		while (node)
		{
			displayCity(node->address->c);
			node = node->next;
		}
	}
}

void displayGraph(NodeGraph* graph)
{
	if (graph)
	{
		NodeGraph* iter = graph;
		while (iter)
		{
			displayCity(iter->c);
			printf("*****************************\n\n");

			displayNode(iter->lines);
			printf("-----------------------------\n\n");
			iter = iter->next;
		}
	}
}

NodeGraph* findNode(int id, NodeGraph* graf)
{
	NodeGraph* iter = graf;
	while (iter->c.id != id && iter)
	{
		iter = iter->next;
	}
	return iter;
}

void createLinkNodes(int id1,int id2, Node* graf)
{
	NodeGraph* ng1 = findNode(id1, graf);
	NodeGraph* ng2 = findNode(id2, graf);

	if (ng1 && ng2)
	{
		insertNodes(ng1, &(ng2->lines));
		insertNodes(ng2, &(ng1->lines));
	}
}

void freeGraph(NodeGraph** graf)
{
	while (*graf)
	{
		NodeGraph* iter = *graf;
		while (iter->lines)
		{
			Node* aux = iter->lines;
			iter->lines = iter->lines->next;
			free(aux);
		}

		free(iter->c.name);
		*graf = (*graf)->next;
		free(iter);
	}
	*graf = NULL;
}

// for traversing graphs, we need to use a queue

typedef struct NodeQueue NodeQueue;

struct NodeQueue
{
	NodeQueue* prev;
	int id;
	NodeQueue* after;
};

typedef struct Queue Queue;

struct Queue
{
	NodeQueue* firstNode;
	NodeQueue* lastNode;
};

void pushStack(int id, Queue* list)
{
	NodeQueue* newNode = (NodeQueue*)malloc(sizeof(NodeQueue));
	newNode->id = id;
	newNode->after = NULL;
	newNode->prev = list->lastNode;

	if (list->lastNode)
	{
		list->lastNode->after = newNode;
	}
	else
	{
		list->firstNode = newNode;
	}

	list->lastNode = newNode;
}

void pushQueue(int id, Queue* list)
{
	NodeQueue* newNode = (NodeQueue*)malloc(sizeof(NodeQueue));
	newNode->id = id;
	newNode->prev = NULL;
	newNode->after = NULL;

	if (list->firstNode)
	{
		newNode->after = list->firstNode;
		list->firstNode->prev = newNode;
		
	}
	else
		list->lastNode = newNode;

	list->firstNode = newNode;
}

int pop(Queue* list)
{
	int e;

	if (list)
	{
		e = list->lastNode->id;

		list->lastNode = list->lastNode->prev;
		if (list->lastNode)
		{
			free(list->lastNode->after);
			list->lastNode->after = NULL;
		}
		else
		{
			free(list->firstNode);
			list->firstNode = NULL;
		}

		return e;

	}
	else return -1;
}

void displayQueue(Queue q)
{
	if (q.firstNode)
	{
		NodeQueue* iter = q.firstNode;

		while (iter)
		{
			printf("%i \t", iter->id);
			iter = iter->after;
		}

		printf("\n");
	}
}

int calculateDimension(NodeGraph* q)
{
	if (q)
	{
		int contor = 0;
		NodeGraph* iter = q;

		while (iter)
		{
			contor++;
			iter = iter->next;
		}

		return contor;
	}
	return 0;
}

void BreadthTraverse(int idStart,NodeGraph* g) //parcurgere in latime 
{
	//this array is used to check if the Node was visited
	int dim = calculateDimension(g);

	int* vector = (int*)malloc(sizeof(int) * dim);
	for (int i = 0; i < dim; i++)
		vector[i] = 0;

	Queue queue;
	queue.firstNode = NULL;
	queue.lastNode = NULL;

	pushQueue(idStart, &queue);
	vector[idStart - 1] = 1;

	while (queue.firstNode)
	{
		int id = pop(&queue);
		NodeGraph* graf = findNode(id, g);
		displayCity(graf->c);

		Node* muchii = graf->lines;

		while (muchii)
		{
			if (vector[muchii->address->c.id - 1] == 0)
			{
				pushQueue(muchii->address->c.id , &queue);
				vector[muchii->address->c.id - 1] = 1;
			}
			muchii = muchii->next;
		}
	}

}

void DepthTraverse(int idStart, NodeGraph* graph)
{
	int dim = calculateDimension(graph);
	int* vector = (int*)malloc(sizeof(int) * dim);
	for (int i = 0; i < dim; i++)
		vector[i] = 0;

	Queue stack;
	stack.firstNode = NULL;
	stack.lastNode = NULL;

	pushStack(idStart, &stack);
	vector[idStart-1] = 1;

	while (stack.firstNode)
	{
		int id = pop(&stack);
		NodeGraph* find = findNode(id, graph);
		displayCity(find->c);

		Node* muchii = find->lines;

		while (muchii)
		{
			if (vector[muchii->address->c.id-1] == 0)
			{
				pushStack(muchii->address->c.id, &stack);
				vector[muchii->address->c.id - 1] = 1;
			}
			muchii = muchii->next;
		}

	}
}

int main()
{
	NodeGraph* graf = NULL;
	insertGraph(&graf, createCity(1, "Bucuresti"));
	insertGraph(&graf, createCity(2, "Pitesti"));
	insertGraph(&graf, createCity(3, "Iasi"));
	insertGraph(&graf, createCity(4, "Cluj"));
	insertGraph(&graf, createCity(5, "Brasov"));
	insertGraph(&graf, createCity(6, "Sibiu"));

	//displayGraph(graf);

	createLinkNodes(1, 2, graf);
	createLinkNodes(1, 3, graf);
	createLinkNodes(1, 4, graf);
	createLinkNodes(4, 3, graf);
	createLinkNodes(2, 3, graf);
	createLinkNodes(2, 5, graf);
	createLinkNodes(2, 6, graf);
	createLinkNodes(5, 6, graf);

	//displayGraph(graf);

	BreadthTraverse(1, graf);
	printf("*************\n\n");
	DepthTraverse(1, graf);

	freeGraph(&graf);
}