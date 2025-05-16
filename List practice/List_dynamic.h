// List_dynamic.h
#ifndef LIST_DYNAMIC_H
#define LIST_DYNAMIC_H

#include <iostream>
using namespace std;

typedef int ElementType; // Adjust based on your needs

class List {
public:
    List(); // Default constructor
    List(int maxSize); // Parameterized constructor
    List(const List &origList); // Copy constructor
    ~List(); // Destructor
    List &operator=(const List &origList); // Assignment operator
    bool empty() const;
    void display(ostream &out) const;
    void insert(ElementType item, int pos);
    void erase(int pos);

private:
    int mySize;
    int myCapacity;
    ElementType *myArrayPtr;
};

ostream &operator<<(ostream &out, const List &aList);

#endif