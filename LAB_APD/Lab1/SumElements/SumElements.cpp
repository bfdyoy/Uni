#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <iostream>
#include <iomanip>
#include <cstdlib> 
#include "mpi.h"
#include <algorithm>

using namespace std;

int generate_and_sum(int numbers_to_generate)
{
	int sum = 0;
	int number;
	
	for (int it = 0; it < numbers_to_generate; it++)
	{
		number = rand() % 1000 + 1;
		sum += number;
	}
	return sum;
}

int no_processes;

int main(int argc, char* argv[])
{
	
    int rc;
    if (argc != 1)
    {
        cout << "Invalid number of arguments" << endl;
        return 0;
    }
	rc = MPI_Init(&argc, &argv);

	if (rc != MPI_SUCCESS) {
		printf("Error starting MPI program. Terminating.\n");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &no_processes);

	int process_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
	int current_sum;

	clock_t start, end;

	srand(time(NULL) + process_rank);
	start = clock();
	int numbers = 100 + (rand() % 1000 - 100 + 1);
	current_sum = generate_and_sum(numbers);
	end = clock();
	
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken = " << fixed << time_taken << setprecision(5) << endl;
		
	if (process_rank != 0)
	{
		MPI_Send(&time_taken, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&current_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	int received_sum;
	double received_time;
	if (process_rank == 0)
	{
		cout << "Current process : " << process_rank << endl;
		cout << "Sum = " << current_sum << endl;
		cout << "Time taken = " << fixed << time_taken << setprecision(5) << endl;
		cout << "------------------------------------";
		for (int it = 1; it < no_processes; it++)
		{
			MPI_Recv(&received_time, 1, MPI_DOUBLE, it, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&received_sum, 1,  MPI_INT, it, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			cout << "Current process : " << it << endl;
			cout << "Sum = " << received_sum << endl;
			cout << "Time taken = " << fixed << received_time << setprecision(5) << endl;
			cout << "------------------------------------";
		}
	}
	MPI_Finalize();
	return 0;
}

