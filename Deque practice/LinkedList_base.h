#pragma once
#include <iostream>
using namespace std;

template <class T>
class Deque
{
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int datasize;

public:
    Deque() : head(nullptr), tail(nullptr), datasize(0) {}
    ~Deque() {
        while (!empty()) pop_front();
    }

    bool empty() const { return datasize == 0; }
    int size() const { return datasize; }

    void push_back(const T& val) {
        Node* node = new Node(val);
        if (empty()) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        datasize++;
    }

    void push_front(const T& val) {
        Node* node = new Node(val);
        if (empty()) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        datasize++;
    }

    void pop_back() {
        if (empty()) return;
        Node* tmp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete tmp;
        datasize--;
    }

    void pop_front() {
        if (empty()) return;
        Node* tmp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete tmp;
        datasize--;
    }

    T& front() {
        if (empty()) throw std::out_of_range("Deque is empty");
        return head->data;
    }

    T& back() {
        if (empty()) throw std::out_of_range("Deque is empty");
        return tail->data;
    }

    void Display() const {
        Node* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};