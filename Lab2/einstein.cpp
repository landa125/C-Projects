//Name: Eduardo Roman
#include "EasyBMP.h"
#include <cstdlib>
using namespace std;
void RescaleImage(BMP & img, BMP & myImage,int width, int height);
//void RescaleImage(BMP & img);
int main()
{
  BMP EinsteinImage;
  EinsteinImage.ReadFromFile("einstein.bmp");
  BMP myImage;
  myImage.SetSize(EinsteinImage.TellWidth(), EinsteinImage.TellHeight());
 //EinsteinImage.SetSize(1,1);
/*  
  int dim = (EinsteinImage.TellWidth()/2);
  Rescale(EinsteinImage, 'f', dim);
  
  RangedPixelToPixelCopy(EinsteinImage, 0,EinsteinImage.TellWidth(), EinsteinImage.TellHeight(),0 ,myImage, 0, (myImage.TellHeight()/2));
  */
	int width = EinsteinImage.TellWidth();
  	int height = EinsteinImage.TellHeight();

// 	RangedPixelToPixelCopy(EinsteinImage,0,width, height,0 ,myImage, 0, (myImage.TellHeight()/2));
 	
	RescaleImage(EinsteinImage, myImage, width, height);
  	myImage.WriteToFile("einsteinAfter.bmp");

  return 0;
}
/*
void RescaleImage(BMP & img)
{
  int width = img.TellWidth();
  int height = img.TellHeight();

  if (width != 1 && height != 1)
 {     
  int dim = (EinsteinImage.TellWidth()/2);
  Rescale(EinsteinImage, 'f', dim);
  
  RangedPixelToPixelCopy(EinsteinImage, 0,EinsteinImage.TellWidth(), EinsteinImage.TellHeight(),0 ,myImage, 0, (myImage.TellHeight()/2));
 
}
*/

void RescaleImage(BMP & img, BMP & myImage,int width, int height)
{
 // int width = img.TellWidth();
 // int height = img.TellHeight();
 int myimgH = myImage.TellHeight();
 int myimgW = myImage.TellWidth();

  if (width != 1 && height != 1)
 {     
  	int dim = (width/2);
 	Rescale(img, 'f', width/2);
  	RangedPixelToPixelCopy(img,0,width, height,0 ,myImage,0 ,0);
 	RescaleImage(img,myImage, width/2,height/2);
 
}
 	//RescaleImage(img,myImage, width/2,height/2);

/*	  if (width!= myimgH && height !=myimgW)
 {     
  //	int dim = (width/2);
 	Rescale(img, 'f', width);
  	RangedPixelToPixelCopy(img,0,width, height,0 ,myImage,0 ,myimgH/2);
 	RescaleImage(img,myImage, width*2,height*2);
 
}*/
 
}
  
