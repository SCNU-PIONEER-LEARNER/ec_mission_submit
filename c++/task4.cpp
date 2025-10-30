#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int arr[7];
    
    cout << "请输入7个整数: ";
    for (int i = 0; i < 7; i++) {
        cin >> arr[i];
    }
    
    sort(arr, arr + 7);
    
    cout << "排序后的数组: ";
    for (int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}