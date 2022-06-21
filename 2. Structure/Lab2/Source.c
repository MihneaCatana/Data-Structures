#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

//we use this line so we wont repeat "struct"
typedef struct Company Company;

struct Company {

	int nrEmployees;
	char* nameCompany;
	float earnings;
};

//create a company like a constructor in C++
Company createCompany(int nr, char* name, float earnings)
{
	Company c;
	c.nrEmployees = nr;
	c.nameCompany = (char*)malloc(strlen(name) + 1);
	strcpy(c.nameCompany, name);
	c.earnings = earnings;
	return c;
}

//display company
void displayCompany(Company c)
{
	printf("Company \n - name : %s \n - number of employees: %i \n - earnings: %7.2f euros \n\n",c.nameCompany,c.nrEmployees,c.earnings);
}

Company readCompanyFile(FILE* f)
{
	//read only one company
	Company c;

	//we start reading each field

	fscanf(f, "%i", &c.nrEmployees);

	//for char* we need to use a buffer and then write the content in the field
	//for every type of dynamically allocated variable, DON'T forget to allocate memory

	char buffer[100];
	//fgets(buffer,100, f);
	
	fscanf(f, "%s", &buffer);
	c.nameCompany = (char*)malloc(strlen(buffer)+1);
	strcpy(c.nameCompany, buffer);

	fscanf(f, "%f", &c.earnings);
	return c;

}

//reading every company from a file and displaying it 
void readFromFile(char* fileName)
{
	FILE* f =  fopen(fileName, "r");

	if (f !=NULL )
	{
		while (!(feof(f)))
		{
			Company c = readCompanyFile(f);
			displayCompany(c);
		}
	}
	else
	{
		printf("File can not be opened!");
	}
}

//reading a matrix of Companies from a file and displaying it
void readMatrixOfCompanies(char* fileName, int* lines, int* columns, Company*** matrixCompanies)
{
	FILE* f = fopen(fileName, "r");

	if (f)
	{
		fscanf(f, "%i", lines);
		fscanf(f, "%i", columns);

		*matrixCompanies = (Company*)malloc(sizeof(Company) * (*lines));
		for (int i = 0; i < *lines; i++)
			(*matrixCompanies)[i] = (Company*)malloc(sizeof(Company) * (*columns));

		for(int i=0;i< *lines;i++)
			for (int j = 0; j < *columns; j++)
			{
				Company c;
				fscanf(f, "%i", &c.nrEmployees);


				char buffer[100];
				fscanf(f, "%s", &buffer);

				c.nameCompany = (char*)malloc(strlen(buffer) + 1);
				strcpy(c.nameCompany, buffer);


				fscanf(f, "%f", &c.earnings);


				(*matrixCompanies)[i][j] = c;
			}

		for (int i = 0; i < *lines; i++)
		{
			for (int j = 0; j < *columns; j++)
			{
				displayCompany((*matrixCompanies)[i][j]);
			}
			printf("--------------- \n \n");
		}
			
	}
	else
		printf("File not found!");

}

//free memory
void freeMemoryMatrix(Company** matrix, int lines, int columns)
{

	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
			free(matrix[i][j].nameCompany);
		free(matrix[i]);
	}
	free(matrix);
		
}

int main()
{
	Company c1 = createCompany(100, "Altex", 5800);
	Company c2 = createCompany(150, "Emag", 9000);
	displayCompany(c1);
	displayCompany(c2);

	readFromFile("company.txt");
	int lines, columns;
	Company** matrix;
	readMatrixOfCompanies("matrix.txt",&lines,&columns,&matrix);
	freeMemoryMatrix(matrix, lines, columns);
}