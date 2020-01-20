#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const int MAX_STACK_SIZE = 50;

class ArrayStack
{
	public:
		int top;
		int data[MAX_STACK_SIZE];
		
		ArrayStack() { top = -1;}
		~ArrayStack() { }
		bool isEmpty()
		{
			return top == -1;
		}
		bool isFull()
		{
			return top == MAX_STACK_SIZE-1;
		}
		
		void push(int e)
		{
			if(isFull())
				printf("스택 포화\n");
			data[++top] = e; 
		}
		
		int pop()
		{
			if(isEmpty())
				printf("스택 공백\n");
			return data[top--]; 
		}
		
		int peek(){
			if(isEmpty())
				printf("스택 공백\n");
			return data[top]; 
		}
		
};

//--------------------STACK---------------------------

class Node{
	public:
		int id;
		Node* link;
		Node* forward;
		
		Node(int i, Node *l=NULL, Node *f=NULL) : id(i), link(l), forward(l) {	}
		~Node()
		{
			if(link != NULL)
				delete link;
		}
		
		int getId() {
			return id;
		}
		
		Node* getLink(){
			return link;
		}
		
		Node* getForward(){
			return forward;
		}
		
		void setLink(Node* l){
			link = l;
		}
};

//-------------------------NODE--------------------------


#define MAX_VTXS 1000

class AdjListGraph{
	public:
		int size;
		string vertices[MAX_VTXS];
		Node* adj[MAX_VTXS];
		
		AdjListGraph() : size(0) {	}
		~AdjListGraph() { reset(); }
		void reset(void){
			for(int i=0; i<size; i++)
				if(adj[i] != NULL)
					delete adj[i];
			size = 0;
		}
		
		bool isEmpty()  {return (size==0);}
		bool isFull() { return (size>=MAX_VTXS);}
		string getVertex(int i) { return vertices[i];	}
		
		void insertVertex(string val){
			if(!isFull()){
				vertices[size] = val;
				adj[size++] = NULL;
			}
			else
				printf("Error: 그래프 정점 개수 초과\n");
				
		}
		
		void insertEdge(int u, int v){
			adj[u] = new Node(v, adj[u]);
			//adj[v] = new Node(u, adj[v]);
		}
		
};

class TopoSortGraph : public AdjListGraph{
	public:
		int inDeg[MAX_VTXS];
		vector<int> buffer;
		int count;
		
		void insertDirEdge(int u, int v){
			adj[u] = new Node(v, adj[u]);
		}
		
		void TopoSort(){
			for(int i=0; i<size; i++)
				inDeg[i] = 0;
			for(int i=0; i<size; i++){
				Node *node = adj[i];
				while(node != NULL){
					inDeg[node->getId()]++;
					node = node->getLink();
				}
			}
			
			ArrayStack s;
			for(int i=0; i<size; i++)
				if(inDeg[i] == 0)
					s.push(i);
					
			while(s.isEmpty() == false){
				int w = s.pop();
				cout << getVertex(w) << " ";
				Node *node = adj[w];
				while(node != NULL){
					int u = node->getId();
					inDeg[u]--;
					if(inDeg[u] == 0)
						buffer.push_back(u);					
						//s.push(u);
					node = node->getLink();	
				}
				while(buffer.size() != 0){
					s.push(buffer.back());
					buffer.pop_back();
				}	
			}
			printf("\n");
		}
};

int main(void)
{
	TopoSortGraph g;
	int vertexnum;
	int edgenum;
	string vertexname;
	int start;
	int end;
	
	cin >> vertexnum;
	cin >> edgenum;
	/*if(vertexnum > 1000 || edgenum > 2*vertexnum*(vertexnum-1)){
		printf("Wrong value! Enter vertexnum <= 1000 & edgenum <= 2n(n-1)\n");
		cin >> vertexnum;
		cin >> edgenum;
	}*/
	
	for(int i=0; i<vertexnum; i++){
		cin >> vertexname;
		g.insertVertex(vertexname);
	}	

	
	for(int j=0; j<edgenum; j++){
		cin >> start;
		cin >> end;
		g.insertDirEdge(start,end);
	}
	g.TopoSort();
}
