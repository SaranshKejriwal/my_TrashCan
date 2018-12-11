#include <iostream>
#include<string.h>
#include<fstream>

using namespace std;
void binary(int number) {
    int remainder;

	int arr[32];
    for(int m=0; m<32; m++) {
        
        if(number<=1) {
            remainder = number;
             number = number/2;
        }
        else {
            remainder = number%2;
            number = number/2;
        }
        arr[31-m] = remainder;
    }
	    for(int m=0; m<32; m++) {
         cout<<arr[m];   
	    }
}
int main()
{
	
	ofstream outp;//added by me (outp is an identifier)
	outp.open("output1_Saurabh_sir.txt");//added by me
    unsigned int k=1;
   for(int i=1; i<=300; i++)
    {
        for(int j=1; j<=75; j++)
        {
			
            outp<<"abc"<<i<<j<<" for i in 0 to 3 generate"<<"\n\t"<<"first_frame(0)(i+"<<(j-1)*4<<") <= slv_reg";//like cout to a file
			cout<<"abc"<<i<<j<<" for i in 0 to 3 generate"<<"\n\t"<<"first_frame(0)(i+"<<(j-1)*4<<") <= slv_reg";
			
            if(j<=25) {
                cout<<j-1;
            }
            else if(j<=50) {
                cout<<j-26;
            }
            else if(j<=75) {
                cout<<j-51;
            }
            cout<<"(8*i+7 downto 8*i) when slv_reg31=";
            cout<<"\"";
			outp<<"(8*i+7 downto 8*i) when slv_reg31=";//added by me
            outp<<"\"";//added by me (cout:console :: ofstream:file)
            
            binary(k);
            cout<<"\"";
			outp<<"\"";//added by me
            if(j==25 || j==50 || j==75) {
                k++;
            }
            cout<<"\nend generate abc"<<i<<j<<"\n\n";
			outp<<"\nend generate abc"<<i<<j<<"\n\n";//added by me
        }
    }
   
   return 0;
}
