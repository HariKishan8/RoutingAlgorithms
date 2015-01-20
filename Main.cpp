
using namespace std;
#include "Graph2.h"
#include <iostream>
#include <cstdlib>

#include <algorithm>


int main(){
	
	vector<int> D1, D2, D3;
	clock_t diff;
	clock_t start;
	double time, time2;
	int Src = 1, Dest = 1, i;
//	vector<int> Dad1, Dad2, Dad3;

/*
	ofstream GraphG1;
	GraphG1.open("Results.txt");
	if (!(GraphG1.is_open())){
		cout << "Unable to Open File" << endl;
		system("pause");
		return 0;
	}*/
	
	for (int i = 0; i < 5; i++){
		Graph2 TestG(5000);
		cout << "Generating Sparse Graph " << i << ".." << endl;
		TestG.generateGraph(6, 0); // Exact Degree 6, hence range is 0
		//	TestG.writeGraph("TestG.txt");

		for (int j = 0; j < 5; j++){
			cout << "Picking s and t and creating a path through all vertices.." << endl;
			TestG.pickandGenPath(&Src, &Dest);
			cout << "Source s: " << Src << endl;
			cout << "Destination t: " << Dest << endl;

			cout << "Running Dijkstras without Heap.." << endl;
			TestG.DkstrMaxCap(Src, Dest, &time);
			D1 = TestG.getDistance();
			//Dad1 = TestG.getDadMaxCap();
			cout << "Maximum Bandwidth: " << D1[Dest] << endl;
			cout << "Time Taken in sec: " << time << endl << endl;

			cout << "Running Dijkstras with Heap.." << endl;
			TestG.DkstrMaxCapMaxHeap(Src, Dest, &time);
			D2 = TestG.getDistance();
			//Dad2 = TestG.getDadMaxCap();
			cout << "Maximum Bandwidth: " << D2[Dest] << endl;
			cout << "Time Taken in sec: " << time << endl << endl;

			cout << "Running Kruskal with Heapsort.." << endl;
			TestG.KruskalMaxCap(Src, Dest, &time, &time2);
			D3 = TestG.getDistance();
			//Dad3 = TestG.getDadMaxCap();
			cout << "Maximum Bandwidth: " << D3[Dest] << endl;
			cout << "Time Taken for Max Spanning Tree in sec: " << time << endl;
			cout << "Time Taken including DFS to find Dad Array in sec: " << time2 << endl << endl;

			//	i = Dest;
			//while (i != Src)
			//{
			//	cout << "Dad3[" << i << "]: " << Dad3[i] << endl << endl;
			//	i = Dad3[i];
			//}
		}
		TestG.~Graph2();

		Graph2 TestG2(5000);
		cout << "Generating Dense Graph" << i << ".." << endl;
		TestG2.generateGraph(1000, 50); // about 20%, hence range is taken as 50 i.e., degree from 950 to 1000
		//	TestG.writeGraph("TestG.txt");

		for (int j = 0; j < 5; j++){
			cout << "Picking s and t and creating a path through all vertices.." << endl;
			TestG2.pickandGenPath(&Src, &Dest);
			cout << "Source s: " << Src << endl;
			cout << "Destination t: " << Dest << endl;

			cout << "Running Dijkstras without Heap.." << endl;
			TestG2.DkstrMaxCap(Src, Dest, &time);
			D1 = TestG2.getDistance();
			//Dad1 = TestG.getDadMaxCap();
			cout << "Maximum Bandwidth: " << D1[Dest] << endl;
			cout << "Time Taken in sec: " << time << endl << endl;

			cout << "Running Dijkstras with Heap.." << endl;
			TestG2.DkstrMaxCapMaxHeap(Src, Dest, &time);
			D2 = TestG2.getDistance();
			//Dad2 = TestG.getDadMaxCap();
			cout << "Maximum Bandwidth: " << D2[Dest] << endl;
			cout << "Time Taken in sec: " << time << endl << endl;

			cout << "Running Kruskal with Heapsort.." << endl;
			TestG2.KruskalMaxCap(Src, Dest, &time, &time2);
			D3 = TestG2.getDistance();
			//Dad3 = TestG.getDadMaxCap();
			cout << "Maximum Bandwidth: " << D3[Dest] << endl;
			cout << "Time Taken for Max Spanning Tree in sec: " << time << endl;
			cout << "Time Taken including DFS to find Dad Array in sec: " << time2 << endl << endl;

			//	i = Dest;
			//while (i != Src)
			//{
			//	cout << "Dad3[" << i << "]: " << Dad3[i] << endl << endl;
			//	i = Dad3[i];
			//}
		}
		TestG2.~Graph2();
	}

	/*for (int i = 0; i < 5; i++){
		Graph2 TestG(5000);
		cout << "Generating Dense Graph" << i << ".." << endl;
		TestG.generateGraph(1000, 50); // about 20%, hence range is taken as 50 i.e., degree from 950 to 1000
		//	TestG.writeGraph("TestG.txt");

		for (int j = 0; j < 5; j++){
			cout << "Picking s and t and creating a path through all vertices.." << endl;
			TestG.pickandGenPath(&Src, &Dest);
			cout << "Source s: " << Src << endl;
			cout << "Destination t: " << Dest << endl;

			cout << "Running Dijkstras without Heap.." << endl;
			TestG.DkstrMaxCap(Src, Dest, &time);
			D1 = TestG.getDistance();
			//Dad1 = TestG.getDadMaxCap();
			cout << "Maximum Bandwidth: " << D1[Dest] << endl;
			cout << "Time Taken in sec: " << time << endl << endl;

			cout << "Running Dijkstras with Heap.." << endl;
			TestG.DkstrMaxCapMaxHeap(Src, Dest, &time);
			D2 = TestG.getDistance();
			//Dad2 = TestG.getDadMaxCap();
			cout << "Maximum Bandwidth: " << D2[Dest] << endl;
			cout << "Time Taken in sec: " << time << endl << endl;

			cout << "Running Kruskal with Heapsort.." << endl;
			TestG.KruskalMaxCap(Src, Dest, &time, &time2);
			D3 = TestG.getDistance();
			//Dad3 = TestG.getDadMaxCap();
			cout << "Maximum Bandwidth: " << D3[Dest] << endl;
			cout << "Time Taken for Max Spanning Tree in sec: " << time << endl;
			cout << "Time Taken including DFS to find Dad Array in sec: " << time2 << endl << endl;

			//	i = Dest;
			//while (i != Src)
			//{
			//	cout << "Dad3[" << i << "]: " << Dad3[i] << endl << endl;
			//	i = Dad3[i];
			//}
		}
		TestG.~Graph2();
	}*/
	
	system("pause");
	return 0;
}