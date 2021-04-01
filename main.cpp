#include<iostream>
#include<fstream>
#include"Graph.h"
#include"AstarAlgo.h"
using namespace std;


void add_Vertices(Graph<char>* graph) {
	int x = 0; int y = 0; char temp_char = 0;
	ifstream infile; infile.open("vertex list.txt");
	Vertex<char>* temp = NULL;
	while (!infile.eof()) {
		infile >> x >> y >> temp_char;
		temp = new Vertex<char>(temp_char);
		temp->setPosition(x, y);
		graph->addVertex(temp);
	}
	infile.close();
}

void add_edges(Graph<char>* graph) {
	int frm_x = 0, frm_y = 0, to_x = 0, to_y = 0, weight = 0;
	ifstream infile; infile.open("input.txt");
	Vertex<char>* from = NULL; Vertex<char>* to = NULL;
	while (!infile.eof()){
		infile >> frm_x >> frm_y >> to_x >> to_y >> weight;
		graph->addEdgeUndir(graph->vertexReturn(frm_x, frm_y), graph->vertexReturn(to_x, to_y), weight);
	}
	infile.close();
}





int main() {
	Graph<char>* graph = new Graph<char>();
	add_Vertices(graph);
	add_edges(graph);
	graph->printGraph();
	AstarAlgo<char>* PathFinder = new AstarAlgo<char>(graph);
	char data_from;
	char data_to;
	cout << "Enter Start: "; cin >> data_from;
	cout << "Enter To: "; cin >> data_to;
	Vertex<char>* from;
	Vertex<char>* to;

	PathFinder->setVertices(graph->searchData(data_from), graph->searchData(data_to));
	PathFinder->findRoute(); PathFinder->print_path();
	system("pause");
}
