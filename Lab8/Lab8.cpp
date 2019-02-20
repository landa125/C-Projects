
//name: Eduardo Roman
// Assignment: Lab8
// File: Lab8.cpp

#include <cctype>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include "BinarySearch.h"
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;

void Check(vector<int> & B);

int CreateBinaryTree (ifstream & input, BinarySearchTree<string>& BST);
  
int main ()
{
  int number;
  
  BinarySearchTree<int>  BST;
  vector<int>AList;
  vector<int>List;
 
  
  cout << "Enter an integer:  ";
  cin >> number;
  cout << endl;
  srand(time(NULL));
  int RandomNumber;
  for (int n = 0; n < number; n++)
    {
      RandomNumber = rand() % RAND_MAX;
      BST.insert(RandomNumber);
      AList.push_back(RandomNumber);
    }
  cout << "The height of the tree is: " << BST.depth()<<endl;
  cout <<"The size of the tree is: "<< BST.size()<< endl;
  float n = number;
  cout <<"The log base 2 of "<< number<< " is " << log2(n)<< endl;
  cout << endl;
  
  BST.InOrder(List);
  Check(List);
  cout <<endl;
  
  //KeyOfRank(n/2)
  int KeyOfRank = BST.KeyOfRank(number/2);
  if(KeyOfRank == List[number/2 - 1])
    {
      cout << "key of rank-successful\n";
    }
  else
    {
      cout << "Key of rank-unsuccessful\n";
    }
  cout <<endl;

  int RankOfKey = BST.RankOfKey(AList[number/2]);
  if(RankOfKey > 0)
    {
      if(AList[number/2] == List[RankOfKey-1])
	{
	  cout << "Rank of Key-successful\n";
	}
      else
	{
	  cout << "Rank of Key-unsuccessful\n";
	}
    }
  cout << endl;

  //delete keys
  for (int i = List.size()/2; i < List.size(); i++)
    {
      BST.remove(AList[i]);
    }
  cout << "After Deletion: "<<endl;
  cout << "The height of the tree is: " << BST.depth()<<endl;
  cout <<"The size of the tree is: "<< BST.size()<< endl;
  cout <<"The log base 2 of " << number/2 << " is " << log2(n/2)<< endl;
  
  //Inorder for C vector
  cout << "InOrder for vector C: "<< endl<<endl;
  vector<int>CList;
  BST.InOrder(CList);
  Check(CList);
  cout <<endl;

  //Keyofrank (n/4)
  int KeyOfRank2 = BST.KeyOfRank(number/4);
  if(KeyOfRank2 == CList[number/4 - 1])
    {
      cout << "key of rank-successful\n";
    }
  else
    {
      cout << "Key of rank-unsuccessful\n";
    }
  cout <<endl;

  int RankOfKey2 = BST.RankOfKey(AList[number/4]);
  if(AList[number/4] == CList[RankOfKey2 - 1])
    {
      //if(CList[number/4] == CList[RankOfKey-1])
      cout << "Rank of Key-successful\n";
    }
  else
    {
      cout << "Rank of Key-unsuccessful\n";
    }
    
  
  


  return 0;
}


void Check(vector<int> & B)
{
  int count;
  for (int j = 0; j < B.size()-1; j++)
    {
      if (B[j]<B[j+1])
	{
	  count++;
	}
    }
  if (count == B.size()-1)
    {
      cout << "Order Check-Succesful\n";
    }
  else
    {
      cout << "Order Check-Unsuccesful\n";
    }
}	 
	 
	       
	  
	  
	  
      
