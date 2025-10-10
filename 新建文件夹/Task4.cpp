#include <vector>
#include <iostream>

using namespace std;

int main(void)
{
    vector<int> numbers;
    int num;
    cout << "请输入数列并以分号结尾" << endl;
    
    while(cin >> num)
    {
        numbers.push_back(num);
    }

    for(int i = numbers.size(); i > 1; )
    {
        int m=0;
        for(int k = 0; k < i - 1; k++) 
        {
            if(numbers[k] > numbers[k+1])
            {
                int temp = numbers[k];
                numbers[k] = numbers[k+1];
                numbers[k+1] = temp;
                m=k+1;
            }
        }
        i=m;
    }
    
    for(int num : numbers)
    {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;  
}