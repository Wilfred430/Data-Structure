#include <iostream>
#include<iterator>
#include "LinkedList_base.h"
using namespace std;

int main()
{
    Deque<int> q;

    for (int i = 1; i <= 10; i++)
    {
        q.push_back(i);
    }

    for (int i = 2; i <= 10; i++)
    {
        q.push_front(i);
    }

    q.Display();


    for (int i = 1; i <= 5; i++)
    {
        q.pop_back();
    }

    for (int i = 1; i <= 5; i++)
    {
        q.pop_front();
    }

    q.Display();


    return 0;
}