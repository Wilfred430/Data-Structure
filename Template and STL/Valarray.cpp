#include <iostream>
#include <valarray>
using namespace std;

int main() {
    valarray<int> v1 = {1, 2, 3, 4};
    valarray<int> v2 = {10, 20, 30, 40};
    valarray<int> v3 = v1 + v2; // 元素對元素相加

    for (int x : v3)
        cout << x << " "; // 11 22 33 44
    cout << endl;

    cout << v3.sum() << endl; // 110
}