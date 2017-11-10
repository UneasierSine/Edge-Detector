/*Do edge detection by using a light source wherein the brightness of the light is broken down to a 0 and 1 where the threshold is going to
be changing. Lower brightness most likely indicates brightness. To prevent issues, subtract pixel brightness without lighting.*/
#include <stdlib>
#include <stdio>
#include <math.h>
#include "imgproc.h"
#include <wiringPi.h>

//function declarations
int pixelBrightness(int x, int y, Image * img);
int thresholdBrightness(char * pixel, int threshold);

int main(int argc, char * argv[])
{
  //initialize librares
  init_imgproc();
  wiringPiSetup();
  
  //set up camera and viewer
  Camera * camera = camOpen(640, 480);
  Viewer * viewer = viewOpen(640, 480, "viewer");
  
  //threshold variable
  int threshold = 765;
  
  while(1 == 1)
  {
    threshold-=3;
    
    Image * image = camGrabImg(camera);
    unsigned int x, y;
    for(x = 0; x < image->imgWidth; x++)
    {
      for(y = 0; y < image->imgHeight; y++)
      {
        thesholdbrightness(imgGetPixel(img, x, y), threshold);
      }
    }
  }
  
  //end
  quit_imgproc();
  return 0;
}
