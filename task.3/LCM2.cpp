#include <iostream>

using namespace std;

int main(void)
{
    int a,b;

    cout<<"请输入第一关个整数a:"<<endl;
    cin>>a;
    cout<<"请输入第二个整数b:"<<endl;
    cin>>b;
    int num1=a*b;

    a=a>b?a:b;
    b=a>b?b:a;
    int temp=0;
    while(b!=0)
    {
        temp=b;
        b=a%b;
        a=temp;
    }
    cout<<"最小公倍数为："<<num1/a<<endl;
    return 0;
    
}