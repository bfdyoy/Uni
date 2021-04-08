// MPI3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "mpi.h"
#include <iostream>

using namespace std;

#define STUDENTS 26


typedef struct {
	int id;
	char name;
} Student;

int main(int argc, char* argv[])
{
	int no_tasks, rank, source = 0, tag = 1;

	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &no_tasks);
	
	MPI_Datatype student_type;

	Student studenti[STUDENTS], s[STUDENTS];

	int lengths[2] = { 1, 1 };
	const MPI_Aint displacements[2] = { 0, sizeof(int) };
	MPI_Datatype types[2] = { MPI_INT, MPI_CHAR };
	MPI_Type_create_struct(2, lengths, displacements, types, &student_type);
	MPI_Type_commit(&student_type);	

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Status stat;
	
	char name_search = 'z';

	int cnt = 0;

	if (rank == 0)
	{
		for (char ch = 'a'; ch <= 'z'; ch++)
		{
			
			studenti[cnt].id = cnt;
			studenti[cnt].name = ch;
			cnt++;
		}

		for (int it = 1; it < no_tasks; it++)
			MPI_Send(studenti, STUDENTS, student_type, it, tag, MPI_COMM_WORLD);
	}
	else
	{
		MPI_Recv(s, STUDENTS, student_type, 0, tag, MPI_COMM_WORLD, &stat);

		for (int it = STUDENTS * (rank - 1) / (no_tasks - 1); it < STUDENTS * rank / (no_tasks - 1); it++)
		{
			if (s[it].name == name_search)
			{
				cout << "Studentul a fost gasit de catre rank-ul " << rank << " cu id-ul " << s[it].id << "!\n";
			}
		}
	}
	
	MPI_Type_free(&student_type);
	MPI_Finalize();
}