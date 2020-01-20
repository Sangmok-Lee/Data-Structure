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
		int size();  //������ ũ�� ��ȯ 
		bool empty();  //������ ������� Ȯ�� 
		string& top();   //������ �ֻ�ܿ�� ��ȯ 
		void push(string& e);    //������ �ֻ�ܿ� ��� �߰� 
		void pop();	    //�ֻ�� ��� ���� 
		Node* header;   //������ ���� �Ʒ� ��带 ����Ŵ 
		Node* trailer;  //������ ���� �� ��带 ����Ŵ 
	protected:
		void add(Node *v, string& e);
		void remove(Node *v);
};


Stack::Stack() {          
	header = new Node;
	trailer = new Node;
	header->next = trailer;
	trailer->prev = header;
}  // ������ �����ϰ�, head�� ���� ���� trailer�� ����Ű��, trailer�� ���� ���� head�� ����Ŵ 
 
Stack::~Stack(){
	while(!empty())
	{
		pop();
	}
	delete header;
	delete trailer;
}// ������ ��� ���� ������, ���Ҹ� ��� ����. ���Ű� ������ head�� trailer ���� 

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
}// ������ ó������ �����ؼ� ����带 ������ ���� ������ ���� ����� ���� 

bool Stack::empty() {
	return header->next == trailer;
}// header��尡 ���� ���� trailer��带 ����Ű��, ������ ��� ���� 

string& Stack::top() {
	return trailer->prev->elem;
}//stack�� �� ��� ����� ��� ��ȯ 

void Stack::add(Node *v, string& e){
	Node* u = new Node;
	u->elem = e;
	u->next = v;
	u->prev = v->prev;
	v->prev->next = v->prev = u;
}//���ÿ� � ��带 �߰��ϴ� �Լ�, ��� v�տ� �����Ѵ�. 

void Stack::remove(Node* v) {
	Node* u = v->prev;
	Node* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}//��� v�� �����ϴ� �Լ� 

void Stack::push(string& e) {
	add(trailer,e);
} //stack�� �ֻ�ܿ� ��� �߰�. add �Լ� ��� 

void Stack::pop(){
	if (header->next == trailer)
	{
	}	
	else
		remove(trailer->prev);
}// stack�� �ֻ�� ��� ����. ���� ������ ����ٸ�, �ƹ��͵� �������� ���� 

//-------------------LinkedListStack ����-------------------- 

string intToString(int n){
		stringstream s;
		s << n;
		return s.str();
}

int main(void)
{
	Stack stack;
	string operation;  // �Է¹޴� ��� 
	string content;    // ������ ��� 
	string output;     // ��� ����� ������ ���ڿ� 
	
	string push = "PUSH" ; string pop = "POP"; string size = "SIZE";
	string empty = "EMPTY" ; string top = "TOP"; string quit = "QUIT";
	cout << "Stack�� �� ���� : PUSH // POP // SIZE // EMPTY // TOP // QUIT" << endl;
	while(1){
		cin >> operation;
		if (operation.compare(push)==0)  // push ���� 
		{
			cin >> content;
			stack.push(content);
		}
		else if (operation.compare(pop)==0) // pop ���� 
		{
			if (stack.empty()==1)
			{
				output += "ERROR";   //������ ���������, pop�� �������� �ʰ� error ��� 
				output += "\n"; 
			}

			else
				stack.pop();	//������ ������� ������ pop���� 
		}
		else if (operation.compare(size)==0)  // stack size���ϱ� 
		{
			output += intToString(stack.size());
			output += "\n"; 
		}
		else if (operation.compare(empty)==0)  //stack�� ������� Ȯ�� 
		{ 
			if(stack.empty()==1){
				output += "TRUE";     //������ ������� ��¿� TRUE �߰� 
				output += "\n";
		    }
			else{

				output += "FALSE";    //������ ������� ������ ��¿� FALSE �߰� 
				output += "\n";
			}
		}
		else if (operation.compare(top)==0)  //stack�� ���� ���� ��� ��ȯ 
		{
			output += stack.top();
			output += "\n";                // top(�ذ�),empty(�ذ�),size, pop���� �� ERROR ���(�ذ�) 
		}
		else if (operation.compare(quit)==0)  // ��ɾ� �ޱ� ���� 
		{ 
			break;
		}
		else
		{ 
			cout << "wrong instruction" << endl;  //��ϵ��� �ʴ� ����̸� ���� ��� 
		}
	}
	cout << endl;
	cout << output << endl;          //��� ���� ��� ��� 
}
