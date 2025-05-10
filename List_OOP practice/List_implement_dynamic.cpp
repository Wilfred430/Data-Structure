#include <cassert>
#include <new>
#include <stdexcept>
#include <iostream>
using namespace std;

#include "List_dynamic.h"

//--- Definition of default constructor
List::List(): mySize(0), myCapacity(10) // Default capacity
{
    myArrayPtr = new (nothrow) ElementType[myCapacity];
    if (!myArrayPtr) {
        throw bad_alloc();
    }
}

//--- Definition of parameterized constructor
List::List(int maxSize)
    : mySize(0), myCapacity(maxSize)
{
    if (maxSize <= 0) {
        throw invalid_argument("Capacity must be positive");
    }
    myArrayPtr = new (nothrow) ElementType[maxSize];
    if (!myArrayPtr) {
        throw bad_alloc();
    }
}

//--- Definition of class destructor
List::~List()
{
    delete[] myArrayPtr;
}

//--- Definition of the copy constructor
List::List(const List &origList)
    : mySize(origList.mySize), myCapacity(origList.myCapacity)
{
    myArrayPtr = new (nothrow) ElementType[myCapacity];
    if (!myArrayPtr) {
        throw bad_alloc();
    }
    for (int i = 0; i < mySize; i++) {
        myArrayPtr[i] = origList.myArrayPtr[i];
    }
}

//--- Definition of the assignment operator
List &List::operator=(const List &origList)
{
    if (this != &origList) {
        // Create a temporary array to avoid losing data if allocation fails
        ElementType *newArray = new (nothrow) ElementType[origList.myCapacity];
        if (!newArray) {
            throw bad_alloc();
        }
        for (int i = 0; i < origList.mySize; i++) {
            newArray[i] = origList.myArrayPtr[i];
        }
        // Delete old array and update members
        delete[] myArrayPtr;
        myArrayPtr = newArray;
        mySize = origList.mySize;
        myCapacity = origList.myCapacity;
    }
    return *this;
}

//--- Definition of empty()
bool List::empty() const
{
    return mySize == 0;
}

//--- Definition of display()
void List::display(ostream &out) const
{
    for (int i = 0; i < mySize; i++) {
        out << myArrayPtr[i] << " ";
    }
}

//--- Definition of output operator
ostream &operator<<(ostream &out, const List &aList)
{
    aList.display(out);
    return out;
}

//--- Definition of insert()
void List::insert(ElementType item, int pos)
{
    if (mySize == myCapacity) {
        throw runtime_error("List is full");
    }
    if (pos < 0 || pos > mySize) {
        throw out_of_range("Invalid position");
    }
    for (int i = mySize; i > pos; i--) {
        myArrayPtr[i] = myArrayPtr[i - 1];
    }
    myArrayPtr[pos] = item;
    mySize++;
}

//--- Definition of erase()
void List::erase(int pos)
{
    if (mySize == 0) {
        throw runtime_error("List is empty");
    }
    if (pos < 0 || pos >= mySize) {
        throw out_of_range("Invalid position");
    }
    for (int i = pos; i < mySize - 1; i++) {
        myArrayPtr[i] = myArrayPtr[i + 1];
    }
    mySize--;
}

// Main program
void print(List aList)
{
    cout << aList << endl;
}

int main()
{
    try {
        int listLimit;
        cout << "Enter maximum number of list elements: ";
        cin >> listLimit;
        cout << "\n*** Next Statement: List list1(listLimit);\n";
        List list1(listLimit);
        for (int i = 0; i <= 4; i++) {
            cout << "*** Next Statement: list1.insert(i, i);\n";
            list1.insert(i, i);
        }
        cout << "\n*** Next Statement: List list2 = list1;\n";
        List list2 = list1;
        cout << "\n*** Next Statement: print(list2);\n";
        print(list2);
        cout << "\n*** Next Statement: List list3;\n";
        List list3;
        cout << "\n*** Next Statement: list3 = list2;\n";
        list3 = list2;
        cout << "\n*** Next Statement: print(list3);\n";
        print(list3);
        cout << "\n*** Next Statement: return 0;\n";
    }
    catch (const bad_alloc &e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
        return 1;
    }
    catch (const invalid_argument &e) {
        cerr << "Invalid argument: " << e.what() << endl;
        return 1;
    }
    catch (const runtime_error &e) {
        cerr << "Runtime error: " << e.what() << endl;
        return 1;
    }
    catch (const out_of_range &e) {
        cerr << "Out of range: " << e.what() << endl;
        return 1;
    }
    return 0;
}