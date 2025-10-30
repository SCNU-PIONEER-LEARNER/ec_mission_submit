#include<iostream>
using namespace std;
int main(void)
{
 int peach=1;
 int day=9;
 for(day;day>=1;day--)
    {
        peach=2*(peach+1);
    }
    cout<<"小猴子第一天摘了"<<peach<<"个桃子"<<endl;
    return 0;
}