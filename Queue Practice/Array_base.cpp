#include <iostream>
#include <string>
using namespace std;

template <class T>
class Queue
{
private:
    int datasize;
    T *data;

public:
    Queue() : datasize(0), data(nullptr) {}
    ~Queue() { delete[] this->data; }
    bool empty()
    {
        return this->datasize == 0;
    }
    void Pop()
    {
        if (this->empty())
            return;
        T *tmp = new T[this->datasize - 1];
        for (int i = 0; i < this->datasize - 1; i++)
        {
            tmp[i] = this->data[i + 1];
        }
        delete[] this->data;
        this->datasize--;
        this->data = tmp;
    }
    void Push_back(const T Data)
    {
        T *tmp = new T[this->datasize + 1];
        for (int i = 0; i < this->datasize; i++)
        {
            tmp[i] = this->data[i];
        }
        tmp[datasize] = Data;
        delete[] this->data;
        this->datasize++;
        this->data = tmp;
    }
    void Display()
    {
        for (int i = 0; i < this->datasize; i++)
        {
            cout << this->data[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Queue<int> q;

    string com;
    while (cout << "Please enter the commit : ",cin >> com)
    {
        int D;
        if (com == "0")
            break;
        else if (com == "push")
        {
            cin >> D;
            q.Push_back(D);
        }
        else if (com == "pop")
        {
            q.Pop();
        }
        cout << "Correct Queue : ";
        q.Display();
    }

    return 0;
}