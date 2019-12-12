#include "CAttribute.h"

CAttribute::CAttribute(string aNameAttribute, string anAttribute) :
	nameAttribute(aNameAttribute), attribute(anAttribute)
{

}

CAttribute::CAttribute()
{
	nameAttribute = "";
	attribute = "";
}

CAttribute::CAttribute(const CAttribute& anAttribute)
{
	this->attribute = anAttribute.attribute;
	this->nameAttribute = anAttribute.nameAttribute;
}

CAttribute::~CAttribute()
{
	
}

void CAttribute::print(ofstream& file)
{
	file << " " << this->nameAttribute << "=\"" << this->attribute << "\"";
}

bool CAttribute::isEmpty()
{
	return this->attribute.empty();
}

string CAttribute::getAttribute()
{
	return this->attribute;
}
