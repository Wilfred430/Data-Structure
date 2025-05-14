#include <iostream>
#include <cassert>
using namespace std;
#ifndef DSTACKT
#define DSTACKT

#include <iostream>
#include <cassert>

// 先宣告 operator<<
template <typename StackElement>
class Stack;

template <typename StackElement>
std::ostream &operator<<(std::ostream &out, const Stack<StackElement> &st);

template <typename StackElement>
class Stack
{
public:
    Stack(int numElements = 128);
    Stack(const Stack<StackElement> &original);
    ~Stack();
    const Stack<StackElement> &operator=(const Stack<StackElement> &original);
    bool empty() const;
    void push(const StackElement &value);
    void display(std::ostream &out) const;
    StackElement top() const;
    void pop();
private:
    int myCapacity, myTop;
    StackElement *myArray;
};

//====== FUNCTION DEFINITIONS ======
#include <new>

//--- Definition of Stack constructor
template <typename StackElement>
Stack<StackElement>::Stack(int numElements)
{
    assert(numElements > 0);
    myCapacity = numElements;
    myArray = new (std::nothrow) StackElement[myCapacity];
    if (myArray != 0)
        myTop = -1;
    else
    {
        std::cerr << "Inadequate memory to allocate stack \n"
                     " -- terminating execution\n";
        exit(1);
    }
}

//--- Definition of Stack copy constructor
template <typename StackElement>
Stack<StackElement>::Stack(const Stack<StackElement> &original)
    : myCapacity(original.myCapacity), myTop(original.myTop)
{
    myArray = new (std::nothrow) StackElement[myCapacity];
    if (myArray != 0)
        for (int pos = 0; pos <= myTop; pos++)
            myArray[pos] = original.myArray[pos];
    else
    {
        std::cerr << "*Inadequate memory to allocate stack ***\n";
        exit(1);
    }
}

//--- Definition of destructor
template <typename StackElement>
Stack<StackElement>::~Stack()
{
    delete[] myArray;
}

//--- Definition of assignment operator
template <typename StackElement>
const Stack<StackElement> &Stack<StackElement>::operator=(const Stack<StackElement> &original)
{
    if (this != &original)
    {
        delete[] myArray;
        myCapacity = original.myCapacity;
        myTop = original.myTop;
        myArray = new (std::nothrow) StackElement[myCapacity];
        if (myArray != 0)
            for (int pos = 0; pos <= myTop; pos++)
                myArray[pos] = original.myArray[pos];
        else
        {
            std::cerr << "*Inadequate memory to allocate stack ***\n";
            exit(1);
        }
    }
    return *this;
}

//--- Definition of empty()
template <typename StackElement>
inline bool Stack<StackElement>::empty() const
{
    return (myTop == -1);
}

//--- Definition of push()
template <typename StackElement>
inline void Stack<StackElement>::push(const StackElement &value)
{
    if (myTop < myCapacity - 1)
    {
        ++myTop;
        myArray[myTop] = value;
    }
    else
    {
        std::cerr << "*** Stack full -- can't add new value ***\n"
                     "Must increase Stack's capacity\n";
        exit(1);
    }
}

//--- Definition of display()
template <typename StackElement>
inline void Stack<StackElement>::display(std::ostream &out) const
{
    for (int i = myTop; i >= 0; i--)
        out << myArray[i] << std::endl;
}

//--- Definition of operator<<()
template <typename StackElement>
inline std::ostream &operator<<(std::ostream &out, const Stack<StackElement> &st)
{
    st.display(out);
    return out;
}

//--- Definition of top()
template <typename StackElement>
inline StackElement Stack<StackElement>::top() const
{
    if (!empty())
        return (myArray[myTop]);
    else
    {
        std::cerr << "*** Stack is empty -- returning garbage value ***\n";
        return (myArray[myCapacity - 1]);
    }
}

//--- Definition of pop()
template <typename StackElement>
inline void Stack<StackElement>::pop()
{
    if (myTop >= 0)
        myTop--;
    else
        std::cerr << "*** Stack is empty -- can't remove a value ***\n";
}

#endif