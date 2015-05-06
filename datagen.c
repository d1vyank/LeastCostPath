/*
Generate the input matrix for ECE Lab2.

The first command line input is the size of the matrix. The second one is optional and the program will display the generated matrix when more than one command line arguments are passed.
The program will generate a matrix indicating the weight of a directed graph. The elements in the diagnal are set to 0. The other elements are intergers randomly uniformly generated in the range [1,MAXDIS]. The elements reaching MAXDIS are replaced by INFINITY to represent the absense of some arcs. The elements in the final output are other integers in [1, MAXDIS-1] or INFINITY. The value for MAXDIS and INFINITY are defined in the macro.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INFINITY 100000
#define MAXDIS 1000

int main (int argc, char* argv[])
{
	int i,j,n,temp;
	FILE * fp;

	if (argc==1)
	{	
		printf("Please assign the number of cities!\n");
		return 1;
	}
	n=strtol(argv[1], NULL, 10);

	if ((fp=fopen("data_input","w"))==NULL)
	{
		printf("Fail to open a file.\n");
		return 2;
	}
	/*Generate the matrix*/	
	fprintf(fp, "%d\n\n",n);
	srand(time(NULL));
	for (i=0;i<n;i++)
	{	
		for (j=0;j<n;j++)
			{
				if (i==j)
					fprintf(fp, "%d\t", 0);
				else	if ((temp=random()%MAXDIS+1)==MAXDIS)
						fprintf(fp, "%d\t", INFINITY);
					else
						fprintf(fp, "%d\t", temp);	
			}
		fprintf(fp, "\n");
	}
	fclose(fp);
	/*print the matrix if needed*/
	if (argc>2)
	{
		if ((fp=fopen("data_input","r"))==NULL)
			{	
				printf("Fail to open the saved data to display!\n");
				return 3;
			}
		fscanf(fp, "%d\n\n", &n);
		printf("The number of cities is %d\nThe distances between them are\n", n);
		for (i=0; i<n; i++)
		{
			for (j=0; j<n; j++)
			{
				fscanf(fp, "%d\t", &temp);
				printf("%d\t", temp);
			}
			fscanf(fp,"\n");
			printf("\n");
		}
	fclose(fp);
	}
	return 0;
}
