// Contains Sub routine for Max heap Structure used for Kruskal's

#include "MaxHeapKrskl.h"
#include <vector>
MaxHeapKrskl::MaxHeapKrskl()
{

}

MaxHeapKrskl::MaxHeapKrskl(Graph2* Gr)
{
	G = Gr;
	/*cout << G.getNoOfVertices() << endl;
	vector<int> D = G.getEdgeCount();
	cout << D[1] << endl;
	cout << D[2] << endl;
	cout << D[3] << endl;
	cout << D[4] << endl;
	cout << D[5] << endl;*/
	Edge E;
	E.src = -1;
	E.dest = -1;
	E.wt = -1;
	H.noOfEdges = G->getEList()->noOfEdges;
	for (int i = 0; i < H.noOfEdges; i++)
		H.Edges.push_back(E);
	//position = new int[G->getEList().noOfEdges];
	heapSize = 0;
	arraySize = H.noOfEdges;
}

MaxHeapKrskl::~MaxHeapKrskl()
{
	//delete[] position;
}

int MaxHeapKrskl::getLeftIndex(int nodeIndex){
	return nodeIndex * 2 + 1;
}

int MaxHeapKrskl::getRightIndex(int nodeIndex){
	return nodeIndex * 2 + 2;
}

int MaxHeapKrskl::getParentIndex(int nodeIndex){
	return ((nodeIndex - 1) / 2);
}

void MaxHeapKrskl::siftUp(int nodeIndex){
	Edge temp;
	int parentIndex;
	if (nodeIndex != 0)
	{
		parentIndex = getParentIndex(nodeIndex);
		if (H.Edges[nodeIndex].wt > H.Edges[parentIndex].wt)
		{
			temp = H.Edges[nodeIndex];
			//position[H[nodeIndex]] = parentIndex;
			H.Edges[nodeIndex] = H.Edges[parentIndex];
			H.Edges[parentIndex] = temp;
			siftUp(parentIndex);
		}
	}
}

void MaxHeapKrskl::siftDown(int nodeIndex){
	int leftIndex, rightIndex, maxIndex;
	Edge temp;
	//	if (nodeIndex != heapSize - 1)
	//	{
	leftIndex = getLeftIndex(nodeIndex);
	rightIndex = getRightIndex(nodeIndex);
	if (leftIndex <= heapSize - 1)
	{
		if (rightIndex <= heapSize - 1)
		{
			if (H.Edges[leftIndex].wt >= H.Edges[rightIndex].wt){
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
	if (H.Edges[maxIndex].wt > H.Edges[nodeIndex].wt)
	{
		temp = H.Edges[nodeIndex];
		//position[H[nodeIndex]] = maxIndex;
		H.Edges[nodeIndex] = H.Edges[maxIndex];
		H.Edges[maxIndex] = temp;
		siftDown(maxIndex);
	}

	//	}
}

void MaxHeapKrskl::insertHeap(Edge E){
	if (heapSize == arraySize)
		return;
	heapSize++;
	H.Edges[heapSize - 1] = E;
	//position[vertex] = heapSize - 1;
	siftUp(heapSize - 1);
}

//always deleting the first element
void MaxHeapKrskl::deleteHeap(){

	int parentIndex;
	int nodeIndex = 0;
	if (heapSize == 0)
		return;
	if (nodeIndex > heapSize - 1)
		return;
	//position[H[heapSize - 1]] = nodeIndex;
	H.Edges[nodeIndex] = H.Edges[heapSize - 1];
	heapSize--;
	H.noOfEdges--;
	parentIndex = getParentIndex(nodeIndex);
	if ((nodeIndex == 0) || (H.Edges[nodeIndex].wt < H.Edges[parentIndex].wt))
		siftDown(nodeIndex);
	else
		siftUp(nodeIndex);
}

void MaxHeapKrskl::displayHeap(){
	for (int i = 0; i < heapSize; i++)
	{
		//cout << H[i] << "  ";
	}
	cout << endl;
}

void MaxHeapKrskl::displaySortArray(){
	while (heapSize != 0)
	{
		//cout << getMaximum() << "  ";
		deleteHeap();
	}
	cout << endl;
}

Edge MaxHeapKrskl::getMaximum(){
	return H.Edges[0];
}

void MaxHeapKrskl::generateHeap(){
	EdgeList* EList;
	EList = G->getEList();
	//EList->noOfEdges = G->getEList()->noOfEdges;
	//EList->Edges = G->getEList()->Edges;
	for (int i = 0; i < EList->noOfEdges; i++){
		insertHeap(EList->Edges[i]);
	}
	H.noOfEdges = EList->noOfEdges;
}