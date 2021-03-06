
//Name: Eduardo Roman
//Assignment: Lab4

#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <string>
//#include <stdlib.h>
//#include "scan.cpp"

using namespace std;

vector<string>ReadString(string input);

class Stack;

//class Node
//*************************************************//*************************************************
class Node {

public:
Node(int key1){
	key = key1;
	tag = 0;
	down = NULL;
	next = NULL;
}

Node(Node* dptr, Node* nptr) {
	tag = 1;
	down = dptr;
	next = nptr;
}

void setKey(int k) {
	key = k;
}

void setDown(Node* ptr) {
	down = ptr;
}

void setNext(Node* ptr) {
	next = ptr;
}

int getKey() {
	return key;
}

Node* getDown() {
	return down;
}

Node* getNext() {
	return next;
}

int size() {
	if (this == NULL)
	   return 0;
	else if (this->tag == 0) return 1;
	else
	   return down->size() + next->size();
}
//UPDATE **************
void update(int j, int k)
{
	if (this -> size() == 0)
	{
		cout << "Error: not valid to update empty list\n";
		return;
   	}
	else if (this ->tag == 0)
	{
		this ->key = k;
		return;
	}
	else 
	{
		int s = down->size();
		if ( j <= s)
			down->update(j, k);
		else
			next->update(j-s, k);
	}
			
  } 


bool isEmpty() {
	  return this == NULL;
  }

void print(int depth) {
	  if (this == NULL) return;
	  if (tag == 0) {
	      cout << "(" << key << "," << depth << ") " ;
	      }
	  else {
	     down->print(depth+1);
	     next->print(depth);
	    } // end else
	 } // end print

private:
   int tag;
   int key;
   Node* down;
   Node* next;
};

//class Stack
//*************************************************//*************************************************
class Stack {

private:
  int maxTop;// max stack size = size - 1
  int top;// current top of stack
  Node* values[1000];// element array

public:

  bool IsEmpty() { return top == -1; }
  bool IsFull() { return top == maxTop; }

 Stack() {
    top=-1;
    maxTop= 999;
  }

  void Push(Node* x) {
    if (IsFull())  // if stack is full, print error
      cout << "Error: the stack is full." << endl;
    else {
        values[++top]= x;
        }
  }

  Node*  Pop() {
    if (IsEmpty()) { //if stack is empty, print error
      cout << "Error: the stack is empty." << endl;
      return NULL;
    }
    else {
      return values[top--];
    }
  }

  Node* Top() {
    if (IsEmpty()) {
      cout << "Error: the stack is empty." << endl;
      return NULL;
    }
    else
      return values[top];
   }
};

//Function Implementations
//*************************************************//*************************************************

/*int convert(string x) {
 // converts a string rep of decimal integer to an int
  return atoi(x.c_str());
}
*/

Node* create (vector<string> T) {

  Stack S;
  for (int k = 0; k < T.size(); ++k)
    {
      if (T[k] == "[" )
	{
	  Node * n = new Node(NULL, NULL);
	  S.Push(n);
	}
      else if (isdigit(T[k][0]) || T[k][0] == '-')
	{
	  Node * j = new Node(stoi(T[k]));
	  Node * w = new Node(j, NULL);
	  S.Push(w);
	}
      else if (T[k] == "]")
	{
	  Node * N = S.Pop();
	  //	  if (S.Pop() == NULL)
	  //{
	  //  cout << "Error: one of the Lists is empty!\n ";
	  //  exit(1);
	  //}
	  while(S.Top()->size() != 0)
	    {
	      Node * k1= S.Pop();
	      k1->setNext(N);
	      N = k1;
	    }
	  Node * L = S.Pop();
	  L -> setDown(N);
	  S.Push(L);
	}
    }
  return S.Pop();
 
  // return NULL; // to be completed. Takes as input a vector of strings and builds a generalized list
  
} 
//****************************************************************************************************

vector<string>ReadString(string input)
{
  vector<string>UserVector;
  stringstream UserList;
  UserList << input;
  int i;
  char c;
  //if (IsEmpty() != NULL)
  while (UserList >> c)
    {
      if (c == '[')
	UserVector.push_back("[");
      else if ( c == ']')
	UserVector.push_back("]");
      else if (c == '-' || isdigit(c))
	{
	  UserList.putback(c);
	  UserList >> i;
	  UserVector.push_back(to_string(i));
	}
    }
  return UserVector;
}

//main()
//*************************************************//*************************************************
int main(int argc, char* argv[]) {

  string UserList;
  cout << "Input a generalized list: "<< endl;
  cin >>  UserList;

  vector<string> VectorList = ReadString(UserList);

  Node * MakeList = create(VectorList);
  MakeList -> print(-1);
  
  cout <<endl;
  cout <<endl;
  
  char u;
  while ( u != 'q')
    {
      cout << "What would you like to do?" << endl;
      cout << "'u' : Update an element\n";
      cout << "'q' : Quit the program\n";
      cout << endl;
      cin >> u;
      
      if (u == 'q')
	exit(1);
      else if ( u == 'u')
	{
	  int element;
	  cout << "Which element would you like to update? ";
	  cin >> element;
	  int element2;
	  cout << "What would you like to update it to? ";
	  cin >> element2;
	  cout << endl;
	  MakeList -> update(element, element2);
	  cout << "The updated list is:\n";
	  MakeList -> print(-1);
	}
    }

 

  /*
    Node* temp = new Node(3);
    Node* temp1 = new Node(5);
    Node* temp2 = new Node(temp1, NULL);
    temp = new Node(temp, temp2);
    temp1 = new Node(new Node(2), NULL);
    temp = new Node(temp, temp1);
    cout << "The list before update: " << endl;
    temp->print(0);
    cout << "The size is " << temp->size() << endl;
  */

    return 0;
}

