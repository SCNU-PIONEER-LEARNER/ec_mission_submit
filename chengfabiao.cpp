#include<iostream>
using namespace std;
int main()
{
    int i,j;
    for(i=9;i>=1;i--)
    {
        for(j=1;j<=i;j++)
        {
            cout<<j<<"*"<<i<<"="<<i*j<<"\t";
          
        }
        cout<<endl;
    }
}