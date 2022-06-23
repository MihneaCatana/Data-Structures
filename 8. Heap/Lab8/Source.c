#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Truck Truck;

struct Truck
{
	char* plate;
	float capacity;
};

typedef struct Heap Heap;

struct Heap
{
	Truck* vector;
	int dimension;
	int dimensionTotal;
};

Truck createTruck(char* plate, float capacity)
{
	Truck t;
	t.plate = (char*)malloc(strlen(plate) + 1);
	strcpy(t.plate, plate);
	t.capacity = capacity; 
	return t;
} 

void displayTruck(Truck t)
{
	printf("Truck with the plate %s can carry %f tonnes \n\n", t.plate, t.capacity);
}

//Heap is an tree, but it is reprezented as an array 

void allocateMemoryHeap(int dim, int dimTotal, Heap* heap)
{
	heap->dimension = dim;
	heap->dimensionTotal = dimTotal;
	heap->vector = (Truck*)malloc(sizeof(Truck) * heap->dimensionTotal);
}

void displayHeap(Heap p)
{
	for (int i = 0; i < p.dimension; i++)
		displayTruck(p.vector[i]);
}

void filterHeap(Heap p,int index)
{
	//Heap is a tree where every parent Node can have 0,1 or 2 child Nodes;
	//IS - index of the first child Node
	//ID - index of the second child Node
	int IS = 2*index +1;
	int ID = 2*index +2;

	Truck aux;

	int max = index;

	if (IS <p.dimension && p.vector[IS].capacity > p.vector[max].capacity)
	{
		max = IS;
	}

	if (ID < p.dimension && p.vector[ID].capacity > p.vector[max].capacity)
	{
		max = ID;
	}

	if (max != index)
	{
		aux = p.vector[max];
		p.vector[max] = p.vector[index];
		p.vector[index] = aux;

		if (max < p.dimension / 2)
			filterHeap(p, max);
	}


}

Truck extractTruck(Heap* h)
{
	if (h)
	{
		Truck p;
		p.capacity = h->vector[h->dimension - 1].capacity;
		p.plate = (char*)malloc(strlen(h->vector[h->dimension-1].plate) + 1);
		strcpy(p.plate, h->vector[h->dimension - 1].plate);

		h->dimension--;

		for (int i = h->dimension / 2 - 1; i >= 0; i--)
			filterHeap(*h, i);

		return p;
	}
	else
		return createTruck("INVALID", -1);

}

void freeHeap(Heap* p)
{
	for (int i = 0; i < p->dimensionTotal; i++)
		free(p->vector[i].plate);
	free(p->vector);
	p->dimension = 0;
	p->dimensionTotal = 0;
}

int main()
{
	Heap h ;
	allocateMemoryHeap(6, 6, &h);
	h.vector[0] = createTruck("BI04GWE", 100);
	h.vector[1] = createTruck("AG02CCE", 120);
	h.vector[2] = createTruck("IF54BYE", 80);
	h.vector[3] = createTruck("CT32TRE", 90);
	h.vector[4] = createTruck("BR01PPM", 170);
	h.vector[5] = createTruck("BH05GIE", 200);
	displayHeap(h);
	printf("-------------------------\n\n");
	for (int i = h.dimension / 2 - 1; i >= 0; i--)
		filterHeap(h, i);
	displayHeap(h);
	printf("-------------------------\n\n");
	displayTruck(extractTruck(&h));
	printf("-------------------------\n\n");
	displayHeap(h);
	
	freeHeap(&h);

}