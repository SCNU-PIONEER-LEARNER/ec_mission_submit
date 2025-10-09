#include  <iostream>
#include  <vector>
using namespace std;

int main()
{
    int count=0;
    vector <int> number;
    for(int i=1;i<=4;i++)
    {
        for(int j=1;j<=4;j++)
        {
            for(int k=1;k<=4;k++)
            {
                if(i!=j && j!=k && k!=i)
                {
                    number.push_back(i*100 +j*10 +k);
                    count++;
                }
            }
        }
    }
    cout <<"一共" << count << endl;
    cout << "三位数为：" <<endl;
    for(int i=0;i<number.size();i++)
    {
        cout<<number[i]<<" ";
    }
    return 0;
}