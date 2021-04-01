//
// Created by Ahsan Jalil on 11/30/17.
//

#ifndef DSAPROJ_MINHEAP_H
#define DSAPROJ_MINHEAP_H

#include "Graph.h"
using namespace std;

template<class DT>
class MinHeap
{
private:
    Vertex<DT>** arr;
    int heapSize;
public:
    explicit MinHeap(int maxsize = 10) {
        arr = new Vertex<DT>* [maxsize];
        for(int i=0; i<maxsize; i++){
            arr[i]=new Vertex<DT>();
        }
        heapSize = 1;
    }
    bool Push(Vertex<DT>* data) {
        int nodeIndex, parentIndex;
        Vertex<DT> *temp = NULL;
        heapSize++;
        arr[heapSize - 1] = data;
        nodeIndex = heapSize - 1;
        while (nodeIndex != 1) {
            parentIndex = (nodeIndex) / 2;
            if (arr[nodeIndex]->get_valF() <= arr[parentIndex]->get_valF()) {
                temp = arr[nodeIndex];
                arr[nodeIndex] = arr[parentIndex];
                arr[parentIndex] = temp;
                nodeIndex = parentIndex;
            } else {
                return true;
            }
        }
        return false;
    }
    Vertex<DT>* Pop() {
	
	
        if(heapSize==2){
            heapSize--;
            return arr[1];
        }
        int nodeIndex = 1, leftchildIndex, rightchildIndex;
        Vertex<DT> *flag = NULL;
        Vertex<DT> *temp = arr[1];
        arr[nodeIndex] = arr[heapSize - 1];
        heapSize--;
        leftchildIndex = 2 * nodeIndex;
        rightchildIndex = (2 * nodeIndex) + 1;
        while (leftchildIndex < heapSize && rightchildIndex < heapSize) {
            leftchildIndex = 2 * nodeIndex;
            rightchildIndex = (2 * nodeIndex) + 1;
            if (arr[nodeIndex]->get_valF() < arr[leftchildIndex]->get_valF() || arr[nodeIndex]->get_valF() < arr[rightchildIndex]->get_valF()) {
				break;
            } 
			else if (arr[nodeIndex]->get_valF() > arr[leftchildIndex]->get_valF() && arr[nodeIndex]->get_valF() > arr[rightchildIndex]->get_valF()) {
                if (arr[leftchildIndex]->get_valF() < arr[rightchildIndex]->get_valF()) {
                    flag = arr[leftchildIndex];
                    arr[leftchildIndex] = arr[nodeIndex];
                    arr[nodeIndex] = flag;
                    nodeIndex = leftchildIndex;
                } 
				else {
                    flag = arr[rightchildIndex];
                    arr[rightchildIndex] = arr[nodeIndex];
                    arr[nodeIndex] = flag;
                    nodeIndex = rightchildIndex;
                }
            } 
			else if (arr[nodeIndex]->get_valF() > arr[leftchildIndex]->get_valF()) {
                flag = arr[leftchildIndex];
                arr[leftchildIndex] = arr[nodeIndex];
                arr[nodeIndex] = flag;
                nodeIndex = leftchildIndex;
            } 
			else if (arr[nodeIndex]->get_valF() > arr[rightchildIndex]->get_valF()) {
                flag = arr[rightchildIndex];
                arr[rightchildIndex] = arr[nodeIndex];
                arr[nodeIndex] = flag;
                nodeIndex = rightchildIndex;
            }
        }
		return temp;
    }
    bool isEmpty() {
        return heapSize == 1;
    }
    bool isPresent(Vertex<DT>* tobefound) {
        for (int i = 1; i < heapSize; i++) {
            if (arr[i] == tobefound) {
                return true;
            }
        }
        return false;
    }
	Vertex<DT>* Top() {
		return arr[1];
	}
};

#endif //DSAPROJ_MINHEAP_H
