#include <iostream>
using namespace std;
//千行任务最大公倍数


int func(int a, int b)
{
	if (b == 0)

		return a;

	else

		return func(b, a % b);

}




int main()
{
	int a,b;
	cout << "请输入两个数:" ;
	cin >>a >> b;
	int num1 = func(a, b);
	cout << "最大公约数为" << num1 << endl;
	int num2 = a * b / func(a, b);
		cout << "最小公倍数为" << num2 << endl;


system("pause")
		; return 0;
}