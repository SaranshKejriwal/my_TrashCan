#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<vector>

using namespace cv;
using namespace std;

int maink()
{
	Mat img1=imread("img.jpg");
	Mat img2=img1.clone();
	Mat img3=img1.clone();
	Mat imgs(img1.rows,3*img1.cols,CV_8UC3,Scalar(255));
	
	Rect r(0,0,img1.cols,img1.rows);
	int i=0;
	for(i=0;i<int(img1.cols);i++)
	{
		img1.col(i).copyTo(imgs.col(i));
		img2.col(i).copyTo(imgs.col(i+img1.cols));
		img3.col(i).copyTo(imgs.col(i+2*img1.cols));
	}
	for(;;)
	{
					
	imshow("Image1",img1);
	imshow("Image2",img2);
	imshow("Fusion",imgs);
	char c=waitKey(7);
	if(c=='b' || c=='B')
	break;
	}
	return 1;
	
}