#include<iostream>
#include<string>
using namespace std;

template<typename T>
void Display(const T arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    char A[] = {'a','D','2'};
    Display(A,3);
    string B[] = {"strnig","apple","/???fafea"};
    Display(B,3);
    return 0;
}