
#include<iostream>
#include<boost/thread.hpp>

using namespace std;
//using namespace boost;

void init_thr1(){
    cout<<"in thread 1\n";
}

void init_thr2(int param){
    cout<<"in thread 2 with param="<<param<<"\n";
}

int main(){
   boost::thread t1{init_thr1};
   boost::thread t2{init_thr2,20};

    t1.join();
    t2.join();
    return 0;
}
