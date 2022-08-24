#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

template <typename ValueType>
class Node {
public:
	int* vertex;
	ValueType value;
	vector<int*> indices;

	Node(int* vertex, ValueType value) {
		this->vertex = vertex;
		this->value = value;
	}

	void deleteIndex(int idx) {
		indices.erase(indices.begin() + idx);
	}
};

template <typename ValueType>
class Graph {
private:
	vector<Node<ValueType>*> nodes;

public:
	Node<ValueType>* addNode(ValueType x) {
		Node<ValueType>* node = new Node<ValueType>(new int(nodes.size()), x);
		nodes.push_back(node);
		return node;
	}

	void addEdge(Node<ValueType> *source, Node<ValueType> *dest) {
		source->indices.push_back(dest->vertex);
		dest->indices.push_back(source->vertex);
	}

	void remove(Node<ValueType> *source, Node<ValueType> *dest) {
		vector<int*> temp;
		for (int i = 0; i < source->nodes.size(); i++) {
			if (source.indices[i]->value != dest->value) {
				temp.push_back(source.indices[i]);
			}
		}
		source->indices = temp;
	}

	void deleteEdge(Node<ValueType>* source, Node<ValueType>* dest) {
		remove(source, dest);
		remove(dest, source);
	}

	void deleteNode(Node<ValueType>* nodeToDelete) {

		for (int i = 0; i < nodes.size(); i++) {
			Node<ValueType>* node = nodes[i];
			auto indexItr = node->indices.begin();
			while (indexItr != node->indices.end()) {
				if (nodes[**indexItr]->value == nodeToDelete->value) {
					indexItr = node->indices.erase(indexItr);
				}
				else {
					indexItr++;
				}
			}
		}

		int nodeToDeleteVertex = *(nodeToDelete->vertex);
		nodes.erase(nodes.begin() + nodeToDeleteVertex);

		for (int i = nodeToDeleteVertex; i < nodes.size(); i++) {
			int* vertex = nodes[i]->vertex;
			*vertex = *vertex - 1;
		}
	}

	void print() {
		for (int i = 0; i < nodes.size(); i++) {
			cout << nodes[i]->value << " -> ";
			for (int j = 0; j < nodes[i]->indices.size(); j++) {
				int *index = nodes[i]->indices[j];
				Node<ValueType>* childNode = nodes[*index];
				cout << childNode->value << " -> ";
			}
			cout << endl;
		}
	}
};

