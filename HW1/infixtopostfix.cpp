#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

const string operators = "(+-*/) ";  //������ ����(���� ����) 
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
//------------------------LinkedListSTACK ����----------------------

string GetPostFix(string infixExpression)
{
	string postfixExpression;
	string::iterator i = infixExpression.begin();
	string::iterator start = infixExpression.begin();
	string::iterator end;
	
	Stack stack;
	
	for(; i != infixExpression.end(); i++)  //�������� �б� 
	{
		if(operators.find(*i)==string::npos)  //���ڸ� �ٷ� ��� 
		{
			postfixExpression += *i;
			postfixExpression += " "; //���� ���� ���� �ֱ� 
			continue;
		} 
		
		switch(*i)                //������ 
		{ 
			case '(':
				stack.push('(');   //���ʰ�ȣ�� �ϴ� ���ÿ� �ִ´� 
				break;
			case ')':
				while(stack.top() != '(')    //������ ��ȣ�� ������ ���� ��ȣ�� ���� �� ���� ���ÿ� ��� �ִ� �����ڸ� ������ ��� 
				{
					postfixExpression += stack.top();
					postfixExpression += " ";
					stack.pop();  //���� ������ ���� 
				}
				stack.pop();  // ���� ������ �ֻ����� ������ ��ȣ��, ������� �ʰ� ���ÿ��� ���� 
				break; 
			case '+':
			case '-':           //����켱������ ���� ������ 
				while(stack.size() != 0 && stack.top() != '(')  //������ ������� �ʰ� ������ �ֻ��� ��Ұ� (�� �ƴ� ���� 
				{
					postfixExpression += stack.top();   // ���ÿ� ��� �ִ� �����ڸ�  ǥ���Ŀ� ��� 
					postfixExpression += " ";
					stack.pop();  //���� �����ڴ� ���� 
				}
				stack.push(*i);  //�ݺ��� ������ ���� �����ڸ� ���ÿ� ���� 
				break;
			case '*':
			case '/':           //����켱������ ���� ������ 
				while(stack.size()!=0 && (stack.top()== '*'|| stack.top()== '/'))   //������ ������� �ʰ� ���� �� ������ * �Ǵ� /�� ���� (��������� ���� ���� ���� ����) 
				{
					postfixExpression += stack.top();   //// ���ÿ� ��� �ִ� �����ڸ�  ǥ���Ŀ� ��� 
					postfixExpression += " ";
					stack.pop();  //���� �����ڴ� ���� 
				}
				stack.push(*i);  //������ �ֻ����� +�Ǵ� -�� ���, �� ���� * �Ǵ� /�� ����(������ �켱���� ����) 
				break;
			case ' ':  //������ �ǳʶ� 
				break; 
			default:   // ���� ó�� 
				break;
		}
    }
	for(int i=0; i<stack.size()+1; i++ )
	{
		postfixExpression += stack.top();  // ���ÿ� ���� �ִ� �����ȣ�� �ִ� ���� 
		postfixExpression += " ";
		stack.pop();  //�����ȣ�� �ְ� ���ÿ� ��� �ִ� �����ȣ�� ���� 
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
		getline(cin, infixExpression[i]);   // �������� n���� �Է¹��� 
	}
	for (int i=1; i<n+1; i++)
	{
		postfixExpression[i] = GetPostFix(infixExpression[i]);  // �������� n���� �������� n���� ��ȯ 
		cout << postfixExpression[i] << endl;   // �������� ��� 
	}
	return 0;
}

