#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<vector>

using namespace cv;
using namespace std;

int main()
{
	Mat image1=imread("sample3.jpg");
	//VideoCapture cap(1);
	Mat dst, cdst;
	int i=0;

	for(;;)
	{
	
//	cap>>image1;
	Canny(image1, dst, 0, 200,3);
	cvtColor(dst,cdst,CV_GRAY2BGR);
    
	
	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
	for(i = 0; i < lines.size(); i++ )
    {
    Vec4i l = lines[i];
    line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
    }
    imshow("Image1",image1);
	imshow("dst",dst);
	imshow("cdst",cdst);
	waitKey(10);
	}
	
	return 1;
}



/*
//Previous Code below
int main()
{
	Mat image1=imread("sample.jpg");
	cvtColor(image1,image1,CV_BGR2GRAY);
	VideoCapture cap(1);
	//cvtColor(image1, image1, CV_BGR2GRAY);
	for(;;)
	{
	Mat image2;
	Mat image3;//= image1.clone();
	inRange(image1,100,200,image3);
	imshow("b",image3);
	Mat img;
	Canny(image1,img,50,100);
	Mat c ;//= image1.clone();
	absdiff(image1,image1,c);
	flip(image1,image2,1);
	int i;
	dilate(img,img,cv::Mat());
	//erode(img,img,cv::Mat());
	vector<Vec2f> lines;
	HoughLines(img,lines,150,CV_PI/180,150,0,0);
	Mat out=image1.clone();
	for( size_t i = 0; i < lines.size(); i++ )
	{
	float theta = lines[i][1];
	float rho = lines[i][0];
	double a = cos(theta), b = sin(theta);
	double x0 = a*rho, y0 = b*rho;
	Point pt1(cvRound(x0 + 1000*(-b)),
	cvRound(y0 + 1000*(a)));
	Point pt2(cvRound(x0 - 1000*(-b)),
	cvRound(y0 - 1000*(a)));
	line( out, pt1, pt2, Scalar(0,0,255), 2, 8 );
	}
	for(i=0;i<int(image1.rows);i++)
	{
		if(i%2==0)
		{
		image1.row(i).copyTo(c.row(i));
		}
		
		else //if(i%2==1)
		{
		//	for(int j=0; j<image1.cols; j++)
			//	c.at<uchar>(Point(j, i)) = image2.at<uchar>(Point(j,i));
		image2.row(i).copyTo(c.row(i));
		}
	}
			
	imshow("Image1",image1);
	imshow("Image2",image2);
	imshow("Fusion",c);
	imshow("n",img);
	imshow("m",out);
	waitKey(7);
	}
	return 1;
	
}
	*/