#include<iostream>
#include <vector>
#include<iterator>
using namespace std;

int main()
{
    vector<int> v;
    for(int i = 1;i<=10;i++)
    {
        v.push_back(i);
    }

    for(vector<int>::iterator it = v.begin();it!=v.end();it++)
    {
        cout << *it << " "; 
    }
    cout << endl;

    return 0;
}