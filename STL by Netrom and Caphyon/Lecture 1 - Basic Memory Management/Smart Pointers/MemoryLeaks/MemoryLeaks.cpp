/* 
  Scopul acestui proiect este identificarea si eliminarea memory leak-urilor din fiecare cele 3 functii de mai jos.

  Realizati modificarile necesare in asa fel incat memoria utilizata sa fie si eliberata in final.

  Nota: Modificarile nu trebuie sa afecteze corectitudinea programului (datele afisate raman aceleasi).
*/

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Printarea caracterelor din cele doua array-uri (ce contin majuscule, respectiv minuscule)
void useAlphabet()
{
	string constUpperAlphabet = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
	string constLowerAlphabet = "the quick brown fox jumps over the lazy dog";

	unique_ptr<char[]> upperAlphabet = make_unique<char[]>(100);
	//char* upperAlphabet = new char[100];
	
	// changed i++ to ++i 
	for (size_t i = 0; i < constUpperAlphabet.size(); ++i)
	{
		// as long as we don t use the array afterwards, we can use
		// move semantics
		upperAlphabet[i] = move(constUpperAlphabet[i]);
		cout << upperAlphabet[i];
	}
	cout << "\n";

	unique_ptr<char[]> lowerAlphabet = make_unique<char[]>(100);

	//char* lowerAlphabet = new char[100];
	for (size_t i = 0; i < constLowerAlphabet.size(); ++i)
	{
		lowerAlphabet[i] = move(constLowerAlphabet[i]);
		cout << lowerAlphabet[i];
	}
	cout << "\n";
}

// Initializarea si afisarea unui array alocat dinamic
void useDynamicArray()
{
	//int* ptr1 = new int(10);
	//int* ptr2 = new int(20);

	unique_ptr<int> smartPtr1 = make_unique<int>(10);
	unique_ptr<int> smartPtr2 = make_unique<int>(20);

	int* ptr1 = smartPtr1.get();
	int* ptr2 = smartPtr2.get();

	int arraySize = 10;

	unique_ptr<int[]> array = make_unique<int[]>(arraySize);
	//int* array = new int[arraySize];

	for (size_t i = 0; i < arraySize; ++i)
	{
		array[i] = (i % 2 == 0 ? *ptr1 : *ptr2);
	}

	ptr1 = array.get();
	ptr2 = (array.get() + arraySize);

	int* current = array.get();
	while (current != ptr2)
	{
		cout << *current << " ";
		++current;
	}
	cout << "\n";
	
}

// Generarea si afisarea unei "imagini" stocate intr-un array (matrice linearizata)
void useImage()
{
	int size = 15;
	unique_ptr<char[]> imageArray = make_unique<char[]>(size * size);
	//char* imageArray = new char[size * size];

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

	unique_ptr<char[]>pcaImageArray = make_unique<char[]>(size);
	//char* pcaImageArray = new char[size];
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
			cout << imageArray[i * size + j];
		}
		cout << "\n";
	}
	cout << "\n";
}

int main()
{
	useAlphabet();

	useDynamicArray();

	useImage();

	return 0;
}
