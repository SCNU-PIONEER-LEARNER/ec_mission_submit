#include <iostream>
using namespace std;
//ǧ�������ظ�����



int main()
{
	
	
	cout << "��������������ֱ�Ϊ" << endl;
	
	int num = 0;
	for (int a = 1; a < 5; a++)
	{
		for (int b = 1;b<5;b++)
			if (a != b)
			{
				for (int c = 1; c < 5; c++)
				{
					if (c != b && c != a)
					{
						int num1 = a * 100 + b * 10 + c;
						
						cout << num1 << "  ";
						
				    }
					else
					{
						num++
					}
				}
			}
	}
	cout << "�����" << num << "��������ͬ�����ظ����ֵ���λ��" << endl;
	





	system("pause")
		; return 0;
}