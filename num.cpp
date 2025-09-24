#include <vector>
#include <iostream>
using namespace std;

int main(void)
{
    vector<int> numbers;
    int num;
    char ch;
    
    cout << "请输入要排序的整数，以空格隔开，以分号结束。" << endl;
    while (cin >> num) {
        numbers.push_back(num);
        if (cin.peek() == ';') {
            cin.get(); 
            break;
        }
    }
    int k = numbers.size();
    while (k > 1) {
        int m = 0;
        for (int i = 0; i < k - 1; i++) 
        { 
            if (numbers[i] > numbers[i + 1]) {
                int temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                m = i + 1;
            }
        }
        k = m;
    }
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}