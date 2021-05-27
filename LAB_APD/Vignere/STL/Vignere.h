#include <iostream>
#include <execution>
#include <string>

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

char vigenere_decrypt(char txt, char k)
{
	char x;
	if (!isalpha(txt))
		return txt;
	x = (txt - k + 26) % 26;
	x += 'A';

	return x;
}
