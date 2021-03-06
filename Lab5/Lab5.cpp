//Name: Eduardo Roman
//Assignment: Lab5

#include "EasyBMP.h"
#include <cstdlib>
#include <climits>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>

using namespace std;

void BFS(BMP & IMG, int Sx, int Sy, int Ex, int Ey);
void colorToGray(BMP & Output);

int main (int argc, char * argv[])
{
  BMP MazeImage;
  MazeImage.ReadFromFile(argv[1]);
  colorToGray(MazeImage);
  // BMP MazeAfterImage = MazeImage;
  //MazeAfterImage.SetSize(MazeImage.TellWidth(),MazeImage.TellHeight());
  
  int startingX,startingY,EndingX, EndingY;
  cout << "Enter the starting point: (X,Y) \n";
  cin >> startingX;
  cin >> startingY;
  cout << "Enter the ending point: (X,Y) \n";
  cin >> EndingX;
  cin >> EndingY;
  
  if((MazeImage(startingX,startingY)->Red == 0) && (MazeImage(startingX,startingY)->Blue == 0) && (MazeImage(startingX, startingY)->Green == 0))
    {
      cout << "Error: Those are black pixels. ";
      exit(1);
    }
  else if((MazeImage(EndingX, EndingY)->Red == 0) && (MazeImage(EndingX,EndingY)->Blue == 0) && (MazeImage(EndingX, EndingY)->Green == 0))
    {
      cout << "Error: Those are black pixels. ";
      exit(1);
    }

  else if ((startingX < 0) || (startingX > MazeImage.TellWidth())) 
    {
      cout << "Error: The input (X) is out of range. ";
      exit(1);
    }
  else if ((startingY < 0) || (startingY > MazeImage.TellHeight()))
    {
      cout << "Error: The input (Y) is out of range. ";
      exit (1);
    }
  else if ((EndingX < 0) || (EndingX > MazeImage.TellHeight()))
    {
      cout << "Error: The input (X) is out of range. ";
      exit (1);
    }
  else if ((EndingY < 0) || (EndingY > MazeImage.TellHeight()))
    {
      cout << "Error: The input (Y) is out of range. ";
      exit (1);
    }
    
    
  BFS(MazeImage, startingX,startingY, EndingX, EndingY);
  
  //MazeImage.WriteToFile("output.bmp");

  return 0;
}

void BFS(BMP & IMG, int Sx, int Sy, int Ex, int Ey)
{
  // s is the start vertex, t is the destination
  // count returns the number of pixels that enter the queue
  // Pre-processing recommended: change I to BW image

  int M = IMG.TellWidth();
  int N = IMG.TellHeight();
  
  queue <int> Q;
  int start = Sy * M + Sx;
  int end = Ey * M + Ex;

  Q.push(start);
  int count = 0;
  count++;
  
  bool visited[N * M] = {false};
  visited[start] = true;
  int distance [N * M];
  bool black [N*M] = {false};

  for( int i = 0; i < M*N ; i++)
    {
      distance[i] = INT_MAX;
      int X = i%M;
      int Y = i/M;
      if((IMG(X,Y)->Red == 0) && (IMG(X,Y)->Blue == 0) && (IMG(X,Y)->Green == 0))
	{
	  black [i] = true;
	}
      
    }
  
  distance [start] = 0;
  int Parent [N *M];
  
  while (!Q.empty() && visited[end] == false)
    {
      int XY = Q.front();
      Q.pop();
      int CorX = XY % M;
      int CorY = XY / M;
      
      if ((CorX >= 0 && CorX < M) && (CorY -1 >= 0 && CorY-1 < N))
	{
	  int UPI = (CorY-1) * M + (CorX);
	  if (black[UPI] == false)
	    {
	      if (!visited[UPI])
		{
		  visited[UPI] = true;
		  distance[UPI] = distance[XY] + 1;
		  Parent[UPI] = XY;
		  Q.push(UPI);
		  count++;
		}
	    }
	}
      
      if ((CorX+1 >= 0 && CorX+1 < M) && (CorY >= 0 && CorY < N))
	{
	  int RI = (CorY) * M + (CorX+1);
	  if (black[RI] == false)
	    {
	      if (!visited[RI])
		{
		  visited[RI] = true;
		  distance[RI] = distance[XY] + 1;
		  Parent[RI] =XY;
		  Q.push(RI);
		  count++;
		}
	    }
	}
      if ((CorX-1 >= 0 && CorX-1 < M) && (CorY >= 0 && CorY < N))
	{
	  int LI = (CorY) * M + (CorX-1);
	  if (black[LI] == false)
	    {
	      if (!visited[LI])
		{
		  visited[LI] = true;
		  distance[LI] = distance[XY] + 1;
		  Parent[LI] =XY;
		  Q.push(LI);
		  count++;
		}
	    }
	}
      if ((CorX >= 0 && CorX < M) && (CorY +1 >= 0 && CorY+1 < N))
	{
	  int DI = (CorY+1) * M + (CorX);
	  if (black[DI] == false)
	    {
	      if (!visited[DI])
		{
		  visited[DI] = true;
		  distance[DI] = distance[XY] + 1;
		  Parent[DI] = XY;
		  Q.push(DI);
		  count++;
		}
	    }
	}
    }
  if (visited[end])
    {
      cout << "\nPath found\n";
      int Target = end;
      int TotalDistance = 0;
      int TotalPixels = N*M;
      while (Target != start)
	{
	  int Xp = Target %M;
	  int Yp = Target /M;
	  IMG(Xp,Yp) -> Red = 255;
	  IMG(Xp,Yp) -> Blue = 0;
	  IMG(Xp,Yp) -> Green = 0;
	  Target = Parent[Target];
	  TotalDistance++;
	}
      IMG.WriteToFile("output.bmp");
      cout<< "Distance: " << TotalDistance << "\nCount: " << count<< "\nTotal Pixels in Queue: " << TotalPixels << endl;;
      
    }
  else
    {
      cout << "No path from starting to end"<<endl;
    }
}						     
   
			
void colorToGray(BMP & Output) {
  int picWidth = Output.TellWidth();
  int picHeight = Output.TellHeight();
  Output.SetBitDepth(8); 

  for (int i = 0; i < picWidth-1; ++i)
    {
      for(int j = 0; j < picHeight-1; ++j)
	{
	  int col = 0.1* Output(i, j)->Blue +0.6*Output(i,j)->Green +0.3* Output(i,j)->Red;
	  if (col > 127)
	    {
	      Output(i,j)->Red = 255;
	      Output(i,j)->Blue = 255;
	      Output(i,j)->Green = 255;
	    } 
	}
    }
}
