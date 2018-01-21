//December 28, 2017
//9:49 P.M. is when I finished, and this is the most I wil do for today. Mentally exhausted? Yes. Happy? No. What? Exhilarated.

//impor tlibraries
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <SDL.h>
#include "imgproc.h"

//camera picture dimensions
int camWidth = 640;
int camHeight = 480;
int x,y;

//declare functions
int SumPixels (int r, int g, int b);
int getBrightness(int x, int y, Image * img);
int edgeDetector(int m, int o, int t, int th, int f);

int main(int argc, char **argv)
{
	//initialize libraries
	wiringPiSetup();
	init_imgproc();
	
	//initialize camera and viewer
	Camera * camera = camOpen(camWidth, camHeight);
	Viewer * viewer = viewOpen(camWidth, camHeight, "Viewer");
	
  int trialNumber = 0;
  
	//start analysis here
	while(trialNumber < 40)
  {
    //save image pixels that line up to array and store brightness in the array
	  Image * image = camGrabImage(camera);
		
    int numberOfEdges = 0;
    
	  //iterate through pixels within a 480x800 range (for the display in the AR application)
	  for(x = 2; x<=637; x++)
	  {
		  for(y = 2; y<=477; y++)
		  {
			  //brightness of certain pixels in 5x5 kernel
			  int m = getBrightness(x, y, image);
			  int d1 = getBrightness(x, y-2, image);
			  int d2 = getBrightness(x, y-1, image);
			  int d3 = getBrightness(x, y+1, image);
			  int d4 = getBrightness(x, y+2, image);
			  int r1 = getBrightness(x-2, y, image);
			  int r2 = getBrightness(x-1, y, image);
			  int r3 = getBrightness(x+1, y, image);
			  int r4 = getBrightness(x+2, y, image);
		
			  //edge detection and set edges to red
			  if(edgeDetector(m, d1, d2, d3, d4) == 1)
			  {
				  imgSetPixel(image, x, y, 255, 0, 0);
          numberOfEdges++;
			  }
			  if(edgeDetector(m, r1, r2, r3, r4) == 1)
			  {
			  	imgSetPixel(image, x, y, 255, 0, 0);
          numberOfEdges++;
			  }
		  }
	  }
	  //display image and destroy images for space
	  viewDisplayImage(viewer, image);
	  
    trialNumber++;
    
    SDL_SaveBMP(image, "/home/pi/testing/output/%d.bmp", trialNumber);
    imgDestroy(image);
    
    //write trial and number of edges to txt file
    outputTxt = fopen("/home/pi/testing/output/outputFile.txt", "w");
    fprintf(outputTxt, "%d : %d\n", trialNumber, numberOfEdges);
    fclose(outputTxt);
  }
	viewClose(viewer);
	camClose(camera);

	// finally we unintialise the library
	quit_imgproc();
	return 0;
}

//return the sum of three values
int SumPixels (int r, int g, int b)
{
	return (r + g + b);
}

//get the brightness of a pixel on a scale from 0 to 765
int getBrightness(int x, int y, Image * img)
{
	char * pxlVals = imgGetPixel(img, x, y);
	int brightness = SumPixels(pxlVals[0], pxlVals[1], pxlVals[2]);
	return brightness;
}

//edge detection algorithm
int edgeDetector(int m, int o, int t, int th, int f)
{
	if(t>(m-20) && t<(m+20))
	{
		if(m>(th-20) && m<(th+20))
		{
			return 0;
		}
	}
	if((m-t)>(th-m-20))
	{
		if((m-t)<(th-m+20))
		{
			return 0;
		}
	}
	if((m-t)>(th-m+50))
	{
		if((t-o)>(m-t+50))
		{
			return 0;
		}
		if((th-m)>(f-th+50))
		{
			return 0;
		}
	}
	if((m-t)<(th-m-50))
	{
		if((t-o)<(m-t-50))
		{
			return 0;
		}
		if((th-m)<(f-th-50))
		{
			return 0;
		}
	}
	return 1;
}
