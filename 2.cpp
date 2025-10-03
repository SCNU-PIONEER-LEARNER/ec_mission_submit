#include <iostream>
using namespace std;

int main(void){
   int num=1;

   for(int day=9;day>=1;day--){
    num=(num+1)*2;
   } 
   
   cout<<"小猴子第一天共摘了"<<num<<"个桃子"<<endl;

   return 0;
}