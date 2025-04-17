#include <iostream>
using namespace std;

struct List
{
    int data;
    int pos;
    List* next;
};

int main()
{
    cout << "Enter the integer array with the zero element at the end :";
    int data;
    int position = 1;
    cin >> data;
    List* head = new List{data,position,nullptr};
    List* node = head;
    while(cin >> data)
    {
        if(data == 0) break;
        position++;
        List* current = new List{data,position,nullptr};
        node->next = current; // head 的下一個設為 current;
        node = current; // 更新 node 為 current
    }
    node = head;
    while(node)
    {
        cout << node->data << " " << node->pos << endl;
        node = node->next;
    }

    while (head) {
        List* temp = head;
        head = head->next;
        delete temp;
    }


    return 0;
}