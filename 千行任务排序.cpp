#include <iostream>
using namespace std;
//ǧ����������



int main() 
{
	int arr[7] = { 11,4,5,14,1,919,810 };
	cout << "ԭ����˳��Ϊ��" << endl;
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
	cout << "���������˳��Ϊ��" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;
	 
	system("pause")
		; return 0;
}