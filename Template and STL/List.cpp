#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l;
    l.push_back(3);
    l.push_front(1);
    l.insert(++l.begin(), 2); // 插入到第二個位置

    for (auto it = l.begin(); it != l.end(); ++it)
        cout << *it << " "; // 1 2 3
    cout << endl;

    l.pop_front();
    l.remove(2);

    for (int x : l)
        cout << x << " "; // 3
    cout << endl;
}