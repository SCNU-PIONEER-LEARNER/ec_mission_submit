#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<int> numbers;
    int num;
    int temp;
    
    
    while(cin>>num)
    {
        numbers.push_back(num);
    }
    int n=numbers.size();
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(numbers[j]>numbers[j+1])
            {
                temp=numbers[j];
                numbers[j]=numbers[j+1];
                numbers[j+1]=temp;
            }

        }
    }
    
    for(int x= 0; x < numbers.size(); x++){
        cout << numbers[x];
        if(x < numbers.size() - 1){
            cout << ",";
        }
        cout << endl;
    }
    return 0; 
}