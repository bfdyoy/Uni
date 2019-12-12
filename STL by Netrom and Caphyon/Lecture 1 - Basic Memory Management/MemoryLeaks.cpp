/* 
  Scopul acestui proiect este identificarea si eliminarea memory leak-urilor din fiecare cele 3 functii de mai jos.

  Realizati modificarile necesare in asa fel incat memoria utilizata sa fie si eliberata in final.

  Nota: Modificarile nu trebuie sa afecteze corectitudinea programului (datele afisate raman aceleasi).
*/

#include <iostream>
#include <string>
#include <memory>

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

void useAlphabet_SP()
{
	std::string constUpperAlphabet = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
	std::string constLowerAlphabet = "the quick brown fox jumps over the lazy dog";

	std::unique_ptr<char[]> upperAlphabet = std::make_unique<char[]>(100);
	//char* upperAlphabet = new char[100];

	// changed i++ to ++i 
	for (size_t i = 0; i < constUpperAlphabet.size(); ++i)
	{
		// as long as we don t use the array afterwards, we can use
		// move semantics
		upperAlphabet[i] = std::move(constUpperAlphabet[i]);
		std::cout << upperAlphabet[i];
	}
	std::cout << "\n";

	std::unique_ptr<char[]> lowerAlphabet = std::make_unique<char[]>(100);

	//char* lowerAlphabet = new char[100];
	for (size_t i = 0; i < constLowerAlphabet.size(); ++i)
	{
		lowerAlphabet[i] = std::move(constLowerAlphabet[i]);
		std::cout << lowerAlphabet[i];
	}
	std::cout << "\n";
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
	
	delete ptr1;
	ptr1 = nullptr;
	delete ptr2;
	ptr2 = nullptr;

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
	delete[]array;
	array = nullptr;
}

void useDynamicArray_SP()
{
	//int* ptr1 = new int(10);
	//int* ptr2 = new int(20);

	std::unique_ptr<int> smartPtr1 = std::make_unique<int>(10);
	std::unique_ptr<int> smartPtr2 = std::make_unique<int>(20);

	int* ptr1 = smartPtr1.get();
	int* ptr2 = smartPtr2.get();

	int arraySize = 10;

	std::unique_ptr<int[]> array = std::make_unique<int[]>(arraySize);
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
		std::cout << *current << " ";
		++current;
	}
	std::cout << "\n";
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
	imageArray = nullptr;
	delete[]pcaImageArray;
	pcaImageArray = nullptr;
}

void useImage_SP()
{
	int size = 15;
	std::unique_ptr<char[]> imageArray = std::make_unique<char[]>(size * size);
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

	std::unique_ptr<char[]>pcaImageArray = std::make_unique<char[]>(size);
	//char* pcaImageArray = new char[size];
	pcaImageArray[0] = 'P';
	pcaImageArray[1] = 'C';
	pcaImageArray[2] = 'A';
	pcaImageArray[3] = ' ';
	pcaImageArray[4] = 'f';
	pcaImageArray[5] = 'o';
	pcaImageArray[6] = 'r';
	pcaImageArray[7] = ' ';
	pcaImageArray[8] = 't';
	pcaImageArray[9] = 'h';
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
}

int main()
{
	useAlphabet();

	useAlphabet_SP();

	std::cout << "\n\n";

	useDynamicArray();

	useDynamicArray_SP();

	std::cout << "\n\n";

	useImage();

	useImage_SP();

	return 0;
}
