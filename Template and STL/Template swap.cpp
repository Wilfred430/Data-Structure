#include<iostream>
#include<string>
using namespace std;

template<class T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

int main()
{
    string a="apple",b="banana";
    cout << a << " " << b << endl;
    Swap(a,b);
    cout << a << " " << b << endl;
    long long c=468483465,d=564882;
    cout << c << " " << d << endl;
    Swap(c,d);
    cout << c << " " << d << endl;
    return 0;
}