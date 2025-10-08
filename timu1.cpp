 #include <iostream>
using namespace std;

int main(void)
{
    int count=0;
    for(int a=1;a<=4;a++)
    {
        for(int b=1;b<=4;b++)
        {
            for (int c=1;c<=4;c++)
            {
                if((a==b)||(a==c)||(b==c))
                continue;
                count++;
                cout<<a*100+b*10+c<<" ";
            }
        }
    }
    cout<<"共"<<count<<"个"<<endl;
    return 0;
    
}