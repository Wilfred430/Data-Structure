#include <cassert>
using namespace std;

#include "List_statics.h"

List::List() : mysize(0)
{
    for (int i = 0; i < CAPACITY; i++)
    {
        this->myarray[i] = 0;
    }
}

bool List::empty() const
{
    return mysize == 0;
}

void List::display(ostream &out) const
{
    for (int i = 0; i < this->mysize; i++)
        out << this->myarray[i] << " ";
    out << endl;
}

void List::insert(ElementType item, int pos)
{
    if (this->mysize == CAPACITY)
    {
        cerr << "*** No space for list element -- terminating "
                "execution ***\n";
        exit(1);
    }
    if (pos < 0 || pos > this->mysize)
    {
        cerr << "*** Illegal location to insert -- " << pos
             << ". List unchanged. ***\n";
        return;
    }
    // First shift array elements right to make room for item
    for (int i = this->mysize; i > pos; i--)
        this->myarray[i] = this->myarray[i - 1];
    // Now insert item at position pos and increase list size
    this->myarray[pos] = item;
    this->mysize++;
}

void List::erase(int pos)
{
    if (this->mysize == 0)
    {
        cerr << "*** List is empty ***\n";
        return;
    }
    if (pos < 0 || pos >= this->mysize)
    {
        cerr << "Illegal location to delete -- " << pos
             << ". List unchanged. ***\n";
        return;
    }
    for (int i = pos; i < this->mysize; i++)
    {
        this->myarray[i] = this->myarray[i + 1];
    }
    this->mysize--;
}

ostream&operator<<(ostream& out, const List& L)
{
    for(int i=0;i<L.mysize;i++)
    {
        out << L.myarray[i] << " ";
    }
    out << endl;

    return out;
}

//--- Program to test List class.
#include <iostream>
int main()
{
    // Test the class constructor
    List intList;
    cout << "Constructing intList\n";
    // Test empty() and output of empty list
    if (intList.empty())
        cout << "Empty List: \n"
             << intList << endl; // Test output of empty list
    // Test insert()
    for (int i = 0; i < 9; i++)
    {
        cout << "Inserting " << i << " at position " << i / 2 << endl;
        intList.insert(i, i / 2); // -- Insert i at position i/2
        // Test output
        cout << intList << endl;
    }
    cout << "List empty? " << (intList.empty() ? "Yes" : "No") << endl;

    cout << "\nTry to insert at position -1" << endl;
    intList.insert(0, -1);
    cout << "\nTry to insert at position 10" << endl;
    intList.insert(0, 10);
    // Test erase()
    int index;
    cout << endl;
    while (!intList.empty())
    {
        cout << "Give an index of a list element to remove: ";
        cin >> index;
        intList.erase(index);
        cout << intList << endl;
    }
    cout << "List is empty" << endl;
    cout << "\nInserting " << CAPACITY << " integers\n";
    for (int i = 0; i < CAPACITY; i++)
        intList.insert(i, i);
    cout << "Attempting to insert one more integer:\n";
    intList.insert(-1, 0);
    cout << intList << endl;
    return 0;
}