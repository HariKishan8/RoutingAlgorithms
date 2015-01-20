// Header==> Function Declarations

#include <iostream>
using namespace std;
#include <string>
#include "Graph2.h"

#ifndef MAXHEAPKRSKL_H
#define MAXHEAPKRSKL_H

class MaxHeapKrskl
{
private:
	Graph2* G;
	EdgeList H;
	int heapSize;
	int arraySize;
	//int* position; // position of a vertex (of the graph) after heapify
	int getLeftIndex(int nodeIndex);
	int getRightIndex(int nodeIndex);
	int getParentIndex(int nodeIndex);


public:
	MaxHeapKrskl();
	MaxHeapKrskl(Graph2* Gr);
	~MaxHeapKrskl();
	void insertHeap(Edge E);
	void siftUp(int nodeIndex);
	void siftDown(int nodeIndex);
	void deleteHeap();
	void generateHeap();
	EdgeList* getHeapList(){ return &H; }
	void displayHeap();
	void displaySortArray();
	Edge getMaximum();
	int isEmpty(){ return heapSize == 0; };
};

#endif
