#include<iostream>
#include<opencv2/core/core.hpp>
#include<conio.h>

using namespace cv;
using namespace std;

int main()
	{
		double t;
		t=getTickCount()/getTickFrequency();
		for(;;)
		{
			cout<<getTickCount()/getTickFrequency()-t<<"\n";
		
		
		}
		getch();
		return 1;
	}