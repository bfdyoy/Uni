#include "CElement.h"

CElement::CElement(int aIndex, string aNameElement) : index(aIndex), nameElement(aNameElement)
{
	this->hasChild = false;
	this->level = -1;
	this->isAlive = true;
}

CElement::CElement(int aIndex, string aNameElement, string aText) :
	index(aIndex) , nameElement(aNameElement), text(aText)
{
	this->hasChild = false;
	this->level = -1;
	this->isAlive = true;
}

CElement::CElement()
{
	nameElement = "";
	text = "";
	this->hasChild = false;
	this->level = -1;
	this->isAlive = true;
}

CElement::CElement(CElement* element)
{
	this->nameElement = element->nameElement;
	this->text = element->text;
	this->index = element->index;
	this->hasChild = element->hasChild;
	this->level = element->level;
	this->isAlive = true;
}

CElement::~CElement()
{
	attributes.clear();
}

void CElement::print(ofstream& file)
{
	file << "<" << this->nameElement;

	for (int it = 0; it != attributes.size(); ++it)
	{
		attributes[it].print(file);
	}

	file << ">";
	if (!this->text.empty())
	{
		file << this->text;
	}
}

string CElement::getElemName()
{
	return this->nameElement;
}

void CElement::addAttribute(string aNameAttribute, string anAttribute)
{
	this->attributes.emplace_back(aNameAttribute, anAttribute);
}

vector<string> CElement::getListAttributes()
{
	vector<string> attrVect;
	for (auto it = attributes.begin(); it != attributes.end(); ++it)
	{
		attrVect.push_back(it->getAttribute());
	}
	return attrVect;
}