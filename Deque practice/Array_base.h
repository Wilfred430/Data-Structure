#pragma once
#include <iostream>
using namespace std;

template <class T>
class Deque
{
private:
    int datasize;
    T *data;

public:
    Deque() : datasize(0), data(nullptr) {}
    ~Deque() { delete[] data; }

    bool empty() const { return datasize == 0; }
    int size() const { return datasize; }

    void push_back(const T &val)
    {
        T *tmp = new T[datasize + 1];
        for (int i = 0; i < datasize; i++)
            tmp[i] = data[i];
        tmp[datasize] = val;
        delete[] data;
        data = tmp;
        datasize++;
    }

    void push_front(const T &val)
    {
        T *tmp = new T[datasize + 1];
        tmp[0] = val;
        for (int i = 0; i < datasize; i++)
            tmp[i + 1] = data[i];
        delete[] data;
        data = tmp;
        datasize++;
    }

    void pop_back()
    {
        if (empty())
            return;
        T *tmp = new T[datasize - 1];
        for (int i = 0; i < datasize - 1; i++)
            tmp[i] = data[i];
        delete[] data;
        data = tmp;
        datasize--;
    }

    void pop_front()
    {
        if (empty())
            return;
        T *tmp = new T[datasize - 1];
        for (int i = 0; i < datasize - 1; i++)
            tmp[i] = data[i + 1];
        delete[] data;
        data = tmp;
        datasize--;
    }

    T &front()
    {
        if (empty())
            throw std::out_of_range("Deque is empty");
        return data[0];
    }

    T &back()
    {
        if (empty())
            throw std::out_of_range("Deque is empty");
        return data[datasize - 1];
    }

    void Display() const
    {
        for (int i = 0; i < datasize; i++)
            cout << data[i] << " ";
        cout << endl;
    }
};