#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include<iostream>
#include<conio.h>
#include<vector>
using namespace std;
using namespace cv;


int main()
{
	Mat img;
	Mat imgt;
	VideoCapture cap("http://10.60.86.133:8080//video?x.mjpeg");
	if(!cap.isOpened())
	{
		cout<<"IP cam not captured\n_________\n";
	}
	else
	{
		cout<<"IP cam captured \n";
	}
		Mat fore,back;
		Mat cont;
		BackgroundSubtractorMOG2 bg;//works on GMM
		bg.set ("nmixtures", 10);
		vector < vector < Point > >contours;
		double t=getTickCount()/getTickFrequency();
	for(;;)
	{
		cap>>img;
		cvtColor(img,img,CV_BGR2HSV);
		flip(img,img,1);
		//Thresholding and extraction part__________________________________________
		static int BL=0;
		static int GL=65;
		static int RL=56;
		static int BH=75;
		static int GH=230;
		static int RH=194;
		namedWindow("Color",WINDOW_NORMAL);
		createTrackbar("BL","Color",&BL,255);
		createTrackbar("GL","Color",&GL,255);
		createTrackbar("RL","Color",&RL,255);
		createTrackbar("BH","Color",&BH,255);
		createTrackbar("GH","Color",&GH,255);
		createTrackbar("RH","Color",&RH,255);
		inRange(img,Scalar(BL,GL,RL),Scalar(BH,GH,RH),imgt);
		static int e=1,d=5;
		int i=0,j=0,k=0;
		createTrackbar("erosion","Color",&e,5);
		createTrackbar("dilation","Color",&d,10);
		for(i=0;i<e;i++)
		{
			erode(imgt,imgt,cv::Mat());
		}
		for(j=0;j<d;j++)
		{
			dilate(imgt,imgt,cv::Mat());
		}
		Mat mask;
		cvtColor(imgt,imgt,CV_GRAY2BGR);
		cvtColor(img,img,CV_HSV2BGR);
		absdiff(img,img,mask);
		subtract(imgt,img,mask);
		subtract(imgt,mask,mask);
		

		//Contour edges Part_______________________________________________________
		
		Mat add,edge;
		Mat draw;
		absdiff(imgt,imgt,draw);
		static int cannyt1=127,cannyt2=73;
		createTrackbar("CannyT1","Color",&cannyt1,200);
		createTrackbar("CannyT2","Color",&cannyt2,200);
		Canny(mask,edge,cannyt1,cannyt2,3,0);
		dilate(edge,edge,cv::Mat());
		//imshow("edge",edge);
		Scalar color=Scalar(255,0,0);
		
	
		moveWindow("draw",660,0);
		//	imshow("draw",draw);
			imshow("mask",mask);
		//end of if condition
	
		//cout<<"max="<<max<<"\n";
		//cvtColor(img,img,CV_HSV2BGR);
		cvtColor(edge,edge,CV_GRAY2BGR);
		//addWeighted(imgt,1,img,1,0,add);


		moveWindow("HSV",0,0);
		moveWindow("Color",320,0);
		
		resize(img,img,Size(320,240));
		imshow("HSV",img);
		//imshow("thres",imgt);
		//imshow("cont",cont);
		cout<<"______________________________________\n";
		waitKey(5);
	
	}//end of infinite loop

	return 1;
	getch();

}