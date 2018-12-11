#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
	{
		Mat img;
		VideoCapture cap("aban2.wmv");
		VideoWriter outp;
		outp.open("aban400.wmv",CV_FOURCC('M','P','4','2'),10,Size(400,400),false);//10 is fps
		int i=0;
		//ensure that binary images ARE NOT written on outp when bool isColor is true
		for(i=0;i<500;i++)
			{
				cout<<i<<"\n";
				cap>>img;
				cvtColor(img,img,CV_BGR2GRAY);
				resize(img,img,Size(400,400));
				outp.write (img);
				//flip(img,img,0);
				//inRange(img,Scalar(0,0,50),Scalar(100,100,255),img);
				imshow("inp",img);
				
				waitKey(10);
			}
		return 1;
	}