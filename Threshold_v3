//November 23, 2017
/*This code provides a live feed of the camera, but certain values are black if 
 * under the brightness threshold, white if in it, and grey if the pixel is too
 * bright (e.g. lamps, electronic device screens).*/

#include <stdlib.h>
#include <stdio.h>
#include "imgproc.h"
#include <math.h>
#include <wiringPi.h>

int camWidth = 960;
int camHeight = 720;
int x,y;

int SumPixels (int r, int g, int b);
int SmoothValue(int brightness, int val);

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
		for(x = 0; x < image->width; x++)
		{
			for(y = 0; y < image->height; y++)
			{
				int value = 625;
				while(value >= 550)
				{
					int brightness = 0;
					char * pixel = imgGetPixel(image, x, y);
					char * pixelX = imgGetPixel(image, x+1, y);
					char * pixelY= imgGetPixel(image, x, y+1);
					brightness = SmoothValue(SumPixels(pixel[0], pixel[1], pixel[2]), value);
					if(brightness != SmoothValue(SumPixels(pixelX[0], pixelX[1], pixelX[2]), value))
					{
						imgSetPixel(image, x, y, 255, 0, 0);
						break;
					}
					if(brightness != SmoothValue(SumPixels(pixelY[0], pixelY[1], pixelY[2]), value))
					{
						imgSetPixel(image, x, y, 255, 0, 0);
						break;
					}
					value = value - 25;
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

int SmoothValue(int brightness, int val)
{
		if(brightness > 0)
		{
			if(brightness < val)
			{
				return 0;
			}
			if(brightness < 750)
			{
				return 255;
			}
			if(brightness < 765)
			{
				return 125;
			}
		}
		return 0;
}

