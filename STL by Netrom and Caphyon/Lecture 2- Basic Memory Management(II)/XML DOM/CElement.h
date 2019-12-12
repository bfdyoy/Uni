#ifndef CODE_CELEMENT_H
#define CODE_CELEMENT_H

#include "CAttribute.h"

// clasa rootElement cu un vector de CElement
//clasa CElement cu un struct childElement
// CElement are element si atribut 
// childElement are atribut si text
// clasa CAtribut cu numeAtribut si tiAptribut
class CElement
{
public:
	CElement();
	CElement(int aIndex , string nameElement);
	CElement(int aIndex, string nameElement, string text);
	CElement(CElement* element);
	void addAttribute(string aNameAttribute, string anAttribute);
	~CElement();
	void print(ofstream& file);
	string getElemName();
	vector<string> getListAttributes();

	int index;
	bool hasChild;
	bool isAlive;
	int level;
private:
	vector<CAttribute> attributes;
	string nameElement;
	string text;
};

#endif // !CODE_CELEMENT_H