#include "Helper.h"

int getIndexByName(const vector<shared_ptr<CElement>>& elements, string searchedString)
{
	int position;
	for (position = 0; position != elements.size(); ++position)
	{
		if (elements[position]->getElemName() == searchedString)
		{
			return position;
		}
	}
	return -1;
}

int getIndexByAttribute(const vector<shared_ptr<CElement>>& elements, string nameElem, string attribute)
{
	int position;

	for (position = 0; position != elements.size(); ++position)
	{
		if (elements[position]->getElemName() == nameElem)
		{
			vector<string> attributes = elements[position]->getListAttributes();
			for (auto it = attributes.begin(); it != attributes.end(); ++it)
			{
				if (*it == attribute)
				{
					return position;
				}
			}
		}
	}
	return -2;
}