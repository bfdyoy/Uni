/* 
  Scopul acestui proiect este identificarea si eliminarea memory leak-urilor din fiecare cele 3 functii de mai jos.

  Realizati modificarile necesare in asa fel incat memoria utilizata sa fie si eliberata in final.

  Nota: Modificarile nu trebuie sa afecteze corectitudinea programului (datele afisate raman aceleasi).
*/

#include <iostream>
#include <string>

// Printarea caracterelor din cele doua array-uri (ce contin majuscule, respectiv minuscule)
void useAlphabet()
{
	std::string constUpperAlphabet = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
	std::string constLowerAlphabet = "the quick brown fox jumps over the lazy dog";

	char* upperAlphabet = new char[100];
	for (size_t i = 0; i < constUpperAlphabet.size(); i++)
	{
		upperAlphabet[i] = constUpperAlphabet[i];
		std::cout << upperAlphabet[i];
	}
	std::cout << "\n";

	delete[]upperAlphabet;
	upperAlphabet = nullptr;

	char* lowerAlphabet = new char[100];
	for (size_t i = 0; i < constLowerAlphabet.size(); i++)
	{
		lowerAlphabet[i] = constLowerAlphabet[i];
		std::cout << lowerAlphabet[i];
	}
	std::cout << "\n";

	delete[]lowerAlphabet;
	lowerAlphabet = nullptr;
}

// Initializarea si afisarea unui array alocat dinamic
void useDynamicArray()
{
	int* ptr1 = new int(10);
	int* ptr2 = new int(20);

	int arraySize = 10;
	int* array = new int[arraySize];

	for (int i = 0; i < arraySize; i++)
	{
		array[i] = (i % 2 == 0 ? *ptr1 : *ptr2);
	}

	ptr1 = array;
	ptr2 = array + arraySize;

	int* current = ptr1;
	while (current != ptr2)
	{
		std::cout << *current << " ";
		++current;
	}
	std::cout << "\n";
	current = nullptr;
	delete current;
	ptr1 = nullptr;
	delete ptr1;
	ptr2 = nullptr;
	delete ptr2;
	delete[]array;
	array = nullptr;
}

// Generarea si afisarea unei "imagini" stocate intr-un array (matrice linearizata)
void useImage()
{
	int size = 15;
	char* imageArray = new char[size * size];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j || i == size - j - 1)
			{
				imageArray[i * size + j] = '*';
			}
			else if (i < j)
			{
				imageArray[i * size + j] = '|';
			}
			else
			{
				imageArray[i * size + j] = '-';
			}
		}
	}

	char* pcaImageArray = new char[size];
	pcaImageArray[0]  = 'P';
	pcaImageArray[1]  = 'C';
	pcaImageArray[2]  = 'A';
	pcaImageArray[3]  = ' ';
	pcaImageArray[4]  = 'f';
	pcaImageArray[5]  = 'o';
	pcaImageArray[6]  = 'r';
	pcaImageArray[7]  = ' ';
	pcaImageArray[8]  = 't';
	pcaImageArray[9]  = 'h';
	pcaImageArray[10] = 'e';
	pcaImageArray[11] = ' ';
	pcaImageArray[12] = 'w';
	pcaImageArray[13] = 'i';
	pcaImageArray[14] = 'n';

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i % 3 == 0)
			{
				imageArray[i * size + j] = pcaImageArray[j];
			}
			std::cout << imageArray[i * size + j];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
	delete[]imageArray;
	delete[]pcaImageArray;
}

int main()
{
	useAlphabet();

	useDynamicArray();

	useImage();

	return 0;
}
