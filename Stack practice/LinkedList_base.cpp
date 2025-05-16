#include <iostream>
#include <algorithm>
#include "LinkedList_base.h"
using namespace std;

int main()
{
    Stack s;

    s.Pop();
    for (int i = 1; i <= 10; i++)
    {
        s.Push(i);
    }

    Stack ss(s);
    ss.Display();
    for (int i = 0; i < 5; i++)
    {
        s.Pop();
    }

    Stack se = s;
    se.Display();

    cout << se.Top() << " " << se.GetSize() << endl;

    return 0;
}