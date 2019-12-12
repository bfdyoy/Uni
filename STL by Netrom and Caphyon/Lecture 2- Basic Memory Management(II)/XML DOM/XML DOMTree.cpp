#include "CAttribute.h"
#include "CElement.h"
#include "CGraph.h"
#include "Helper.h"

int main()

{

	int option, it, position, numberAttributes;
	char option2;
	string nameElement;

	while (true)
	{
		vector<shared_ptr<CElement>> elements;
		int vertices;
		bool work = true;

		cout << "Type in the number of elements :\n";
		cin >> vertices;
		unique_ptr<CGraph> myGraph(new CGraph(vertices));

		cout << "Creating the root element ...\n";
		cout << "Type in the name of the element :\n";
		cin >> nameElement;

		elements.emplace_back(make_shared<CElement>(new CElement((int)elements.size(), nameElement)));
		elements[0]->level = 0;
		do
		{
			position = 0;
			string textElement, nameAttribute, attribute;
			cout << "\n1. Create a new element.\n";
			cout << "2. Delete an element.\n";
			cout << "3. Move an element.\n";
			cout << "4. Load the tree into an text/xml file.\n";
			cout << "5. Create a new XML DOM tree.\n";
			cout << "6. Exit.\n";
			cin >> option;
			switch (option)
			{
			case 1:
			{
				attribute.clear();
				nameElement.clear();
				cout << "Type in the name of the element: \n";
				cin >> nameElement;

				cout << "Does it have a text ?(y/n)\n";
				cin >> option2;

				if (option2 == 'y')
				{
					cout << "Type in the text : \n";
					cin >> textElement;
				}

				elements.emplace_back(make_shared<CElement>(new CElement((int)elements.size(), nameElement, textElement)));

				cout << "Type in the name of parent's element : \n";
				cin >> nameElement;
				cout << "Do you have elements with same name ?(y/n)";
				cin >> option2;
				if (option2 == 'y')
				{
					cout << "Type in an unique attribute:\n";
					cin >> attribute;
					position = getIndexByAttribute(elements, nameElement, attribute);
				}
				else
				{
					position = getIndexByName(elements, nameElement);
				}
		
				if (position == -1)
				{
					cout << "The element with the name " << nameElement << " doesn't exist!";
					break;
				}
				else if (position == -2)
				{
					cout << "The elemet with name " << nameElement << " and attribute " << attribute
						<< " does not exist!\n";
					break;
				}

				myGraph->addEdge(elements[position], elements[elements.size() - 1]);

				cout << "Do you want to add attributes to this element ?(y/n)\n";
				cin >> option2;
				if (option2 == 'y')
				{
					cout << "How many ?\n";
					cin >> numberAttributes;
					for (it = 0; it < numberAttributes; ++it)
					{
						cout << "Type in the name of the attribute :\n";
						cin >> nameAttribute;
						cout << "Type in the attribute :\n";
						cin >> attribute;
						elements[elements.size() - 1]->addAttribute(nameAttribute, attribute);
					}
				}
				attribute.clear();
				break;
			}
			case 2:
			{
				attribute.clear();
				nameElement.clear();
				position = 0;
				cout << "Type in the name of the element which will be deleted:\n";
				cin >> nameElement;
				cout << "Do you have elements with same name ?(y/n)\n";
				cin >> option2;
				if (option2 == 'y')
				{
					cout << "Type in an unique attribute:\n";
					cin >> attribute;
					position = getIndexByAttribute(elements, nameElement, attribute);
				}
				else
				{
					position = getIndexByName(elements, nameElement);
				}

				if (position == -1)
				{
					cout << "The element with the name " << nameElement << " doesn't exist!\n";
					break;
				}
				else if (position == -2)
				{
					cout << "The elemet with name " << nameElement << " and attribute " << attribute
						<< " does not exist!\n";
					break;
				}
				myGraph->removeElement(position, elements);
				attribute.clear();
				break;
			}
			case 3:
			{
				attribute.clear();
				nameElement.clear();
				position = 0;
				string nameElement2;
				string attribute2;
				int position2;

				cout << "Type in the name of the element which will be moved:\n";
				cin >> nameElement;
				cout << "Do you have elements with same name ?(y/n)\n";
				cin >> option2;
				
				if (option2 == 'y')
				{
					cout << "Type in an unique attribute:\n";
					cin >> attribute;
					position = getIndexByAttribute(elements, nameElement, attribute);
				}
				else
				{
					position = getIndexByName(elements, nameElement);
				}

				if (position == -1)
				{
					cout << "The element with the name " << nameElement << " doesn't exist!\n";
					break;
				}
				else if (position == -2)
				{
					cout << "The elemet with name " << nameElement << " and attribute " << attribute
						<< " does not exist!\n";
					break;
				}
				
				cout << "Type in the name of the element which will be his father:\n";
				cin >> nameElement2;
				cout << "Do you have elements with same name ?(y/n)\n";
				cin >> option2;
				if (option2 == 'y')
				{
					cout << "Type in an unique attribute:\n";
					cin >> attribute;
					position2 = getIndexByAttribute(elements, nameElement, attribute);
				}
				else
				{
					position2 = getIndexByName(elements, nameElement);
				}

				if (position2 == -1)
				{
					cout << "The element with the name " << nameElement << " doesn't exist!\n";
					break;
				}
				else if (position2 == -2)
				{
					cout << "The elemet with name " << nameElement << " and attribute " << attribute
						<< " does not exist!\n";
					break;
				}
				myGraph->moveElement(position, position2, elements);
				break;
			}
			case 4:
			{
				string fileName;
				cout << "Type in the name of the file:(name.extension)\n";
				cin >> fileName;

				ofstream outputFile;
				outputFile.open(fileName);

				myGraph->serializeDom(outputFile, elements);
				break;
			}
			case 5:
			{
				cout << "Do you want to save the current tree into a file ?(y/n)\n";
				cin >> option2;
				if (option2 == 'y')
				{
					string fileName;
					cout << "Type in the name of the file:(name.extension)\n";
					cin >> fileName;

					ofstream outputFile;
					outputFile.open(fileName);

					myGraph->serializeDom(outputFile, elements);
				}
				work = false;
				break;
			}
			case 6:
			{
				return 0;
				break;
			}
			default:
				cout << "Key : " << option << " is not an option!\n";
				break;
			}
		} while (work);
	}
	return 0;
}