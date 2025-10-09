#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    while(b!=0)
    {
        int temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

int lcm(int a,int b)
{
    return (a*b)/gcd(a,b);
}

int main()
{
    int a,b;
    cout <<"请输入两个正整数：";
    cin >> a >> b ;
    int result=lcm(a,b);
    cout <<"这两个正整数的最小公倍数为："<<result ;
    return 0;
}