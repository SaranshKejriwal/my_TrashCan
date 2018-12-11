#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/objdetect/objdetect.hpp>//for Cascade Classifiers

using namespace cv;
using namespace std;

vector<Point> kalmanv;//to load coordinates of previous and next points
CascadeClassifier facecascade;

int main () 
{
    Mat img(480, 640, CV_8UC3);
	VideoCapture cap(0);//insert IP
	int i=0;
	facecascade.load("haarcascade_frontalface_alt.xml");
	KalmanFilter KF(4, 2, 0);//4 states= variables, 2 mesurement dimensions
    Mat_<float> state(4, 1); /* (x, y, Vx, Vy) */
    Mat processNoise(4, 1, CV_32F);//to simulate measurement noise, slows process
    Mat_<float> measurement(2,1);
	measurement.setTo(Scalar(0));//measurement matrix initialized to zero
    char code = (char)-1;
	
	namedWindow("Output");
	for(;;)
    {
		cap>>img;
		KF.statePre.at<float>(0) = 5;
		KF.statePre.at<float>(1) = 0;
		KF.statePre.at<float>(2) = 0;
		KF.statePre.at<float>(3) = 0;
		KF.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,0,0,   0,1,0,0,  0,0,1,0,  0,0,0,1);
		
        setIdentity(KF.measurementMatrix);
        setIdentity(KF.processNoiseCov, Scalar::all(1e-4));
        setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));
        setIdentity(KF.errorCovPost, Scalar::all(.1));
		
		kalmanv.clear();
        for(;;)
        {
			cap>>img;
			cvtColor(img,img,CV_BGR2GRAY);

			vector<Rect>faces;
			facecascade.detectMultiScale(img,faces,1.1,2,0|CV_HAAR_SCALE_IMAGE,Size(70,70));//30,30 is max object size
			Point facecenter;
				if(faces.size()>0)
				 {
				 cout<<"\a";
				// cout<<"sound\n";
				 for(i=0;i<faces.size();i++)
					{
						facecenter=Point((faces[i].x+faces[i].width/2),(faces[i].y+faces[i].height/2));
						putText(img,"Face Detected",Point(40,40),FONT_HERSHEY_TRIPLEX,1,Scalar(250,250,250),2);
						rectangle(img,faces[i],Scalar(200,200,250),2,8,0);
						circle(img,facecenter,5,Scalar(255,255,255),3);
					 }
					}
				else
				{
				putText(img,"No Face Detected",Point(40,40),FONT_HERSHEY_TRIPLEX,1,Scalar(250,250,250),2);
				}

            Mat prediction = KF.predict();
            Point predictPt(prediction.at<float>(0),prediction.at<float>(1));
			
			measurement(0) = facecenter.x;
			measurement(1) = facecenter.y;
			
			Point measPt(measurement(0),measurement(1));
			Mat estimated = KF.correct(measurement);
			Point statePt(estimated.at<float>(0),estimated.at<float>(1));
			kalmanv.push_back(statePt);
			
            // plot points
			#define drawCross( center, color, d )                                 \
			line( img, Point( center.x - d, center.y - d ),                \
		Point( center.x + d, center.y + d ), color, 2, CV_AA, 0); \
		line( img, Point( center.x + d, center.y - d ),                \
			Point( center.x - d, center.y + d ), color, 2, CV_AA, 0 )
		       
            drawCross( statePt, Scalar(255,255,255), 5 );
			putText(img,"Target",measPt,FONT_HERSHEY_DUPLEX,0.5,Scalar(250,250,250),1);
            drawCross( measPt, Scalar(0,0,0), 5 );//measPt is controlled by face
//            drawCross( predictPt, Scalar(0,255,0), 3 );
//			line( img, statePt, measPt, Scalar(0,0,255), 3, CV_AA, 0 );
//			line( img, statePt, predictPt, Scalar(0,255,255), 3, CV_AA, 0 );
			
			for (int i = 0; i < kalmanv.size()-1; i++) {
				line(img, kalmanv[i], kalmanv[i+1], Scalar(255,255,255), 2);
			}
			
			
//            randn( processNoise, Scalar(0), Scalar::all(sqrt(KF.processNoiseCov.at<float>(0, 0))));
//            state = KF.transitionMatrix*state + processNoise;
			
            imshow( "Output", img );
            code = (char)waitKey(100);
			
            if( code > 0 )
                break;
        }
        if( code == 27 || code == 'b' || code == 'B' )//breaks when Q is pressed
            break;
    }
	
    return 0;
}
