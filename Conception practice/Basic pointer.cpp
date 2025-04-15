#include<iostream>
using namespace std;

int main()
{
    int a = 1000;
    int* b = &a;
    int* c = b;

    cout << *b << endl;
    cout << *c << endl;
    a = 243;
    cout << *b << endl;
    cout << *c << endl;

    return 0;
}