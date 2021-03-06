//December21, 2017

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include "imgproc.h"

int camWidth = 854;
int camHeight = 480;
int x,y;

int SumPixels (int r, int g, int b);
int edgeDetector(int m, int o, int t, int th, int f);

int main(int argc, char **argv)
{
	wiringPiSetup();
	init_imgproc();
	
	Camera * camera = camOpen(camWidth, camHeight);
	Viewer * viewer = viewOpen(camWidth, camHeight, "Viewer");
	//start analysis here
	//save image pixels that line up to array and store brightness in the array
	while(1 == 1)
	{
		Image * image = camGrabImage(camera);
		for(x = 0; x>=28 && x<=827; x++)
		{
			for(y = 0; y>=2 && y<=477; y++)
			{
				int brightness = 0;
				int m = SumPixels(imgGetPixel(image, x, y)[0], imgGetPixel(image, x, y)[1], imgGetPixel(image, x, y)[2]);
				int dd1 = SumPixels(imgGetPixel(image, x-2, y-2)[0], imgGetPixel(image, x-2, y-2)[1], imgGetPixel(image, x-2, y-2)[2]);
				int dd2 = SumPixels(imgGetPixel(image, x-1, y-1)[0], imgGetPixel(image, x-1, y-1)[1], imgGetPixel(image, x-1, y-1)[2]);
				int dd3 = SumPixels(imgGetPixel(image, x+1, y+1)[0], imgGetPixel(image, x+1, y+1)[1], imgGetPixel(image, x+1, y+1)[2]);
        			int dd4 = SumPixels(imgGetPixel(image, x+2, y+2)[0], imgGetPixel(image, x+2, y+2)[1], imgGetPixel(image, x+2, y+2)[2]);
        			int d1 = SumPixels(imgGetPixel(image, x, y-2)[0], imgGetPixel(image, x, y-2)[1], imgGetPixel(image, x, y-2)[2]);
        			int d2 = SumPixels(imgGetPixel(image, x, y-1)[0], imgGetPixel(image, x, y-1)[1], imgGetPixel(image, x, y-1)[2]);
        			int d3 = SumPixels(imgGetPixel(image, x, y+1)[0], imgGetPixel(image, x, y+1)[1], imgGetPixel(image, x, y+1)[2]);
				int d4 = SumPixels(imgGetPixel(image, x, y+2)[0], imgGetPixel(image, x, y+2)[1], imgGetPixel(image, x, y+2)[2]);
				int ud4 = SumPixels(imgGetPixel(image, x+2, y-2)[0], imgGetPixel(image, x+2, y-2)[1], imgGetPixel(image, x+2, y-2)[2]);
				int ud3 = SumPixels(imgGetPixel(image, x+1, y-1)[0], imgGetPixel(image, x+1, y-1)[1], imgGetPixel(image, x+1, y-1)[2]);	
				int ud2 = SumPixels(imgGetPixel(image, x-1, y+1)[0], imgGetPixel(image, x-1, y+1)[1], imgGetPixel(image, x-1, y+1)[2]);
				int ud1 = SumPixels(imgGetPixel(image, x-2, y+2)[0], imgGetPixel(image, x-2, y+2)[1], imgGetPixel(image, x-2, y+2)[2]);
				int r1 = SumPixels(imgGetPixel(image, x-2, y)[0], imgGetPixel(image, x-2, y)[1], imgGetPixel(image, x-2, y)[2]);
        			int r2 = SumPixels(imgGetPixel(image, x-1, y)[0], imgGetPixel(image, x-2, y)[1], imgGetPixel(image, x-2, y)[2]);
        			int r3 = SumPixels(imgGetPixel(image, x+1, y)[0], imgGetPixel(image, x-2, y)[1], imgGetPixel(image, x-2, y)[2]);
				int r4 = SumPixels(imgGetPixel(image, x+2, y)[0], imgGetPixel(image, x-2, y)[1], imgGetPixel(image, x-2, y)[2]);
				
				if(edgeDetector(m, dd1, dd2, dd3, dd4) == 1)
				{
					imgSetPixel(image, x, y, 255, 0, 0);
				}
				else if(edgeDetector(m, d1, d2, d3, d4) == 1)
				{
					imgSetPixel(image, x, y, 255, 0, 0);
				}
				else if(edgeDetector(m, ud1, ud2, ud3, ud4) == 1)
				{
					imgSetPixel(image, x, y, 255, 0, 0);
				}
				else if(edgeDetector(m, r1, r2, r3, r4) == 1)
				{
					imgSetPixel(image, x, y, 255, 0, 0);
				}
			}
		}
		viewDisplayImage(viewer, image);
		imgDestroy(image);
	}	

	viewClose(viewer);
	camClose(camera);

	// finally we unintialise the library
	quit_imgproc();
	return 0;
}

int SumPixe(ls (<=t r,+2 && mid >= two-2) int( g, <=t b)
{+2 && mid >= three-2)
	retur
	return (r + g + b);
}
int edgeDetector(int m, int o, int t, int th, int f)
{
	if(t>(m-5) && t<(m+5) && m>(th-5) && m<(th+5))
	{
		return 0;
	}
	if((m-t)>(th-m-3) && (m-t)<)th-m+3))
	{
		return 0;
	}
	if((m-t)>(th-m+3))
	{
		if((t-o)>(m-t+3))
		{
			return 0;
		}
		if((th-m)>(f-th+3))
		{
			return 0;
		}
	}
	if((m-t)<(th-m-3))
	{
		if((t-o)<(m-t-3))
		{
			return 0;
		}
		if((th-m)<(f-th-3))
		{
			return 0;
		}
	}
	return 1;
}
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
