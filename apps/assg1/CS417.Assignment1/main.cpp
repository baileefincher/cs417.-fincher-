#include "AdjancyListGraph.h"
#include "AdjancyMatrixGraph.h"
#include <string>

void test(Graph<string> *graph) {
	graph->addNode("A");
	graph->addNode("B");
	graph->addNode("C");
	graph->addNode("D");

	graph->addEdge("A", "B");
	graph->addEdge("A", "C");
	graph->addEdge("B", "D");
	graph->addEdge("C", "D");
	graph->print();

	graph->deleteNode("A");
	cout << endl << endl;
	graph->print();

}

void testCycle(Graph<string>* graph) {
	graph->addNode("A");
	graph->addNode("B");
	graph->addNode("C");
	graph->addNode("D");

	graph->addEdge("A", "B");
	graph->addEdge("B", "C");
	graph->addEdge("C", "D");
	graph->addEdge("D", "A");
	graph->print();

	graph->checkCycle();

}

int main() {
	Graph<string> *graph;
	cout << "testing adjancy list..." << endl;
	graph = new AdjancyListGraph<string>();
	testCycle(graph);
	delete graph;


	cout << endl << endl;
	cout << "testing adjancy matrix..." << endl;
	graph = new AdjancyMatrixGraph<string>(4);
	testCycle(graph);
	delete graph;
	
}

