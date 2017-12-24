/*Do edge detection by using a light source wherein the brightness of the light is broken down to a 0 and 1 where the threshold is going to
be changing. Lower brightness most likely indicates brightness. To prevent issues, subtract pixel brightness without lighting.*/
#include <stdlib>
#include <stdio>
#include <math.h>
#include "imgproc.h"
#include <wiringPi.h>

//function declarations
int thresholdBrightness(char * pixel, int threshold);

int main(int argc, char * argv[])
{
  //initialize librares
  init_imgproc();
  wiringPiSetup();
  
  //set up camera and viewer
  Camera * camera = camOpen(640, 480);
  Viewer * viewer = viewOpen(640, 480, "viewer");
  
  //threshold variable set to max
  int threshold = 768;
  
  while(1 == 1)
  {
    //decrease threshold by 3
    threshold-=3;
    //take image
    Image * image = camGrabImg(camera);
    //x and y values
    unsigned int x, y;
    for(x = 0; x < image->imgWidth - 1; x++)
    {
      for(y = 0; y < image->imgHeight - 1; y++)
      {
        //if there is a difference in threshold result to left or bottom then make pixel red
        if(thesholdbrightness(imgGetPixel(image, x, y), threshold) != thresholdBrightness(imgGetPixel(image, x+1, y)))
        {
          imgSetPixel(img, x, y, 255, 0, 0);
        }
        if(thesholdbrightness(imgGetPixel(image, x, y), threshold) != thresholdBrightness(imgGetPixel(image, x+1, y)))
        {
          imgSetPixel(img, x, y, 255, 0, 0);
        }
      }
    }
    //go max threshold if it is too low
    if(threshold < 500)
    {
      threshold = 765;
      //and take a new image
      image = camGrabImg(camera);
    }
  }
  
  //end
  quit_imgproc();
  return 0;
}

int thresholdBrightness(char * pixel, int threshold)
{
  //get brightness of the pixel by adding RGB values
  int brightness = pixel[0] + pixel[1] + pixel[2];
  //compare brightness to the threshold
  if(brightness >= threshold)
  {
    return 1;
  }
  return 0;
}
