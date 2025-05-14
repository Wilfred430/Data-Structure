#include<iostream>
using namespace std;

template <class T1,class T2>
void Convert(T1 & a, T2 & b){
    b = static_cast<T2>(a);
}

int main()
{
    char a = 'A';
    int tA;
    Convert(a,tA);
    cout << a << " " << tA << endl;

    return 0;
}