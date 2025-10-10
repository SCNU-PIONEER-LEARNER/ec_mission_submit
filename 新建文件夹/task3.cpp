#include<iostream>
using namespace std;
long long int num(int a, int b)
{
    if(a<0,b<0)
    {
        a=-a;
        b=-b;
    }
    if (a>b)
    {
        if(a%b!=0)
        {  
            return num(b,a%b);
        }
        if(a%b==0)
        {
            return b;
        }
    }
     if (b>a)
    {
        if(b%a!=0)
        {
            
            return num(b,b%a);
        }
        if(b%a==0)
        {
            return b;
        }
    }
    else
    {
        return a;
    }
    return 0;
}
int result ()
{
int e;
cout<<"请输入第一个数"<<endl;
cin>>e;
int f;
cout<<"请输入第二个数"<<endl;
cin>>f;
if(e==0||f==0)
{
    cout<<"false"<<endl;
    return 1;
}
long long int d=num(e,f);
long long int g=(long long )e*f/d;
cout<<e<<"与"<<f<<"的最小公倍数是"<<g<<endl;
return 0;
}
int main ()
{
    return result();
}
