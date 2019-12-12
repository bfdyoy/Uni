#ifndef CODE_HELPER_H
#define CODE_HELPER_H

#include "CElement.h"

int getIndexByName(const vector<shared_ptr<CElement>>& elements, string searchString);
int getIndexByAttribute(const vector<shared_ptr<CElement>>& elements, string nameElem, string attribute);

#endif // !CODE_HELPER_H