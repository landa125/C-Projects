#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <ostream>

using namespace std;
int insertionSort(vector<int> A);
int main()
{
  int num;
  vector<int>a;
  cin >> num;
  num = 10 * num;
  for (int j = 0; j < num; j++)
    {
      int numbers = rand () % num;
      a.push_back(numbers);
    }
  int total = insertionSort(a);
  cout << total << endl;
  return 0;
}

int insertionSort(vector<int>A)
{
  int count = 0;
  for ( int j = 1; j < A.size(); ++j)
    {
      int temp = A[j];
      int c;
      for (int k = j-1; (k >= 0) && (A[k] > temp); k--)
	{
	  count++;
	  A[k+1] = A[k];
	  c =k;
	}
      if (c >= 0)
	{
	  count++;
	}
      A[c+1] = temp;
    }
  
  return count;
}
