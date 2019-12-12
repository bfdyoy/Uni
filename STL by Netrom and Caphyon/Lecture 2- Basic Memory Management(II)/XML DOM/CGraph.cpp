#include "CGraph.h"

#define FALSE_INDEX -1000

CGraph::CGraph(int vertices)
{
	this->vertices = vertices;
	adj.resize(vertices);
}

CGraph::~CGraph()
{
	adj.clear();
}

void CGraph::addEdge(const shared_ptr<CElement>& src, const shared_ptr<CElement>& dest)
{
	this->adj[src->index].push_back(dest->index);
	src->hasChild = true;
	dest->level = src->level + 1;
}

void CGraph::serialiseUtil(int srcIndex, vector<bool>& visited, ofstream& file, const vector<shared_ptr<CElement>>& elements)
{
	if (elements[srcIndex]->isAlive)
	{
		visited[srcIndex] = true;
		file << string(elements[srcIndex]->level, '\t');
		elements[srcIndex]->print(file);

		if (elements[srcIndex]->hasChild == false)
		{
			file << "</" << elements[srcIndex]->getElemName() << ">";
		}
		file << "\n";

		for (auto it2 = adj[srcIndex].begin(); it2 != adj[srcIndex].end(); ++it2)
		{
			if ((!visited[*it2]) && (elements[*it2]->isAlive) )
			{
				serialiseUtil(*it2, visited, file, elements);
			}
		}

		if (elements[srcIndex]->hasChild == true)
		{
			file << string(elements[srcIndex]->level, '\t');
			file << "</" << elements[srcIndex]->getElemName() << ">\n";
		}
	}
}

vector<int> CGraph::getAdjList(int indexSrc)	
{
	vector<int>listAdj;
	for (auto it = adj[indexSrc].begin(); it != adj[indexSrc].end(); ++it)
	{
		listAdj.push_back(*it);
	}
	return listAdj;
}

void CGraph::serializeDom(ofstream& file, const vector<shared_ptr<CElement>>& elements)
{
	vector<bool> visited(vertices, false);

	for (int it = 0; it < vertices; ++it)
	{
		if ((!visited[it]) && (elements[it]->isAlive == true))
		{
			serialiseUtil(it, visited, file, elements);
		}
	}
}

void CGraph::removeElement(int indexElem, vector<shared_ptr<CElement>>& elements)
{
	vector<int> elementAdj = getAdjList(indexElem);
	elements[indexElem]->isAlive = false;
	for (auto it = elementAdj.begin(); it != elementAdj.end(); ++it)
	{
		elements[*it]->isAlive = false;
	}

	cout << "The element has been deleted!\n";

}

void CGraph::moveElement(int srcIndex, int destIndex, const vector<shared_ptr<CElement>>& elements)
{	
	for (int it = 0; it < adj.size(); ++it)
	{
		auto iter = find(adj[it].begin(), adj[it].end(), srcIndex);
		if (iter != adj[it].end())
		{
			this->adj[it].erase(iter);
			if (adj[it].size() == 0)
			{
				elements[it]->hasChild = false;
			}

		}
		/*
		for (auto it2 = 0; it2 < adj[it].size(); ++it2)
		{
			if (adj[it][it2] == srcIndex)
			{
				this->adj[it].erase(adj[it].begin() + it2);
				break;
			}
		}
		*/
	}
	
	elements[srcIndex]->level--;
	this->addEdge(elements[srcIndex], elements[destIndex]);

	cout << "\nThe element was moved!\n";
}
