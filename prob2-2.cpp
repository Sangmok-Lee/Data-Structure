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
	Stack stack;  // 숫자를 저장할 스택 
	string token = "후위표기법의 글자 하나를 저장할 변수//일단 임의의 내용으로 선언";

	stringstream temp(postfixExpression);  //temp라는 string에 후위표기법을 넣는다. 
	while(!temp.eof())
	{
		temp >> token;        //token에는 후위표기법에서 한 글자씩 읽은 것이 들어간다. 
		if (operators.find(token) == string::npos)   // token이 숫자이면 
		{
			double num;
			stringstream(token) >> num;    //token을 임시 숫자 변수에 넣는다. 
			stack.push(num);             // 임시 숫자 변수의 내용을 stack에 넣는다. 
		}
		else                               // 읽은 글자가 연산기호이면, 
		{
			double op1, op2;
			op2 = stack.top();            // op2 : 숫자stack의 가장 위의 숫자 
			stack.pop();
			op1 = stack.top();            // op1 : 숫자stack의 위에서 2번째 숫자. 숫자가 들어있는 스택에서 숫자 2개를 꺼낸다.
			stack.pop();
			switch (operators[operators.find(token)])    // 읽은 연산 기호에 따라서 연산의 종류가 달라진다. 
			{
			case '+':
				stack.push(op1 + op2); break;
			case '-':
				stack.push(op1 - op2); break;
			case '*':
				stack.push(op1 * op2); break;
			case '/':
				stack.push(op1 / op2); break;
			}// 연산 결과를 숫자가 들어있는 stack에 넣는다. 
		}
	}

	return stack.top();  // 반복문이 끝나면, 스택에 남아있는 한 개의 요소를 꺼낸다. 이것이 연산의 최종 결과이다. 
}


int main()
{
	int n;
    cin >> n;
    string *postfixExpression = new string[n+1];
    int *result = new int[n];
    for (int i=0; i<n+1; i++){
    	getline(cin, postfixExpression[i]);         // 공백 포함 입력받기 위해 getline 사용 
	}
	for (int i=0; i<n+1; i++){
		result[i] = Calculate(postfixExpression[i]);  // 연산결과를 저장할 배열에 연산 결과를 저장 
	}
	for (int i=1; i<n+1; i++){
		cout << result[i] << endl;    //n개의 연산 결과 출력 
	}
}
