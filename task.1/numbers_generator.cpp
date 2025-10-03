#include <iostream>
using namespace std;

int main(void)
{
    cout<<"能生成的三位数有:"<<endl;

    int i=0;
    for(int hundreds=1;hundreds<=4;hundreds++)
        {
        for(int tens=1;tens<=4;tens++)
        {
            if(hundreds==tens) 
            {
                continue;
            }
            for(int units=1;units<=4;units++)
            {
                if(units==hundreds || units==tens)
                {
                    continue;
                }
                cout<<hundreds*100+tens*10+units<<" ";
                i++;
            }
        }
        cout<<endl;
    }
    cout<<endl<<"共"<<i<<"种三位数"<<endl;
}