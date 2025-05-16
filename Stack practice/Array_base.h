#include <iostream>
using namespace std;

#ifndef ARRAY_BASE
#define ARRAY_BASE

class Stack
{
private:
    int *Data;
    int Size;

public:
    Stack();
    Stack(const Stack &s);
    ~Stack();
    const Stack &operator=(const Stack &s);
    void Push(const int &val);
    void Pop();
    const void Display();
    const bool Empty();
};

#endif

Stack::Stack() : Data(nullptr), Size(0) {}

Stack::Stack(const Stack &s)
{
    this->Data = new int[s.Size];
    this->Size = s.Size;
    for (int i = 0; i < s.Size; i++)
    {
        this->Data[i] = s.Data[i];
    }
}

Stack::~Stack()
{
    delete [] this->Data;
}

const Stack &Stack::operator=(const Stack &s)
{
    if (this != &s)
    {
        delete[] this->Data;
        this->Size = s.Size;
        this->Data = new int[this->Size];
        for (int i = 0; i < Size; ++i)
        {
            this->Data[i] = s.Data[i];
        }
    }

    return *this;
}

void Stack::Push(const int &val)
{
    int *tmp = new int[this->Size + 1];
    for (int i = 0; i < this->Size; i++)
    {
        tmp[i] = this->Data[i];
    }
    tmp[this->Size] = val;
    delete[] this->Data;
    this->Data = tmp;
    this->Size = this->Size + 1;
}

void Stack::Pop()
{
    if (!this->Empty())
    {
        int *tmp = new int[this->Size - 1];
        for (int i = 0; i < this->Size - 1; i++)
        {
            tmp[i] = this->Data[i];
        }
        delete[] this->Data;
        this->Data = tmp;
        this->Size = this->Size - 1;
    }
    else
    {
        cout << "Sorry, there have no element in Stack.\n";
    }
}

const bool Stack::Empty()
{
    return this->Size == 0;
}

const void Stack::Display()
{
    for(int i=0;i<this->Size;i++)
    {
        cout << this->Data[i] << " ";
    }

    cout << endl;
}