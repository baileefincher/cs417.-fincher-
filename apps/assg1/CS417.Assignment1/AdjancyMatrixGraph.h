#pragma once

#include "Graph.h"
#include <vector>

template<class N>
class Entry {
public:
	N n;
	int vertex;
	vector<int> matrix;

public:
	Entry(N n, int vertex, int numEntries) :
			n(n), vertex(vertex) {
		for (int i = 0; i < numEntries; i++) {
			matrix.push_back(0);
		}
	}

	~Entry() {
	}
};

template<class N>
class AdjancyMatrixGraph: public Graph<N> {

private:
	int numEntries;
	vector<Entry<N>*> *entries;

	Entry<N>* getEntry(N n) {
		for (int i = 0; i < numEntries; i++) {
			Entry<N> *entry = (*entries)[i];
			if (entry != NULL && entry->n == n) {
				return entry;
			}
		}

		return NULL;
	}

public:
	AdjancyMatrixGraph(int numEntries) {

		this->numEntries = numEntries;
		entries = new vector<Entry<N>*>(numEntries);
		for (int i = 0; i < numEntries; i++) {
			entries->push_back(NULL);
		}
	}

	AdjancyMatrixGraph(const AdjancyMatrixGraph &other) :
			Graph<N>(), numEntries(other->numEntries), entries(other->entries) {
	}

	virtual ~AdjancyMatrixGraph() {
		for (int i = 0; i < numEntries; i++) {
			if ((*entries)[i] != NULL) {
				delete ((*entries)[i]);
			}
		}
		delete (entries);
	}

	AdjancyMatrixGraph& operator=(const AdjancyMatrixGraph &other) {
		numEntries = other->numEntries;
		entries = other->entries;
		return *this;
	}

	bool adjacent(N x, N y) {
		Entry<N> *entryX = getEntry(x);
		Entry<N> *entryY = getEntry(y);
		vector<int> matrix = entryX->matrix;
		return matrix[entryY->vertex] == 1;
	}

	vector<N> neighbors(N n) {
		vector<N> neighbors;
		Entry<N> *entry = getEntry(n);

		vector<int> matrix = (*entries)[entry->vertex]->matrix;
		for (int i = 0; i < numEntries; i++) {
			if (matrix[i] == 1) {
				neighbors.push_back((*entries)[i]->n);
			}
		}

		return neighbors;
	}

	void addNode(N n) {
		for (int i = 0; i < numEntries; i++) {
			if ((*entries)[i] == NULL) {
				(*entries)[i] = new Entry<N>(n, i, numEntries);
				return;
			}
		}
	}

	void deleteNode(N n) {
		Entry<N> *entryToDelete = getEntry(n);
		(*entries)[entryToDelete->vertex] = NULL;

		for (int i = 0; i < numEntries; i++) {
			Entry<N> *entry = (*entries)[i];
			if (entry != NULL) {
				entry->matrix[entryToDelete->vertex] = 0;
			}
		}

		delete (entryToDelete);
	}

	void addEdge(N x, N y) {
		Entry<N> *entryX = getEntry(x);
		Entry<N> *entryY = getEntry(y);
		entryX->matrix[entryY->vertex] = 1;
		entryY->matrix[entryX->vertex] = 1;
	}

	void deleteEdge(N x, N y) {
		Entry<N> *entryX = getEntry(x);
		Entry<N> *entryY = getEntry(y);
		entryX->matrix[entryY->vertex] = 0;
		entryY->matrix[entryX->vertex] = 0;
	}

	void print() {
		for (int i = 0; i < numEntries; i++) {
			if ((*entries)[i] != NULL) {
				Entry<N> *entry = (*entries)[i];
				cout << entry->n << " = ";
				bool isFirst = true;
				for (int j = 0; j < numEntries; j++) {
					if (entry->matrix[j] == 1) {
						Entry<N> *otherEntry = (*entries)[j];
						if (!isFirst) {
							cout << ", ";
						}
						isFirst = false;
						cout << entry->n << " -> " << otherEntry->n;
					}
				}
				cout << endl;
			}
		}
	}
};
