#include<iostream>
#include<boost/thread.hpp>
#include<boost/chrono.hpp>
using namespace std;
using namespace boost;

mutex m;

void init_thr1(){
   // cout<<"in thread 1\n";
   for(int i=0;i<7;i++){
       this_thread::sleep_for(boost::chrono::seconds{1});//introduce a delay of 1 second per iteration
       //int thredID=(int)this_thread::get_id();
       cout<<"iteration "<<i<<" by thread "<<this_thread::get_id()<<"\n";
   }
}

/*void init_thr2(int param){
    cout<<"in thread 2 with param="<<param<<"\n";
}*/

int main(){
  thread t1{init_thr1};
  thread t2{init_thr1};

    t1.join();
    t2.join();
    return 0;
}
