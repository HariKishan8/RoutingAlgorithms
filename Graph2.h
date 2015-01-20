// Header==> Function Declarations


#include <fstream>
#include <iostream>
using namespace std;
#include <string>
#include <set>
#include <cstdlib>
#include <vector>
#include <queue>
#include <list>
#include <time.h>

#ifndef GRAPH2_H
#define GRAPH2_H

#define INTREE 0
#define FRINGE 1
#define UNSEEN 2


struct Edge{
	int src;
	int dest;
	int wt;
};

struct EdgeList{
	vector<Edge> Edges;
	int noOfEdges;
};

class Graph2 {
private:
	vector< vector<int> > adjMatrix;
	int noOfVertices;
	vector<int> edgeCount;
	EdgeList eList;
	vector<int> D;
	vector<int> status;
	vector<int> DadMaxCap;
	vector<int> DadKrskl;
	vector<int> rank;
public:
	Graph2(int noOfVertices);
	~Graph2();
	int getNoOfVertices(){ return noOfVertices; };
	vector<int> getEdgeCount(){ return edgeCount; };
	vector<int> getDistance(){ return D; };
	vector<int> getDadMaxCap(){ return DadMaxCap; };
	EdgeList* getEList(){ return &eList; };

	void addEdge(int i, int j, int wt);
	void removeEdge(int i, int j);
	bool isEdge(int i, int j);
	void generateGraph(int vertexDegree, int range);
	void writeGraph(string);

	int MaxDistVertex();
	void DkstrMaxCap(int Src, int Dest, double* time);
	void DkstrMaxCapMaxHeap(int s, int t, double* time);
	
	EdgeList* KruskalMaxCap(int s, int t, double* time1, double* time2);
	//Graph2* KruskalMaxCap(int s, int t);
	void MakeSet(int i);
	int Find(int i);
	void Union(int r1, int r2);
	void DFS(int v);
	void DFSVisit(int v, bool visited[]);

	void pickandGenPath(int* s, int* t);
};



#endif