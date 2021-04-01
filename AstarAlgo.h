//
// Created by Ahsan Jalil on 11/30/17.
//

#ifndef DSAPROJ_ASTARALGO_H
#define DSAPROJ_ASTARALGO_H

#include"Graph.h"
#include "BinarySearchTree.h"
#include "MinHeap.h"
using namespace std;


template<class graphtype>
class AstarAlgo {
private:
    Vertex<graphtype>* start;
    Vertex<graphtype>* end;
    MinHeap<graphtype>* openList;
    BinarySearchTree<graphtype>* closedList;
    Graph<graphtype>* graph;
protected:

public:
	explicit AstarAlgo(Graph<graphtype>* _graph = NULL, Vertex<graphtype>* _start = NULL, Vertex<graphtype>* _end = NULL) {
		start = _start;
		end = _end;
		openList = new MinHeap<graphtype>(_graph->numofVertices());
		closedList = new BinarySearchTree<graphtype>();
		graph = _graph;
	}
    void setGraph(Graph<graphtype>* _graph){
        graph=_graph;
    }
    void setVertices(Vertex<graphtype>* _start, Vertex<graphtype>* _end){
        start=_start;
        end=_end;
    }
	void findRoute() {
		
		Vertex<graphtype>* current = start;
		Vertex<graphtype>* current_neighbor = NULL;
		Edges<graphtype>* current_edges = current->get_edgeList();
		int distancetravelled = 0;
		int g = 0, f = 0, h = 0;
		current->set_valF(distancetravelled + g, end);
		while (current != end && current != NULL) {
			while (current_edges != NULL) {
				current_neighbor = current_edges->get_vertexKey();
				if (current_neighbor == NULL) return;
				if (!openList->isPresent(current_neighbor) && closedList->Search(current_neighbor) == NULL) {
					openList->Push(current_neighbor);
					g = distancetravelled + current_edges->get_edgeWeight();
					h = abs(current_neighbor->get_X() - end->get_X()) + abs(current_neighbor->get_Y() - end->get_Y());
					f = g + h;
					if (f <= current_neighbor->get_valF() && current_neighbor != NULL) {
						current_neighbor->set_valF(g, h);
						current_neighbor->set_prevVertex(current);
					}
				}

				current_edges = current_edges->get_nextEdge();
			}
			
			closedList->Insert(current);
			distancetravelled = distancetravelled + graph->getWeight(current, openList->Top());
			current = openList->Pop();
			current_edges = current->get_edgeList();
		}
	}
	void print_path() {
		
		Vertex<graphtype>* temp = end;
		
		while (temp != start) {
			cout << temp->get_data()<<"<-";
			temp = temp->get_prevVertex();
		}
		cout << start->get_data();
		cout << endl;
	}
};






#endif //DSAPROJ_ASTARALGO_H
