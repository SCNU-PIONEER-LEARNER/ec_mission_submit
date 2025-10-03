#include <iostream>
using namespace std;
//千行任务排序



int main() 
{
	int arr[7] = { 11,4,5,14,1,919,810 };
	cout << "原数组顺序为：" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << arr[i]<<"  " ;
	}
	cout <<endl;
	
	for (int i = 0; i < 7-1; i++)
	{
		for (int j = 0; j < 7 - i- 1; j++)
		{
			if (arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	
	}
	cout << "排序后数组顺序为：" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;
	 
	system("pause")
		; return 0;
}