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

char vigenere_decrypt(char txt, char k)
{
	char x;
	if (!isalpha(txt))
		return txt;
	x = (txt - k + 26) % 26;
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

	string decrypted;
	char decrypted_character, key_character, character_to_decrypt;


	MPI_Bcast(&textlen, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&keylen, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		for (int i = 1; i <= keylen; i++)
		{
			MPI_Send(&key[i - 1], 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}

		for (int i = 0; i < textlen; i++)
		{
			MPI_Send(&text[i], 1, MPI_CHAR, (i % keylen) + 1, 0, MPI_COMM_WORLD);
			MPI_Recv(&decrypted_character, 1, MPI_CHAR, (i % keylen) + 1, 0, MPI_COMM_WORLD, &status);
			decrypted.push_back(decrypted_character);
		}
	}
	else
	{
		MPI_Recv(&key_character, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

		if (rank <= textlen % keylen)
		{
			for (int i = 0; i < textlen / keylen + 1; i++)
			{
				MPI_Recv(&character_to_decrypt, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
				decrypted_character = vigenere_decrypt(character_to_decrypt, key_character);
				MPI_Send(&decrypted_character, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			}
		}
		else
		{
			for (int i = 0; i < textlen / keylen; i++)
			{
				MPI_Recv(&character_to_decrypt, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
				decrypted_character = vigenere_decrypt(character_to_decrypt, key_character);
				MPI_Send(&decrypted_character, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			}
		}
	}

	if (rank == 0)
	{
		cout << "\nThe decrypted string is: " << decrypted;
		cout << endl;
	}

	MPI_Finalize();

	return 0;
}

