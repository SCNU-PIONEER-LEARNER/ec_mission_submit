//获得数字后用大的除以小的，再判断大小，再用大的除小的
#include <iostream>
using namespace std;

int main(void)
{
    unsigned int a,b;
    cout<<"请输入数字1:"<<endl;
    cin>>a;
    cout<<"请输入数字2:"<<endl;
    cin>>b;

    int gcd;
    for(int i =min(a,b);i>=1;i--)
    {
        if(a%i==0&&b%i==0)
        {
            gcd=i;
            break;
        }
    }

    cout<<"最小公倍数为："<<a/gcd*b<<endl;

    return 0;
}