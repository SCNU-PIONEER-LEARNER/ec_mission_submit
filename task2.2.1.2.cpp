#include<iostream>
using namespace std;
int main(void){
    int cnt=1;
    int a=1;
    while(cnt<10){
        a=2*(a+1);
        cnt++;
    }
    cout<<"第一天共摘了"<<a<<"个桃子"<<endl;
}