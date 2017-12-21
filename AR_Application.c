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
		for(x = 0; x>=28 && x<=826; x++)
		{
			for(y = 0; y>=2 && y<=477; y++)
			{
				int brightness = 0;
				int m = SumPixels(imgGetPixel(image, x, y)[0], imgGetPixel(image, x, y)[1], imgGetPixel(image, x, y)[2]);
				int t1 = SumPixels(imgGetPixel(image, x-1, y-1)[0], imgGetPixel(image, x-1, y-1)[1], imgGetPixel(image, x-1, y-1)[2]);
				int t2 = SumPixels(imgGetPixel(image, x, y-1)[0], imgGetPixel(image, x, y-1)[1], imgGetPixel(image, x, y-1)[2]);
        int t3 = SumPixels(imgGetPixel(image, x, y-1)[0], imgGetPixel(image, x, y-1)[1], imgGetPixel(image, x, y-1)[2]);
				int m1 = SumPixels(imgGetPixel(image, x-1, y)[0], imgGetPixel(image, x-1, y)[1], imgGetPixel(image, x-1, y)[2]);
				int m3 = SumPixels(imgGetPixel(image, x+1, y)[0], imgGetPixel(image, x+1, y)[0], imgGetPixel(image, x+1, y)[2]);
        int b1 = SumPixels(imgGetPixel(image, x-1, y+1)[0], imgGetPixel(image, x-1, y+1)[1], imgGetPixel(image, x-1, y+1)[2]);
				int b2 = SumPixels(imgGetPixel(image, x, y+1)[0], imgGetPixel(image, x, y+1)[1], imgGetPixel(image, x, y+1)[2]);
				int b3 = SumPixels(imgGetPixel(image, x+1, y+1)[0], imgGetPixel(image, x+1, y+1)[1], imgGetPixel(image, x+1, y+1)[2]);
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
