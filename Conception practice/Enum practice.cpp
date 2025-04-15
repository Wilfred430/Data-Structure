#include<iostream>
using namespace std;

enum Base {IDLE,RED,ORANGE,BLUE,PURPLE};
enum BASEII {I = 4,R = 10};

int main()
{
    cout << RED << " " << PURPLE << endl;

    cout << I << " " << R << endl;
    return 0;
}