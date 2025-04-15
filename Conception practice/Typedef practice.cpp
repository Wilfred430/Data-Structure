#include<iostream>
#include<cmath>
using namespace std;

int main()
{
    typedef int real;
    typedef double complex;

    real first;
    complex second;
    cin >> first >> second;
    cout << first << "+" << abs(second) << endl;

    return 0;
}