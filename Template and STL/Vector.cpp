#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> v{14, 1515, 4745, 13143};

    cout << v.size() << " " << v.capacity() << endl;
    cout << *(v.begin()) << " " << *(v.end()) << " " << *(v.end() - 1) << endl;

    for (auto it : v)
    {
        cout << it << " ";
    }

    cout << endl;

    reverse(v.begin(), v.end());

    for (auto it : v)
    {
        cout << it << " ";
    }

    cout << endl;

    return 0;
}