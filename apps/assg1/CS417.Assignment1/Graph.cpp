#include "Graph.h"
#include <iostream>
using namespace std;

int main() {
	Graph<string> graph;
	Node<string>* a = graph.addNode("A");
	Node<string>* b = graph.addNode("B");
	Node<string>* c = graph.addNode("C");
	Node<string>* d = graph.addNode("D");

	graph.addEdge(a, b);
	graph.addEdge(a, c);
	graph.addEdge(b, d);
	graph.addEdge(c, d);
	graph.print();

	graph.deleteNode(b);
	cout << endl << endl;
	graph.print();
}