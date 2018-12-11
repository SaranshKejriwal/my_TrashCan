#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

char RGB_window[30] = "RGB Window";
char HSV_window[30] = "HSV Window";
 Mat src,hsv;
 
 static void onMouse( int event, int x, int y, int f, void* ){
 Mat image=src.clone();
 Vec3b rgb=image.at<Vec3b>(y,x);
 int B=rgb.val[0];
 int G=rgb.val[1];
 int R=rgb.val[2];

  Mat HSV;
  Mat RGB=image(Rect(x,y,1,1));//capture that pixel in its own ROI
  cvtColor(RGB, HSV,CV_BGR2HSV);

    Vec3b hsv=HSV.at<Vec3b>(0,0);
    int H=hsv.val[0];
    int S=hsv.val[1];
    int V=hsv.val[2];

    char name[30];
    sprintf(name,"B=%d",B);
    putText(image,name, Point(150,40) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"G=%d",G);
    putText(image,name, Point(150,80) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"R=%d",R);
    putText(image,name, Point(150,120) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"H=%d",H);
    putText(image,name, Point(25,40) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"S=%d",S);
    putText(image,name, Point(25,80) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"V=%d",V);
    putText(image,name, Point(25,120) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,255,0), 2,8,false );

    sprintf(name,"X=%d",x);
    putText(image,name, Point(25,300) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,0,255), 2,8,false );

    sprintf(name,"Y=%d",y);
    putText(image,name, Point(25,340) , FONT_HERSHEY_SIMPLEX, .7, Scalar(0,0,255), 2,8,false );
	//namedWindow("Ref HSV",WINDOW_NORMAL);
	Mat ref(50,50,CV_8UC3,Scalar(H,S,V));
 //imwrite("hsv.jpg",image);
 imshow( RGB_window, image );
 //imshow( "Ref HSV",ref);

}



int main()

{
//VideoCapture cap(0);
static int Bs=0,Gs=0,Rs=0;
namedWindow("colourCtrl");
 //src = imread("bgr.png",1);
for(;;)
{
  //cap>>src;
  createTrackbar("B","colourCtrl",&Bs,255);
  createTrackbar("G","colourCtrl",&Gs,255);
  createTrackbar("R","colourCtrl",&Rs,255);
  Mat refRGB(500,500,CV_8UC3,Scalar(Bs,Gs,Rs));
  src=refRGB;
  cvtColor(src,hsv,CV_BGR2HSV);
  imshow(RGB_window,src);
 imshow(HSV_window,hsv);
 setMouseCallback( RGB_window, onMouse, 0 );
 setMouseCallback( HSV_window, onMouse, 0 );
 char c=waitKey(10);
 if(c=='b')
	{break;}
 }
return 0;
}
