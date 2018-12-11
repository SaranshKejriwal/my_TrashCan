#include <opencv2/opencv.hpp>
#include<opencv2/video/background_segm.hpp>
#include <iostream>
#include <vector>
#include<stdio.h>

using namespace cv;
using namespace std; 

int main ()
{
  
  Mat frame;
  Mat back;
  Mat backz;
  Mat fore;
  Mat img;
  Mat oth;
  Mat sub;
  int flag = 0;
   
 VideoCapture cap1("normal_rgb.avi");//*to capture from camera*//
 VideoWriter out_rgb;//to save a video
 out_rgb.open("rec_rgb.mp4",CV_FOURCC('M','P','4','2'),10,Size(160,160),false);//20 is fps
 VideoWriter out_disp;//to save a video
 out_disp.open("rec_disp.avi",CV_FOURCC('M', 'J', 'P', 'G'),10,Size(160,160),true);//20 is fps
  BackgroundSubtractorMOG2 bg;
  bg.set ("nmixtures", 10);
  bool bShadowDetection = false;
  std::vector < std::vector < cv::Point > >contours;

  
  	
  for (;;)
    {
     cap1 >> frame;
     imshow("rgb",frame);
     out_rgb.write(frame);
     bg.operator()(frame, fore);
     bg.getBackgroundImage (back);
     erode (fore, fore, cv::Mat ());//to remove image noise
     erode (fore, fore, cv::Mat ());//to remove image noise more, but reduces contour size
     dilate (fore, fore, cv::Mat ());// perhaps to sharpen contour without noise,gives more square contour
     dilate (fore, fore, cv::Mat ());// perhaps to sharpen contour without noise
    Mat out=frame.clone();

    absdiff(fore,fore,out);
	
     findContours (fore, contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
     drawContours (out, contours, -1, cv::Scalar (255, 255, 255), CV_FILLED);
	
   imshow ("disp", out);
   out_disp.write(out);
	
	char c=waitKey(10);
	if (c=='b')
    	 break;
  	
	 }
	
    	 
    return 1;
}

