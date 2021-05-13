#include "mpi.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

string generateKey(string str, string key)
{
	int x = str.size();

	for (int i = 0; ; i++)
	{
		if (x == i)
			i = 0;
		if (key.size() == str.size())
			break;
		key.push_back(key[i]);
	}
	return key;
}

char vigenere_encrypt(char msg, char k)
{
	char x;
	if (!isalpha(msg))
	{
		return msg;
	}
	x = (msg + k) % 26;
	x += 'A';
	return x;
}


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Status status;
	int keylen, textlen;
	string text, s_key;
	char key[50];

	if (rank == 0)
	{
		cin >> text >> s_key;
		
		string ss_key = generateKey(text, s_key);
		keylen = s_key.length();
		textlen = text.length();
		strcpy_s(key, ss_key.c_str());
	}
	
	string encrypted;
	char encrypted_character, key_character, character_to_encrypt;

	MPI_Bcast(&textlen, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&keylen, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		cout << "Insranke root process\n";
		for (int i = 1; (i <= textlen) && (i < size); i++)
		{
			cout << "Sending " << key[i] << " to " << (i % (size-1)) +1 << endl;
			MPI_Send(&key[i - 1], 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}

		for (int i = 0; i < textlen; i++)
		{
			cout << "Sending " << text[i] << " to " << (i % (size - 1)) + 1 << endl;
			MPI_Send(&text[i], 1, MPI_CHAR, (i % (size - 1)) + 1, 0, MPI_COMM_WORLD);
			MPI_Recv(&encrypted_character, 1, MPI_CHAR, (i % (size - 1)) + 1, 0, MPI_COMM_WORLD, &status);
			cout << "Received encrypted: " << encrypted_character << " in root\n";
			encrypted.push_back(encrypted_character);
		}
	}
	else
	{
		MPI_Recv(&key_character, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		cout << "Process-" << rank << " received " << key_character << endl;
		if (rank <= textlen % keylen)
		{
			for (int i = 0; i < textlen / keylen + 1; i++)
			{
				cout << "Process-" << rank << " is trying to receive " << endl;
				MPI_Recv(&character_to_encrypt, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
				encrypted_character = vigenere_encrypt(character_to_encrypt, key_character);
				MPI_Send(&encrypted_character, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			}
		}
		else
		{
			for (int i = 0; i < textlen / keylen; i++)
			{
				cout << "Process-" << rank << " is trying to receive " << endl;
				MPI_Recv(&character_to_encrypt, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
				encrypted_character = vigenere_encrypt(character_to_encrypt, key_character);
				MPI_Send(&encrypted_character, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			}
		}
	}
	if (rank == 0)
	{
		cout << "\nThe encrypted string is: " << encrypted;
		cout << endl;
	}

	MPI_Finalize();
	return 0;
}