#pragma once

#include "Graph.h"
#include <list>
#include <map>
#include <set>
#include <iostream>

template<class N>
class Edge {
private:
	N x;
	N y;

public:
	Edge(N x, N y) :
		x(x), y(y) {
	}

	Edge(const Edge &other) :
			x(other.x), y(other.y) {
	}

	~Edge() {
	}

	Edge& operator=(const Edge &other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	bool operator==(const Edge &other) {
		return x == other.x && y == other.y;
	}

	const N getX() {
		return x;
	}

	const N getY() {
		return y;
	}

	friend ostream& operator<<(ostream& os, const Edge<N>& dt) {
		os << dt.x << " -> " << dt.y;
		return os;
	}
};

template <class N>
class AdjancyListGraph : public Graph<N> {
private:
	map<N, list<Edge<N>>> vertexMap;

	bool checkCycle(N entry, list <Edge<N>> edges, set<N>* entriesChecked) {
		for (auto itr = edges.begin(); itr != edges.end(); itr++) {
			if (checkCycle(entry, itr->getY(), 2, entriesChecked)) {
				return true;
			}
		}

		return false;
	}

	bool doesSetContain(set<N>* theSet, N n) {
		return theSet->find(n) != theSet->end();
	}

	bool checkCycle(N entry, N n, int count, set<N>* entriesChecked) {

		list<Edge<N>> edges = vertexMap[n];
		entriesChecked->insert(n);

		if (edges.size() == 1) {
			return false;
		}

		for (auto itr = edges.begin(); itr != edges.end(); itr++) {
			if (count > 2 && itr->getY() == entry) {
				cout << "A cycle exists from " << entry << " back to itself. count = " << count << endl;
				return true;
			}

			if (!doesSetContain(entriesChecked, itr->getY()) && checkCycle(entry, itr->getY(), count + 1, entriesChecked)) {
				return true;
			}
		}

		return false;
	}

public:
	AdjancyListGraph() {
	}

	AdjancyListGraph(const AdjancyListGraph& other) : vertexMap(other->vertexMap) {
	}

	AdjancyListGraph(vector<N> newNodes, vector<Edge<N>> newEdges) :
		Graph<N>(newNodes, newEdges) {
		auto itr = newNodes.begin();
		while (itr != newNodes.end()) {
			vertexMap[*itr].push_back(newEdges);
			itr++;
		}
	}

	~AdjancyListGraph() {
	}

	AdjancyListGraph& operator=(const AdjancyListGraph& other) {
		vertexMap = other->vertexMap;
		return *this;
	}

	bool adjacent(N x, N y) {
		list<Edge<N>> edges = vertexMap[x];

		auto itr = edges.begin();
		while (itr != edges.end()) {
			Edge<N> edge = *itr;
			if (edge.getY() == y) {
				return true;
			}
			itr++;
		}

		return false;
	}

	vector<N> neighbors(N n) {
		vector<N> neighbors;
		list<Edge<N>> edges = vertexMap[n];

		auto itr = edges.begin();
		while (itr != edges.end()) {
			Edge<N> edge = *itr;
			neighbors.push_back(edge.getX());
			itr++;
		}

		return neighbors;
	}

	void addNode(N n) {
		list<Edge<N>> emptyList;
		vertexMap[n] = emptyList;
	}

	void deleteNode(N n) {
		list<Edge<N>> node = vertexMap[n];
		for (auto itr = node.begin(); itr != node.end(); itr++) {
			Edge<N> edge = *itr;
			deleteEdge(edge.getX(), edge.getY());
		}

		vertexMap.erase(n);
	}

	void addEdge(N x, N y) {
		Edge<N> edge1(x, y);
		Edge<N> edge2(y, x);
		vertexMap[x].push_back(edge1);
		vertexMap[y].push_back(edge2);
	}

	void deleteEdge(N x, N y) {
		Edge<N> edge1(x, y);
		Edge<N> edge2(y, x);
		this->deleteFromList(&vertexMap[x], edge1);
		this->deleteFromList(&vertexMap[y], edge2);
	}

	bool checkCycle() {
		for (auto mapItr = vertexMap.begin(); mapItr != vertexMap.end(); mapItr++) {
			N entry = mapItr->first;
			set<N>* entriesChecked = new set<N>();
			entriesChecked->insert(entry);
			list<Edge<N>> edges = mapItr->second;
			if (checkCycle(entry, edges, entriesChecked)) {
				return true;
			}
		}

		return false;
	}

	void print() {
		for (auto mapItr = vertexMap.begin(); mapItr != vertexMap.end(); mapItr++) {
			cout << mapItr->first << " = ";
			auto edges = mapItr->second;
			auto edgeItr = edges.begin();
			while (edgeItr != edges.end()) {
				cout << *edgeItr;
				edgeItr++;
				if (edgeItr != edges.end()) {
					cout << ", ";
				}
			}
			cout << endl;
		}
	}


};
