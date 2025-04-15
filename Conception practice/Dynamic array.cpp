#include <iostream>
#include <cstdlib>  // Fix: Added for rand()
#include <ctime>    // Fix: Added for time()
using namespace std;

const int row = 10, column = 5;

int main()
{
    int** Array = new int*[row];
    for (int i = 0; i < row; i++)
    {
        Array[i] = new int[column];
    }

    srand(time(nullptr));  // Fix: Seed rand() for different random numbers each run
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            Array[i][j] = rand() % 1000;
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cout << Array[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < row; i++)  // Fix: Changed column to row
    {
        delete[] Array[i];
    }

    delete[] Array;

    return 0;
}