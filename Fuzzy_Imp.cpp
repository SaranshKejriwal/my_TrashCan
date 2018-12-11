#include <opencv2/opencv.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <conio.h>
#include <math.h>

int main() 
{
	using namespace cv;
	using namespace std;
  Mat frame;//to get primary frame
  Mat back;//to get background exclusively 
  Mat fore;//to get foreground contours
  Mat out;//aimed to obtain only foreground objects
VideoCapture cap1("test.wmv");/*to capture from saved video*/
  //Background Subtraction Part_____________________________________________________________
 BackgroundSubtractorMOG2 bg;//works on GMM
  bg.set ("nmixtures", 10);
  vector < vector < Point > >contours;
 namedWindow ("Frame",WINDOW_NORMAL);
 namedWindow( "Rectangle",WINDOW_NORMAL);
 cvMoveWindow("Rectangle",600,190);//to relocate the window to desired coordinates
 cvMoveWindow("Background",0,250);
 cvMoveWindow("Frame",0,0);//to relocate the "Frame" window to desired coordinates
   int i,j,k=0;
	int flag=0;
 double t1=getTickCount()/getTickFrequency();//for velocity
 double t = getTickCount()/getTickFrequency();//for abandoned object
  for (;;)
    {
		cap1 >> frame;
		out=frame.clone(); //should we need more processing
      bg.operator()(frame, fore);
      bg.getBackgroundImage (back);
      erode (fore, fore, cv::Mat ());//to remove image noise
     //erode (fore, fore, cv::Mat ());//to remove image noise more, but reduces contour size
     dilate (fore, fore, cv::Mat ());// perhaps to sharpen contour without noise,gives more square contour
     dilate (fore, fore, cv::Mat ());// perhaps to sharpen contour without noise,gives more square contour
     dilate (fore, fore, cv::Mat ());// perhaps to sharpen contour without noise
     findContours (fore, contours, CV_RETR_EXTERNAL,
     CV_CHAIN_APPROX_NONE);//CHAIN_APPROX_NONE ensures that straight lines of contour are also included
     for(i=0;i<contours.size();i++)
	 {
		 if(contourArea(contours[i])>500)//to eliminate noise contours
			drawContours (frame, contours, -1, cv::Scalar (255, 255, 255), 1);
	 }
	if (cv::waitKey(3)>=10)
     break;
	//Rectangles Part________________________________________________
	    Mat drawing = Mat::zeros( fore.size(), CV_8UC3 );//to initialize drawing to a blank matrix
	    drawing=out.clone();
		Scalar color = Scalar( 100, 100, 100);
	    int a=0;
	 	vector<Rect> boundRect( contours.size() );
		vector<RotatedRect> rotellipse( contours.size() );
        vector<Point> center( boundRect.size() );
        
 		 for( int i = 0; i < contours.size(); i++ )
		  {
		  
			boundRect[i] = boundingRect( contours[i] );//draws upright rectangles
			rotellipse[i] = fitEllipse(contours[i]);//draws free rotating ellipses
			if(boundRect[i].width>=50 || boundRect[i].height>=50)//eliminates small boxes
				{
					center[i] = Point((boundRect[i].x+boundRect[i].width/2),boundRect[i].y+boundRect[i].height/2);
					circle(drawing,center[i],4, Scalar(0,255,255),2,8);
					color=Scalar(200,200,200);
					//5 is radius, 2 is thickness, 8 means that point should be 8-connected
					if(float(boundRect[i].height)/float(boundRect[i].width)>1.6 && float(boundRect[i].height)/float(boundRect[i].width)<3.2)
						{
							color=Scalar(0,255,50);//green
							float c,r;
							r=float(boundRect[i].height)/float(boundRect[i].width);
							if(r<=2.45)
								{
									cout<<"Probability of Human presence = "<<100*r/2.45<<"%\n";
								}
		//here r=2.45 is taken as ideal ratio of height to width
							if(r>2.45)
								{
									cout<<"Probability of Human presence = "<<245/r<<"%\n";
								}
						}
				
				}
         drawContours( drawing, contours, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
         rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 1,0);//0 decides that the rectangle superimposes contour
	     ellipse( drawing, rotellipse[i], Scalar(255,200,2),1,0);
		  }

imshow ("Frame", out);
imshow( "Rectangle", drawing );

}//end of infinite loop
return 1;
}//end of main