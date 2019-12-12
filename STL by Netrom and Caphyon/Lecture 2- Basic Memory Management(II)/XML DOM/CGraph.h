#ifndef CODE_GRAPH_H
#define CODE_GRAPH_H

#include "CElement.h"
#include <algorithm>
#include <utility>
#include <stack>
#include <map>

class CGraph
{
public:
	CGraph(int vertices);
	~CGraph();
	void addEdge(const shared_ptr<CElement>& src, const shared_ptr<CElement>& dest);
	void serializeDom(ofstream& file, const vector<shared_ptr<CElement>>& elements);
	void removeElement(int indexElem, vector<shared_ptr<CElement>>& elements);
	void moveElement(int srcElem, int destElem, const vector<shared_ptr<CElement>>& elements);
private:
	vector<vector<int>> adj;
	vector<int> getAdjList(int indexSrc);
	void serialiseUtil(int indexSrc , vector<bool>& visited, ofstream& file, const vector<shared_ptr<CElement>>& elements);
	int vertices;
};


#endif // !CODE_GRAPH_H