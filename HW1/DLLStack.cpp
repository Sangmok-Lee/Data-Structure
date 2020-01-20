#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream> 
using namespace std;

class Node {
	public:
		string elem;
		Node* prev;
		Node* next;
		friend class Stack;	
};

class Stack {
	public:
		Stack();
		~Stack();
		int size();  //스택의 크기 반환 
		bool empty();  //스택이 비었는지 확인 
		string& top();   //스택의 최상단요소 반환 
		void push(string& e);    //스택의 최상단에 요소 추가 
		void pop();	    //최상단 요소 제거 
		Node* header;   //스택의 가장 아래 노드를 가리킴 
		Node* trailer;  //스택의 가장 위 노드를 가리킴 
	protected:
		void add(Node *v, string& e);
		void remove(Node *v);
};


Stack::Stack() {          
	header = new Node;
	trailer = new Node;
	header->next = trailer;
	trailer->prev = header;
}  // 스택을 생성하고, head는 다음 노드로 trailer를 가리키고, trailer는 이전 노드로 head를 가리킴 
 
Stack::~Stack(){
	while(!empty())
	{
		pop();
	}
	delete header;
	delete trailer;
}// 스택이 비어 있지 않으면, 원소를 계속 제거. 제거가 끝나면 head와 trailer 삭제 

int Stack::size(){
	Node* n = new Node;
	int count;
	n = header->next;
	while(n != trailer)
	{
		n = n->next;
		count++;
	}
	return count;
}// 스택의 처음부터 시작해서 끝노드를 접근할 동안 증가한 수가 노드의 개수 

bool Stack::empty() {
	return header->next == trailer;
}// header노드가 다음 노드로 trailer노드를 가리키면, 스택은 비어 있음 

string& Stack::top() {
	return trailer->prev->elem;
}//stack의 최 상단 노드의 요소 반환 

void Stack::add(Node *v, string& e){
	Node* u = new Node;
	u->elem = e;
	u->next = v;
	u->prev = v->prev;
	v->prev->next = v->prev = u;
}//스택에 어떤 노드를 추가하는 함수, 노드 v앞에 저장한다. 

void Stack::remove(Node* v) {
	Node* u = v->prev;
	Node* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}//노드 v를 삭제하는 함수 

void Stack::push(string& e) {
	add(trailer,e);
} //stack의 최상단에 노드 추가. add 함수 사용 

void Stack::pop(){
	if (header->next == trailer)
	{
	}	
	else
		remove(trailer->prev);
}// stack의 최상단 노드 제거. 만약 스택이 비었다면, 아무것도 실행하지 않음 

//-------------------LinkedListStack 구현-------------------- 

string intToString(int n){
		stringstream s;
		s << n;
		return s.str();
}

int main(void)
{
	Stack stack;
	string operation;  // 입력받는 명령 
	string content;    // 스택의 요소 
	string output;     // 출력 결과를 저장할 문자열 
	
	string push = "PUSH" ; string pop = "POP"; string size = "SIZE";
	string empty = "EMPTY" ; string top = "TOP"; string quit = "QUIT";
	cout << "Stack에 할 연산 : PUSH // POP // SIZE // EMPTY // TOP // QUIT" << endl;
	while(1){
		cin >> operation;
		if (operation.compare(push)==0)  // push 연산 
		{
			cin >> content;
			stack.push(content);
		}
		else if (operation.compare(pop)==0) // pop 연산 
		{
			if (stack.empty()==1)
			{
				output += "ERROR";   //스택이 비어있으면, pop을 실행하지 않고 error 출력 
				output += "\n"; 
			}

			else
				stack.pop();	//스택이 비어있지 않으면 pop실행 
		}
		else if (operation.compare(size)==0)  // stack size구하기 
		{
			output += intToString(stack.size());
			output += "\n"; 
		}
		else if (operation.compare(empty)==0)  //stack이 비었는지 확인 
		{ 
			if(stack.empty()==1){
				output += "TRUE";     //스택이 비었으면 출력에 TRUE 추가 
				output += "\n";
		    }
			else{

				output += "FALSE";    //스택이 비어있지 않으면 출력에 FALSE 추가 
				output += "\n";
			}
		}
		else if (operation.compare(top)==0)  //stack의 가장 위의 요소 반환 
		{
			output += stack.top();
			output += "\n";                // top(해결),empty(해결),size, pop했을 때 ERROR 출력(해결) 
		}
		else if (operation.compare(quit)==0)  // 명령어 받기 종료 
		{ 
			break;
		}
		else
		{ 
			cout << "wrong instruction" << endl;  //등록되지 않는 명령이면 오류 출력 
		}
	}
	cout << endl;
	cout << output << endl;          //명령 실행 결과 출력 
}
