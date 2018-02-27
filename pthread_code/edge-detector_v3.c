//December 28, 2017
//9:49 P.M. is when I finished, and this is the most I wil do for today. Mentally exhausted? Yes. Happy? No. What? Exhilarated.

//impor tlibraries
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "imgproc.h"

pthread_t horThread, verThread;
pthread_mutex_t wait;

int m=0; int d1=0; int d2=0; int d3=0; int d4=0; int r1=0; int r2=0; int r3=0; int r4;
	
//camera picture dimensions
int camWidth = 640;
int camHeight = 480;
int x,y;

int ready = 0;
int foundEdge = 0;

//declare functions
int SumPixels (int r, int g, int b);
int getBrightness(int x, int y, Image * img);
int edgeDetector(int m, int o, int t, int th, int f);

void * horEdgeDetection(void *_)
{
	pthread_mutex_lock(&wait);
	pthread_mutex_unlock(&wait);
	if(edgeDetector(m, r1, r2, r3, r4) == 1 && foundEdge != 1)
	{
		pthread_mutex_lock(&wait);
		foundEdge = 1;
		pthread_mutex_unlock(&wait);
	}
	ready++;
	while(ready != 2) {}
}

void * verEdgeDetection(void *_)
{
	pthread_mutex_lock(&wait);
	pthread_mutex_unlock(&wait);
	if(edgeDetector(m, r1, r2, r3, r4) == 1 && foundEdge != 1)
	{
		pthread_mutex_lock(&wait);
		foundEdge = 1;
		pthread_mutex_unlock(&wait);
	}
	ready++;
	while(ready != 2) {}
}

int main(int argc, char **argv)
{
	//initialize libraries
	init_imgproc();
		
	//initialize camera and viewer
	Camera * camera = camOpen(camWidth, camHeight);
	Viewer * viewer = viewOpen(camWidth, camHeight, "Viewer");
	
	pthread_create(&horThread, NULL, horEdgeDetection, NULL);
	pthread_create(&verThread, NULL, verEdgeDetection, NULL);
	
	//start analysis here
	//save image pixels that line up to array and store brightness in the array
	while(1 == 1)
	{
		pthread_mutex_lock(&wait);
				
		//take image and make a separate image for edges
		Image * image = camGrabImage(camera);
		Image * img = imgNew(640, 480);
		
		//iterate through pixels within a 480x800 range (for the display in the AR application)
		for(x = 2; x<=637; x++)
		{
			for(y = 2; y<=477; y++)
			{
				//brightness of certain pixels in 5x5 kernel
				m = getBrightness(x, y, image);
				d1 = getBrightness(x, y-2, image);
				d2 = getBrightness(x, y-1, image);
				d3 = getBrightness(x, y+1, image);
				d4 = getBrightness(x, y+2, image);
				r1 = getBrightness(x-2, y, image);
				r2 = getBrightness(x-1, y, image);
				r3 = getBrightness(x+1, y, image);
				r4 = getBrightness(x+2, y, image);
				
				pthread_mutex_unlock(&wait);
				
				while(ready != 2){}
				if(foundEdge == 1) imgSetPixel(img, x, y, 255, 0, 0);
				
				pthread_mutex_lock(&wait);
				
				foundEdge = 0;
				ready = 0;
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
	pthread_exit(NULL);
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
