// Header==> Function Declarations

#include <iostream>
using namespace std;
#include <string>
#include "Graph2.h"

#ifndef MAXHEAPGRAPH_H
#define MAXHEAPGRAPH_H

class MaxHeapGraph
{
private:
	Graph2* G;
	int* H;
	int heapSize;
	int arraySize;
	int* position; // position of a vertex (of the graph) after heapify
	int getLeftIndex(int nodeIndex);
	int getRightIndex(int nodeIndex);
	int getParentIndex(int nodeIndex);

public:
	MaxHeapGraph();
	MaxHeapGraph(Graph2* Gr);
	~MaxHeapGraph();
	void insertHeap(int vertex);
	void siftUp(int nodeIndex);
	void siftDown(int nodeIndex);
	void deleteHeap(int vertex);
	void displayHeap();
	void displaySortArray();
	int getMaximum();
	int isEmpty(){ return heapSize == 0; };
};

#endif