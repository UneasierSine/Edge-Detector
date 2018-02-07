//import libraries
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include "imgproc.h"

//camera picture dimensions
int camWidth = 790;
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
	
	//start analysis here
	//save image pixels that line up to array and store brightness in the array
	while(1 == 1)
	{
		//take image and make a separate image for edges
		Image * image = camGrabImage(camera);
		Image * img = imgNew(640, 480);
		
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
					imgSetPixel(img, x, y, 255, 0, 0);
				}
				if(edgeDetector(m, r1, r2, r3, r4) == 1)
				{
					imgSetPixel(img, x, y, 255, 0, 0);
				}
			}
		}
		//display image and destroy images for space
		viewDisplayImage(viewer, img);
		imgDestroy(image);
		imgDestroy(img);
	}	

	//yeah that
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
	//are adjacent pixels of the same value?
	if(t>(m-20) && t<(m+20))
	{
		if(m>(th-20) && m<(th+20))
		{
			return 0;
		}
	}
	//are there any interrupted linear patterns?
	if((m-t)>(th-m-20))
	{
		if((m-t)<(th-m+20))
		{
			return 0;
		}
	}
	//is there a general trend of increasing values?
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
	//is there a general trend of decreasing values?
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
