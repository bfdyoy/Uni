#include "mpi.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

#include <iostream>
#include <cstdlib>

using namespace std;

int* elements;
int array_size, max_element, element_to_find;
int no_processes;
int k;
int found = 0;

int* build_array(int array_size, int max_element)
{
	srand(time(0));
	int* elements = new int[array_size];

	for (int it = 0; it < array_size; it++)
	{
		elements[it] = rand() % max_element + 1;
	}

	return elements;
}

int main(int argc, char*argv[])
{
	int rc;

	if (argc != 4)
	{
		cout << "Invalid number of arguments" << endl;
		return 0;
	}

	array_size = atoi(argv[1]);
	max_element = atoi(argv[2]);
	element_to_find = atoi(argv[3]);

	elements = build_array(array_size, max_element);

	rc = MPI_Init(&argc, &argv);

	if (rc != MPI_SUCCESS) {
		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &no_processes);

	int process_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

	int current_status = 0;

	for (int it = array_size * process_rank / no_processes; it < array_size * (process_rank + 1) / no_processes; it++)
	{
		if (elements[it] == element_to_find)
		{
			current_status = 1;
		}
	}

	if (process_rank != 0)
	{
		MPI_Send(&current_status, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	int received_status = 0;

	if (process_rank == 0)
	{
		if (current_status == 1)
		{
			found = 1;
		}

		for (int it = 1; it < no_processes; it++)
		{
			MPI_Recv(&received_status, 1, MPI_INT, it, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (received_status == 1)
			{
				found = 1;
			}
		}
		if (found == 1)
		{
			cout << "The element has been found !";
		}
		else
		{
			cout << "Not found!";
		}
	}
	
	MPI_Finalize();
	return 0;
}
