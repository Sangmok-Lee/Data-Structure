#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

const string operators = "(+-*/) ";  //연산자 종류(공백 포함) 
string GetPostFix(const string infixExpression);

class Node {
	public:
		char elem;
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
		char top();
		void push(char e);    //add at top (addBack)
		void pop();	    //remove the top (removeBack)
		Node* header;
		Node* trailer;
		void add(Node *v, char e);
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

char Stack::top() {
	return trailer->prev->elem;
}

void Stack::add(Node *v, char e){
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

void Stack::push(char e) {
	add(trailer,e);
}

void Stack::pop(){
	if (header->next == trailer)
		cout << "ERROR" << endl;
	else
		remove(trailer->prev);
}
//------------------------LinkedListSTACK 구현----------------------

string GetPostFix(string infixExpression)
{
	string postfixExpression;
	string::iterator i = infixExpression.begin();
	string::iterator start = infixExpression.begin();
	string::iterator end;
	
	Stack stack;
	
	for(; i != infixExpression.end(); i++)  //중위연산 읽기 
	{
		if(operators.find(*i)==string::npos)  //숫자면 바로 출력 
		{
			postfixExpression += *i;
			postfixExpression += " "; //숫자 다음 공백 넣기 
			continue;
		} 
		
		switch(*i)                //연산자 
		{ 
			case '(':
				stack.push('(');   //왼쪽괄호는 일단 스택에 넣는다 
				break;
			case ')':
				while(stack.top() != '(')    //오른쪽 괄호를 읽으면 왼쪽 괄호가 나올 때 까지 스택에 들어 있던 연산자를 꺼내서 출력 
				{
					postfixExpression += stack.top();
					postfixExpression += " ";
					stack.pop();  //꺼낸 연산자 제거 
				}
				stack.pop();  // 만약 스택의 최상위가 오른쪽 괄호면, 출력하지 않고 스택에서 제거 
				break; 
			case '+':
			case '-':           //연산우선순위가 낮은 연산자 
				while(stack.size() != 0 && stack.top() != '(')  //스택이 비어있지 않고 스택의 최상위 요소가 (가 아닌 동안 
				{
					postfixExpression += stack.top();   // 스택에 들어 있던 연산자를  표현식에 출력 
					postfixExpression += " ";
					stack.pop();  //뽑은 연산자는 삭제 
				}
				stack.push(*i);  //반복문 끝나면 읽은 연산자를 스택에 대입 
				break;
			case '*':
			case '/':           //연산우선순위가 높은 연산자 
				while(stack.size()!=0 && (stack.top()== '*'|| stack.top()== '/'))   //스택이 비어있지 않고 스택 최 상위가 * 또는 /인 동안 (연산순위가 같은 것이 없는 동안) 
				{
					postfixExpression += stack.top();   //// 스택에 들어 있던 연산자를  표현식에 출력 
					postfixExpression += " ";
					stack.pop();  //뽑은 연산자는 삭제 
				}
				stack.push(*i);  //스택의 최상위가 +또는 -인 경우, 그 위에 * 또는 /를 넣음(연산자 우선순위 구현) 
				break;
			case ' ':  //공백은 건너뜀 
				break; 
			default:   // 오류 처리 
				break;
		}
    }
	for(int i=0; i<stack.size()+1; i++ )
	{
		postfixExpression += stack.top();  // 스택에 남아 있는 연산기호를 넣는 과정 
		postfixExpression += " ";
		stack.pop();  //연산기호를 넣고 스택에 들어 있던 연산기호는 제거 
	}	
	return postfixExpression;
}

int main(void)
{
	int n;
	cin >> n;
	string *infixExpression = new string[n+1];  
	string *postfixExpression = new string[n+1];

	for (int i=0; i<n+1; i++)
	{
		getline(cin, infixExpression[i]);   // 중위연산 n개를 입력받음 
	}
	for (int i=1; i<n+1; i++)
	{
		postfixExpression[i] = GetPostFix(infixExpression[i]);  // 중위연산 n개롤 후위연산 n개로 변환 
		cout << postfixExpression[i] << endl;   // 후위연산 출력 
	}
	return 0;
}

