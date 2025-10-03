#include <iostream>
using namespace std;
//千行任务不重复数字



int main()
{
	
	
	cout << "能组成这样的数分别为" << endl;
	
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
	cout << "能组成" << num << "个互不相同且无重复数字的三位数" << endl;
	





	system("pause")
		; return 0;
}