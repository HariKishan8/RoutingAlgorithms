// Contains Sub routine for Max heap Structure used for Dijkstra's with heap

#include "MaxHeapGraph.h"
#include <vector>
MaxHeapGraph::MaxHeapGraph()
{	
	
}

MaxHeapGraph::MaxHeapGraph(Graph2* Gr)
{
	G = Gr;
	/*cout << G.getNoOfVertices() << endl;
	vector<int> D = G.getEdgeCount();
	cout << D[1] << endl;
	cout << D[2] << endl;
	cout << D[3] << endl;
	cout << D[4] << endl;
	cout << D[5] << endl;*/
	H = new int[G->getNoOfVertices()];
	position = new int[G->getNoOfVertices()];
	heapSize = 0;
	arraySize = G->getNoOfVertices();
}

MaxHeapGraph::~MaxHeapGraph()
{
	delete[] H;
	delete[] position;
}

int MaxHeapGraph::getLeftIndex(int nodeIndex){
	return nodeIndex * 2 + 1;
}

int MaxHeapGraph::getRightIndex(int nodeIndex){
	return nodeIndex * 2 + 2;
}

int MaxHeapGraph::getParentIndex(int nodeIndex){
	return ((nodeIndex - 1) / 2);
}

void MaxHeapGraph::siftUp(int nodeIndex){
	int temp, parentIndex;
	vector<int> Di = G->getDistance();
	if (nodeIndex != 0)
	{
		parentIndex = getParentIndex(nodeIndex);
		if (Di[H[nodeIndex]] > Di[H[parentIndex]])
		{
			temp = H[nodeIndex];
			position[H[nodeIndex]] = parentIndex;
			position[H[parentIndex]] = nodeIndex;
			H[nodeIndex] = H[parentIndex];
			H[parentIndex] = temp;
			siftUp(parentIndex);
		}
	}
}

void MaxHeapGraph::siftDown(int nodeIndex){
	int leftIndex, rightIndex, maxIndex, temp;
	vector<int> Di = G->getDistance();
	//	if (nodeIndex != heapSize - 1)
	//	{
	leftIndex = getLeftIndex(nodeIndex);
	rightIndex = getRightIndex(nodeIndex);
	if (leftIndex <= heapSize - 1)
	{
		if (rightIndex <= heapSize - 1)
		{
			if (Di[H[leftIndex]] >= Di[H[rightIndex]]){
				maxIndex = leftIndex;
			}
			else
				maxIndex = rightIndex;
		}
		else
			maxIndex = leftIndex;
	}
	else
		return;
	if (Di[H[maxIndex]] > Di[H[nodeIndex]])
	{
		temp = H[nodeIndex];
		position[H[nodeIndex]] = maxIndex;
		position[H[maxIndex]] = nodeIndex;
		H[nodeIndex] = H[maxIndex];
		H[maxIndex] = temp;
		siftDown(maxIndex);
	}

	//	}
}

void MaxHeapGraph::insertHeap(int vertex){
	if (heapSize == arraySize)
		return;
	heapSize++;

	H[heapSize - 1] = vertex;
	position[vertex] = heapSize - 1;
	siftUp(heapSize - 1);
}

void MaxHeapGraph::deleteHeap(int vertex){

	int parentIndex;
	vector<int> Di = G->getDistance();
	int nodeIndex = position[vertex];
	if (heapSize == 0)
		return;
	if (nodeIndex > heapSize - 1)
		return;
	position[H[heapSize - 1]] = nodeIndex;
	H[nodeIndex] = H[heapSize - 1];
	heapSize--;
	parentIndex = getParentIndex(nodeIndex);
	if ((nodeIndex == 0) || (Di[H[nodeIndex]] < Di[H[parentIndex]]))
		siftDown(nodeIndex);
	else
		siftUp(nodeIndex);
}

void MaxHeapGraph::displayHeap(){
	for (int i = 0; i < heapSize; i++)
	{
		cout << H[i] << "  ";
	}
	cout << endl;
}

void MaxHeapGraph::displaySortArray(){
	while (heapSize != 0)
	{
		cout << getMaximum() << "  ";
		deleteHeap(0);
	}
	cout << endl;
}

int MaxHeapGraph::getMaximum(){
	return H[0];
}