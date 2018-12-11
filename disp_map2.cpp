#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/contrib/contrib.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace cv;
using namespace std;

Mat disp8;//global scope for CallBackFunc

int main()
{
    Mat img1, img2, g1, g2;
	Mat imgu1,imgu2;
	Mat disp,diff;
    Mat CM1,CM2,D1,D2;
	Mat R,T;
	Mat R1,R2,P1,P2,Q;
	Mat map1x, map1y, map2x, map2y;
	FileStorage fci("intrinsics.yml",FileStorage::READ);
	fci["M1"]>>CM1;
	fci["M2"]>>CM2;	
	fci["D1"]>>D1;
	fci["D2"]>>D2;
	
	FileStorage fc("extrinsics.yml",FileStorage::READ);
	fc["R"]>>R;
	fc["T"]>>T;
	fc["R1"]>>R1;
	fc["R2"]>>R2;
	fc["P1"]>>P1;
	fc["P2"]>>P2;
	fc["Q"]>>Q;
	VideoCapture cap1(1);
	VideoCapture cap2(2);
	cap1>>img1;
	cap2>>img2;
	Rect roi1,roi2;
	stereoRectify( CM1, D1, CM2, D2, img1.size(), R, T, R1, R2, P1, P2, Q, CALIB_ZERO_DISPARITY, -1, img1.size(), &roi1, &roi2 );
	initUndistortRectifyMap(CM1, D1, R1, P1, img1.size(), CV_32FC1, map1x, map1y);
    initUndistortRectifyMap(CM2, D2, R2, P2, img2.size(), CV_32FC1, map2x, map2y);
	
	int event;
	int sel;
	//cout<<"Enter 1 for BM, 2 for SGBM and 3 for Var \n";
	//cin>>sel;
	//if(sel==1 || sel==2|| sel==3)
	
	for(;;)
	{
		cap2>>img2;//Note: We don't know which is cap1 or cap2...Left can be cap1 or cap2 depending on insertion
		cap1>>img1;
     
		//calib code here__________________________________________
	    remap(img1, imgu1, map1x, map1y, INTER_LINEAR, BORDER_CONSTANT, Scalar());
        remap(img2, imgu2, map2x, map2y, INTER_LINEAR, BORDER_CONSTANT, Scalar());
		static int ROi=3;
		Rect R1(0,ROi,img1.cols,img1.rows-ROi);
		Rect R2(0,0,img1.cols,img1.rows-ROi);
		imgu1=imgu1(R2);
		imgu2=imgu2(R1);
	    //absdiff(imgu1,imgu2,diff);
	    cvtColor(imgu1, g1, CV_BGR2GRAY);
		cvtColor(imgu2, g2, CV_BGR2GRAY);
	
	
	//to find disparity using Semi Global Block Matching (SGBM) algorithm
	//else if(sel==2)
	//namedWindow("Parameters",WINDOW_NORMAL);//WINDOW_NORMAL allows me to set its size
	//for trackbar params_________________
		int disp_number=5;
		int minDisparity=15;
		int SadWindowsize=1;
		int uniqueness=6;
		int speckleWin=100;
		int speckleRange=1;
		int p1=210;
		int p2=860;
		
	    StereoSGBM sbm;
        sbm.SADWindowSize = 2*SadWindowsize+1;//odd no. between 3 and 11
        sbm.numberOfDisparities = 16*disp_number;//multiple of 16
        sbm.preFilterCap = 63;
        sbm.minDisparity = -minDisparity;
        sbm.uniquenessRatio = uniqueness;//percentage, ideally between 5 and 15
        sbm.speckleWindowSize = speckleWin;//Max size of smooth disparity regions to consider their noise speckles. Set to 0 to disable speckle filtering.else set it b/w 50-200 
        sbm.speckleRange = speckleRange;
        sbm.disp12MaxDiff = 1;
        sbm.fullDP = false;//set false for large images
        sbm.P1 = p1;//p2>p1
        sbm.P2 = p2;
        sbm(g1, g2, disp);
    	
	normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
	//binning step____________________________________
	
	resize(imgu1,imgu1,Size(imgu1.cols/2,imgu1.rows/2));
	resize(imgu2,imgu2,Size(imgu2.cols/2,imgu2.rows/2));
	namedWindow("left");
	namedWindow("right");
		
	moveWindow("left",5,5);
	moveWindow("right",340,5);
	//imshow("diff",diff);
	imshow("left", imgu1);
    imshow("right", imgu2);
    imshow("disparity", disp8);
	
	 char c=waitKey(10);
	 if(c=='b' || c=='B')
		 break;
	}

    return 0;
}
