#include <iostream>
using namespace std;

#ifndef LINKEDLIST_BASE
#define LINKEDLIST_BASE

class Stack
{
private:
    struct Node {
        int data;
        Node* next;
        Node(int val, Node* nxt = nullptr) : data(val), next(nxt) {}
    };
    Node* topNode;
    int Size;

public:
    Stack();
    Stack(const Stack &s);
    ~Stack();
    const Stack &operator=(const Stack &s);
    void Push(const int &val);
    void Pop();
    void Display() const;
    bool Empty() const;
    int Top() const;
    int GetSize() const;
};

#endif

// --- Implementation ---

Stack::Stack() : topNode(nullptr), Size(0) {}

Stack::Stack(const Stack &s) : topNode(nullptr), Size(0)
{
    if (s.topNode == nullptr) return;
    // 複製節點（需維持順序）
    Node* currSrc = s.topNode;
    Node* currDst = nullptr;
    Node* prevDst = nullptr;
    while (currSrc) {
        Node* newNode = new Node(currSrc->data);
        if (!topNode) {
            topNode = newNode;
        } else {
            prevDst->next = newNode;
        }
        prevDst = newNode;
        currSrc = currSrc->next;
    }
    Size = s.Size;
}

Stack::~Stack()
{
    while (!Empty()) {
        Pop();
    }
}

const Stack &Stack::operator=(const Stack &s)
{
    if (this != &s) {
        while (!Empty()) Pop();
        // 複製節點
        Node* currSrc = s.topNode;
        Node* currDst = nullptr;
        Node* prevDst = nullptr;
        while (currSrc) {
            Node* newNode = new Node(currSrc->data);
            if (!topNode) {
                topNode = newNode;
            } else {
                prevDst->next = newNode;
            }
            prevDst = newNode;
            currSrc = currSrc->next;
        }
        Size = s.Size;
    }
    return *this;
}

void Stack::Push(const int &val)
{
    Node* newNode = new Node(val, topNode);
    topNode = newNode;
    Size++;
}

void Stack::Pop()
{
    if (!Empty()) {
        Node* tmp = topNode;
        topNode = topNode->next;
        delete tmp;
        Size--;
    } else {
        cout << "Sorry, there have no element in Stack.\n";
    }
}

bool Stack::Empty() const
{
    return Size == 0;
}

void Stack::Display() const
{
    Node* curr = topNode;
    while (curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int Stack::Top() const
{
    if (!Empty()) {
        return topNode->data;
    } else {
        cout << "Stack is empty.\n";
        return -1; // 或丟出例外
    }
}

int Stack::GetSize() const
{
    return Size;
}