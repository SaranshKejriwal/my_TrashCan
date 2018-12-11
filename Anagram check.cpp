#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>

using namespace std;

void main()
{
	char a[5];
	char b[5];
	int len1,len2=0;
	//int suma=0; 
	//int sumb=0;
	int i;
	int flag[256]={0};
	cout<<"Enter String 1\t\n";
	cin>>a;
	//cout<<int(a[0]);
	cout<<"Enter String 2\t\n";
	cin>>b;
	len1=strlen(a);
	len2=strlen(b);
	for(i=0;i<len1;i++)
	{
		flag[a[i]]++;
		//cout<<"1st";
		}
	for(i=0;i<len2;i++)
	{
		flag[b[i]]--;
	}
	for(i=0;i<256;i++)
	{
		if(flag[i] !=0)
			break;
	}
	
	if(i==256)
		cout<<"They're anagrams";
	else
		cout<<"They're not anagrams";
	_getch();
}
