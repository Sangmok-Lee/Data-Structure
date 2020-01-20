#include <cstdio>
#include <string.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class VectorCompleteTree{
	private:
		vector<int> V; //heap이 될 completebiarytree 
		vector<int> Vcopy; //heap의 내용을 복사할 벡터 
		vector<int> minValues;  //heap의 n개의 최솟값을 저장할 벡터 
	public:
		typedef typename std::vector<int>::iterator Position;  //tree의 위치를 position이라 정의 
		string output;  //결과를 한꺼번에 출력할 string 
	protected:
		Position pos(int i){    
			return V.begin() + i;
 		}
 		int idx(const Position& p) const{
			return p-V.begin();
		}
	public:
		int min;
		VectorCompleteTree() : V(1) {	}
		int size() const {
			return V.size()-1;  
		}
		Position left(const Position& p){
			return pos(2*idx(p));
		} 
		Position right(const Position& p){
			return pos(2*idx(p)+1);
		}
		Position parent(const Position& p){
			return pos(idx(p)/2);
		} 
		bool hasLeft(const Position& p) const {
			return 2*idx(p) <= size();
		} 
		bool hasRight(const Position& p) const{
			return 2*idx(p) + 1 <= size();
		} 
		bool isRoot(const Position& p) const{
			return idx(p)==1;
		}
		Position root(){
			return pos(1);
		} 
		Position last(){
			return pos(size());
		} 
		void addLast(const int& e){
			V.push_back(e);
		}
		void removeLast(){
			V.pop_back();
		} 
		void swap(const Position& p, const Position& q){
			int e = *q;
			*q = *p;
			*p = e;
		}
		void vectorcopy(){
			Vcopy.clear();
			Vcopy.assign(V.begin()+1,V.end());
		} 
		void vectorNstore(int num){
			minValues.clear(); 
			if (Vcopy.size()<num){
				minValues.assign(Vcopy.begin(), Vcopy.end());
			}
			else{
				for(int i=0; i<num; i++){
					min = *min_element(Vcopy.begin(), Vcopy.end());
					minValues.push_back(min);
					Vcopy.erase(min_element(Vcopy.begin(), Vcopy.end()));
				}
		   }
		} 
		void vectorNmin(){
			for(int i=0; i<minValues.size(); i++){
				output += intToString(minValues[i]);
				output += " ";
			}
			output += "\n";
		} 
		void printNmin(){
			cout << output << endl;
		} 
		string intToString(int n){
			stringstream s;
			s << n;
			return s.str();
		} // 정수를 string타입으로 변환 

};

class HeapPriorityQueue{
	public:
		int size() const; 
		bool empty() const;
		void insert(const int& e); 
		const int& min(); 
		void removeMin();
		void removeLast();	
		VectorCompleteTree T; 
		int isLess(int a, int b);
		void heapcopy(); 
		void heapNstore(int num); 
		void heapNmin();
		void printheapNmin(); 
		typedef typename VectorCompleteTree::Position Position;  
};

int HeapPriorityQueue::size() const{
	return T.size();
}

bool HeapPriorityQueue::empty() const{
	return T.size() == 0;
}
const int& HeapPriorityQueue::min(){
	return *(T.root());
}
void HeapPriorityQueue::insert(const int& e){
	T.addLast(e);
	Position v = T.last();
		while(!T.isRoot(v)){
			Position u = T.parent(v);
			if(!isLess(*v, *u))
				break;
			T.swap(v,u);
			v = u;
		}
}
void HeapPriorityQueue::removeMin(){
	if(size() == 1)
		T.removeLast();
	else{
		Position u = T.root();
		T.swap(u,T.last());
		T.removeLast();
		while(T.hasLeft(u)){
			Position v = T.left(u);
			if(T.hasRight(u) && isLess(*(T.right(u)),*v));
				v = T.right(u);
			if(isLess(*v, *u)){
				T.swap(u,v);
				u = v;
			}
			else
				break;
		}	
	}
}

void HeapPriorityQueue::heapcopy() {
	T.vectorcopy();
} 

void HeapPriorityQueue::heapNstore(int num){
	T.vectorNstore(num);
}

void HeapPriorityQueue::heapNmin(){ 
	T.vectorNmin();
} 

void HeapPriorityQueue::printheapNmin(){
	T.printNmin();
}

int HeapPriorityQueue::isLess(int a, int b){
	if (a<b)
		return true;
	else
		return false;
} 


int main(void){
	int num;
	int element;
	string output;
	cin >> num;
	HeapPriorityQueue Q;
	while(1){
		cin >> element;
		if (cin.good()){
			Q.insert(element);  // 값을 하나씩 넣음 
			Q.heapcopy();  // heap의 내용을 복사 
			Q.heapNstore(num); // heap의 num개의 최솟값 저장 
			Q.heapNmin();  // 단계별 num개의 최솟값을 output에 저장 
		}
		else if (cin.fail())
			break;
	}
	Q.printheapNmin();  // output 출력 
}

    
