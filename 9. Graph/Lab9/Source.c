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

	displayGraph(graf);
	freeGraph(&graf);
}