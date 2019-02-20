//Name: Eduardo Roman
//Assignment: Lab7

#include <iostream> 
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <array>
#include"SeparateChaining.h"
#include "SeparateChaining.cpp"
#include <math.h>
#include <time.h>
using namespace std;

void set_pegs(ifstream & input, int board[7][7]);
void printboard(int board[7][7]);
vector<vector<int>> nextmoves ( int board[7][7]);
bool isPositionValid(int position, int board[7][7]);
bool ismovevalid ( vector<int>  move, int board[7][7]);
bool solve( int board[7][7], vector<vector<int>>& mseq);
void MakeMove ( vector<int> move, int board[7][7], int newboard[7][7]);
bool hsolve( int board[7][7],vector<vector<int>> & mseq, HashTable<long long int> &hash);

int main()
{
  
        string startingboard;
	cout << "Enter a starting board position as a text file"<< endl;
	cin >> startingboard;
	
	int options;
	while(options)
	{
	int board[7][7];
	ifstream moves_file(startingboard.c_str());
	if (moves_file.fail())
	{
		cout << "File: " << startingboard << " not found\n"<< endl;
	
		exit(1);
	}
	
	vector<vector<int>> mseq;

	set_pegs(moves_file, board);
	cout << endl;
	cout << "Option 1: Solves the peg solitaire with depth first search\n" << "Option 2: Solves the peg solitaire with a hashtable\n"<< "Option 3: Exits the current peg solitaire"<< endl;

		cin >>options;
		if (options==1)
		{
			clock_t start_t, end_t;
			start_t = clock();
			bool result = solve(board, mseq);
			end_t= clock();
			double total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;	
			if (result == true)
			{	
				cout <<"Solution: ";
				for( int i = mseq.size()-1 ; i >=0; i--)
				{	cout<< "(";
					for (int j = 0 ; j <2; j++)
					{
						cout <<mseq[i][j]<< ' ';
					}
					cout<< mseq[i][2]<<") ";
				}
				cout << endl;
				cout <<"Time: "<< total_t<< endl;
			}
	
			else
			cout << "Solution: No Solution\n";
		}
	
		else if (options ==2)
		{
			clock_t begin_t, last_t;
			vector<vector<int>>moveseq;	
			HashTable<long long int> hashresize;
			begin_t = clock();
			bool solution = hsolve(board, moveseq, hashresize);
			last_t = clock();
			double clock_time = (double)(last_t - begin_t)/CLOCKS_PER_SEC;	
			cout << "Testing the Hash Table\n";
			if (solution == true)
			{
				cout << "Solution: ";	
				for( int i = moveseq.size()-1 ; i >=0; i--)
				{	cout<< "(";
					for (int j = 0 ; j <2; j++)
					{
						cout <<moveseq[i][j]<< ' ';
					}
					cout<< moveseq[i][2]<<") ";
				}
				cout << endl;
				
				cout <<"Time: "<< clock_time<< endl;
			}
			else
				cout << "Solution: No Solution\n";
			
			vector<vector<int>>moveseq2;
			clock_t test2, test2end;
			HashTable<long long int> hash2(10000);
			test2 = clock();
			bool solution2 = hsolve(board, moveseq2, hash2);
			test2end = clock();
			double clock_time2 = (double)(test2end - test2)/CLOCKS_PER_SEC;	
			cout << "\nTesting HashTable of size 10,000\n";
			if (solution2 == true)
			{	
				cout<< "Solution: ";
				for( int i = moveseq2.size()-1 ; i >=0; i--)
				{	cout<< "(";
					for (int j = 0 ; j <2; j++)
					{
						cout <<moveseq2[i][j]<< ' ';
					}
					cout<< moveseq2[i][2]<<") ";
				}
				cout << endl;
				
				cout <<"Time: "<< clock_time2<< endl;
			}
			else
				cout << "Solution: No Solution\n";
			
			clock_t test3, test3end;
			vector<vector<int>>moveseq3;
			HashTable<long long int> hash3(50000);
			test3 = clock();
			bool solution3 = hsolve(board, moveseq3, hash3);
			test3end = clock();
			double clock_time3 = (double)(test3end - test3)/CLOCKS_PER_SEC;	
			cout<< "\nTesting HashTable of size 50,000\n";
			if (solution3 == true)
			{	
				cout << "Solution: ";
				for( int i = moveseq3.size()-1 ; i >=0; i--)
				{	cout<< "(";
					for (int j = 0 ; j <2; j++)
					{
						cout <<moveseq3[i][j]<< ' ';
					}
					cout<< moveseq3[i][2]<<") ";
				}
				cout << endl;
				
				cout <<"Time: "<< clock_time3<< endl;
			}
			else
				cout << "Solution: No Solution\n";
		
			clock_t test4, test4end;
			vector<vector<int>>moveseq4;
			HashTable<long long int> hash4(100000);
			test4 = clock();
			bool solution4 = hsolve(board, moveseq4, hash4);
			test4end = clock();
			double clock_time4 = (double)(test4end - test4)/CLOCKS_PER_SEC;	
			cout<< "\nTesting HashTable of size 100,000\n";
			if (solution4 == true)
			{	
				cout<< "Solution: ";
				for( int i = moveseq4.size()-1 ; i >=0; i--)
				{	cout<< "(";
					for (int j = 0 ; j <2; j++)
					{
						cout <<moveseq4[i][j]<< ' ';
					}
					cout<< moveseq4[i][2]<<") ";
				}
				cout << endl;
				
				cout <<"Time: "<< clock_time4<< endl;
			}
			else
				cout << "Solution: No Solution\n";


		}
		else if (options ==3)
		{
			exit(1);
		}
		else
			true;
	}
	
	return 0;
}
bool solved ( int board[7][7])
{
	int numpegs =0;
	for( int row = 0; row < 7; row++)
	{
		for( int col = 0; col < 7; col++)
		{	
			if( board[row][col] == 1) 
				numpegs++;	
		}
	}
	if(numpegs == 1)
		return true;
	return false;
} 
void  set_pegs ( ifstream & input, int board[7][7] )
{
	for (int row =0; row< 7; row++)
	{	for (int col =0 ; col < 7 ; col++)
		{
			if ( (row < 2 || row > 4) && (col < 2 || col > 4)) 
				board[row][col]= -1;
			else
				board[row][col] =0;
		}
	}
	int piece;
	while(input >> piece)
	{
		int row = piece/ 7;
		int col = piece % 7;
		board[row][col] = 1;
	}
}
void printboard( int board[7][7])
{
	for( int row = 0; row < 7; row++)
	{	for(int col = 0; col < 7; col++)
		{
			if (board[row][col] == -1)
				cout << "  ";
			if(board[row][col] == 1)
				cout << "$ ";
			if ( board[row][col]==0)
				cout << "* ";
		}
		cout << endl;
	}
}
vector<vector<int>> nextmoves ( int board[7][7])
{
	vector< vector<int>> nextmoves;
	for( int row =0; row < 7; row++)
	{
		for( int col =0; col < 7; col++)
		{
			vector<int> up;
			int current =col + 7*row;
			int mid = col + 7*(row-1);
			int end = col + 7*(row-2);
			up.push_back(current);
			up.push_back(mid);
			up.push_back(end);
			
			vector<int> down;
			int downmid = col + 7*(row+1);
			int downend = col + 7*(row+2);
			down.push_back(current);
			down.push_back(downmid);
			down.push_back(downend);
		
			vector<int> left;
			int leftmid = (col-1) + (7*row);
			int leftend = (col-2) + (7*row);
			left.push_back(current);
			left.push_back(leftmid);
			left.push_back(leftend);
		
			vector<int> right;
			int rightmid = (col+1) + (7*row);
			int rightend = (col+2) + (7*row);
			right.push_back(current);
			right.push_back(rightmid);
			right.push_back(rightend);
			
			if( ismovevalid(up, board))
				nextmoves.push_back(up);
			
			if ( ismovevalid(down,board))
				nextmoves.push_back(down);
			
			if (ismovevalid(left,board))
				nextmoves.push_back(left);
			
			if (ismovevalid(right,board))
				nextmoves.push_back(right);
		}
	}
	nextmoves[0][1] = -2; 
	return nextmoves;			
}
bool isPositionValid(int position, int board[7][7])
{   
	int row = position / 7;
    	int col = position % 7;
        if (board[row][col] == -1)	
		return false;
	if ( (row < 0 || row > 6) && ( col < 0 || col > 6))
		return false;
    	if ( (row < 0 || row > 6) || ( col < 0 || col > 6))
		return false;
/*	if ( (row < 2 || row > 4) && ( col < 2 || col > 4))
		return false;
*/	
	return true;
}

bool ismovevalid ( vector<int>  move, int board[7][7])
{
	int fromrow = move[0] / 7;
	int fromcol = move[0] % 7;
	int midrow = move[1] / 7;
	int midcol = move[1] % 7;
	int torow = move[2] / 7;
	int tocol = move[2] % 7;
	if (isPositionValid(move[0],board) && board[fromrow][fromcol] ==1)
	{	
		if (isPositionValid(move[1],board) && board[midrow][midcol] == 1)
		{
			if(isPositionValid(move[2],board) && board[torow][tocol] == 0)
			{
				return true;
			}
		}
	}
	return false;
			

}
void CheckMove( vector<int> move, int board[7][7], int newboard[7][7])
{
  int fromrow = move[0] / 7;
  int fromcol = move[0] % 7;
  int midrow = move[1] / 7;
  int midcol = move[1] % 7;
  int torow = move[2] / 7;
  int tocol = move[2] % 7;

  if (board[midrow][midcol] != -2)
    MakeMove(moves,board, newboard);

}

void MakeMove ( vector<int> move, int board[7][7], int newboard[7][7])
{
	for (int h =0; h < 7;h++)
	{
		for (int w= 0; w< 7; w++)
		{	
			newboard[h][w] = board[h][w];
		}
	}

	int fromrow = move[0] / 7;
	int fromcol = move[0] % 7;
	int midrow = move[1] / 7;
	int midcol = move[1] % 7;
	int torow = move[2] / 7;
	int tocol = move[2] % 7;

	newboard[fromrow][fromcol] = 0;	
	newboard[midrow][midcol] = 0;
	newboard[torow][tocol] = 1;
}		
bool solve( int board[7][7], vector< vector<int> >& mseq)
{
	int newboard[7][7];
	
	if (solved(board))
		return true;
	vector< vector<int> > curMoves = nextmoves(board);
	for ( int moves = 0; moves < curMoves.size(); moves++)
	{	MakeMove(curMoves[moves],board, newboard);
		if (solve(newboard,  mseq))
		{
			mseq.push_back(curMoves[moves]);
			return true;
		}
	}
	return false;
}
				
bool hsolve( int board[7][7],vector<vector<int>>& mseq, HashTable<long long int> &hash)
{
	int newboard[7][7];
	
	if (solved(board))
		return true;
	vector< vector<int> > curMoves = nextmoves(board);
	for ( int moves = 0; moves < curMoves.size(); moves++)
	{
		MakeMove(curMoves[moves],board, newboard);
		long long int bint = 0;
		for ( int i = 0; i< 7; i++)
		{
			for (int j =0 ; j< 7;  j++)
			{	
				long long int index = j + 7*i;
				if (newboard[i][j]==1)
					bint |= 1LL << index;
			}
		}	
		if (!hash.contains(bint))
		{
			if (hsolve(newboard,mseq, hash))
			{
				mseq.push_back(curMoves[moves]);
				return true;
			}
			else 
				hash.insert(bint);
		}
	}
	
	return false;
}

