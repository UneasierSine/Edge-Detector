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
int getBrightness(int x, int y, Image * img);
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
		for(x = 28; x<=827; x++)
		{
			for(y = 2; y<=477; y++)
			{
				int m = getBrightness(x, y, image);
				int dd1 = getBrightness(x-2, y-2, image);
				int dd2 = getBrightness(x-1, y-1, image);
				int dd3 = getBrightness(x+1, y+1, image);
				int dd4 = getBrightness(x+2, y+2, image);
				int d1 = getBrightness(x, y-2, image);
				int d2 = getBrightness(x, y-1, image);
				int d3 = getBrightness(x, y+1, image);
				int d4 = getBrightness(x, y+2, image);
				int ud1 = getBrightness(x-2, y+2, image);
				int ud2 = getBrightness(x-1, y+1, image);
				int ud3 = getBrightness(x+1, y-1, image);
				int ud4 = getBrightness(x+2, y-2, image);
				int r1 = getBrightness(x-2, y, image);
				int r2 = getBrightness(x-1, y, image);
				int r3 = getBrightness(x+1, y, image);
				int r4 = getBrightness(x+2, y, image);
				
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

int SumPixels (int r, int g, int b)
{
	return (r + g + b);
}

int getBrightness(int x, int y, Image * img)
{
	char * pxlVals = imgGetPixel(img, x, y);
	int brightness = SumPixels(pxlVals[0], pxlVals[1], pxlVals[2]);
	return brightness;
}

int edgeDetector(int m, int o, int t, int th, int f)
{
	if(t>(m-5) && t<(m+5))
	{
		if(m>(th-5) && m<(th+5)
		{
			return 0;
		}
	}
	if((m-t)>(th-m-5))
	{
		if((m-t)<(th-m+5))
		{
			return 0;
		}
	}
	if((m-t)>(th-m+5))
	{
		if((t-o)>(m-t+5))
		{
			return 0;
		}
		if((th-m)>(f-th+5))
		{
			return 0;
		}
	}
	if((m-t)<(th-m-5))
	{
		if((t-o)<(m-t-5))
		{
			return 0;
		}
		if((th-m)<(f-th-5))
		{
			return 0;
		}
	}
	return 1;
}
