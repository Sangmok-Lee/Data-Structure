#include <cstdio>
#include <cstring>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;

int table_size = 10;
int new_table_size = 20; //사용하지 않는 변수 

inline int transform(string key){
	int number = 0;
	number = key.size();
	return number;
}// 문자열로 된 키를 숫자로 변환 

inline int hashFunction(string key){
	return transform(key) % table_size;
}// 변환한 수의 나머지를 구하는 함수 


class Node{
	public: 
		string key;
		string value;
		Node* link; //다음 노드를 가리킴 
		Node(string k = "", string v = "", Node* link = NULL){
			set(k,v);
			link = NULL;
		}
		void set(string k, string v){
			key = k;
			value = v;
		}
		void reset(){
			set(" ",0);
		}
		bool isEmpty(){
			return key == "";
		}
		bool equal(string k){
			return !k.compare(key);
		}
		string display(){
			return value;
		}
		Node* getLink(){
			return link;
		}
		void setLink(Node* next){
			link = next;
		}
		string getKey(){
			return key;
		}
};


class HashChainMap{
		Node *table = new Node[table_size];
		//Node *newtable = new Node[new_table_size]; 사용하지 않는 부 
		
	public:
		double entrynum = 0;
		HashChainMap(){
			for(int i=0; i<table_size; i++){
				(table+i)->link = NULL;
			}
		}
		
		string addEntry(string key, string value){
			int hashValue = hashFunction (key);
			for(Node *p = table+hashValue ; p != NULL; p=p->getLink()){
				if(p->equal(key)){
					p->set(" ", " ");
					entrynum --;
				}
			} 
			Node* n = new Node;
			n->set(key,value);
			Node* p = (table+hashValue) -> link;
			(table+hashValue) -> link = n;
			n->link = p;
			entrynum = entrynum + 1;
			
			if((entrynum)/table_size >= 0.5){
				table_size = 20;
				Node *newtable = new Node[table_size];
				for(int i=0; i<table_size; i++){
					(newtable+i)->link = (table+i) -> link;
				}
				Node* old = table;
				table = newtable;
				delete [] old; 
				
				return "REHASHING\n";
			}
			else
				return "";
				
		}
		
		string searchEntry(string key){
			int hashValue = hashFunction(key);
			for(Node *p= table+hashValue; p != NULL; p=p->getLink()){
				if(p->equal(key)){
					//printf("탐색 성공\n");  //test용 
					return p->display();
				}		
			}
			return "NOT FOUND";
		}
		
		void eraseEntry(string key){
			int hashValue = hashFunction(key);
			for(Node *p=(table+hashValue); p != NULL; p=p->getLink()){
				if(p->equal(key)){
					p->set(" "," ");
					entrynum--;
				}
			}
		}
};

string doubleTostring(double n){
		stringstream s;
		s << n;
		return s.str();
}

int main(void){
	HashChainMap hash;
	string operation;
	string key;
	string value;
	string output;
	string find = "FIND" ; string put = "PUT"; string erase = "ERASE";
	string size = "SIZE" ; string exit = "EXIT";
	while(1){
		cin >> operation;
		if (operation.compare(find)==0)  //find 
		{
			cin >> key;
			output += hash.searchEntry(key);
			output += "\n";
		}
		else if (operation.compare(put)==0) //entry 추 
		{
			cin >> key;
			cin >> value;
			output += hash.addEntry(key,value);
		}
		else if (operation.compare(erase)==0)
		{
			cin >> key;
			hash.eraseEntry(key);
		}
		else if (operation.compare(size)==0)
		{
			output += doubleTostring(hash.entrynum);
			output += " ";
			output += doubleTostring(table_size);
			output += " ";
			output += doubleTostring((hash.entrynum)/(table_size));
			output += "\n";
		}		
		else if (operation.compare(exit)==0)
		{
			break;
		}
		else
			cout << "wrong instruction" << endl;
			
			
	}
	cout << endl;
	cout << output << endl;          //명령 실행 결과 출력 

}
