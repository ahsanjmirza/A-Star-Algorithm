//
// Created by Ahsan Jalil on 11/30/17.
//

#ifndef DSAPROJ_GRAPH_H
#define DSAPROJ_GRAPH_H

#include<iostream>
#include<cmath>
using namespace std;

template<class edgetype>
class Edges;

template<class vertextype>
class Vertex {
private:
    Vertex<vertextype>* nextVertex;
    Edges<vertextype>* edgeList;
    vertextype data;
    int positionX, positionY;
    int heuristicFromTarget, valF, valG;
    Vertex<vertextype>* prevVertex;
public:
    Vertex(vertextype _data = 65) {
        nextVertex = NULL;
        edgeList = NULL;
        valG = INT_MAX;
        positionX = -1; positionY = -1;
        heuristicFromTarget = INT_MAX;
        valF = INT_MAX;
        data = _data;
        prevVertex = NULL;
    }
    void set_nextVertex(Vertex<vertextype>* next) {
        nextVertex = next;
    }
    void set_nextEdge(Edges<vertextype>* next) {
        edgeList = next;
    }
    void set_data(vertextype Data) {
        data = Data;
    }
    void add_Edge(Edges<vertextype>* tobeadded) {
        if (edgeList == NULL) {
            edgeList = tobeadded;
        }
        else {
            Edges<vertextype>* temp0 = edgeList;
            while (temp0->get_nextEdge() != NULL) {
                if (temp0->get_vertexKey() == tobeadded->get_vertexKey()) {
                    return;
                }
                temp0 = temp0->get_nextEdge();
            }
            temp0->set_nextEdge(tobeadded);
        }
    }
    void remove_Edge(Edges<vertextype>* tobedel_before) {
        Edges<vertextype>* tobedeleted = tobedel_before->get_nextEdge();
        tobedel_before->set_nextEdge(tobedeleted->get_nextEdge());
        delete tobedeleted;
    }
    void setPosition(const int X, const int Y) {
        positionX = X; positionY = Y;
    }
	int get_X() {
		return positionX;
	}
	int get_Y() {
		return positionY;
	}
    void getPosition(int& X, int& Y) {
        X = positionX, Y = positionY;
    }
    Vertex<vertextype>* get_nextVertex() {
        return nextVertex;
    }
    Edges<vertextype>* get_edgeList() {
        return edgeList;
    }
    vertextype get_data() {
        return data;
    }
    void set_valG(int G) {
        valG = G;
    }
    int get_valG() {
        return valG;
    }
    int get_valH(Vertex<vertextype>* target) {
		heuristicFromTarget = abs(target->positionX - this->positionX) + abs(target->positionY - this->positionY);
        return heuristicFromTarget;
    }
    void set_valF(int g, int h) {
		valG = g;
		heuristicFromTarget = h;
        valF = g + h;
    }
    void set_valF(int g, Vertex<vertextype>* target) {
        valG = g;
        heuristicFromTarget = abs(target->positionX - this->positionX) + abs(target->positionY - this->positionY);
        valF = heuristicFromTarget + valG;
    }
    int get_valF() {
        return valF;
    }
    void Print() {
        cout << data;
    }
    void set_prevVertex(Vertex<vertextype>* parent) {
        prevVertex = parent;
    }
    Vertex<vertextype>* get_prevVertex() {
        return prevVertex;
    }
};

template<class edgetype>
class Edges {
private:
    Edges<edgetype>* nextEdge;
    int edgeWeight;
    Vertex<edgetype>* vertexKey;
public:
    Edges() {
        int weight = INT_MAX;
        nextEdge = NULL;
    }
    void set_nextEdge(Edges<edgetype>* next) {
        nextEdge = next;
    }
    void set_edgeWeight(int weight) {
        edgeWeight = weight;
    }
    void set_vertexKey(Vertex<edgetype>* key) {
        vertexKey = key;
    }
    Edges<edgetype>* get_nextEdge() {
        return nextEdge;
    }
    int get_edgeWeight() {
        return edgeWeight;
    }
    Vertex<edgetype>* get_vertexKey() {
        return vertexKey;
    }
};




template<class graphtype>
class Graph {
private:
    Vertex<graphtype>* firstvertex;
	int num_ofVertices;
protected:

public:
    Graph() {
        firstvertex = NULL;
		num_ofVertices = 0;
    }
    void addVertex(Vertex<graphtype>* vertex) {
        if (firstvertex == NULL) {
            firstvertex = vertex;
        }
        else {
            Vertex<graphtype>* temp0 = firstvertex;
            while (temp0->get_nextVertex() != NULL) {
                if (temp0 == vertex) {
                    return;
                }
                temp0 = temp0->get_nextVertex();
            }
            temp0->set_nextVertex(vertex);
        }
		num_ofVertices++;
    }
    void addEdgeUndir(Vertex<graphtype>* from, Vertex<graphtype>* to, int weight) {
        Edges<graphtype>* fromedge = new Edges<graphtype>();
        Edges<graphtype>* toedge = new Edges<graphtype>();
        fromedge->set_vertexKey(to); fromedge->set_edgeWeight(weight);
        from->add_Edge(fromedge);
        toedge->set_vertexKey(from); toedge->set_edgeWeight(weight);
        to->add_Edge(toedge);
    }
    void removeEdgeUndir(Vertex<graphtype>* from, Vertex<graphtype>* to) {
        Edges<graphtype>* edgetobedeleted = from->get_edgeList();
        Edges<graphtype>* pbefore_del = from->get_edgeList();
        while (edgetobedeleted->get_vertexKey() != to) {
            pbefore_del = edgetobedeleted;
            edgetobedeleted = edgetobedeleted->get_nextEdge();
        }
        from->remove_Edge(pbefore_del);
        edgetobedeleted = to->get_edgeList();
        pbefore_del = to->get_edgeList();
        while (edgetobedeleted->get_vertexKey() != from) {
            pbefore_del = edgetobedeleted;
            edgetobedeleted = edgetobedeleted->get_nextEdge();
        }
        to->remove_Edge(pbefore_del);
    }
    int numofVertices() {
		return num_ofVertices;
    }
    int numofEdges(Vertex<graphtype>* vertex) {
        Edges<graphtype>* temp0 = vertex->get_edgeList();
        int Count = 0;
        while (temp0 != NULL) {
            Count++;
            temp0 = temp0->get_nextEdge();
        }
        return Count;
    }
    Vertex<graphtype>* get_vertexList() {
        return firstvertex;
    }
	void printGraph() {
		Vertex<graphtype>* temp = firstvertex;
		Edges<graphtype>* temp_e = NULL;
		while (temp != NULL) {
			temp_e = temp->get_edgeList();
			cout << temp->get_data() << "--->|";
			while (temp_e != NULL) {
				cout << temp_e->get_vertexKey()->get_data() << "->";
				temp_e = temp_e->get_nextEdge();
			}
			cout << "\n";
			temp = temp->get_nextVertex();
			
		}
	}
	int getWeight(Vertex<graphtype>* from, Vertex<graphtype>* to) {
		Edges<graphtype>* edgeF = from->get_edgeList();
		while (edgeF != NULL) {
			if (edgeF->get_vertexKey() == to){
				return edgeF->get_edgeWeight();
			}
			edgeF = edgeF->get_nextEdge();
		}
		return INT_MAX;
	}
	Vertex<graphtype>* vertexReturn(int X, int Y) {
		Vertex<graphtype>* temp = firstvertex;
		while (temp != NULL) {
			if (temp->get_X() == X && temp->get_Y() == Y) {
				return temp;
			}
			temp = temp->get_nextVertex();
		}
		temp = new Vertex<graphtype>(); temp->setPosition(X, Y);
		this->addVertex(temp);
		return temp;
	}
	Vertex<graphtype>* searchData(graphtype _data) {
		Vertex<graphtype>* temp = firstvertex;
		while (temp != NULL) {
			if (temp->get_data() == _data) {
				return temp;
			}
			temp = temp->get_nextVertex();
		}
		return NULL;
	}
};



#endif //DSAPROJ_GRAPH_H
