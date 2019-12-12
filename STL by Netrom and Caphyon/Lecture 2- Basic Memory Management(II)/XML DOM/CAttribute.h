#ifndef CODE_CATTRIBUTE_H
#define CODE_CATTRIBUTE_H

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

using namespace std;

class CAttribute
{
public:
	CAttribute();
	CAttribute(string aNameAttribute, string anAttribute);
	CAttribute(const CAttribute& anAttribute);
	~CAttribute();
	inline bool isEmpty();
	void print(ofstream& file);
	string getAttribute();
private:
	string nameAttribute;
	string attribute;
};

#endif // !CODE_CATTRIBUTE_H