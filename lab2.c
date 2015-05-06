/*
* ECE 420 Lab #2
* By: Divyank Katira
* ID: 1342635
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "timer.h"

#define MAXSIZE 10000000
int A[MAXSIZE];
int n;
int num_thrd;
pthread_barrier_t barr; // Barrier variable


int Loaddata (int* A, int n)
{
	/*
	Load the matrix stored in the file "data_input".
	
	A is the pointer to the destination matrix. n is the size of the matrix to be stored in the array A[].
	The function will first compare the n to the size stored in the file "data_input" and will exit if they don't match. Then the matrix in the file "data_input" is loaded into the array A[].
	The element in the i th row and j th column will be mapped to A[n*i+j].
	*/

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

int Savedata(int* A, int n)
{
	/*
	Save the matrix stored in array A[] into the file "data_output".
	
	A is the pointer to the array storing the matrix. n is the size of the matrix.
	The function will first write n into the file "data_output". Then it will write the elements in A[].
	A[I] will be mapped as the element in the floor(I/n) th row and the I%n th column of a matrix, i.e. A[n*i+j] will be mapped as the elment in the i th row and j th column of a matrix.
	*/
	FILE* op;
        int i,j,temp;
        if ((op=fopen("data_output","w"))==NULL)
        {
                printf("Error opening the file.\n");
                return 1;
        }
        fprintf(op,"%d\n\n",n);
        for (i=0;i<n;i++)
	{
                for (j=0;j<n;j++)
                        fprintf(op,"%d\t",A[n*i+j]);
		fprintf(op,"\n");
	}
        fclose(op);
        
	return 0;
}

int PrintMat(int* A, int n)
{
	/*
	Print the matrix stored in array A[] on the screen.
	*/
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
			printf("%d\t", A[i*n+j]);
		printf("\n");
	}
	return 0;
}
void* findPath(void* arg) 
{
	int i,j,k,temp;
	int rank = (int)arg;
	
	// Determine the rows we will be calculating
	int start = rank * n / num_thrd;
	int end   = (rank + 1) * n / num_thrd;
	
	for(k = 0; k < n; k++) 
	{
		// Synchronization point
 		int rc = pthread_barrier_wait(&barr);
 		if(rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
 		{
 			printf("Could not wait on barrier\n");
 			exit(-1);
 		}
		for(i = start; i < end ; i++)
		{
			for(j = 0; j < n; j++)
			{
				if ((temp=A[i*n+k]+A[k*n+j])<A[i*n+j])
					A[i*n+j]=temp;
			}
		}
	}
	return 0;
}


int main (int argc, char* argv[])
{
	double start,end;
	pthread_t* thread;
	int i,j;
	FILE * fp;

	if (argc < 3)
	{	
		printf("Usage ./lab2 num_cities num_thrds\n");
		return 1;
	}
	n=strtol(argv[1], NULL, 10);
	num_thrd = strtol(argv[2], NULL, 10);
	Loaddata(A, n);
	thread = (pthread_t*) malloc(num_thrd*sizeof(pthread_t));
	// Barrier initialization
 	if(pthread_barrier_init(&barr, NULL, num_thrd))
 	{
 		printf("Could not create a barrier\n");
 		return -1;
 	}
	GET_TIME(start);
 	for(i = 0; i < num_thrd; ++i)
 	{
 		if(pthread_create(&thread[i], NULL, &findPath, (void*)i))
 		{
 			printf("Could not create thread %d\n", i);
 			free(thread);
 			return -1;
 		}
 	}
	for (i = 0; i < num_thrd  ; i++)
 		pthread_join (thread[i], NULL);
	GET_TIME(end);
 	Savedata(A, n);
	printf("Computation time: %F\n",(end - start));	
	return 0;	
}	
