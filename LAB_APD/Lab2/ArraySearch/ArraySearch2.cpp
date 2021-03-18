#include "mpi.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <iostream>
#include <algorithm>
#include<vector>
using namespace std;


int* build_array(int array_size, int max_value)
{

	int* elements = new int[array_size];

	for (int it = 0; it < array_size; it++)
	{
		elements[it] = rand() % max_value + 1;
	}

	return elements;
}

int* elements;
int array_size, max_value, element_to_find;
int no_processes;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid number of arguments !" << endl;
		return 0;
	}

	array_size = atoi(argv[1]);
	max_value = atoi(argv[2]);

	int rc;
	rc = MPI_Init(&argc, &argv);

	if (rc != MPI_SUCCESS) {
		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &no_processes);

	int process_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

	srand(time(NULL) + process_rank);
	elements = build_array(array_size, max_value);

	int index = rand() % array_size + 1;
	element_to_find = elements[index];
	int size_to_share = array_size / no_processes;
	int* elements_received = new int[size_to_share];


	//a) Using Broadcast to send array and read maximum index

	
	if (process_rank == 0)
	{
		MPI_Bcast(elements, array_size, MPI_INT, 0, MPI_COMM_WORLD);
	}
	int current_index = 0;

	for (int it = array_size * process_rank / no_processes; it < array_size * (process_rank + 1) / no_processes; it++)
	{
		if (elements[it] == element_to_find)
		{
			current_index = it;
		}
	}

	int max_index = -1;

	MPI_Reduce(&current_index, &max_index, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (process_rank == 0)
	{
		cout << max_index;
	}
	

	//b) Using scatter to send the array, print all its positions. Use Gather
	/*
	MPI_Scatter(elements, array_size / no_processes, MPI_INT, elements_received, size_to_share, MPI_INT, 0, MPI_COMM_WORLD);

	int* current_indexes = new int[size_to_share];
	for (int it = 0; it < size_to_share; it++)
	{
		current_indexes[it] = -1;
	}
	int index_it = 0;

	for (int it = 0; it < size_to_share; it++)
	{
		if (elements_received[it] == element_to_find)
			current_indexes[index_it++] = it;
	}
	int* all_indexes = new int[array_size];
	int* received_indexes = new int[index_it - 1];
	vector<int> indexes;
	MPI_Gather(current_indexes, size_to_share, MPI_INT, all_indexes, array_size, MPI_INT, 0, MPI_COMM_WORLD);

	if (process_rank == 0)
	{
		for (int it2 = 0; it2 < size_to_share; it2++)
		{
			indexes.push_back(current_indexes[it2]);
		}
		for (int it = no_processes; --it >= 0;)
		{
			for (int it2 = 0; it2 < array_size; it2++)
			{

				indexes.push_back(all_indexes[it2]);
			}
		}
	}

	for (auto a : indexes)
	{
		cout << a << endl;
	}
	*/
	MPI_Finalize();
	return 0;
}

