#include <iostream>
using namespace std;
//ǧ��������󹫱���


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
	cout << "������������:" ;
	cin >>a >> b;
	int num1 = func(a, b);
	cout << "���Լ��Ϊ" << num1 << endl;
	int num2 = a * b / func(a, b);
		cout << "��С������Ϊ" << num2 << endl;


system("pause")
		; return 0;
}