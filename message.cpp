#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<conio.h>
using namespace std;
bool Delay(int delaytime);
int main6()
{
	int i=10,j=0;

	

	int t=0;
		clock_t clk=clock();
		clk=clk/CLOCKS_PER_SEC;//to get time passed in seconds

	for(;;)
	{
		cout<<"\n\n\n\tDid you really think I'd make it that easy ?\n";
		cout<<"\n\tRegards\n";
		cout<<"\n\tSaransh Kejriwal\n";
		cout<<"\n\n\n\tMessage ends in ";
		int sec=(clock()-clk)/CLOCKS_PER_SEC;
		cout<<10- sec<<" seconds...\n";
		Delay(1);
		system("cls");
		if(sec==10)
		{break;}
	
	}
	
	return 1;
}

bool Delay(int delaytime)
{
	int time1 = time(0);
	int time2 = time(0);
	while(time2-time1 < delaytime )
	{
		time2 = time(0);
	}
	return true ;
}