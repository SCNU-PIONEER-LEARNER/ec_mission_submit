#include <iostream>
using namespace std;

int main()
{
    int peaches = 1;
    for(int day=10; day>=1; day--)
    {
        peaches = (peaches + 1) * 2;
    }

    cout<<"第一天桃子的数量为：" << peaches << endl;
}