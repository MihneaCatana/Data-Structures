#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

//we can't use references in C, they are available only in C++ 

void swapValue(int val1, int val2)
{
	int aux = val1;
	val1 = val2;
	val2 = aux;
}

void swapPointers(int *val1, int *val2)
{
	int aux = *val1;
	*val1 = *val2;
	*val2 = aux;
}

void readArray(int *dimension, int** vector)
{
	printf("The dimension of the array is: ");
	scanf("%i", dimension);
	printf("Array: ");
	*vector = (int*)malloc(sizeof(int) * (*dimension));

	for (int i = 0; i < *dimension; i++)
		scanf("%i", &(*vector)[i]);
}

//read an array from file
void readArrayFile(char* fileName, int* dimension, int** vector)
{
	FILE* f = fopen(fileName, "r");

	if (f)
	{
		fscanf(f, "%i", dimension);
		*vector = (int*)malloc(sizeof(int) * (*dimension));
		for (int i = 0; i < *dimension; i++)
			 fscanf(f,"%i", &(*vector)[i]);

		for (int i = 0; i < *dimension; i++)
			printf("%i \t", (*vector)[i]);
	}
	else
		printf("File not found!");
}

int main()
{
	int a = 10;
	double b = 20.8;
	char c = 'C'; 
	// behind every char, there is an ASCII code, so if we add 1, we will get the code of 'D'
	c = c + 1; 
	// %i - for integer, %f - for float , %c - for char, %s - for a string/
	printf("%i \n", a);
	printf("%f \n", b);
	printf("%c \n", c); 

	//An ASCII code is a integer
	a = a + c;
	printf("%i \n", a);

	//memory allocation for an array of characters
	char* str;
	str = (char*)malloc(4 * sizeof(char));

	str[0] = 65;
	str[1] = 66;
	str[2] = 67;
	str[3] = 0; // 0 is the code for '\0'

	printf("%s \n", str);

	//read a value for a 
	printf("Give value for a : ");
	scanf("%i", &a);

	
	int var1 = 10;
	int var2 = 15;

	swapValue(var1, var2);

	//As you can see, the values are not changed 
	printf("var1 = %i ; var2 = %i \n", var1, var2);

	swapPointers(&var1, &var2);
	printf("var1 = %i ; var2 = %i \n", var1, var2);


	int n;
	int* v;
	//we allocate memory for our array and read elements
	readArray(&n, &v);

	for (int i = 0; i < n; i++)
		printf("%i \t", v[i]);

	printf("\n");

	int dim, * v1;
	readArrayFile("vect.txt", &dim, &v1);
}