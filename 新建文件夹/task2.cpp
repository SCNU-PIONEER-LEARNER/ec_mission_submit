#include<iostream>
using namespace std;
int day=1;
int num(int d)
{
if(day<=9)
{
  day++;
return num(2*(d+1));
}
else
{
return d;
}
}

int main()
{
  int c=num(1);
  cout<<"第一天共摘了"<<c<<"个桃子";
  return 0;
}