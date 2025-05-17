#include <iostream>
#include <deque>
#include <iterator>
using namespace std;

int main()
{
    deque<int> q;

    for (int i = 1; i <= 10; i++)
    {
        q.push_back(i);
    }

    for (int i = 2; i <= 10; i++)
    {
        q.push_front(i);
    }

    for (deque<int>::iterator it = q.begin(); it != q.end(); it++)
    {
        cout << *it << " ";
    }

    cout << endl;

    for (int i = 1; i <= 5; i++)
    {
        q.pop_back();
    }

    for (int i = 1; i <= 5; i++)
    {
        q.pop_front();
    }

    for (deque<int>::iterator it = q.begin(); it != q.end(); it++)
    {
        cout << *it << " ";
    }

    cout << endl;

    cout << q.max_size() << endl;

    return 0;
}