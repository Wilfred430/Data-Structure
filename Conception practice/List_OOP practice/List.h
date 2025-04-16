#include<iostream>
using namespace std;

#ifndef LIST
#define LIST

typedef int ElementType;
const int CAPACITY = 1024;

class List
{
    private:
    ElementType mysize;
    ElementType myarray[CAPACITY];
    public:
    List();
    bool empty() const;
    void insert(ElementType item, int pos);
    void erase(int pos);
    void display(ostream& out) const;
    friend ostream&operator<<(ostream& out,const List& L);
};

#endif
