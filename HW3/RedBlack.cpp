#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;  

typedef int ElementType;

vector<int> v;// 넣은 키들 저장 

typedef struct Node
{
public:
	struct Node* Parent;
	struct Node* Left;
	struct Node* Right;
	
	int Color;  //0은 Black, 1은 Red 
	
	ElementType Data;

} RBTNode;

void RBT_DestroyTree(RBTNode* Tree);

RBTNode* RBT_CreateNode(ElementType NewData);
void RBT_DestroyNode(RBTNode* Node);

RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target);
RBTNode* RBT_SearchMinNode(RBTNode* Tree);
string RBT_InsertNode(RBTNode** Tree, RBTNode *NewNode); //string
void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode); //string
RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Target);
void RBT_RebuildAfterInsert(RBTNode** Tree, RBTNode* NewNode);
void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* X);

string RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount);  //string
void RBT_RotateLeft(RBTNode** Root, RBTNode* Parent);
void RBT_RotateRight(RBTNode** Root, RBTNode* Parent); 
string intTostring(int n);

/*----------------------------함수 목록----------------------------------------*/


extern RBTNode* Nil;

RBTNode* RBT_CreateNode( ElementType NewData )
{
    RBTNode* NewNode = (RBTNode*)malloc( sizeof(RBTNode) );
    NewNode->Parent  = NULL;
    NewNode->Left    = NULL;
    NewNode->Right   = NULL;
    NewNode->Data    = NewData;
    NewNode->Color = 0;

    return NewNode;
}

void RBT_DestroyNode( RBTNode* Node )
{
    free(Node);
}

void RBT_DestroyTree( RBTNode* Tree )
{
    if ( Tree->Right != Nil )
        RBT_DestroyTree( Tree->Right );

    if ( Tree->Left != Nil )
        RBT_DestroyTree( Tree->Left );

    Tree->Left = Nil;
    Tree->Right = Nil;

    RBT_DestroyNode( Tree );
}

RBTNode*  RBT_SearchNode( RBTNode* Tree, ElementType Target )
{
    if ( Tree == Nil )
        return NULL;
    
    if ( Tree->Data > Target ) 
        return RBT_SearchNode ( Tree->Left, Target );
    else if ( Tree->Data < Target )
        return RBT_SearchNode ( Tree->Right,  Target );
    else   //같은 값을 찾으면 
        return Tree;
}

RBTNode*  RBT_SearchMinNode( RBTNode* Tree )
{
    if ( Tree == Nil )
        return Nil;

    if ( Tree->Left == Nil ) 
        return Tree;
    else
        return RBT_SearchMinNode( Tree->Left );
}

string RBT_InsertNode( RBTNode** Tree, RBTNode* NewNode)
{
	string output;
	for(int i=0; i<v.size(); i++){
		if(v[i] == NewNode->Data){
			output += intTostring(NewNode->Data);
			output += " ";
			output += "ALREADY EXIST";
			output += "\n";
			return output;			
		}
	}
	RBT_InsertNodeHelper( Tree, NewNode );  //key가 없으면 삽입 실행 
    v.push_back(NewNode->Data);
    
    NewNode->Color = 1;
    NewNode->Left  = Nil;
    NewNode->Right = Nil;
    RBT_RebuildAfterInsert( Tree, NewNode );
    return "";
}

void RBT_InsertNodeHelper( RBTNode** Tree, RBTNode* NewNode)
{
	
    if ( (*Tree) == NULL )
        (*Tree) = NewNode;

    if ( (*Tree)->Data < NewNode->Data ) //넣으려는 값이 작은 경우 
    {
        if ( (*Tree)->Right == Nil )
        {
            (*Tree)->Right  = NewNode;
            NewNode->Parent = (*Tree);
        }
        else
            RBT_InsertNodeHelper(&(*Tree)->Right, NewNode);  //끝이 아니면 재귀적으로 실행 

    } 
    else if ( (*Tree)->Data > NewNode->Data )   //넣으려는 값이 큰 경우 
    {
        if ( (*Tree)->Left == Nil )
        {
            (*Tree)->Left   = NewNode;
            NewNode->Parent = (*Tree);
        }
        else
            RBT_InsertNodeHelper(&(*Tree)->Left, NewNode);  //끝이 아니면 재귀적으로 실행 
    }

   
    	
}

void RBT_RotateRight( RBTNode** Root, RBTNode* Parent )
{
    RBTNode* LeftChild =  Parent->Left;

    Parent->Left = LeftChild->Right;

    if ( LeftChild->Right != Nil )
        LeftChild->Right->Parent = Parent;

    LeftChild->Parent = Parent->Parent;

    if ( Parent->Parent == NULL )
        (*Root) = LeftChild;
    else
    {
        if ( Parent == Parent->Parent->Left )
            Parent->Parent->Left = LeftChild;
        else
            Parent->Parent->Right = LeftChild;
    }

    LeftChild->Right  = Parent;
    Parent->Parent = LeftChild;
}

void RBT_RotateLeft( RBTNode** Root, RBTNode* Parent )
{
    RBTNode* RightChild = Parent->Right;
    
    Parent->Right = RightChild->Left;

    if ( RightChild->Left != Nil )
        RightChild->Left->Parent = Parent;

    RightChild->Parent = Parent->Parent;

    if ( Parent->Parent == NULL )
        (*Root) = RightChild;
    else
    {
        if ( Parent == Parent->Parent->Left )
            Parent->Parent->Left = RightChild;
        else
            Parent->Parent->Right = RightChild;        
    }

    RightChild->Left   = Parent;
    Parent->Parent = RightChild;
}

void RBT_RebuildAfterInsert( RBTNode** Root, RBTNode* X )
{
    while ( X != (*Root) && X->Parent->Color == 1 ) 
    {
       if ( X->Parent == X->Parent->Parent->Left )   //부모 노드가 조부모 노드의 왼쪽 자식인 경우 
       {
           RBTNode* Uncle = X->Parent->Parent->Right;
           if ( Uncle->Color == 1 )   //Recoloring 
           {
               X->Parent->Color         = 0;
               Uncle->Color                   = 0;
               X->Parent->Parent->Color = 1;

               X = X->Parent->Parent;
           }
           else   //reconstructing
           {
               if ( X == X->Parent->Right ) 
               {
                   X = X->Parent;
                   RBT_RotateLeft( Root, X );
               }
               
               X->Parent->Color         = 0;
               X->Parent->Parent->Color = 1;

               RBT_RotateRight( Root, X->Parent->Parent );
           }
       }
       else // 부모 노드가 조부모 노드의 오른쪽 자식인 경우 
       {
            RBTNode* Uncle = X->Parent->Parent->Left;
           if ( Uncle->Color == 1 )   //Recoloring 
           {
               X->Parent->Color         = 0;
               Uncle->Color                   = 0;
               X->Parent->Parent->Color = 1;

               X = X->Parent->Parent;
           }
           else   //Reconstructing
           {
               if ( X == X->Parent->Left ) 
               {
                   X = X->Parent;
                   RBT_RotateRight( Root, X );
               }
               
               X->Parent->Color         = 0;
               X->Parent->Parent->Color = 1;
               RBT_RotateLeft( Root, X->Parent->Parent );
           }
       }
    }

    (*Root)->Color = 0;
}

RBTNode* RBT_RemoveNode( RBTNode** Root, ElementType Data )
{
    RBTNode* Removed   = NULL;
    RBTNode* Successor = NULL;
    RBTNode* Target    = RBT_SearchNode( (*Root), Data );

    if ( Target == NULL )  //삭제하려는 노드가 없을 때 
        return NULL;

    if ( Target->Left == Nil || Target->Right == Nil )  //삭제하려는 노드가 LEAF를 가지는 경우 
    {
        Removed = Target;
    }
    else   //LEAF가 없는 경우, inorder successor를 불러 온다. 
    {
        Removed = RBT_SearchMinNode( Target->Right );
        Target->Data = Removed->Data;
    }
    
    //inorder successor를 원래 가지고 있던 노드를 처리한다. 

    if ( Removed->Left != Nil )
        Successor = Removed->Left;
    else
        Successor = Removed->Right;


    Successor->Parent = Removed->Parent;

    if ( Removed->Parent == NULL )
        (*Root) = Successor;
    else
    {
        if ( Removed == Removed->Parent->Left )
            Removed->Parent->Left = Successor;
        else
            Removed->Parent->Right = Successor;
    }

    if ( Removed->Color == 0 ) 
        RBT_RebuildAfterRemove( Root, Successor );    
        
    for(int i=0; i<v.size(); i++){
		if(v[i] == Data){
			v.erase(v.begin()+i);	
		}
	}

    return Removed;
}

void RBT_RebuildAfterRemove( RBTNode** Root, RBTNode* Successor )
{
    RBTNode* Sibling = NULL;

    while ( Successor->Parent != NULL && Successor->Color == 0)
    {
    	//현재 노드가 root가 아니거나 black이 넘어가기 전 까지 함수를 반복 
        if ( Successor == Successor->Parent->Left )   //Double Black이 왼쪽 노드인 경우 
        {
            Sibling = Successor->Parent->Right;

            if ( Sibling->Color == 1 )  //1) 형제가 Red인 경우 
            {
                Sibling->Color = 0;
                Successor->Parent->Color = 1;
                RBT_RotateLeft( Root, Successor->Parent );
            }
            else  //형제가 Black인 경우 
            {
                if ( Sibling->Left->Color == 0 && 
                     Sibling->Right->Color == 0 ) //2-1) 자식이 모두 Black인 경우 
                {
                    Sibling->Color = 1;
                    Successor      = Successor->Parent;
                }
                else //자식 중 Red가 있는 경우 
                {
                    if ( Sibling->Left->Color == 1 ) // 2-2) 왼쪽 자식이 Red인 경우 
                    {
                        Sibling->Left->Color = 0;
                        Sibling->Color       = 1;

                        RBT_RotateRight( Root, Sibling );
                        Sibling = Successor->Parent->Right;
                    }
                    // 2-3) 오른쪽 자식이 Red인 경우 
                    Sibling->Color           = Successor->Parent->Color;
                    Successor->Parent->Color = 0;
                    Sibling->Right->Color    = 0;
                    RBT_RotateLeft( Root, Successor->Parent );
                    Successor = (*Root);
                }
            }            
        } 
        else  //Double Black이 오른쪽 노드인 경우 
        {
            Sibling = Successor->Parent->Left;

            if ( Sibling->Color == 1 )  //1) 형제가 Red인 경우 
            {
                Sibling->Color           = 0;
                Successor->Parent->Color = 1;
                RBT_RotateRight( Root, Successor->Parent );
            }
            else  //형제가 Black인 경우 
            {
                if ( Sibling->Right->Color == 0 && 
                     Sibling->Left->Color  == 0 )  //2-1) 자식이 모두 Black인 경우 
                {
                    Sibling->Color = 1;
                    Successor      = Successor->Parent;
                }
                else 
                {
                    if ( Sibling->Right->Color == 1 )  // 2-2) 형제의 오른쪽 자식이 Red인 경우 
                    {
                        Sibling->Right->Color = 0;
                        Sibling->Color        = 1;

                        RBT_RotateLeft( Root, Sibling );
                        Sibling = Successor->Parent->Left;
                    }
					// 2-3) 왼쪽 자식이 Red인 경우 
                    Sibling->Color           = Successor->Parent->Color;
                    Successor->Parent->Color = 0;
                    Sibling->Left->Color     = 0;
                    RBT_RotateRight( Root, Successor->Parent );
                    Successor = (*Root);
                }
            }
        }
    }

    Successor->Color = 0;
}


string RBT_PrintTree( RBTNode* Node, int Depth, int BlackCount )
{
	if(v.empty())
		return "NO KEYS\n";
		
	string output;
    int   i = 0;
    string c = "X";
    int  v = -1;
    string cnt;

    if ( Node == NULL || Node == Nil)
        return "";

    if ( Node->Color == 0 )
        BlackCount++;

    if ( Node->Parent != NULL ) 
    {
        v = Node->Parent->Data;

        if ( Node->Parent->Left == Node )
            c = 'L';            
        else
            c = 'R';
    }
	

    if ( Node->Left == Nil && Node->Right == Nil ){
    	for ( i=0; i<Depth+1; i++){
    		cnt += "    ";
    		cnt += "";
		}	
    	cnt += "LEAF (BLACK)";
    	cnt += "\n";
    	for ( i=0; i<Depth+1; i++){
    		cnt += "    ";
    		cnt += "";
		}	
    	cnt += "LEAF (BLACK)";
    	cnt += "\n";
	}
	
	if ((Node->Left == Nil || Node->Right == Nil) && !(Node->Left == Nil && Node->Right == Nil)){
		for ( i=0; i<Depth+1; i++){
    		cnt += "    ";
    		cnt += "";
		}	
		cnt += "LEAF (BLACK)";
    	cnt += "\n";
	}
    else
    	cnt += "";

    for ( i=0; i<Depth; i++){
    	output += "    ";
    	output += "";
	}
    	


	if (Node->Left == Nil && Node->Right == Nil){
		output += intTostring(Node->Data);
		output += " ";
		output += "(";
		output += (Node->Color == 1)?"RED":"BLACK";
		output += ") ";
		output += "\n";
		output += cnt;
	}
	else if ((Node->Left == Nil) && !(Node->Left==Nil && Node->Right== Nil)){
		output += intTostring(Node->Data);
		output += " ";
		output += "(";
		output += (Node->Color == 1)?"RED":"BLACK";
		output += ") ";
		output += "\n";
		output += cnt;
		output += RBT_PrintTree(Node->Right, Depth+1, BlackCount);
	}
	else if ((Node->Right == Nil) && !(Node->Left==Nil && Node->Right==Nil)){
		output += intTostring(Node->Data);
		output += " ";
		output += "(";
		output += (Node->Color == 1)?"RED":"BLACK";
		output += ") ";
		output += "\n";
		output += RBT_PrintTree(Node->Left, Depth+1, BlackCount);
		output += cnt;
	}
	else{
		output += intTostring(Node->Data);
		output += " ";
		output += "(";
		output += (Node->Color == 1)?"RED":"BLACK";
		output += ") ";
		output += "\n";
		output += cnt;
		output += RBT_PrintTree( Node->Left, Depth+1, BlackCount);
    	output += RBT_PrintTree( Node->Right, Depth+1, BlackCount );
	}
    return output;
    
}

string intTostring(int n){
		stringstream s;
		s << n;
		return s.str();
}


/*-----------------------------함수 구현부---------------------------*/ 

RBTNode* Nil;

int main( void )
{
    RBTNode* Tree = NULL;
    RBTNode* Node = NULL;
    
    Nil           = RBT_CreateNode(0);
    Nil->Color    = 0;    

    string operation;
    string output;
    string insert = "INSERT" ; string remove = "DELETE";
	string showtree = "SHOWTREE" ; string quit = "QUIT";
	
    while ( 1 )
    {
        int  cmd   = 0;
        int  param = 0;
        char buffer[10];

        cin >> operation;

		if(operation.compare(insert)==0)
		{
			fgets(buffer, sizeof(buffer)-1, stdin);
        	sscanf(buffer, "%d", &param );
			output += RBT_InsertNode( &Tree, RBT_CreateNode(param) );
		}
		
		else if(operation.compare(remove)==0)
		{
			fgets(buffer, sizeof(buffer)-1, stdin);
        	sscanf(buffer, "%d", &param );
			Node = RBT_RemoveNode( &Tree, param);
                
            if ( Node == NULL )
            {
            	output += intTostring(param);
            	output += " ";
            	output += "NOT FOUND";
            	output += "\n";
			}
            else
                RBT_DestroyNode( Node );	
		}
		else if (operation.compare(showtree)==0 )
        {
            output += RBT_PrintTree( Tree, 0, 0 );
            output += "";
            continue;
        }
        else if (operation.compare(quit)==0 )
            break;
        else
            printf("Wrong Instruction\n");

    }
    cout << endl;
    cout << output << endl;

    RBT_DestroyTree( Tree );
    return 0;
}

