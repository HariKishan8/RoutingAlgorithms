// Contains sub routines for graph generation, Dijkstra without heap, Dijkstra with heap and Kruskal with heap.


#include "Graph2.h"
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include "MaxHeapGraph.h"
#include "MaxHeapKrskl.h"
#define MAXINT 987654321
typedef pair<int, int> ii;

Graph2::~Graph2() {

}

Graph2::Graph2(int noOfVertices) {
	this->noOfVertices = noOfVertices;
	eList.noOfEdges = 0;

	vector<int> empty;
	for (int j = 0; j < noOfVertices; j++)
		empty.push_back(0);

	for (int i = 0; i < noOfVertices; i++) {
		adjMatrix.push_back(empty);
		edgeCount.push_back(0);
		D.push_back(INT_MAX);
		status.push_back(UNSEEN);
		DadMaxCap.push_back(-1);
		rank.push_back(0);
		DadKrskl.push_back(-1);
	}
}

void Graph2::addEdge(int i, int j, int wt) {
	if (((i >= 0 && j > 0) || (i > 0 && j >= 0)) && (i < noOfVertices) && (j < noOfVertices) && !isEdge(i, j)) {
		adjMatrix[i][j] = wt;
		edgeCount[i]++;
		adjMatrix[j][i] = wt;
		edgeCount[j]++;
		Edge e1;
		e1.src = i;
		e1.dest = j;
		e1.wt = wt;
		eList.Edges.push_back(e1);
		eList.noOfEdges ++;
	}
}

void Graph2::removeEdge(int i, int j) {
	if (((i >= 0 && j > 0) || (i > 0 && j >= 0)) && i < noOfVertices && j < noOfVertices) {
		adjMatrix[i][j] = 0;
		edgeCount[i]--;
		adjMatrix[j][i] = 0;
		edgeCount[j]--;
	}
}

bool Graph2::isEdge(int i, int j) {
	if (((i >= 0 && j > 0) || (i > 0 && j >= 0)) && i < noOfVertices && j < noOfVertices)
		return adjMatrix[i][j];
	else
		return false;
}

void Graph2::generateGraph(int vertexDegree, int range){
	int Src, Dest, Weight, temp, count = 0;
	srand(time(NULL));
	for (int i = 0; i < noOfVertices; i++){
		Src = i;
		count = 0;
		while (edgeCount[Src] != (vertexDegree - range)){
			
			//first implementation
			if (range != 0){
				Dest = rand() % (noOfVertices); // dest in the range of 0 to noOfVertices-1			
				while (Src == Dest)
					Dest = rand() % (noOfVertices); // dest in the range of 0 to noOfVertices-1
			}
			else{
				Dest = rand() % (noOfVertices-1 - i) + i+1; // dest in the range of i+1 to noOfVertices-1		
				while (Src == Dest)
					Dest = rand() % (noOfVertices-1 - i) + i+1; // dest in the range of i+1 to noOfVertices-1
			}
			
			Weight = rand() % (noOfVertices * 2) + 1; // rand in the range of 1 to noOfVertices*2
			temp = edgeCount[Src];
			if ((edgeCount[Src] < vertexDegree) && (edgeCount[Dest] < vertexDegree))
				addEdge(Src, Dest, Weight);
			
			if (edgeCount[Src] == temp){
				count++;
				if (count > noOfVertices){
					count = 0;
					break;
				}
			}
			else
				count = 0;
		}
	}
}

void Graph2::pickandGenPath(int* s, int* t){
	//int s, t, 
	int wt;

	srand(time(NULL));
	*s = rand() % (noOfVertices-2) + 1;
	*t = rand() % (noOfVertices - 2) + 1;
	while (*s == *t)
		*t = rand() % (noOfVertices - 2) + 1;
	wt = rand() % (noOfVertices * 2) + 1;
	if(!isEdge(*s, 0))
		addEdge(*s, 0, wt);
	
	for (int i = 0; i < noOfVertices; i++){
		wt = rand() % (noOfVertices * 2) + 1;
		if (i == *s || i == *t){
			continue;
		}
		if (i + 1 == *s || i + 1 == *t){
			if (i + 2 == *s || i + 2 == *t){
				if ((i + 3 < noOfVertices) && !isEdge(i, i + 3))
					addEdge(i, i + 3, wt);
			}
			else{
				if ((i + 2 < noOfVertices) && !isEdge(i, i + 2))
					addEdge(i, i + 2, wt);
			}
		}
		else{
			if ((i + 1 < noOfVertices) && !isEdge(i, i + 1))
				addEdge(i, i + 1, wt);
		}	
	}
	wt = rand() % (noOfVertices * 2) + 1;
	if (!isEdge(noOfVertices - 1, *t))
		addEdge(noOfVertices - 1, *t, wt);
	return;
}


void Graph2::writeGraph(string fileName){
	ofstream GraphG1;
	GraphG1.open(fileName);
	if (!(GraphG1.is_open())){
		cout << "Unable to Open File" << endl;
		return;
	}
	for (int i = 0; i < noOfVertices; i++)
	{
		GraphG1 << "Adj[" << i << "]: ";
		for (int j = 0; j < noOfVertices; j++){
			if (isEdge(i,j))
				GraphG1 << j << "(" << adjMatrix[i][j]<< ")" << " ";
		}		
		GraphG1 << " ; EdgeCount[" << i << "]: " << edgeCount[i] << endl;
	}
	GraphG1.close();
}

int Graph2::MaxDistVertex(){
	int max = INT_MIN, maxVertex = -1;
	for (int w = 0; w < noOfVertices; w++){
		if (status[w] == FRINGE){
			if (max < D[w]){
				max = D[w];
				maxVertex = w;
			}
		}
	}
	return maxVertex;
}

void Graph2::DkstrMaxCap(int s, int t, double* time){

	int v, w, wt, fringeCount = 0;
	clock_t start;
	start = clock();
	// Initialize all distances as -INFINITE and status[] as false
	for (int i = 0; i < noOfVertices; i++){
		D[i] = INT_MIN;
		status[i] = UNSEEN;
		DadMaxCap[i] = -1;
	}

	D[s] = INT_MAX;
	status[s] = INTREE;

	// for each edge of S, make the adj vertex as fringe
	for (int w = 0; w < noOfVertices; w++){
		if (isEdge(s, w)){
			wt = adjMatrix[s][w];
			status[w] = FRINGE;
			D[w] = wt;
			fringeCount++;
			DadMaxCap[w] = s;
		}	
	}

	while (fringeCount != 0){
		v = MaxDistVertex();
		status[v] = INTREE;
		/*Enable the code below to stop after the max capacity path is found*/
		//if (status[t] == INTREE)// We found the path from s to t
			//break;
		fringeCount--;
		// for each edge of v
		for (int w = 0; w < noOfVertices; w++){
			if (isEdge(v, w)){
				wt = adjMatrix[v][w];
				if (status[w] == UNSEEN){
					status[w] = FRINGE;
					D[w] = min(D[v], wt);
					fringeCount++;
					DadMaxCap[w] = v;
				}
				else if ((status[w] == FRINGE) && (D[w] < min(D[v], wt))){
					D[w] = min(D[v], wt);
					DadMaxCap[w] = v;
				}
			}		
		}
	}
	*time = (clock() - start) / (double)CLOCKS_PER_SEC;
}

void Graph2::DkstrMaxCapMaxHeap(int s, int t, double* time){
	int v, w, wt;
	clock_t start;
	start = clock();
	MaxHeapGraph FringeHeap(this);

	// Initialize all distances as -INFINITE and status[] as false
	for (int i = 0; i < noOfVertices; i++){
		D[i] = INT_MIN;
		status[i] = UNSEEN;
		DadMaxCap[i] = 0;
	}

	D[s] = INT_MAX;
	status[s] = INTREE;

	// for each edge of S, make the adj vertex as fringe
	for (int w = 0; w < noOfVertices; w++){
		if (isEdge(s, w)){
			wt = adjMatrix[s][w];
			status[w] = FRINGE;
			D[w] = wt;
			FringeHeap.insertHeap(w);
			DadMaxCap[w] = s;
		}
	}

	while (!FringeHeap.isEmpty()){
		v = FringeHeap.getMaximum();
		FringeHeap.deleteHeap(v);
		status[v] = INTREE;
		/*Enable the code below to stop after the max capacity path is found*/
		if (status[t] == INTREE)// We found the path from s to t
			break;
		// for each edge of v
		for (int w = 0; w < noOfVertices; w++){
			if (isEdge(v, w)){
				wt = adjMatrix[v][w];
				if (status[w] == UNSEEN){
					status[w] = FRINGE;
					D[w] = min(D[v], wt);
					FringeHeap.insertHeap(w);
					DadMaxCap[w] = v;
				}
				else if ((status[w] == FRINGE) && (D[w] < min(D[v], wt))){
					FringeHeap.deleteHeap(w);
					D[w] = min(D[v], wt);
					FringeHeap.insertHeap(w);
					DadMaxCap[w] = v;
				}
			}
		}
	}
	*time = (clock() - start) / (double)CLOCKS_PER_SEC;
}

void Graph2::DFSVisit(int v, bool visited[])
{
	// Mark the current node as visited and print it
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	for (int i = 0; i < noOfVertices; i++){
		if (isEdge(v, i) && !visited[i]){
			DadMaxCap[i] = v;
			D[i] = min(D[v], adjMatrix[v][i]);
			DFSVisit(i, visited);
		}
	}
		
}

// DFS traversal of the vertices reachable from v. It uses recursive DFSUtil()
void Graph2::DFS(int v)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[noOfVertices];
	for (int i = 0; i < noOfVertices; i++)
		visited[i] = false;

	// Call the recursive helper function to print DFS traversal
	D[v] = INT_MAX;
	DFSVisit(v, visited);
}

EdgeList* Graph2::KruskalMaxCap(int s, int t, double* time1, double* time2){
	Edge E;
	E.src = -1;
	E.dest = -1;
	E.wt = -1;
	clock_t start;

	// Sorting all the edges and placing them in heap edge list
	MaxHeapKrskl A(this);
	EdgeList Tree;
	start = clock();
	A.generateHeap();
	//EdgeList* Heap = A.getHeapList();

	Tree.noOfEdges = 0;
	for (int i = 0; i < noOfVertices; i++){
		Tree.Edges.push_back(E);
		MakeSet(i);
	}
	for (int i = 0; i < eList.noOfEdges; i++){
		int r1 = Find(A.getMaximum().src);
		int r2 = Find(A.getMaximum().dest);
		if (r1 != r2){
			Tree.noOfEdges = Tree.noOfEdges + 1;
			Tree.Edges[Tree.noOfEdges - 1] = A.getMaximum();
			Union(r1, r2);
			/*Enable the code below to stop after the max capacity path is found*/
			if (Find(s) == Find(t)) //We got the path from s to t
				break;
		}
		
		A.deleteHeap();
	}
	// Time for finding the Max Spanning tree
	*time1 = (clock() - start) / (double)CLOCKS_PER_SEC;
	
	// Converting tree to graph for the purpose of performing DFS to fill up the DadMaxCap array
	Graph2 TreeListToGraph(noOfVertices);
	for (int i = 0; i < Tree.noOfEdges; i++){
		TreeListToGraph.addEdge(Tree.Edges[i].src, Tree.Edges[i].dest, Tree.Edges[i].wt);
	}
	TreeListToGraph.DFS(s);
	DadMaxCap = TreeListToGraph.getDadMaxCap();
	D = TreeListToGraph.getDistance();
	
	// Time including DFS to get the DadMaxCap array
	*time2 = (clock() - start) / (double)CLOCKS_PER_SEC;

	return &Tree;
}

void Graph2::MakeSet(int i){
		DadKrskl[i] = -1;
		rank[i] = 0;
		DadMaxCap[i] = -1;
		D[i] = INT_MIN;
}

int Graph2::Find(int i){
	int h = i, v;
	vector<int> S;
	while (DadKrskl[h] != -1){
		S.push_back(h);
		h = DadKrskl[h];
	}
	// Path Compression
	while (S.size() != 0){
		v = S.back();
		DadKrskl[v] = h;
		S.pop_back();
	}
	
	return h;
}

void Graph2::Union(int r1, int r2){
	if (rank[r1] > rank[r2])
		DadKrskl[r2] = r1;
	else if (rank[r1] < rank[r2])
		DadKrskl[r1] = r2;
	else{
		DadKrskl[r2] = r1;
		rank[r1]++;
	}
}
