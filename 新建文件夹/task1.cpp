#include <iostream>
using namespace std;

int main()
 {
    int num[]={1,2,3,4};

   for(int z=0;z<=3;z++)
   {
    int a=num[z];
    for(int x=0;x<=3;x++)
    {
        int b=num[x];
        for(int n=0;n<=3;n++)
        {
            int c=num[n];
            if(z!=x&&x!=n&&z!=n)
            {
            int d=100*a+10*b+c;
            cout<<d<<"\t";
            }
        }
    }
   }
    
    return 0;
}