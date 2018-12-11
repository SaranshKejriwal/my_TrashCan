#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace cv;
using namespace std;

Mat disp8;//global scope for CallBackFunc
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	 if  ( event == EVENT_LBUTTONDOWN )
     {
          //cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		 cout << "Colour at point (" << x << ", " << y << ") is "<<int(disp8.at<uchar>(Point(x,y)))<<"\n"<< endl;
		 
     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
          cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
		 circle(disp8,Point(x,y),5,Scalar(255),2);
         		  
     }
//imshow("test",img);
}

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
	if(!fci.isOpened())
		{
			cout<<"Error";	//run in Debug
		}	
	fci["M1"]>>CM1;
	fci["M2"]>>CM2;
	cout<<CM1<<"\n\n\n"<<CM2;
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
	VideoCapture cap1(0);
	VideoCapture cap2(1);
	cap1>>img1;//to get img1.size
	cap2>>img2;
	cout<<"\n"<<img1.size();
	Rect roi1,roi2;
	stereoRectify( CM1, D1, CM2, D2, img1.size(), R, T, R1, R2, P1, P2, Q, CALIB_ZERO_DISPARITY, -1, img1.size(), &roi1, &roi2 );
	initUndistortRectifyMap(CM1, D1, R1, P1, img1.size(), CV_32FC1, map1x, map1y);
    initUndistortRectifyMap(CM2, D2, R2, P2, img2.size(), CV_32FC1, map2x, map2y);
	
	int event;
	int sel;
	cout<<"Enter 1 for BM, 2 for SGBM and 3 for Var \n";
	cin>>sel;
	if(sel==1 || sel==2|| sel==3)
	{
	for(;;)
	{
		cap2>>img1;//Note: We don't know which is cap1 or cap2...Left can be cap1 or cap2 depending on insertion
		cap1>>img2;
     
		//calib code here__________________________________________
	    remap(img1, imgu1, map1x, map1y, INTER_LINEAR, BORDER_CONSTANT, Scalar());
        remap(img2, imgu2, map2x, map2y, INTER_LINEAR, BORDER_CONSTANT, Scalar());
		static int ROi=16;
		createTrackbar("ROI_diff","Parameters",&ROi,30);//number of disparities from 0 to 160

		//Rect R1(0,14,img1.cols,img1.rows-14);
		//Rect R2(0,0,img1.cols,img1.rows-14);
		Rect R1(0,0,img1.cols,img1.rows-ROi);
		Rect R2(0,ROi,img1.cols,img1.rows-ROi);
		imgu1=imgu1(R1);
		imgu2=imgu2(R2);
	    absdiff(imgu1,imgu2,diff);
	    cvtColor(imgu1, g1, CV_BGR2GRAY);
		cvtColor(imgu2, g2, CV_BGR2GRAY);
	
	if(sel==1)//to find disparity using Block Matching (BM) algorithm
	{
		namedWindow("Parameters",WINDOW_NORMAL);//WINDOW_NORMAL allows me to set its size
		//for trackbar params_________________
		static int disp_number=2;
		static int minDisparity=15;
		static int SadWindowsize=1;
		static int uniqueness=6;
		static int speckleWin=100;
		static int speckleRange=1;
		static int p1=210;
		static int p2=860;
		
		createTrackbar("Disparities","Parameters",&disp_number,10);//number of disparities from 0 to 160
		createTrackbar("minDisparities","Parameters",&minDisparity,20);//number of disparities from 0 to 160
		createTrackbar("SADWindowSize","Parameters",&SadWindowsize,5);//odd number between 3 and 11
		createTrackbar("Uniqueness","Parameters",&uniqueness,20);//% kept between 5 and 15
		createTrackbar("SpeckleWindow","Parameters",&speckleWin,200);// kept between 50 and 200
		createTrackbar("SpeckleRange","Parameters",&speckleRange,6);//kept around 1 to 2
		createTrackbar("P1","Parameters",&p1,1000);//P2>P1
		createTrackbar("P2","Parameters",&p2,1000);//
	    StereoBM bm;
        bm.state->SADWindowSize = 2*SadWindowsize+1;
        bm.state->numberOfDisparities =  16*disp_number;
        bm.state->preFilterSize = 5;
        bm.state->preFilterCap = 61;
        bm.state->minDisparity = -minDisparity;
        bm.state->textureThreshold = 507;
        bm.state->uniquenessRatio = uniqueness;
        bm.state->speckleWindowSize = speckleWin;
        bm.state->speckleRange = speckleRange;
        bm.state->disp12MaxDiff = 1;
        bm(g1, g2, disp);
       }
	//to find disparity using Semi Global Block Matching (SGBM) algorithm
	else if(sel==2)
	{namedWindow("Parameters",WINDOW_NORMAL);//WINDOW_NORMAL allows me to set its size
	//for trackbar params_________________
		static int disp_number=5;
		static int minDisparity=15;
		static int SadWindowsize=1;
		static int uniqueness=6;
		static int speckleWin=100;
		static int speckleRange=1;
		static int p1=210;
		static int p2=860;
		
		createTrackbar("Disparities","Parameters",&disp_number,10);//number of disparities from 0 to 160
		createTrackbar("minDisparities","Parameters",&minDisparity,20);//number of disparities from 0 to 160
		createTrackbar("SADWindowSize","Parameters",&SadWindowsize,5);//odd number between 3 and 11
		createTrackbar("Uniqueness","Parameters",&uniqueness,20);//% kept between 5 and 15
		createTrackbar("SpeckleWindow","Parameters",&speckleWin,200);// kept between 50 and 200
		createTrackbar("SpeckleRange","Parameters",&speckleRange,6);//kept around 1 to 2
		createTrackbar("P1","Parameters",&p1,1000);//P2>P1
		createTrackbar("P2","Parameters",&p2,1000);//
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
    }
	else if(sel==3)//to find disparity using Var  
	{
		namedWindow("Parameters",WINDOW_NORMAL);//WINDOW_NORMAL allows me to set its size
		//for trackbar params_________________
		static int maxDisp=30;
		static int minDisparity=10;
		static int polysigma=10;
		static int nIT=6;
		static int pyrscale=10;
		static int polyn=1;
		static int fi=50;
		static int lambda=50;
		static int p2=860;
		createTrackbar("maxDisp","Parameters",&maxDisp,100);//number of disparities from 0 to 160
		createTrackbar("minDispr","Parameters",&minDisparity,40);//number of disparities from 0 to 160
		createTrackbar("poly_sigma","Parameters",&polysigma,15);//odd number between 3 and 11
		createTrackbar("Iterations","Parameters",&nIT,15);//% kept between 5 and 15
		createTrackbar("SpeckleWindow","Parameters",&pyrscale,10);// kept between 50 and 200
		createTrackbar("poly_n","Parameters",&polyn,3);//kept around 1 to 2
		createTrackbar("fi","Parameters",&fi,100);//P2>P1
		createTrackbar("P2","Parameters",&p2,1000);//
	StereoVar sv;
	//levels is 1
	
	sv.levels=0;
	sv.pyrScale=pyrscale/10;//<1
	sv.nIt=nIT;
	sv.minDisp=minDisparity;
	sv.poly_n=2*polyn+1;//usually 3,5 or 7
	sv.poly_sigma=polysigma/10;//best poly_sigma is 1.1 at poly_n=5 and 1.5 for poly_n=7
	sv.maxDisp=maxDisp;
	sv.USE_AUTO_PARAMS;
	sv(g1,g2,disp);

	}

	normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
	//normalize(disp8, disp8, 0, 255, CV_MINMAX, CV_8U);
	
	setMouseCallback("disparity", CallBackFunc, NULL);
	resize(imgu1,imgu1,Size(320,240));
	resize(imgu2,imgu2,Size(320,240));
	
	
	moveWindow("disparity",0,245);
	moveWindow("Parameters",640,0);
	moveWindow("left",0,0);
	moveWindow("right",320,0);

	//imshow("diff",diff);
	imshow("disparity", disp8);

	imshow("left", imgu1);
    imshow("right", imgu2);
    
	
	 waitKey(5);
	}
}
    return 0;
}