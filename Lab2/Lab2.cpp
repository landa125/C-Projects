//Name: Eduardo Roman
//Assignment: Lab2

#include "EasyBMP.h"
#include <cstdlib>

using namespace std;

void RescaleImage(BMP & img, BMP & myImage,int width, int height);
int main(int argc , char * argv[])
{
    //board image
//******************************************************************************************
    BMP myImage;
    myImage.SetSize(256,256);

    for (int i = 0; i < 256; i++)
      {
	for (int j = 0; j < 256; j++)
	  {
	    if (((i/32) + (j/32)) % 2 == 0)
	      {
		myImage(i,j)->Red = 255;
                myImage(i,j)->Blue = 0;
                myImage(i,j)->Green = 0;
	      }
	    else
	      {
		myImage(i,j)->Red = 0;
                myImage(i,j)->Blue = 0;
                myImage(i,j)->Green = 0;
	      }
	  }
      }
    myImage.WriteToFile("board.bmp");
    //sierpinski image
//******************************************************************************************
    BMP sierpinskiImage;
    sierpinskiImage.SetSize(256,256);

    for (int i = 0; i < 256; i++)
      {
	for (int j = 0; j < 256; j++)
	  {
	    sierpinskiImage(i,j)->Red = 255;
            sierpinskiImage(i,j)->Blue = 255;
            sierpinskiImage(i,j)->Green = 255;
	  }
      }
    //X
    sierpinskiImage(128,5)->Red = 255;
    sierpinskiImage(128,5)->Blue = 0;
    sierpinskiImage(128,5)->Green = 0;
    int x1 = 128, y1 = 5;

    //Y
    sierpinskiImage(5,251)->Red = 255;
    sierpinskiImage(5,251)->Blue = 0;
    sierpinskiImage(5,251)->Green = 0;
    int x2 = 5, y2 = 251;

    //Z
    sierpinskiImage(251, 251)->Red = 255;
    sierpinskiImage(251, 251)->Blue = 0;
    sierpinskiImage(251, 251)->Green = 0;
    int x3 = 251, y3 =251;

    //P(171,34)
    int px = 171, py = 34;
    for (int p = 0; p <= 10000; p++)
      {
	int random = rand() %3; //0-2
	if ( random == 0)
	  {
	    px = ((x1 + px)/2); py = ((y1 + py)/2);
	    sierpinskiImage(px, py)->Red = 255;
	    sierpinskiImage(px, py)->Blue = 0;
            sierpinskiImage(px, py)->Green = 0;
	  }
	else if ( random == 1)
	  {
	    px = ((x2 + px)/2); py = ((y2 + py)/2);
	    sierpinskiImage(px, py)->Red = 255;
	    sierpinskiImage(px, py)->Blue = 0;
            sierpinskiImage(px, py)->Green = 0;
	  }
	else if ( random == 2)
	  {
	    px = ((x3 + px)/2); py = ((y3 + py)/2);
	    sierpinskiImage(px, py)->Red = 255;
	    sierpinskiImage(px, py)->Blue = 0;
            sierpinskiImage(px, py)->Green = 0;
	  }
      }

    sierpinskiImage.WriteToFile("sierpinski.bmp");
    // einstein image
//******************************************************************************************
  BMP EinsteinImage;
  EinsteinImage.ReadFromFile(argv[1]);
  BMP myImage2;
  myImage2.SetSize(EinsteinImage.TellWidth(), EinsteinImage.TellHeight());

  int width = EinsteinImage.TellWidth();
  int height = EinsteinImage.TellHeight();


  RescaleImage(EinsteinImage, myImage2, width, height);
  myImage2.WriteToFile("tile.bmp");

    return 0;
}
void RescaleImage(BMP & img, BMP & myImage,int width, int height)
{
  if (width != 1 && height != 1)
 {
 	Rescale(img, 'f', width/2);
	for (int i = 0; i < 1000; i++)
	  {
	    RangedPixelToPixelCopy(img,0,width,0,height, myImage,i * width/2 ,height/2);
	  }
	for (int j = 0; j < 1000; j++)
	  {
	     RangedPixelToPixelCopy(img,0,width,0,height, myImage, width/2 ,j*height/2);
	  }

        RescaleImage(img,myImage, width/2,height/2);
 }
}

