#include<iostream>
#include<conio.h>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img1=imread("castle.jpg");
	Mat img2;
	int i=0;
	//VideoCapture cap1(1);
		
	
	cvtColor(img1,img1,CV_RGB2GRAY);
	FileStorage fs("testFS.xml",FileStorage::WRITE);
	fs<<"test1"<<img1;

	FileStorage fs2;
	fs2.open("out_camR.xml",FileStorage::READ);
	if(!fs2.isOpened())
	{
	cout<<"didn't find FS2\n\n";
	}
	fs2["Camera_Matrix"]>>img2;
	fs2.release();
	for(;;)
	{
		imshow("in",img1);
		imshow("out",img2);//gives a very tiny 3x3 image
		waitKey(10);
	}

	return 1;
} 
