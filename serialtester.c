/*
Serial version implementation and varification program.

	In this program, the sizes of the matrix in the file "data_input" and "data_output" are checked at fisrt and will exit if those sizes are not match. Then the serial version of the Floyd-Warshell Algorithm is implemented on the data in the file "data_input". It will also compare the result with the result in the file "data_output". 
*/

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
int Loaddata(int* A, int n);

int main (int argc, char* argv[])
{
        int i,j,k,n,temp;
        int *dp;
	FILE* fp;
	double start, end;
/*Get the size and test by the size*/
	if ((fp=fopen("data_input","r"))==NULL)
	{	
		printf("Fail to open the input data!\n");
		return 1;
	}
	fscanf(fp, "%d\n\n", &n);
	fclose(fp);
	if ((fp=fopen("data_output","r"))==NULL)
	{	
		printf("Fail to open the result data!\n");
		return 1;
	}
	fscanf(fp, "%d\n\n", &temp);
	/*fclose(fp);*/
	if (temp!=n)
	{	
		fclose(fp);
		printf("Input data size does not match the result size!\n");
		return 2;
	}

/*Load the input data and calculate the result*/
	dp=malloc(n*n*sizeof(int));
	Loaddata(dp, n);
	GET_TIME(start);
	for (k=0; k<n; k++)
		for (i=0; i<n; i++)
			for (j=0; j<n; j++)
				if ((temp=dp[i*n+k]+dp[k*n+j])<dp[i*n+j])
					dp[i*n+j]=temp;
/*Compare the result with the reference*/
	GET_TIME(end);
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			fscanf(fp, "%d\t", &temp);
			if (temp!=dp[i*n+j])
			{
				fclose(fp);
				printf("The result is wrong.\n");
				return -1;
			}
		}
		fscanf(fp, "\n");
	}
	fclose(fp);
	printf("Congratulations! The result is correct! Serial Computation time:%F\n",(end-start));
	return 0;
}


int Loaddata (int* A, int n)
{
        FILE* ip;
        int i,j,temp;
        if ((ip=fopen("data_input","r"))==NULL)
        {
                printf("Error opening the input data.\n");
                return 1;
        }
        fscanf(ip,"%d\n\n",&temp);
        if (temp!=n)
        {
                printf("City count does not match the data!\n");
                return 2;
        }

        for (i=0;i<n;i++)
                for (j=0;j<n;j++)
                        fscanf(ip,"%d\t",A+n*i+j);
        fclose(ip);
        return 0;
}
