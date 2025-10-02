#include<iostream>
using namespace std;

int gcd (int a,int b){
    int c;
    while(b!=0){
       c=b;
       b=a%b;
       a=c; 
    }
    return a;
}

int main(void){
    int a,b;
    cout<<"请输入第一个整数:"<<endl;
    cin>>a;
    cout<<"请输入第二个整数："<<endl;
    cin>>b;
    
    int lcm;
    lcm=(a*b)/gcd(a,b);
    cout<<"两数的最小公倍数是："<<lcm<<endl;




}