#pragma once

#include <vector>
#include <iostream>
#include <list>

using namespace std;

template<class N>
class Graph {
public:
	virtual ~Graph() {
	}

	virtual bool adjacent(N x, N y) = 0;
	virtual vector<N> neighbors(N x) = 0;
	virtual void addNode(N x) = 0;
	virtual void deleteNode(N x) = 0;
	virtual void addEdge(N x, N y) = 0;
	virtual void deleteEdge(N x, N y) = 0;
	virtual void print() = 0;

protected:
	template <class T>
	void deleteFromList(list<T>* theList, T toDelete) {
		auto itr = theList->begin();
		while (itr != theList->end()) {
			T t = *itr;
			if (t == toDelete) {
				itr = theList->erase(itr);
			} else {
				itr++;
			}
		}
	}
};
