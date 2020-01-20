#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

const string operators = "(+-*/) ";
double Calculate(const string postfixExpression);

class Node {
	public:
		double elem;
		Node* prev;
		Node* next;
		friend class Stack;	
};

class Stack {
	public:
		Stack();
		~Stack();
		int size();
		bool empty();
		double top();
		void push(double e);    //add at top (addBack)
		void pop();	    //remove the top (removeBack)
		Node* header;
		Node* trailer;
	protected:
		void add(Node *v, double e);
		void remove(Node *v);
};


Stack::Stack() {
	header = new Node;
	trailer = new Node;
	header->next = trailer;
	trailer->prev = header;
}

Stack::~Stack(){
	while(!empty())
	{
		pop();
	}
	delete header;
	delete trailer;
}

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
}
bool Stack::empty() {
	return header->next == trailer;
}

double Stack::top() {
	return trailer->prev->elem;
}

void Stack::add(Node *v, double e){
	Node* u = new Node;
	u->elem = e;
	u->next = v;
	u->prev = v->prev;
	v->prev->next = v->prev = u;
}

void Stack::remove(Node* v) {
	Node* u = v->prev;
	Node* w = v->next;
	u->next = w;
	w->prev = u;
	delete v;
}

void Stack::push(double e) {
	add(trailer,e);
}

void Stack::pop(){
	if (header->next == trailer)
		cout << "ERROR" << endl;
	else
		remove(trailer->prev);
}

//-----------Stack-------------

double Calculate(const string postfixExpression)
{
	Stack stack;  // ���ڸ� ������ ���� 
	string token = "����ǥ����� ���� �ϳ��� ������ ����//�ϴ� ������ �������� ����";

	stringstream temp(postfixExpression);  //temp��� string�� ����ǥ����� �ִ´�. 
	while(!temp.eof())
	{
		temp >> token;        //token���� ����ǥ������� �� ���ھ� ���� ���� ����. 
		if (operators.find(token) == string::npos)   // token�� �����̸� 
		{
			double num;
			stringstream(token) >> num;    //token�� �ӽ� ���� ������ �ִ´�. 
			stack.push(num);             // �ӽ� ���� ������ ������ stack�� �ִ´�. 
		}
		else                               // ���� ���ڰ� �����ȣ�̸�, 
		{
			double op1, op2;
			op2 = stack.top();            // op2 : ����stack�� ���� ���� ���� 
			stack.pop();
			op1 = stack.top();            // op1 : ����stack�� ������ 2��° ����. ���ڰ� ����ִ� ���ÿ��� ���� 2���� ������.
			stack.pop();
			switch (operators[operators.find(token)])    // ���� ���� ��ȣ�� ���� ������ ������ �޶�����. 
			{
			case '+':
				stack.push(op1 + op2); break;
			case '-':
				stack.push(op1 - op2); break;
			case '*':
				stack.push(op1 * op2); break;
			case '/':
				stack.push(op1 / op2); break;
			}// ���� ����� ���ڰ� ����ִ� stack�� �ִ´�. 
		}
	}

	return stack.top();  // �ݺ����� ������, ���ÿ� �����ִ� �� ���� ��Ҹ� ������. �̰��� ������ ���� ����̴�. 
}


int main()
{
	int n;
    cin >> n;
    string *postfixExpression = new string[n+1];
    int *result = new int[n];
    for (int i=0; i<n+1; i++){
    	getline(cin, postfixExpression[i]);         // ���� ���� �Է¹ޱ� ���� getline ��� 
	}
	for (int i=0; i<n+1; i++){
		result[i] = Calculate(postfixExpression[i]);  // �������� ������ �迭�� ���� ����� ���� 
	}
	for (int i=1; i<n+1; i++){
		cout << result[i] << endl;    //n���� ���� ��� ��� 
	}
}
