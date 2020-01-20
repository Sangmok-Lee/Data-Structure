#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define MAX_VTXS 200

class AdjMatGraph{
	public:
		int size;
		string vertices[MAX_VTXS];
		int adj[MAX_VTXS][MAX_VTXS];  //그래프 원본 2차원 배 
		
		AdjMatGraph() { reset();}
		string getVertex(int i) { return vertices[i];}
		int getEdge(int i, int j) { return adj[i][j];	}
		void setEdge(int i, int j, int val) { adj[i][j] = val;		}
		
		bool isEmpty() {return size == 0;		}
		bool isFull() {return size>=MAX_VTXS;		}
		
		void reset(){
			size = 0;
			for(int i=0; i<MAX_VTXS; i++){
				for(int j=0; j<MAX_VTXS; j++)
					setEdge(i,j,0);
			}	
		}
		
		 void insertVertex(string name){
		 	if(!isFull())
		 		vertices[size++] = name;
		 	else
		 		printf("Error : 개수 초과\n");
		 }
		 
};

//----------------------AdjMatrixGraph--------------------

#define INFINITE 9999

class WGraph : public AdjMatGraph{
	public:
		void insertEdge(int u, int v, int weight){
			if(weight > INFINITE)
				weight = INFINITE;
			setEdge(u,v,weight);
		}
		
		bool hasEdge(int i, int j){
			return (getEdge(i,j)<INFINITE);
		}
};

//------------------WeightedGraph---------------------

class WGraphShortest : public WGraph{
	public: 
		int A[MAX_VTXS][MAX_VTXS];
		
		void ShortestPathFind(int vertexN){
			for(int i=0; i<vertexN; i++){
				for(int j=0; j<vertexN; j++){
					A[i][j] = adj[i][j]; //원본 그래프를 새 배열에 복사 
				}
			}
			
			for(int k=0; k<vertexN; k++){
				for(int i=0; i<vertexN; i++){
					for(int j=0; j<vertexN; j++){
						if(A[i][k]+A[k][j] < A[i][j])
							A[i][j] = A[i][k]+A[k][j];
					}
				}
				//printA();
			}
		}
		
		/*void printA(){
			printf("==================================\n");
			for(int i=0; i<size; i++){
				for(int j=0; j<size; j++){
					if(A[i][j] == INFINITE)
						printf(" INF ");
					else
						printf("%4d", A[i][j]);
				}
				printf("\n");
			}
		}*/
};


int main(void)
{
	WGraphShortest g;
	vector<string> names;
	int vertexnum;
	int edgenum;
	string startpoint;
	string destination;
	string vertexname;
	string s;  int sidx;
	string e;  int eidx;
	int weight;
	
	int sp; int dp;
	
	
	cin >> vertexnum;
	cin >> edgenum;
	/*if(vertexnum > 200 || edgenum > 10000){
		printf("Wrong value! Enter vertexnum <=200 & edgenum <=10000\n");
		cin >> vertexnum;
		cin >> edgenum;
	}*/
	cin >> startpoint;
	cin >> destination;
	
	for(int i=0; i<vertexnum; i++){
		for(int j=0; j<vertexnum; j++){
			g.adj[i][j] = 9999;
		}
	}
	for(int i=0; i<vertexnum; i++){
		g.adj[i][i] = 0;
	}
	
	for(int i=0; i<vertexnum; i++){
		cin >> vertexname;
		g.insertVertex(vertexname);
		names.push_back(vertexname);
		
	}		
	for(int j=0; j<edgenum; j++){
		cin >> s;
		cin >> e;
		cin >> weight;
		for(int k=0; k<vertexnum; k++){
			if (names[k] == s)
				sidx = k;
			if (names[k] == e)
				eidx = k;
		}
		g.insertEdge(sidx,eidx,weight);
		g.insertEdge(eidx,sidx,weight);
	}
	
	g.ShortestPathFind(vertexnum);
	
	for(int p=0; p<vertexnum; p++){
		if(names[p] == startpoint)
			sp = p;
		if(names[p] == destination)
			dp = p;
	}
	
	/*for(int i=0; i<vertexnum; i++){
		int k=0;
		for(int j=0; j<vertexnum; j++){
			printf("%4d ",g.adj[i][j]);// g.adj[i][j] << "    ";
			k++;
			if (k==8){
				cout << endl;
				k = 0;
			}
		}
	}
	
	printf("\n");
	
	for(int i=0; i<vertexnum; i++){
		int k=0;
		for(int j=0; j<vertexnum; j++){
			printf("%4d ",g.A[i][j]);// g.adj[i][j] << "    ";
			k++;
			if (k==8){
				cout << endl;
				k = 0;
			}
		}
	}*/
	
	cout << startpoint << " " << destination << " " << g.A[sp][dp] << endl;
	
}
