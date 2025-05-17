#pragma once
#include <iostream>
using namespace std;

typedef int QueueElement;

class CircularQueue {
private:
    class Node {
    public:
        QueueElement data;
        Node* next;
        Node(QueueElement value, Node* link = nullptr)
            : data(value), next(link) {}
    };
    Node* rear; // 指向尾端節點（rear->next 是 front）
    int count;  // 元素個數

public:
    CircularQueue() : rear(nullptr), count(0) {}
    ~CircularQueue();

    bool empty() const { return rear == nullptr; }
    int size() const { return count; }

    void enqueue(const QueueElement& value);
    void dequeue();
    QueueElement front() const;
    void display(ostream& out = cout) const;
};

// --- Implementation ---

CircularQueue::~CircularQueue() {
    while (!empty()) dequeue();
}

void CircularQueue::enqueue(const QueueElement& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        rear = newNode;
        rear->next = rear; // 指向自己
    } else {
        newNode->next = rear->next; // 指向原 front
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

void CircularQueue::dequeue() {
    if (empty()) {
        cerr << "*** Queue is empty -- can't remove a value ***\n";
        return;
    }
    Node* frontNode = rear->next;
    if (rear == frontNode) { // 只剩一個節點
        delete frontNode;
        rear = nullptr;
    } else {
        rear->next = frontNode->next;
        delete frontNode;
    }
    count--;
}

QueueElement CircularQueue::front() const {
    if (empty()) {
        cerr << "*** Queue is empty -- returning garbage ***\n";
        return QueueElement();
    }
    return rear->next->data;
}

void CircularQueue::display(ostream& out) const {
    if (empty()) {
        out << "(empty)\n";
        return;
    }
    Node* curr = rear->next; // front
    do {
        out << curr->data << " ";
        curr = curr->next;
    } while (curr != rear->next);
    out << endl;
}