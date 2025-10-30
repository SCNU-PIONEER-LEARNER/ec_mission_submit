#include<iostream>
using namespace std;
int gcd(int a, int b){
    return b==0?a:gcd(b,a%b);
}
int lcm(int a, int b){
    return a/gcd(a,b)*b;
}
int main(){
    int a,b;
    cout<<"请输入两个正整数：";
    cin>>a>>b;
    if(a<=0||b<=0){
        cout<<"输入错误！"<<endl;
        return 0;
    }
    cout<<a<<"和"<<b<<"的最大公约数是："<<gcd(a,b)<<endl;
    cout<<a<<"和"<<b<<"的最小公倍数是："<<lcm(a,b)<<endl;
    return 0;
}