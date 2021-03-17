#include <mpi.h>
#include <stdio.h>

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

bool isPrime(int number)
{
	if ((number & 1) == 0)
		return 0;
	for (int it = 3; it < sqrt(number); it += 2)
		if (number % it == 0)
			return 0;
	return 1;
}

int n;
int no_processes; 

int* current_primes;
int k;

int* received_primes;

vector <int> prime_numbers;

int main(int argc, char* argv[]) {

	int it;
	
	if (argc != 2)
	{
		cout << "Invalid number of arguments" << endl;
		return 0;
	}
	
	// n - limita superioara
	n = atoi(argv[1]);
	
	current_primes = new int[n / 2];

	
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &no_processes);
	
	int process_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);


	for (it = n * process_rank / no_processes; it < n * (process_rank + 1) / no_processes; it++)
		if (isPrime(it))
			current_primes[k++] = it;
	
	if (process_rank != 0)
	{
		MPI_Send(&k, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(current_primes, k, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	int received_size;

	if (process_rank == 0)
	{
		for (it = 0; it < k; it++)
			prime_numbers.push_back(current_primes[it]);
		
		delete[] current_primes;
		
		for (it = 1; it < no_processes; it++)
		{
			MPI_Recv(&received_size, 1, MPI_INT, it, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			received_primes = new int[received_size];
			MPI_Recv(received_primes, received_size, MPI_INT, it, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for (int it2 = 0; it2 < received_size; it2++)
				prime_numbers.push_back(received_primes[it2]);
			delete[] received_primes;
		}

		
		for (it= 0; it < prime_numbers.size(); it++)
			printf("%d ", prime_numbers[it]);
	}



	MPI_Finalize();
	return 0;
}