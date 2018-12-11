#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<iostream>
using namespace std;
using namespace cv;

Mat showrot(Mat img);

 int main()
 {
     Mat img,img2;//
	 Mat matRotation;
     Mat rotn;
	
	VideoCapture cap(1);
    VideoWriter out;
    out.open("rotn_out3.wmv",CV_FOURCC('M','P','4','2'),80,Size(400,400),false);//10 is fps
	 static int angle = 0;
	 int i=0,j=0;
     int count=1;
	 for(i=0;i<100;i++)
     {
		 img=imread("CP.jpg");
		 cvtColor(img,img,CV_BGR2GRAY);
         resize(img,img,Size(400,400));
         out.write(rotn);
         //circle(img,Point(400,400),5,Scalar(255),1);
		  matRotation = getRotationMatrix2D( Point(img.cols/2,img.rows/2), angle, 1 );
		 warpAffine( img, rotn, matRotation, img.size() );
		      
		
		  imshow("rotn",rotn);
          
		  char c = waitKey(30);
          
             
          if (c=='b' || c=='B' )
          {
               break;
          }
     
	 }
     for(angle=0;angle<180;angle++)
         {
            cout<<"into new loop\n";
            img=imread("CP.jpg");
		    cvtColor(img,img,CV_BGR2GRAY);
            resize(img,img,Size(400,400));
		    matRotation = getRotationMatrix2D( Point(img.cols/2,img.rows/2), angle, 1 );
		    warpAffine( img, rotn, matRotation, img.size() );
            out.write(rotn);
		
		    resize(matRotation,matRotation,Size(400,400));
		    imshow("mat",matRotation);
		  imshow("rotn",rotn);
          
		 waitKey(1);
                     
         
         }
         for(i=0;i<100;i++)
         {
             cout<<"into new loop\n";
            img=imread("CP.jpg");
		    cvtColor(img,img,CV_BGR2GRAY);
            resize(img,img,Size(400,400));
		    matRotation = getRotationMatrix2D( Point(img.cols/2,img.rows/2), 180, 1 );//only inverted image
		    warpAffine( img, rotn, matRotation, img.size() );
            out.write(rotn);
		 
		     imshow("rotn",rotn);
          
		     waitKey(1);
         }

     
     return 0;
}