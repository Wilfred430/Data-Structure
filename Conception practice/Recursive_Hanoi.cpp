#include <iostream>
#include <iomanip>
using namespace std;

void move(unsigned n, unsigned &moveNumber, char source, char destination, char spare)
{
    if (n == 1)
    {
        moveNumber++;
        cout << setw(3) << moveNumber << " . Move the top disk from " << source << " to " << destination << endl;
    }
    else
    {
        move(n - 1, moveNumber, source, spare, destination);
        move(1, moveNumber, source, destination, spare);
        move(n - 1, moveNumber, spare, destination, source);
    }
}

int main()
{
    const char PEG1 = 'A';
    const char PEG2 = 'B';
    const char PEG3 = 'C';
    unsigned moveNumber = 0;

    cout << "This program solves the Hanoi Towers puzzle.\n";
    cout << "Enter the number of disks: ";
    int numDisks;
    cin >> numDisks;
    cout << endl;

    move(numDisks, moveNumber, PEG1, PEG3, PEG2);

    return 0;
}