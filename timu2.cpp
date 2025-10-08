#include <iostream>
using namespace std;
int main(void)
{
    int peach=1;
    for(int i=1;i<10;i++)
    {
        peach=(peach+1)*2;
    }
    cout<<"小猴子共摘了"<<peach<<"个桃子"<<endl;
}