#include <iostream>
using namespace std;

int gcd(int a,int b){
    while(b!=0){
        int c=b;
        b=a%b;
        a=c;
    }
    return a;
}

int lcm(int a,int b){
    return a*b/gcd(a,b);
}

int main(void){
    int num1,num2;
    
    cout<<"请输入两个整数:"<<endl;
    cin>>num1>>num2;

    int result=lcm(num1,num2);

    cout<<num1<<"和"<<num2<<"的最小公倍数是"<<result<<endl;

    return 0;
}