#pragma once

#include "Graph.h"
#include <list>
#include <map>
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
